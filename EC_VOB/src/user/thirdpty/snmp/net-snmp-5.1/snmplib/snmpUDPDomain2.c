#include <net-snmp/net-snmp-config.h>
#ifndef VXWORKS
#include <stdio.h>
#include <sys/types.h>
#include <ctype.h>

#if HAVE_STRING_H
#include <string.h>
#else
#include <strings.h>
#endif
#if HAVE_STDLIB_H
#include <stdlib.h>
#endif
#endif /*end of #ifndef VXWORKS*/

#include <errno.h>

#if HAVE_UNISTD_H
#include <unistd.h>
#endif
#if HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#if HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif
#if HAVE_ARPA_INET_H
#include <arpa/inet.h>
#endif
#if HAVE_NETDB_H
#include <netdb.h>
#endif

#if HAVE_DMALLOC_H
#include <dmalloc.h>
#endif

#ifdef VXWORKS
#include "l_inet.h"
#include "snmp_mgr.h"
#include "sys_adpt.h"
#endif

#include <net-snmp/types.h>
#include <net-snmp/output_api.h>
#include <net-snmp/config_api.h>

#include <net-snmp/library/snmp_transport.h>
#include <net-snmp/library/snmpUDPDomain.h>

#ifndef INADDR_NONE
#define INADDR_NONE	-1
#endif

static netsnmp_tdomain udpDomain;
#ifdef VXWORKS
extern int snmp_trap_socket;
static BOOL_T trap_socket_create= FALSE;
static int snmpudpdomain_trap_socket=-1;
#endif
/*
 * Return a string representing the address in data, or else the "far end"
 * address if data is NULL.  
 */

static char *
netsnmp_udp_fmtaddr(netsnmp_transport *t, void *data, int len)
{
    struct sockaddr_in *to = NULL;

    if (data != NULL && len == sizeof(struct sockaddr_in)) {
        to = (struct sockaddr_in *) data;
    } else if (t != NULL && t->data != NULL) {
        to = (struct sockaddr_in *) t->data;
    }
    if (to == NULL) {
        return strdup("UDP: unknown");
    } else {
	char tmp[64];

        /*
         * Here we just print the IP address of the peer for compatibility
         * purposes.  It would be nice if we could include the port number and
         * some indication of the domain (c.f. AAL5PVC).  
         */
        #ifndef VXWORKS
        sprintf(tmp, "%s", inet_ntoa(to->sin_addr));
        #else
        L_INET_Ntoa( to->sin_addr, tmp);
        #endif
        return strdup(tmp);
    }
}



/*
 * You can write something into opaque that will subsequently get passed back 
 * to your send function if you like.  For instance, you might want to
 * remember where a PDU came from, so that you can send a reply there...  
 */

static int
netsnmp_udp_recv(netsnmp_transport *t, void *buf, int size,
		 void **opaque, int *olength)
{
    int             rc = -1;
    socklen_t       fromlen = sizeof(struct sockaddr);
    struct sockaddr *from;

    if (t != NULL && t->sock >= 0) {
        from = (struct sockaddr *) malloc(sizeof(struct sockaddr_in));
        if (from == NULL) {
            *opaque = NULL;
            *olength = 0;
            return -1;
        } else {
            memset(from, 0, fromlen);
        }

	while (rc < 0) {
	    rc = recvfrom(t->sock, buf, size, 0, from, &fromlen);
	    if (rc < 0 && errno != EINTR) {
		break;
	    }
	}

        if (rc >= 0) {
            char *string = netsnmp_udp_fmtaddr(NULL, from, fromlen);
            DEBUGMSGTL(("netsnmp_udp",
			"recvfrom fd %d got %d bytes (from %s)\n",
			t->sock, rc, string));
            free(string);
        } else {
            DEBUGMSGTL(("netsnmp_udp", "recvfrom fd %d err %d (\"%s\")\n",
                        t->sock, errno, strerror(errno)));
        }
        *opaque = (void *)from;
        *olength = sizeof(struct sockaddr_in);
    }
    return rc;
}



static int
netsnmp_udp_send(netsnmp_transport *t, void *buf, int size,
		 void **opaque, int *olength)
{
    int rc = -1;
    struct sockaddr *to = NULL;

    if (opaque != NULL && *opaque != NULL &&
        *olength == sizeof(struct sockaddr_in)) {
        to = (struct sockaddr *) (*opaque);
    } else if (t != NULL && t->data != NULL &&
               t->data_length == sizeof(struct sockaddr_in)) {
        to = (struct sockaddr *) (t->data);
    }

    if (to != NULL && t != NULL && t->sock >= 0) {
        char *string = netsnmp_udp_fmtaddr(NULL, (void *) to,
					sizeof(struct sockaddr_in));
        DEBUGMSGTL(("netsnmp_udp", "send %d bytes from %p to %s on fd %d\n",
                    size, buf, string, t->sock));
        free(string);
	while (rc < 0) {
	    rc = sendto(t->sock, buf, size, 0, to, sizeof(struct sockaddr));
	    if (rc < 0 && errno != EINTR) {
		break;
	    }
	}
    }
    return rc;
}



static int
netsnmp_udp_close(netsnmp_transport *t)
{
    int rc = -1;
    if (t->sock >= 0) {
#ifndef HAVE_CLOSESOCKET
        rc = close(t->sock);
#else
        #ifndef VXWORKS
        rc = closesocket(t->sock);
        #else
        rc = s_close(t->sock);
        trap_socket_create = FALSE;
        #endif
#endif
        t->sock = -1;
    }
    return rc;
}



/*
 * Open a UDP-based transport for SNMP.  Local is TRUE if addr is the local
 * address to bind to (i.e. this is a server-type session); otherwise addr is 
 * the remote address to send things to.  
 */
