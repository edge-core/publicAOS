#include <net-snmp/net-snmp-config.h>

#include <stdio.h>
#include <sys/types.h>
#include <ctype.h>
#include <errno.h>

#if HAVE_STRING_H
#include <string.h>
#else
#include <strings.h>
#endif
#if HAVE_STDLIB_H
#include <stdlib.h>
#endif
#if HAVE_UNISTD_H
#include <unistd.h>
#endif
#if HAVE_SYS_SOCKET_H
#include <sys/socket.h>
#endif
#if HAVE_NETINET_IN_H
#include <netinet/in.h>
#endif

#if HAVE_DMALLOC_H
#include <dmalloc.h>
#endif

#include <net-snmp/types.h>
#include <net-snmp/output_api.h>
#include <net-snmp/config_api.h>

#include <net-snmp/library/snmp_transport.h>
#include <net-snmp/library/snmpIPXDomain.h>

#define SNMP_IPX_DEFAULT_PORT	36879   /*  Specified in RFC 1420.  */
static netsnmp_tdomain ipxDomain;

/*
 * Return a string representing the address in data, or else the "far end"
 * address if data is NULL.  
 */

static char *
netsnmp_ipx_fmtaddr(netsnmp_transport *t, void *data, int len)
{
    struct sockaddr_ipx *to = NULL;

    if (data != NULL && len == sizeof(struct sockaddr_ipx)) {
        to = (struct sockaddr_ipx *) data;
    } else if (t != NULL && t->data != NULL) {
        to = (struct sockaddr_ipx *) t->data;
    }
    if (to == NULL) {
        return strdup("IPX: unknown");
    } else {
        char tmp[64];
        sprintf(tmp, "IPX: %08X:%02X%02X%02X%02X%02X%02X/%hu",
                ntohl(to->sipx_network), to->sipx_node[0],
                to->sipx_node[1], to->sipx_node[2], to->sipx_node[3],
                to->sipx_node[4], to->sipx_node[5], ntohs(to->sipx_port));
        return strdup(tmp);
    }
}



/*
 * You can write something into opaque that will subsequently get passed back 
 * to your send function if you like.  For instance, you might want to
 * remember where a PDU came from, so that you can send a reply there...  
 */

static int
netsnmp_ipx_recv(netsnmp_transport *t, void *buf, int size,
		 void **opaque, int *olength)
{
    int rc = -1, fromlen = sizeof(struct sockaddr);
    struct sockaddr *from;

    if (t != NULL && t->sock >= 0) {
        from = (struct sockaddr *)malloc(sizeof(struct sockaddr_ipx));
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
            char *string = netsnmp_ipx_fmtaddr(NULL, from, fromlen);
            DEBUGMSGTL(("netsnmp_ipx","recvfrom fd %d got %d bytes(from %s)\n",
			t->sock, rc, string));
            free(string);
        } else {
            DEBUGMSGTL(("netsnmp_ipx", "recvfrom fd %d err %d (\"%s\")\n",
                        t->sock, errno, strerror(errno)));
        }
        *opaque = (void *) from;
        *olength = sizeof(struct sockaddr_ipx);
    }
    return rc;
}