#if 1
netsnmp_transport *
netsnmp_udp_transport(struct sockaddr_in *addr, int local)
{
    netsnmp_transport *t = NULL;
    int             rc = 0, udpbuf = (1 << 17);
    char           *string = NULL;
    char           *client_socket = NULL;
    
    if (addr == NULL || addr->sin_family != AF_INET) {
        return NULL;
    }

    t = (netsnmp_transport *) malloc(sizeof(netsnmp_transport));
    if (t == NULL) {
        return NULL;
    }

    string = netsnmp_udp_fmtaddr(NULL, (void *)addr, 
				 sizeof(struct sockaddr_in));
    DEBUGMSGTL(("netsnmp_udp", "open %s %s\n", local ? "local" : "remote",
                string));
    free(string);

    memset(t, 0, sizeof(netsnmp_transport));

    t->domain = netsnmpUDPDomain;
    t->domain_length = netsnmpUDPDomain_len;

    t->sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (t->sock < 0) {
        netsnmp_transport_free(t);
        return NULL;
    }
//#ifdef  SO_BSDCOMPAT
    /*
     * Patch for Linux.  Without this, UDP packets that fail get an ICMP
     * response.  Linux turns the failed ICMP response into an error message
     * and return value, unlike all other OS's.  
     */
    {
      //  int             one = 1;
     //   setsockopt(t->sock, SOL_SOCKET, SO_BSDCOMPAT, (void *) &one,
     //              sizeof(one));
    }
//#endif                          /*SO_BSDCOMPAT */
    /*
     * SO_REUSEADDR will allow multiple apps to open the same port at
     * the same time. Only the last one to open the socket will get
     * data. Obviously, for an agent, this is a bad thing. There should
     * only be one listener.
     */
//#ifdef ALLOW_PORT_HIJACKING
//#ifdef  SO_REUSEADDR
    /*
     * Allow the same port to be specified multiple times without failing.
     *    (useful for a listener)
     */
    {
        int             one = 1;
        setsockopt(t->sock, SOL_SOCKET, SO_REUSEADDR, (void *) &one,
                   sizeof(one));
    }
//#endif                          /*SO_REUSEADDR */
//#endif
    /*
     * Try to set the send and receive buffers to a reasonably large value, so
     * that we can send and receive big PDUs (defaults to 8192 bytes (!) on
     * Solaris, for instance).  Don't worry too much about errors -- just
     * plough on regardless.  
     */

//#ifdef  SO_SNDBUF
    if (setsockopt
        (t->sock, SOL_SOCKET, SO_SNDBUF, (void *) &udpbuf,
         sizeof(int)) != 0) {
        DEBUGMSGTL(("netsnmp_udp", "couldn't set SO_SNDBUF to %d bytes: %s\n",
                    udpbuf, strerror(errno)));
    }
//#endif                          /*SO_SNDBUF */

//#ifdef  SO_RCVBUF
    if (setsockopt
        (t->sock, SOL_SOCKET, SO_RCVBUF, (void *) &udpbuf,
         sizeof(int)) != 0) {
        DEBUGMSGTL(("netsnmp_udp", "couldn't set SO_RCVBUF to %d bytes: %s\n",
                    udpbuf, strerror(errno)));
    }
//#endif                          /*SO_RCVBUF */

    if (local) {
        /*
         * This session is inteneded as a server, so we must bind on to the
         * given IP address, which may include an interface address, or could
         * be INADDR_ANY, but certainly includes a port number.
         */

        t->local = malloc(6);
        if (t->local == NULL) {
            netsnmp_transport_free(t);
            return NULL;
        }
        memcpy(t->local, (u_char *) & (addr->sin_addr), 4);
        t->local[4] = (htons(addr->sin_port) & 0xff00) >> 8;
        t->local[5] = (htons(addr->sin_port) & 0x00ff) >> 0;
        t->local_length = 6;

        rc = bind(t->sock, (struct sockaddr *) addr,
                  sizeof(struct sockaddr));
        if (rc != 0) {
            netsnmp_udp_close(t);
            netsnmp_transport_free(t);
            return NULL;
        }
        t->data = NULL;
        t->data_length = 0;
    } else {
        /*
         * This is a client session.  If we've been given a
         * client address to send from, then bind to that.
         * Otherwise the send will use "something sensible".
         */
        client_socket = netsnmp_ds_get_string(NETSNMP_DS_LIBRARY_ID,
                                              NETSNMP_DS_LIB_CLIENT_ADDR);
        
        
       client_socket = 1;
        
        if (client_socket) {
            struct sockaddr_in client_addr;
            netsnmp_sockaddr_in( &client_addr, client_socket, 0);
            client_addr.sin_port = 0;
            bind(t->sock, (struct sockaddr *)&client_addr,
                  sizeof(struct sockaddr));
        }
        
        
        /*
         * Save the (remote) address in the
         * transport-specific data pointer for later use by netsnmp_udp_send.
         */

        t->data = malloc(sizeof(struct sockaddr_in));
        t->remote = malloc(6);
        if (t->data == NULL || t->remote == NULL) {
            netsnmp_transport_free(t);
            return NULL;
        }
        memcpy(t->remote, (u_char *) & (addr->sin_addr), 4);
        t->remote[4] = (htons(addr->sin_port) & 0xff00) >> 8;
        t->remote[5] = (htons(addr->sin_port) & 0x00ff) >> 0;
        t->remote_length = 6;
        memcpy(t->data, addr, sizeof(struct sockaddr_in));
        t->data_length = sizeof(struct sockaddr_in);
    }

    /*
     * 16-bit length field, 8 byte UDP header, 20 byte IPv4 header  
     */

    t->msgMaxSize = 0xffff - 8 - 20;
    t->f_recv     = netsnmp_udp_recv;
    t->f_send     = netsnmp_udp_send;
    t->f_close    = netsnmp_udp_close;
    t->f_accept   = NULL;
    t->f_fmtaddr  = netsnmp_udp_fmtaddr;

    return t;
}

#else


#ifndef VXWORKS
netsnmp_transport *
netsnmp_udp_transport(struct sockaddr_in *addr, int local)
{
    netsnmp_transport *t = NULL;
    int             rc = 0, udpbuf = (1 << 17);
    char           *string = NULL;
    char           *client_socket = NULL;

    if (addr == NULL || addr->sin_family != AF_INET) {
        return NULL;
    }

    t = (netsnmp_transport *) malloc(sizeof(netsnmp_transport));
    if (t == NULL) {
        return NULL;
    }

    string = netsnmp_udp_fmtaddr(NULL, (void *)addr, 
				 sizeof(struct sockaddr_in));
    DEBUGMSGTL(("netsnmp_udp", "open %s %s\n", local ? "local" : "remote",
                string));
    free(string);

    memset(t, 0, sizeof(netsnmp_transport));

    t->domain = netsnmpUDPDomain;
    t->domain_length = netsnmpUDPDomain_len;

    t->sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (t->sock < 0) {
        netsnmp_transport_free(t);
        return NULL;
    }
#ifdef  SO_BSDCOMPAT
    /*
     * Patch for Linux.  Without this, UDP packets that fail get an ICMP
     * response.  Linux turns the failed ICMP response into an error message
     * and return value, unlike all other OS's.  
     */
    {
        int             one = 1;
        setsockopt(t->sock, SOL_SOCKET, SO_BSDCOMPAT, (void *) &one,
                   sizeof(one));
    }
#endif                          /*SO_BSDCOMPAT */
    /*
     * SO_REUSEADDR will allow multiple apps to open the same port at
     * the same time. Only the last one to open the socket will get
     * data. Obviously, for an agent, this is a bad thing. There should
     * only be one listener.
     */
#ifdef ALLOW_PORT_HIJACKING
#ifdef  SO_REUSEADDR
    /*
     * Allow the same port to be specified multiple times without failing.
     *    (useful for a listener)
     */
    {
        int             one = 1;
        setsockopt(t->sock, SOL_SOCKET, SO_REUSEADDR, (void *) &one,
                   sizeof(one));
    }
#endif                          /*SO_REUSEADDR */
#endif
    /*
     * Try to set the send and receive buffers to a reasonably large value, so
     * that we can send and receive big PDUs (defaults to 8192 bytes (!) on
     * Solaris, for instance).  Don't worry too much about errors -- just
     * plough on regardless.  
     */

#ifdef  SO_SNDBUF
    if (setsockopt
        (t->sock, SOL_SOCKET, SO_SNDBUF, (void *) &udpbuf,
         sizeof(int)) != 0) {
        DEBUGMSGTL(("netsnmp_udp", "couldn't set SO_SNDBUF to %d bytes: %s\n",
                    udpbuf, strerror(errno)));
    }
#endif                          /*SO_SNDBUF */

#ifdef  SO_RCVBUF
    if (setsockopt
        (t->sock, SOL_SOCKET, SO_RCVBUF, (void *) &udpbuf,
         sizeof(int)) != 0) {
        DEBUGMSGTL(("netsnmp_udp", "couldn't set SO_RCVBUF to %d bytes: %s\n",
                    udpbuf, strerror(errno)));
    }
#endif                          /*SO_RCVBUF */

    if (local) {
        /*
         * This session is inteneded as a server, so we must bind on to the
         * given IP address, which may include an interface address, or could
         * be INADDR_ANY, but certainly includes a port number.
         */

        t->local = malloc(6);
        if (t->local == NULL) {
            netsnmp_transport_free(t);
            return NULL;
        }
        memcpy(t->local, (u_char *) & (addr->sin_addr.s_addr), 4);
        t->local[4] = (htons(addr->sin_port) & 0xff00) >> 8;
        t->local[5] = (htons(addr->sin_port) & 0x00ff) >> 0;
        t->local_length = 6;

        rc = bind(t->sock, (struct sockaddr *) addr,
                  sizeof(struct sockaddr));
        if (rc != 0) {
            netsnmp_udp_close(t);
            netsnmp_transport_free(t);
            return NULL;
        }
        t->data = NULL;
        t->data_length = 0;
    } else {
        /*
         * This is a client session.  If we've been given a
         * client address to send from, then bind to that.
         * Otherwise the send will use "something sensible".
         */
        client_socket = netsnmp_ds_get_string(NETSNMP_DS_LIBRARY_ID,
                                              NETSNMP_DS_LIB_CLIENT_ADDR);
        if (client_socket) {
            struct sockaddr_in client_addr;
            netsnmp_sockaddr_in( &client_addr, client_socket, 0);
            client_addr.sin_port = 0;
            bind(t->sock, (struct sockaddr *)&client_addr,
                  sizeof(struct sockaddr));
        }
        /*
         * Save the (remote) address in the
         * transport-specific data pointer for later use by netsnmp_udp_send.
         */

        t->data = malloc(sizeof(struct sockaddr_in));
        t->remote = malloc(6);
        if (t->data == NULL || t->remote == NULL) {
            netsnmp_transport_free(t);
            return NULL;
        }
        memcpy(t->remote, (u_char *) & (addr->sin_addr.s_addr), 4);
        t->remote[4] = (htons(addr->sin_port) & 0xff00) >> 8;
        t->remote[5] = (htons(addr->sin_port) & 0x00ff) >> 0;
        t->remote_length = 6;
        memcpy(t->data, addr, sizeof(struct sockaddr_in));
        t->data_length = sizeof(struct sockaddr_in);
    }

    /*
     * 16-bit length field, 8 byte UDP header, 20 byte IPv4 header  
     */

    t->msgMaxSize = 0xffff - 8 - 20;
    t->f_recv     = netsnmp_udp_recv;
    t->f_send     = netsnmp_udp_send;
    t->f_close    = netsnmp_udp_close;
    t->f_accept   = NULL;
    t->f_fmtaddr  = netsnmp_udp_fmtaddr;

    return t;
}