static int
netsnmp_ipx_send(netsnmp_transport *t, void *buf, int size,
		 void **opaque, int *olength)
{
    int rc = -1;
    struct sockaddr *to = NULL;

    if (opaque != NULL && *opaque != NULL &&
	*olength == sizeof(struct sockaddr_ipx)) {
        to = (struct sockaddr *) (*opaque);
    } else if (t != NULL && t->data != NULL &&
               t->data_length == sizeof(struct sockaddr_ipx)) {
        to = (struct sockaddr *) (t->data);
    }

    if (to != NULL && t != NULL && t->sock >= 0) {
        char *string = netsnmp_ipx_fmtaddr(NULL, (void *)to,
					sizeof(struct sockaddr_ipx));
        DEBUGMSGTL(("netsnmp_ipx", "send %d bytes from %p to %s on fd %d\n",
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
netsnmp_ipx_close(netsnmp_transport *t)
{
    int rc = -1;
    if (t->sock >= 0) {
#ifndef HAVE_CLOSESOCKET
        rc = close(t->sock);
#else
        rc = closesocket(t->sock);
#endif
        t->sock = -1;
    }
    return rc;
}



/*
 * Open a IPX-based transport for SNMP.  Local is TRUE if addr is the local
 * address to bind to (i.e. this is a server-type session); otherwise addr is 
 * the remote address to send things to.  
 */

netsnmp_transport *
netsnmp_ipx_transport(struct sockaddr_ipx *addr, int local)
{
    netsnmp_transport *t = NULL;
    int             rc = 0;
    char           *string = NULL;

    if (addr == NULL || addr->sipx_family != AF_IPX) {
        return NULL;
    }

    t = (netsnmp_transport *) malloc(sizeof(netsnmp_transport));
    if (t == NULL) {
        return NULL;
    }

    string = netsnmp_ipx_fmtaddr(NULL, (void *)addr, 
				 sizeof(struct sockaddr_ipx));
    DEBUGMSGTL(("netsnmp_ipx", "open %s %s\n", local ? "local" : "remote",
                string));
    free(string);

    memset(t, 0, sizeof(netsnmp_transport));

    t->domain = netsnmpIPXDomain;
    t->domain_length = netsnmpIPXDomain_len;

    t->sock = socket(AF_IPX, SOCK_DGRAM, AF_IPX);
    if (t->sock < 0) {
        netsnmp_transport_free(t);
        return NULL;
    }

    if (local) {
        t->local = malloc(12);
        if (t->local == NULL) {
            netsnmp_transport_free(t);
            return NULL;
        }
        memcpy(&(t->local[00]), (u_char *) & (addr->sipx_network), 4);
        memcpy(&(t->local[04]), (u_char *) & (addr->sipx_node), 6);
        memcpy(&(t->local[10]), (u_char *) & (addr->sipx_port), 2);
        t->local_length = 12;

        /*
         * This session is inteneded as a server, so we must bind on to the
         * given address (which may include a particular network and/or node
         * address, but definitely includes a port number).
         */

        rc = bind(t->sock, (struct sockaddr *) addr,
                  sizeof(struct sockaddr));
        if (rc != 0) {
            netsnmp_ipx_close(t);
            netsnmp_transport_free(t);
            return NULL;
        }
        t->data = NULL;
        t->data_length = 0;
    } else {
        t->remote = malloc(12);
        if (t->remote == NULL) {
            netsnmp_transport_free(t);
            return NULL;
        }
        memcpy(&(t->remote[00]), (u_char *) & (addr->sipx_network), 4);
        memcpy(&(t->remote[04]), (u_char *) & (addr->sipx_node), 6);
        memcpy(&(t->remote[10]), (u_char *) & (addr->sipx_port), 2);
        t->remote_length = 12;

        /*
         * This is a client session.  Save the address in the
         * transport-specific data pointer for later use by snmp_ipx_send.
         */

        t->data = malloc(sizeof(struct sockaddr_ipx));
        if (t->data == NULL) {
            netsnmp_transport_free(t);
            return NULL;
        }
        memcpy(t->data, addr, sizeof(struct sockaddr_ipx));
        t->data_length = sizeof(struct sockaddr_ipx);
    }

    /*
     * Maximum size of an IPX PDU is 576 bytes including a 30-byte header.
     * Ridiculous!  
     */

    t->msgMaxSize = 576 - 30;
    t->f_recv     = netsnmp_ipx_recv;
    t->f_send     = netsnmp_ipx_send;
    t->f_close    = netsnmp_ipx_close;
    t->f_accept   = NULL;
    t->f_fmtaddr  = netsnmp_ipx_fmtaddr;

    return t;
}



/*
 * Attempt to parse a string of the form [%08x]:%12x[/%d] where the parts
 * are the network number, the node address and the port in that order.  
 */

int
netsnmp_sockaddr_ipx(struct sockaddr_ipx *addr, const char *peername)
{
    char           *cp = NULL;
    unsigned int    network = 0, i = 0;

    if (addr == NULL) {
        return 0;
    }
    memset(addr, 0, sizeof(struct sockaddr_ipx));

    DEBUGMSGTL(("netsnmp_sockaddr_ipx", "addr %p, peername \"%s\"\n",
                addr, peername ? peername : "[NIL]"));

    addr->sipx_family = AF_IPX;
    addr->sipx_type = 4;        /*  Specified in RFC 1420.  */

    if (peername == NULL) {
        return 0;
    }

    /*
     * Skip leading white space.  
     */

    while (*peername && isspace((int) *peername)) {
        peername++;
    }

    if (!*peername) {
        /*
         * Completely blank address.  Let this mean "any network, any address,
         * default SNMP port".  
         */
        addr->sipx_network = htonl(0);
        for (i = 0; i < 6; i++) {
            addr->sipx_node[i] = 0;
        }
        addr->sipx_port = htons(SNMP_IPX_DEFAULT_PORT);
        return 1;
    }

    /*
     * Try to get a leading network address.  
     */

    network = strtoul(peername, &cp, 16);
    if (cp != peername) {
        DEBUGMSGTL(("netsnmp_sockaddr_ipx", "network parsed okay\n"));
        addr->sipx_network = htonl(network);
        peername = cp;
    } else {
        DEBUGMSGTL(("netsnmp_sockaddr_ipx",
                    "no network part of address\n"));
        addr->sipx_network = htonl(0);
    }

    if (*peername == ':') {
        /*
         * Okay we are looking for a node number plus optionally a port here.  
         */
        int             node[6] = { 0, 0, 0, 0, 0, 0 }, rc = 0;
        unsigned short  port = 0;
        rc = sscanf(peername, ":%02X%02X%02X%02X%02X%02X/%hu",
                    &node[0], &node[1], &node[2], &node[3], &node[4],
                    &node[5], &port);
        if (rc < 6) {
            DEBUGMSGTL(("netsnmp_sockaddr_ipx",
                        "no node -- fail (rc %d)\n", rc));
            return 0;
        } else if (rc == 6) {
            DEBUGMSGTL(("netsnmp_sockaddr_ipx", "node, no port\n"));
            for (i = 0; i < 6; i++) {
                addr->sipx_node[i] = node[i];
            }
            addr->sipx_port = htons(SNMP_IPX_DEFAULT_PORT);
        } else if (rc == 7) {
            DEBUGMSGTL(("netsnmp_sockaddr_ipx", "node and port\n"));
            for (i = 0; i < 6; i++) {
                addr->sipx_node[i] = node[i];
            }
            addr->sipx_port = htons(port);
        }
    } else if (*peername == '/') {
        /*
         * Okay we are just looking for a port number here.  
         */
        unsigned short  port = 0;
        for (i = 0; i < 6; i++) {
            addr->sipx_node[i] = 0;
        }
        if (sscanf(peername, "/%hu", &port) != 1) {
            DEBUGMSGTL(("netsnmp_sockaddr_ipx", "no port\n"));
            addr->sipx_port = htons(SNMP_IPX_DEFAULT_PORT);
        } else {
            addr->sipx_port = htons(port);
        }
    } else {
        return 0;
    }

    return 1;
}



netsnmp_transport *
netsnmp_ipx_create_tstring(const char *string, int local)
{
    struct sockaddr_ipx addr;

    if (netsnmp_sockaddr_ipx(&addr, string)) {
        return netsnmp_ipx_transport(&addr, local);
    } else {
        return NULL;
    }
}



netsnmp_transport *
netsnmp_ipx_create_ostring(const u_char * o, size_t o_len, int local)
{
    struct sockaddr_ipx addr;

    if (o_len == 12) {
        addr.sipx_family = AF_IPX;
        memcpy((u_char *) & (addr.sipx_network), &(o[00]), 4);
        memcpy((u_char *) & (addr.sipx_node), &(o[04]), 6);
        memcpy((u_char *) & (addr.sipx_port), &(o[10]), 2);
        return netsnmp_ipx_transport(&addr, local);
    }
    return NULL;
}



void
netsnmp_ipx_ctor(void)
{
    ipxDomain.name = netsnmpIPXDomain;
    ipxDomain.name_length = netsnmpIPXDomain_len;
    ipxDomain.prefix = calloc(2, sizeof(char *));
    ipxDomain.prefix[0] = "ipx";

    ipxDomain.f_create_from_tstring = netsnmp_ipx_create_tstring;
    ipxDomain.f_create_from_ostring = netsnmp_ipx_create_ostring;

    netsnmp_tdomain_register(&ipxDomain);
}