#else
netsnmp_transport *
netsnmp_udp_transport(struct sockaddr_in *addr, int local)
{
   
    netsnmp_transport *t = NULL;
    int             rc = 0, udpbuf = (1 << 17);
 
    int socket_id;

    if (addr == NULL || addr->sin_family != AF_INET)
    {
        return NULL;
    }

  
    t = (netsnmp_transport *) malloc(sizeof(netsnmp_transport));
    if (t == NULL) 
    {
        return NULL;
    }

    memset(t, 0, sizeof(netsnmp_transport));

    t->domain = netsnmpUDPDomain;
    t->domain_length = netsnmpUDPDomain_len;

       SNMP_TASK_Socket_Init();
       SNMP_TASK_Get_Socket_ID(&socket_id);
       t->sock =  socket_id;
   /* kinghong modified to not to create socket here*/
   //    t->sock = socket(AF_INET, SOCK_DGRAM, 0);
 
    
    if (t->sock < 0) 
    {
        netsnmp_transport_free(t);
        return NULL;
    }
    
                      
#ifdef  SO_REUSEADDR
    /*
     * Allow the same port to be specified multiple times without failing.
     *    (useful for a listener)
     */
    {
        int             one = 1;
        setsockopt(t->sock, SOL_SOCKET, SO_REUSEADDR, (void *) &one,
                   sizeof(one));
    }
#endif                          /*SO_REUSEADDR */

    /*
     * Try to set the send and receive buffers to a reasonably large value, so
     * that we can send and receive big PDUs (defaults to 8192 bytes (!) on
     * Solaris, for instance).  Don't worry too much about errors -- just
     * plough on regardless.  
     */

#ifdef  SO_SNDBUF
    if (setsockopt
        (t->sock, SOL_SOCKET, SO_SNDBUF, (void *) &udpbuf,
         sizeof(int)) != 0) 
         {
#if 0       
 DEBUGMSGTL(("netsnmp_udp", "couldn't set SO_SNDBUF to %d bytes: %s\n",
                    udpbuf, strerror(errno)));
#endif
    }
#endif                          /*SO_SNDBUF */

#ifdef  SO_RCVBUF
    if (setsockopt
        (t->sock, SOL_SOCKET, SO_RCVBUF, (void *) &udpbuf,
         sizeof(int)) != 0) {
#if 0
        DEBUGMSGTL(("netsnmp_udp", "couldn't set SO_RCVBUF to %d bytes: %s\n",
                    udpbuf, strerror(errno)));
#endif
    }
#endif                          /*SO_RCVBUF */


    if (local) 
    {
        /*
         * This session is inteneded as a server, so we must bind on to the
         * given IP address, which may include an interface address, or could
         * be INADDR_ANY, but certainly includes a port number.
         */

        t->local = malloc(6);
        if (t->local == NULL) 
        {
            netsnmp_transport_free(t);
            return NULL;
        }
        memcpy(t->local, (u_char *) & (addr->sin_addr), 4);
        t->local[4] = (htons(addr->sin_port) & 0xff00) >> 8;
        t->local[5] = (htons(addr->sin_port) & 0x00ff) >> 0;
        t->local_length = 6;
        
        /* kinghong remove the bind socket, since it is now do in SNMP_TASK
           and suppose it should not be fail
         */ 
        #if 0
        rc = bind(t->sock, (struct sockaddr *) addr,
                  sizeof(struct sockaddr));
        if (rc != 0) {
            netsnmp_udp_close(t);
            netsnmp_transport_free(t);
            return NULL;
        }
        #endif
        
        t->data = NULL;
        t->data_length = 0;
    } else {
        /*
         * This is a client session.  Save the address in the
         * transport-specific data pointer for later use by netsnmp_udp_send.
         */

        t->data = malloc(sizeof(struct sockaddr_in));
        t->remote = malloc(6);
        if (t->data == NULL || t->remote == NULL) {
            netsnmp_transport_free(t);
            return NULL;
        }
        memcpy(t->remote, (u_char *) & (addr->sin_addr), 4);
        t->remote[4] = (htons(addr->sin_port) & 0xff00) >> 8;
        t->remote[5] = (htons(addr->sin_port) & 0x00ff) >> 0;
        t->remote_length = 6;
        memcpy(t->data, addr, sizeof(struct sockaddr_in));
        t->data_length = sizeof(struct sockaddr_in);
    }

    /*
     * 16-bit length field, 8 byte UDP header, 20 byte IPv4 header  
     */

    t->msgMaxSize = 0xffff - 8 - 20;
    t->f_recv     = netsnmp_udp_recv;
    t->f_send     = netsnmp_udp_send;
    t->f_close    = netsnmp_udp_close;
    t->f_accept   = NULL;
    t->f_fmtaddr  = netsnmp_udp_fmtaddr;

    return t;
}
#endif
#endif

/* kinghong add the below*/
netsnmp_transport *
SNMPUDPDOMAIN_netsnmp_udp_transport(struct sockaddr_in *addr, int local)
{
    netsnmp_transport *t = NULL;
    int             rc = 0, udpbuf = (1 << 17);
   // char           *string = NULL;
  

    if (addr == NULL || addr->sin_family != AF_INET) {
        return NULL;
    }

  
    t = (netsnmp_transport *) malloc(sizeof(netsnmp_transport));
    if (t == NULL) {
        return NULL;
    }

    memset(t, 0, sizeof(netsnmp_transport));

    t->domain = netsnmpUDPDomain;
    t->domain_length = netsnmpUDPDomain_len;

       //t->sock = socket(PF_INET, SOCK_DGRAM, 0);
     //  SNMPUDPDOMAIN_CreateTrapSocket();
      t->sock = snmpudpdomain_trap_socket;
    
   // t->sock = TRAP_MGR_GetTrapSocketId();
    if (t->sock < 0) 
    {
        netsnmp_transport_free(t);
        return NULL;
    }    

    if (local) 
    {
        /*
         * This session is inteneded as a server, so we must bind on to the
         * given IP address, which may include an interface address, or could
         * be INADDR_ANY, but certainly includes a port number.
         */

        t->local = malloc(6);
        if (t->local == NULL) 
        {
            netsnmp_transport_free(t);
            return NULL;
        }
        memcpy(t->local, (u_char *) & (addr->sin_addr), 4);
        t->local[4] = (htons(addr->sin_port) & 0xff00) >> 8;
        t->local[5] = (htons(addr->sin_port) & 0x00ff) >> 0;
        t->local_length = 6;
         
  
        rc = bind(t->sock, (struct sockaddr *) addr,
                  sizeof(struct sockaddr));
        if (rc != 0) {
            netsnmp_udp_close(t);
            netsnmp_transport_free(t);
            return NULL;
        }
        t->data = NULL;
        t->data_length = 0;
    } else {
        /*
         * This is a client session.  Save the address in the
         * transport-specific data pointer for later use by netsnmp_udp_send.
         */

        t->data = malloc(sizeof(struct sockaddr_in));
        t->remote = malloc(6);
        if (t->data == NULL || t->remote == NULL) {
            netsnmp_transport_free(t);
            return NULL;
        }
        memcpy(t->remote, (u_char *) & (addr->sin_addr), 4);
        t->remote[4] = (htons(addr->sin_port) & 0xff00) >> 8;
        t->remote[5] = (htons(addr->sin_port) & 0x00ff) >> 0;
        t->remote_length = 6;
        memcpy(t->data, addr, sizeof(struct sockaddr_in));
        t->data_length = sizeof(struct sockaddr_in);
    }

    /*
     * 16-bit length field, 8 byte UDP header, 20 byte IPv4 header  
     */

    t->msgMaxSize = 0xffff - 8 - 20;
    t->f_recv     = netsnmp_udp_recv;
    t->f_send     = netsnmp_udp_send;
    t->f_close    = netsnmp_udp_close;
    t->f_accept   = NULL;
    t->f_fmtaddr  = netsnmp_udp_fmtaddr;

    return t;
}


/* ---------------------------------------------------------------------------
 *  ROUTINE NAME  - SNMPUDPDOMAIN_CreateTrapSocket								
 * ---------------------------------------------------------------------------
 *  FUNCTION: 											      
 *  INPUT	 : None.													      
 *  OUTPUT	 : None.													      
 *  RETURN	 : None.													      
 *  NOTE	 : None.													      
 * ---------------------------------------------------------------------------
 */
void SNMPUDPDOMAIN_CreateTrapSocket(void)
{
  //  SYSLOG_OM_RecordOwnerInfo_T       owner_info;    


    struct sockaddr_in   srvr;
    I32_T rc;
    
    fd_set ready;
    struct timeval timeout;
    
    FD_ZERO(&ready);
	FD_SET(snmpudpdomain_trap_socket, &ready);
    timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	
   
    rc=select(snmpudpdomain_trap_socket+1, &ready, &ready, NULL, &timeout); 
	
    if (rc >= 1)
    {           	    
    	return TRUE;/*socket already open, don't need to open anymore*/
	}
	
    /* BODY */

    if ((snmpudpdomain_trap_socket = socket(AF_INET4, SOCK_DGRAM, 0)) < 0)
    {
        return FALSE;                
    } /* End of if */
    trap_socket_create = TRUE;
    srvr.sin_family = AF_INET4;
    /* need to back here to check if 1039 is correct*/
    srvr.sin_port = htons(162);
    srvr.sin_addr= 0L;
    /* Remove by amytu 3-29-2002 */

    if (bind(snmpudpdomain_trap_socket, (struct sockaddr*)&srvr, sizeof (srvr)) == -1)
    {
        
        return FALSE;

     } /* End of if */   
    return TRUE;
    
} /* end of SNMPUDPDOMAIN_CreateTrapSocket() */
//#endif /*endof #ifndef VXWORKS*/

int
netsnmp_sockaddr_in(struct sockaddr_in *addr,
                    const char *inpeername, int remote_port)
{
    char           *cp = NULL, *peername = NULL;
    #ifdef VXWORKS
      UI32_T         ip_address;
    #endif


    if (addr == NULL) {
        return 0;
    }
    memset(addr, 0, sizeof(struct sockaddr_in));

    DEBUGMSGTL(("netsnmp_sockaddr_in", "addr %p, peername \"%s\"\n",
                addr, inpeername ? inpeername : "[NIL]"));
    #ifndef VXWORKS
    addr->sin_addr.s_addr = htonl(INADDR_ANY);
    #else
    addr->sin_addr = htonl(INADDR_ANY);
    #endif
    addr->sin_family = AF_INET;
    if (remote_port > 0) {
        addr->sin_port = htons(remote_port);
    } else if (netsnmp_ds_get_int(NETSNMP_DS_LIBRARY_ID, 
				  NETSNMP_DS_LIB_DEFAULT_PORT) > 0) {
        addr->sin_port = htons(netsnmp_ds_get_int(NETSNMP_DS_LIBRARY_ID, 
						 NETSNMP_DS_LIB_DEFAULT_PORT));
    } else {
        addr->sin_port = htons(SNMP_PORT);
    }

    if (inpeername != NULL) {
        /*
         * Duplicate the peername because we might want to mank around with
         * it.  
         */

        peername = strdup(inpeername);
        if (peername == NULL) {
            return 0;
        }

        /*
         * Try and extract an appended port number.  
         */
        cp = strchr(peername, ':');
        if (cp != NULL) {
            *cp = '\0';
            cp++;
            if (atoi(cp) != 0) {
                DEBUGMSGTL(("netsnmp_sockaddr_in",
                            "port number suffix :%d\n", atoi(cp)));
                addr->sin_port = htons(atoi(cp));
            }
        }

        for (cp = peername; *cp && isdigit((int) *cp); cp++);
        #ifdef VXWORKS
            L_INET_Aton(peername, &ip_address);
       #endif
        if (!*cp && atoi(peername) != 0) {
            /*
             * Okay, it looks like just a port number.  
             */
            DEBUGMSGTL(("netsnmp_sockaddr_in", "totally numeric: %d\n",
                        atoi(peername)));
            addr->sin_port = htons(atoi(peername));
        #ifdef VXWORKS
        } else if (ip_address != INADDR_NONE) {
        #else
        } else if (inet_addr(peername) != INADDR_NONE) {
        #endif
            /*
             * It looks like an IP address.  
             */
            DEBUGMSGTL(("netsnmp_sockaddr_in", "IP address\n"));
            #ifndef VXWORKS
            addr->sin_addr.s_addr = inet_addr(peername);
            #else
            addr->sin_addr = ip_address;
            #endif
        } else {
            /*
             * Well, it must be a hostname then.  
             */
#ifndef VXWORKS
#ifdef  HAVE_GETHOSTBYNAME
            struct hostent *hp = gethostbyname(peername);
            if (hp == NULL) {
                DEBUGMSGTL(("netsnmp_sockaddr_in",
                            "hostname (couldn't resolve)\n"));
                free(peername);
                return 0;
            } else {
                if (hp->h_addrtype != AF_INET) {
                    DEBUGMSGTL(("netsnmp_sockaddr_in",
                                "hostname (not AF_INET!)\n"));
                    free(peername);
                    return 0;
                } else {
                    DEBUGMSGTL(("netsnmp_sockaddr_in",
                                "hostname (resolved okay)\n"));
                    memcpy(&(addr->sin_addr), hp->h_addr, hp->h_length);
                }
            }
#else                           /*HAVE_GETHOSTBYNAME */
            DEBUGMSGTL(("netsnmp_sockaddr_in",
                        "hostname (no gethostbyname)\n"));
            free(peername);
            return 0;
#endif                          /*HAVE_GETHOSTBYNAME */
#endif /*end of #ifndef VXWORKS*/
        }
    } else {
        DEBUGMSGTL(("netsnmp_sockaddr_in", "NULL peername"));
        return 0;
    }
    #ifndef VXWORKS
    DEBUGMSGTL(("netsnmp_sockaddr_in", "return { AF_INET, %s:%hu }\n",
                inet_ntoa(addr->sin_addr), ntohs(addr->sin_port)));
    #endif
    free(peername);
    return 1;
}



/*
 * The following functions provide the "com2sec" configuration token
 * functionality for compatibility.  
 */

#define EXAMPLE_NETWORK		"NETWORK"
#define EXAMPLE_COMMUNITY	"COMMUNITY"

#ifndef VXWORKS
typedef struct _com2SecEntry {
    char            community[VACMSTRINGLEN];
    unsigned long   network;
    unsigned long   mask;
    char            secName[VACMSTRINGLEN];
    struct _com2SecEntry *next;
} com2SecEntry;
#endif
com2SecEntry   *com2SecList = NULL, *com2SecListLast = NULL;

#ifndef VXWORKS
void
netsnmp_udp_parse_security(const char *token, char *param)
{
    char           *secName = NULL, *community = NULL, *source = NULL;
    char           *cp = NULL;
    const char     *strmask = NULL;
    com2SecEntry   *e = NULL;
    unsigned long   network = 0, mask = 0;

    /*
     * Get security, source address/netmask and community strings.  
     */

    secName = strtok(param, "\t\n ");
    if (secName == NULL) {
        config_perror("missing NAME parameter");
        return;
    } else if (strlen(secName) > (VACMSTRINGLEN - 1)) {
        config_perror("security name too long");
        return;
    }
    source = strtok(NULL, "\t\n ");
    if (source == NULL) {
        config_perror("missing SOURCE parameter");
        return;
    } else if (strncmp(source, EXAMPLE_NETWORK, strlen(EXAMPLE_NETWORK)) ==
               0) {
        config_perror("example config NETWORK not properly configured");
        return;
    }
    community = strtok(NULL, "\t\n ");
    if (community == NULL) {
        config_perror("missing COMMUNITY parameter\n");
        return;
    } else
        if (strncmp
            (community, EXAMPLE_COMMUNITY, strlen(EXAMPLE_COMMUNITY))
            == 0) {
        config_perror("example config COMMUNITY not properly configured");
        return;
    } else if (strlen(community) > (VACMSTRINGLEN - 1)) {
        config_perror("community name too long");
        return;
    }

    /*
     * Process the source address/netmask string.  
     */

    cp = strchr(source, '/');
    if (cp != NULL) {
        /*
         * Mask given.  
         */
        *cp = '\0';
        strmask = cp + 1;
    }

    /*
     * Deal with the network part first.  
     */

    if ((strcmp(source, "default") == 0)
        || (strcmp(source, "0.0.0.0") == 0)) {
        network = 0;
        strmask = "0.0.0.0";
    } else {
        /*
         * Try interpreting as a dotted quad.  
         */
        #ifdef VXWORKS
        L_INET_Aton(source, &network);
        #else
        network = inet_addr(source);
        #endif

        if (network == (unsigned long) -1) {
            /*
             * Nope, wasn't a dotted quad.  Must be a hostname.  
             */
#ifdef  HAVE_GETHOSTBYNAME
            struct hostent *hp = gethostbyname(source);
            if (hp == NULL) {
                config_perror("bad source address");
                return;
            } else {
                if (hp->h_addrtype != AF_INET) {
                    config_perror("no IP address for source hostname");
                    return;
                }
                network = *((unsigned long *) hp->h_addr);
            }
#else                           /*HAVE_GETHOSTBYNAME */
            /*
             * Oh dear.  
             */
            config_perror("cannot resolve source hostname");
            return;
#endif                          /*HAVE_GETHOSTBYNAME */
        }
    }

    /*
     * Now work out the mask.  
     */

    if (strmask == NULL || *strmask == '\0') {
        /*
         * No mask was given.  Use 255.255.255.255.  
         */
        mask = 0xffffffffL;
    } else {
        if (strchr(strmask, '.')) {
            /*
             * Try to interpret mask as a dotted quad.  
             */
            #ifdef VXWORKS
            L_INET_Aton(strmask, &mask);
            #else
            mask = inet_addr(strmask);
            #endif
            if (mask == (unsigned long) -1 &&
                strncmp(strmask, "255.255.255.255", 15) != 0) {
                config_perror("bad mask");
                return;
            }
        } else {
            /*
             * Try to interpret mask as a "number of 1 bits".  
             */
            int             maskLen = atoi(strmask), maskBit = 0x80000000L;
            if (maskLen <= 0 || maskLen > 32) {
                config_perror("bad mask length");
                return;
            }
            while (maskLen--) {
                mask |= maskBit;
                maskBit >>= 1;
            }
            mask = htonl(mask);
        }
    }

    /*
     * Check that the network and mask are consistent.  
     */

    if (network & ~mask) {
        config_perror("source/mask mismatch");
        return;
    }

    e = (com2SecEntry *) malloc(sizeof(com2SecEntry));
    if (e == NULL) {
        config_perror("memory error");
        return;
    }

    /*
     * Everything is okay.  Copy the parameters to the structure allocated
     * above and add it to END of the list.  
     */

    DEBUGMSGTL(("netsnmp_udp_parse_security",
                "<\"%s\", 0x%08x/0x%08x> => \"%s\"\n", community, network,
                mask, secName));

    strcpy(e->secName, secName);
    strcpy(e->community, community);
    e->network = network;
    e->mask = mask;
    e->next = NULL;

    if (com2SecListLast != NULL) {
        com2SecListLast->next = e;
        com2SecListLast = e;
    } else {
        com2SecListLast = com2SecList = e;
    }
}
#else

UI32_T 
netsnmp_udp_parse_security(const char *token, char *param, int access_right)
{
    char           *secName = NULL, *community = NULL, *source = NULL;
    char           *cp = NULL;
    const char     *strmask = NULL;
    com2SecEntry   *e = NULL;
    unsigned long   network = 0, mask = 0;
    
    /* kinghong added for limited control*/
    UI32_T  comm_counter;

    /*
     * Get security, source address/netmask and community strings.  
     */
    SNMP_MGR_GetSnmpCommCounter(& comm_counter);
    
   
    /*kinghong added*/
    if (comm_counter >= SYS_ADPT_MAX_NBR_OF_SNMP_COMMUNITY_STRING)
        {
     
        return SNMP_MGR_ERROR_EXCEED_LIMIT;
       }
    
    secName = strtok(param, "\t\n ");
    if (secName == NULL) {
        config_perror("missing NAME parameter");
        /*kinghong modified   //return; */ 

        return  SNMP_MGR_ERROR_PARAMETER_NOT_MATCH;
    } else if (strlen(secName) > (VACMSTRINGLEN - 1)) {
        config_perror("security name too long");
      
        return  SNMP_MGR_ERROR_PARAMETER_NOT_MATCH;
    }
    source = strtok(NULL, "\t\n ");
    if (source == NULL) {
        config_perror("missing SOURCE parameter");
        /*kinghong modified   //return; */ 
    
        return  SNMP_MGR_ERROR_PARAMETER_NOT_MATCH;
    } else if (strncmp(source, EXAMPLE_NETWORK, strlen(EXAMPLE_NETWORK)) ==
               0) {
      
        config_perror("example config NETWORK not properly configured");
        /*kinghong modified   //return; */ 
        return  SNMP_MGR_ERROR_PARAMETER_NOT_MATCH;
    }
    community = strtok(NULL, "\t\n ");
    if (community == NULL) {
        config_perror("missing COMMUNITY parameter\n");
         /*kinghong modified   //return; */ 
       
        return  SNMP_MGR_ERROR_PARAMETER_NOT_MATCH;
    } 
   /* our mercury platform have no EXAMPLE_COMMUNITY and no restrict to it, kinghong*/
   #if 0
    else if (strncmp
            (community, EXAMPLE_COMMUNITY, strlen(EXAMPLE_COMMUNITY))
            == 0) 
            {
        config_perror("example config COMMUNITY not properly configured");
        /*kinghong modified   //return; */ 
       
        return  SNMP_MGR_ERROR_PARAMETER_NOT_MATCH;
    
    }
     #endif 
     else if (strlen(community) > (VACMSTRINGLEN - 1)) {
        config_perror("community name too long");
         /*kinghong modified   //return; */ 
        
        return  SNMP_MGR_ERROR_PARAMETER_NOT_MATCH;
    }

    /*
     * Process the source address/netmask string.  
     */

    cp = strchr(source, '/');
    if (cp != NULL) {
        /*
         * Mask given.  
         */
        *cp = '\0';
        strmask = cp + 1;
    }

    /*
     * Deal with the network part first.  
     */

    if ((strcmp(source, "default") == 0)
        || (strcmp(source, "0.0.0.0") == 0)) {
        network = 0;
        strmask = "0.0.0.0";
    } else {
        /*
         * Try interpreting as a dotted quad.  
         */
   
        L_INET_Aton(source, &network);
      //  network = inet_addr(source);

     
    }

    /*
     * Now work out the mask.  
     */

    if (strmask == NULL || *strmask == '\0') {
        /*
         * No mask was given.  Use 255.255.255.255.  
         */
        mask = 0xffffffffL;
    } else {
        if (strchr(strmask, '.')) {
            /*
             * Try to interpret mask as a dotted quad.  
             */
            L_INET_Aton(strmask, &mask);
            //mask = inet_addr(strmask);
            if (mask == (unsigned long) -1 &&
                strncmp(strmask, "255.255.255.255", 15) != 0) {
                config_perror("bad mask");
                 /*kinghong modified   //return; */ 

        return  SNMP_MGR_ERROR_PARAMETER_NOT_MATCH;
            }
        } else {
            /*
             * Try to interpret mask as a "number of 1 bits".  
             */
            int             maskLen = atoi(strmask), maskBit = 0x80000000L;
            if (maskLen <= 0 || maskLen > 32) {
                config_perror("bad mask length");
                /*kinghong modified   //return; */ 
               return  SNMP_MGR_ERROR_PARAMETER_NOT_MATCH;
            }
            while (maskLen--) {
                mask |= maskBit;
                maskBit >>= 1;
            }
            mask = htonl(mask);
        }
    }

    /*
     * Check that the network and mask are consistent.  
     */

    if (network & ~mask) {
        config_perror("source/mask mismatch");
         /*kinghong modified   //return; */ 
   
        return  SNMP_MGR_ERROR_PARAMETER_NOT_MATCH;
    }

    e = (com2SecEntry *) malloc(sizeof(com2SecEntry));
    if (e == NULL) {
        config_perror("memory error");
        /*kinghong modified   //return; */ 
   
        return  SNMP_MGR_ERROR_MEM_ALLOC_FAIL;
    }
    else
    {
       SNMP_MGR_AdjustCommCounter(TRUE);
    }

    /*
     * Everything is okay.  Copy the parameters to the structure allocated
     * above and add it to END of the list.  
     */

    DEBUGMSGTL(("netsnmp_udp_parse_security",
                "<\"%s\", 0x%08x/0x%08x> => \"%s\"\n", community, network,
                mask, secName));

    strcpy(e->secName, secName);
    strcpy(e->community, community);
    e->network = network;
    e->mask = mask;
    e->next = NULL;
    e->access_right = access_right;

    if (com2SecListLast != NULL) 
    {
        com2SecListLast->next = e;
        com2SecListLast = e;
    } else
     {
        com2SecListLast = com2SecList = e;
    }
    /* kinghong added*/

    return SNMP_MGR_ERROR_OK;
}

#endif



void
netsnmp_udp_com2SecList_free(void)
{
    com2SecEntry   *e = com2SecList;
    while (e != NULL) {
        com2SecEntry   *tmp = e;
        e = e->next;
        free(tmp);
    }
    com2SecList = com2SecListLast = NULL;
}


void
netsnmp_udp_agent_config_tokens_register(void)
{
    register_app_config_handler("com2sec", netsnmp_udp_parse_security,
                                netsnmp_udp_com2SecList_free,
                                "name IPv4-network-address[/netmask] community");
}



/*
 * Return 0 if there are no com2sec entries, or return 1 if there ARE com2sec 
 * entries.  On return, if a com2sec entry matched the passed parameters,
 * then *secName points at the appropriate security name, or is NULL if the
 * parameters did not match any com2sec entry.  
 */

int
netsnmp_udp_getSecName(void *opaque, int olength,
                       const char *community,
                       size_t community_len, char **secName)
{
    com2SecEntry   *c;
    struct sockaddr_in *from = (struct sockaddr_in *) opaque;
    char           *ztcommunity = NULL;

    /*
     * Special case if there are NO entries (as opposed to no MATCHING
     * entries).  
     */

    if (com2SecList == NULL) {
        DEBUGMSGTL(("netsnmp_udp_getSecName", "no com2sec entries\n"));
        if (secName != NULL) {
            *secName = NULL;
        }
        return 0;
    }

    /*
     * If there is no IPv4 source address, then there can be no valid security
     * name.  
     */

    if (opaque == NULL || olength != sizeof(struct sockaddr_in) ||
        from->sin_family != AF_INET) {
        DEBUGMSGTL(("netsnmp_udp_getSecName",
		    "no IPv4 source address in PDU?\n"));
        if (secName != NULL) {
            *secName = NULL;
        }
        return 1;
    }

    DEBUGIF("netsnmp_udp_getSecName") {
	ztcommunity = (char *)malloc(community_len + 1);
	if (ztcommunity != NULL) {
	    memcpy(ztcommunity, community, community_len);
	    ztcommunity[community_len] = '\0';
	}
    #ifndef VXWORKS
	DEBUGMSGTL(("netsnmp_udp_getSecName", "resolve <\"%s\", 0x%08x>\n",
		    ztcommunity ? ztcommunity : "<malloc error>",
		    from->sin_addr.s_addr));
    #endif
    }

    for (c = com2SecList; c != NULL; c = c->next) {
        DEBUGMSGTL(("netsnmp_udp_getSecName","compare <\"%s\", 0x%08x/0x%08x>",
		    c->community, c->network, c->mask));
        if ((community_len == strlen(c->community)) &&
	    (memcmp(community, c->community, community_len) == 0) &&
	    #ifndef VXWORKS
            ((from->sin_addr.s_addr & c->mask) == c->network)) {
        #else
            ((from->sin_addr & c->mask) == c->network)) {
        #endif
            DEBUGMSG(("netsnmp_udp_getSecName", "... SUCCESS\n"));
            if (secName != NULL) {
                *secName = c->secName;
            }
            break;
        }
        DEBUGMSG(("netsnmp_udp_getSecName", "... nope\n"));
    }
    if (ztcommunity != NULL) {
        free(ztcommunity);
    }
    return 1;
}



netsnmp_transport *
netsnmp_udp_create_tstring(const char *string, int local)
{
    struct sockaddr_in addr;

    if (netsnmp_sockaddr_in(&addr, string, 0)) {
        return netsnmp_udp_transport(&addr, local);
    } else {
        return NULL;
    }
}


netsnmp_transport *
netsnmp_udp_create_ostring(const u_char * o, size_t o_len, int local)
{
    struct sockaddr_in addr;

    if (o_len == 6) {
        addr.sin_family = AF_INET;
        #ifndef VXWORKS
        memcpy((u_char *) & (addr.sin_addr.s_addr), o, 4);
        #else
        memcpy((u_char *) & (addr.sin_addr), o, 4);
        #endif
        addr.sin_port = ntohs((o[4] << 8) + o[5]);
        return netsnmp_udp_transport(&addr, local);
    }
    return NULL;
}

#ifdef VXWORKS
/* kinghong add the below*/
netsnmp_transport *
SNMPUDPDOMAIN_netsnmp_udp_create_ostring(const u_char * o, size_t o_len, int local)
{
    struct sockaddr_in addr;

    if (o_len == 6) {
        addr.sin_family = AF_INET;
        memcpy((u_char *) & (addr.sin_addr), o, 4);
        addr.sin_port = ntohs((o[4] << 8) + o[5]);
      return SNMPUDPDOMAIN_netsnmp_udp_transport(&addr, local);     
    }
    return NULL;
}
#endif
void
netsnmp_udp_ctor(void)
{
    udpDomain.name = netsnmpUDPDomain;
    udpDomain.name_length = netsnmpUDPDomain_len;
    udpDomain.prefix = calloc(2, sizeof(char *));
    udpDomain.prefix[0] = "udp";

    udpDomain.f_create_from_tstring = netsnmp_udp_create_tstring;
    udpDomain.f_create_from_ostring = netsnmp_udp_create_ostring;

    netsnmp_tdomain_register(&udpDomain);
}



#ifdef VXWORKS
/* kinghong add the following API*/


struct _com2SecEntry *
netsnmp_udp_get_com2SecList(void)
{
    return com2SecList;
}



struct _com2SecEntry *
netsnmp_udp_getCom2SecEntry(const char *secName)
{
    struct _com2SecEntry *cp;
    char            securityName[VACMSTRINGLEN];
    int               slen;

    slen = (int) strlen(secName);
    if (slen < 0 || slen >= VACMSTRINGLEN)
        return NULL;
   
    strcpy(securityName ,  secName);
   
    for (cp = com2SecList; cp; cp = cp->next) 
    {
        if (strcmp( cp->community, securityName) == 0)
            return cp;
    }
    return NULL;
}



void
netsnmp_udp_destroyViewEntry(const char *comm)
{
      struct _com2SecEntry  *cp, *lastcp = NULL;

  
    if (com2SecList && !strcmp(com2SecList->community, comm))
        {
        cp = com2SecList;
        com2SecList = com2SecList->next;
        
        /* kinghong patched to set the com2SecListLast to Null if com2SecList is empty*/
        
        if (!com2SecList)
        {
         com2SecListLast = NULL;
        }
        
       } else 
       {
        for (cp = com2SecList; cp; cp = cp->next) 
        {
            if (!strcmp(cp->community, comm))
                break;
            lastcp = cp;
        }
        if (!cp)
            {
            return;
            }
        if (!cp->next)
            com2SecListLast = lastcp;
        lastcp->next = cp->next;
    }
    free(cp);
    /* kinghong added */
    SNMP_MGR_AdjustCommCounter(0);
    return;
}
#endif