/*
 * Author: Tatu Ylonen <ylo@cs.hut.fi>
 * Copyright (c) 1995 Tatu Ylonen <ylo@cs.hut.fi>, Espoo, Finland
 *                    All rights reserved
 * This file contains code implementing the packet protocol and communication
 * with the other side.  This same code is used both on client and server side.
 *
 * As far as I am concerned, the code I have written for this software
 * can be used freely for any purpose.  Any derived versions of this
 * software must be clearly marked as such, and if the derived work is
 * incompatible with the protocol description in the RFC file, it must be
 * called by a name other than "ssh" or "Secure Shell".
 *
 *
 * SSH2 packet format added by Markus Friedl.
 * Copyright (c) 2000, 2001 Markus Friedl.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "includes.h"
#include "sshd_vm.h"
#include "openssl/rand.h"
#include <stdarg.h>
RCSID("$OpenBSD: packet.c,v 1.102 2002/12/10 19:47:14 markus Exp $");

#if 0 /* squid, does not need for linux platform */
#include "iproute.h"
#endif

#include "xmalloc.h"
#include "buffer.h"
#include "packet.h"
#include "bufaux.h"
#include "crc32.h"
#include "getput.h"

#include "compress.h"
#include "deattack.h"
#include "channels.h"

#include "compat.h"
#include "ssh1.h"
#include "ssh2.h"

#include "cipher.h"
#include "kex.h"
#include "mac.h"
#include "log.h"
#include "canohost.h"
#include "misc.h"
#include "ssh.h"

int close(int fd);
extern int errno;
extern int vsprintf(char *str, const char *format, va_list ap);

#ifdef PACKET_DEBUG
#define DBG(x) x
#else
#define DBG(x)
#endif

/*
 * This variable contains the file descriptors used for communicating with
 * the other side.  connection_in is used for reading; connection_out for
 * writing.  These can be the same descriptor, in which case it is assumed to
 * be a socket.
 */
//static int connection_in = -1;/*isiah.*/
//static int connection_out = -1;

/* Protocol flags for the remote side. */
//static u_int remote_protocol_flags = 0;/*isiah*/

/* Encryption context for receiving data.  This is only used for decryption. */
//static CipherContext receive_context;/*isiah*/

/* Encryption context for sending data.  This is only used for encryption. */
//static CipherContext send_context;/*isiah*/

/* Buffer for raw input data from the socket. */
//Buffer input;/*isiah*/

/* Buffer for raw output data going to the socket. */
//Buffer output;/*isiah*/

/* Buffer for the partial outgoing packet being constructed. */
//static Buffer outgoing_packet;/*isiah*/

/* Buffer for the incoming packet currently being processed. */
//static Buffer incoming_packet;/*isiah*/

/* Scratch buffer for packet compression/decompression. */
static Buffer compression_buffer;
static int compression_buffer_ready = 0;

/* Flag indicating whether packet compression/decompression is enabled. */
static int packet_compression = 0;

/* default maximum packet size */
//int max_packet_size = 32768; /*isiah*/

/* Flag indicating whether this module has been initialized. */
//static int initialized = 0;

/* Set to true if the connection is interactive. */
//static int interactive_mode = 0; /*isiah*/

/* Session key information for Encryption and MAC */
//Newkeys *newkeys[MODE_MAX];/*isiah*/
//static u_int32_t read_seqnr = 0; /*isiah*/
//static u_int32_t send_seqnr = 0; /*isiah*/

/* Session key for protocol v1 */
/*static u_char ssh1_key[SSH_SESSION_KEY_LENGTH];
static u_int ssh1_keylen;*//*isiah*/

/* roundup current message to extra_pad bytes */
static u_char extra_pad = 0;

/*
 * Sets the descriptors used for communication.  Disables encryption until
 * packet_set_encryption_key is called.
 */
void
packet_set_connection(int fd_in, int fd_out)
{
	Cipher *none = cipher_by_name("none");
    CipherContext *receive_context;/*isiah*/
    CipherContext *send_context;/*isiah*/
    Buffer *input;/*isiah*/
    Buffer *output;/*isiah*/
    Buffer *outgoing_packet;/*isiah*/
    Buffer *incoming_packet;/*isiah*/
    Newkeys **newkeys;/*isiah*/

	if (none == NULL)
		fatal("packet_set_connection: cannot load cipher 'none'");
/*	connection_in = fd_in;
	connection_out = fd_out;*/
	SSHD_VM_SetSshConnectionSockId(fd_in, fd_out);
	SSHD_VM_GetSshSendContext(&send_context);
	SSHD_VM_GetSshReceiveContext(&receive_context);
/*	cipher_init(&send_context, none, "", 0, NULL, 0, CIPHER_ENCRYPT);
	cipher_init(&receive_context, none, "", 0, NULL, 0, CIPHER_DECRYPT);*/
	cipher_init(send_context, none, (const char *)"", 0, NULL, 0, CIPHER_ENCRYPT);
	cipher_init(receive_context, none, (const char *)"", 0, NULL, 0, CIPHER_DECRYPT);
	SSHD_VM_GetSshNewKey(&newkeys);
	newkeys[MODE_IN] = newkeys[MODE_OUT] = NULL;
/*	if (!initialized) {
		initialized = 1;
		buffer_init(&input);
		buffer_init(&output);
		buffer_init(&outgoing_packet);
		buffer_init(&incoming_packet);
	}*//*isiah*/
    SSHD_VM_GetSshInputBuffer(&input);
    SSHD_VM_GetSshOutputBuffer(&output);
    SSHD_VM_GetSshOutgoingPacketBuffer(&outgoing_packet);
    SSHD_VM_GetSshIncomingPacketBuffer(&incoming_packet);
    buffer_init(input);
    buffer_init(output);
    buffer_init(outgoing_packet);
    buffer_init(incoming_packet);

	/* Kludge: arrange the close function to be called from fatal(). */
	fatal_add_cleanup((void (*) (void *)) packet_close, NULL);
}

/* Returns 1 if remote host is connected via socket, 0 if not. */

int
packet_connection_is_on_socket(void)
{
    return 1;/*isiah*/
#if 0
	struct sockaddr_storage from, to;
	socklen_t fromlen, tolen;

	/* filedescriptors in and out are the same, so it's a socket */
	if (connection_in == connection_out)
		return 1;
	fromlen = sizeof(from);
	memset(&from, 0, sizeof(from));
	if (getpeername(connection_in, (struct sockaddr *)&from, &fromlen) < 0)
		return 0;
	tolen = sizeof(to);
	memset(&to, 0, sizeof(to));
	if (getpeername(connection_out, (struct sockaddr *)&to, &tolen) < 0)
		return 0;
	if (fromlen != tolen || memcmp(&from, &to, fromlen) != 0)
		return 0;
	if (from.ss_family != AF_INET && from.ss_family != AF_INET6)
		return 0;
	return 1;
#endif
}

/*
 * Exports an IV from the CipherContext required to export the key
 * state back from the unprivileged child to the privileged parent
 * process.
 */

void
packet_get_keyiv(int mode, u_char *iv, u_int len)
{
	CipherContext *cc;
    CipherContext *receive_context;/*isiah*/
    CipherContext *send_context;/*isiah*/

	if (mode == MODE_OUT)
	{
	    SSHD_VM_GetSshSendContext(&send_context);/*isiah*/
		cc = send_context;
	}
	else
	{
	    SSHD_VM_GetSshReceiveContext(&receive_context);/*isiah*/
		cc = receive_context;
	}

	cipher_get_keyiv(cc, iv, len);
}

int
packet_get_keycontext(int mode, u_char *dat)
{
	CipherContext *cc;
    CipherContext *receive_context;/*isiah*/
    CipherContext *send_context;/*isiah*/

	if (mode == MODE_OUT)
	{
	    SSHD_VM_GetSshSendContext(&send_context);/*isiah*/
		cc = send_context;
	}
	else
	{
	    SSHD_VM_GetSshReceiveContext(&receive_context);/*isiah*/
		cc = receive_context;
	}

	return (cipher_get_keycontext(cc, dat));
}

void
packet_set_keycontext(int mode, u_char *dat)
{
	CipherContext *cc;
    CipherContext *receive_context;/*isiah*/
    CipherContext *send_context;/*isiah*/

	if (mode == MODE_OUT)
	{
	    SSHD_VM_GetSshSendContext(&send_context);/*isiah*/
		cc = send_context;
	}
	else
	{
	    SSHD_VM_GetSshReceiveContext(&receive_context);/*isiah*/
		cc = receive_context;
	}

	cipher_set_keycontext(cc, dat);
}

int
packet_get_keyiv_len(int mode)
{
	CipherContext *cc;
    CipherContext *receive_context;/*isiah*/
    CipherContext *send_context;/*isiah*/

	if (mode == MODE_OUT)
	{
	    SSHD_VM_GetSshSendContext(&send_context);/*isiah*/
		cc = send_context;
	}
	else
	{
	    SSHD_VM_GetSshReceiveContext(&receive_context);/*isiah*/
		cc = receive_context;
	}

	return (cipher_get_keyiv_len(cc));
}
void
packet_set_iv(int mode, u_char *dat)
{
	CipherContext *cc;
    CipherContext *receive_context;/*isiah*/
    CipherContext *send_context;/*isiah*/

	if (mode == MODE_OUT)
	{
	    SSHD_VM_GetSshSendContext(&send_context);/*isiah*/
		cc = send_context;
	}
	else
	{
	    SSHD_VM_GetSshReceiveContext(&receive_context);/*isiah*/
		cc = receive_context;
	}

	cipher_set_keyiv(cc, dat);
}
#if 0
int
packet_get_ssh1_cipher()
{
    CipherContext *receive_context;/*isiah*/
	return (cipher_get_number(receive_context->cipher));
}
#endif	


u_int32_t
packet_get_seqnr(int mode)
{
    u_int32_t read_seqnr; /*isiah*/
    u_int32_t send_seqnr; /*isiah*/

    SSHD_VM_GetSshReadSequenceNumber(&read_seqnr);
    SSHD_VM_GetSshSendSequenceNumber(&send_seqnr);
	return (mode == MODE_IN ? read_seqnr : send_seqnr);
}

void
packet_set_seqnr(int mode, u_int32_t seqnr)
{
	if (mode == MODE_IN)
//		read_seqnr = seqnr; /*isiah*/
        SSHD_VM_SetSshReadSequenceNumber(seqnr);
	else if (mode == MODE_OUT)
//		send_seqnr = seqnr; /*isiah*/
        SSHD_VM_SetSshSendSequenceNumber(seqnr);
	else
		fatal("packet_set_seqnr: bad mode %d", mode);
}

/* returns 1 if connection is via ipv4 */

int
packet_connection_is_ipv4(void)
{
    return 1;
#if 0
	struct sockaddr_storage to;
	socklen_t tolen = sizeof(to);

	memset(&to, 0, sizeof(to));
	if (getsockname(connection_out, (struct sockaddr *)&to, &tolen) < 0)
		return 0;
	if (to.ss_family != AF_INET)
		return 0;
	return 1;
#endif
}

/* Sets the connection into non-blocking mode. */

void
packet_set_nonblocking(void)
{
    /*isiah. rewrite packet_set_nonblocking() */
//    int on = 1;
    I32_T connection_in;
    I32_T connection_out;

    SSHD_VM_GetSshConnectionSockId(&connection_in, &connection_out);
//    s_ioctl(connection_in, SIOCNBIO, &on, sizeof(int));
    if( connection_out != connection_in )
    {
//        s_ioctl(connection_out, SIOCNBIO, &on, sizeof(int));
    }
#if 0
	/* Set the socket into non-blocking mode. */
	if (fcntl(connection_in, F_SETFL, O_NONBLOCK) < 0)
	    ;
//		error("fcntl O_NONBLOCK: %.100s", strerror(errno));

	if (connection_out != connection_in) {
		if (fcntl(connection_out, F_SETFL, O_NONBLOCK) < 0)
		    ;
//			error("fcntl O_NONBLOCK: %.100s", strerror(errno));
	}
#endif
}

/* Returns the socket used for reading. */

int
packet_get_connection_in(void)
{
    I32_T connection_in;/*isiah.*/
    I32_T connection_out;/*isiah.*/

    SSHD_VM_GetSshConnectionSockId(&connection_in, &connection_out);
	return connection_in;
}

/* Returns the descriptor used for writing. */

int
packet_get_connection_out(void)
{
    I32_T connection_in;/*isiah.*/
    I32_T connection_out;/*isiah.*/

    SSHD_VM_GetSshConnectionSockId(&connection_in, &connection_out);
	return connection_out;
}

/* Closes the connection and clears and frees internal data structures. */

void
packet_close(void)
{
    I32_T connection_in;/*isiah.*/
    I32_T connection_out;/*isiah.*/
    Buffer *input;/*isiah*/
    Buffer *output;/*isiah*/
    Buffer *outgoing_packet;/*isiah*/
    Buffer *incoming_packet;/*isiah*/
    CipherContext *receive_context;/*isiah*/
    CipherContext *send_context;/*isiah*/
/*isiah.2003-07-21*/
    UI32_T  fdin, fdout, fderr;

    SSHD_VM_GetSshConnectionSockId(&connection_in, &connection_out);
/*	if (!initialized)
		return;
	initialized = 0;*//*isiah*/
/*isiah.2003-05-22*/
    if( (connection_in > 0) || (connection_out > 0) )
    {
	    if (connection_in == connection_out)
	    {
		    shutdown(connection_out, SHUT_RDWR);
		    s_close(connection_out);
		    connection_in = connection_out = -1;
	    }
	    else
	    {
		    s_close(connection_in);
		    s_close(connection_out);
		    connection_in = connection_out = -1;
	    }
	    SSHD_VM_SetSshConnectionSockId(connection_in, connection_out);
	}

    SSHD_VM_GetSshInputBuffer(&input);
    SSHD_VM_GetSshOutputBuffer(&output);
    SSHD_VM_GetSshOutgoingPacketBuffer(&outgoing_packet);
    SSHD_VM_GetSshIncomingPacketBuffer(&incoming_packet);
	buffer_free(input);
	buffer_free(output);
	buffer_free(outgoing_packet);
	buffer_free(incoming_packet);

	if (compression_buffer_ready) {
		buffer_free(&compression_buffer);
		buffer_compress_uninit();
	}

    SSHD_VM_GetSshSendContext(&send_context);/*isiah*/
    SSHD_VM_GetSshReceiveContext(&receive_context);/*isiah*/
	cipher_cleanup(send_context);
	cipher_cleanup(receive_context);

/*isiah.2003-07-21*/
	SSHD_VM_GetSshStdioDescriptor((I32_T *)&fdin, (I32_T *)&fdout, (I32_T *)&fderr);
	if( fdin == fdout )
	{
	    if( fdin > 0 )
	    {
	        s_close(fdin);
	        fdin = fdout = fderr = -1;
	        SSHD_VM_SetSshStdioDescriptor(fdin, fdout, fderr);
	        return;
	    }
	    else
	    {
	        return;
	    }
	}
	if( fdin > 0 )
	{
	    s_close(fdin);
        fdin = fderr = -1;
        SSHD_VM_SetSshStdioDescriptor(fdin, fdout, fderr);
	}
	if( fdout > 0 )
	{
	    s_close(fdout);
        fdout = fderr = -1;
        SSHD_VM_SetSshStdioDescriptor(fdin, fdout, fderr);
	}
}

/* Sets remote side protocol flags. */

void
packet_set_protocol_flags(u_int protocol_flags)
{
    SSHD_VM_SetSshRemoteProtocolFlags(protocol_flags);
/*	remote_protocol_flags = protocol_flags;*//*isiah*/
}

/* Returns the remote protocol flags set earlier by the above function. */

u_int
packet_get_protocol_flags(void)
{
    u_int remote_protocol_flags = 0;/*isiah*/
    UI32_T  temp;

    SSHD_VM_GetSshRemoteProtocolFlags(&temp);
    remote_protocol_flags = (u_int)temp;
	return remote_protocol_flags;
}

/*
 * Starts packet compression from the next packet on in both directions.
 * Level is compression level 1 (fastest) - 9 (slow, best) as in gzip.
 */

static void
packet_init_compression(void)
{
	if (compression_buffer_ready == 1)
		return;
	compression_buffer_ready = 1;
	buffer_init(&compression_buffer);
}

void
packet_start_compression(int level)
{
	I32_T compat20;/*isiah*/

    SSHD_VM_GetSshCompat20(&compat20);
	if (packet_compression && !compat20)
		fatal("Compression already enabled.");
	packet_compression = 1;
	packet_init_compression();
	buffer_compress_init_send(level);
	buffer_compress_init_recv();
}

/*
 * Causes any further packets to be encrypted using the given key.  The same
 * key is used for both sending and reception.  However, both directions are
 * encrypted independently of each other.
 */

void
packet_set_encryption_key(const char *key, u_int keylen,
    int number)
{
	Cipher *cipher = cipher_by_number(number);
    CipherContext *receive_context;/*isiah*/
    CipherContext *send_context;/*isiah*/

	if (cipher == NULL)
		fatal("packet_set_encryption_key: unknown cipher number %d", number);
	if (keylen < 20)
		fatal("packet_set_encryption_key: keylen too small: %d", keylen);
	if (keylen > SSH_SESSION_KEY_LENGTH)
		fatal("packet_set_encryption_key: keylen too big: %d", keylen);
/*	memcpy(ssh1_key, key, keylen);
	ssh1_keylen = keylen;*//*isiah*/
//	SSHD_VM_SetSshv1SessionKey(key, keylen);

	SSHD_VM_GetSshSendContext(&send_context);
	SSHD_VM_GetSshReceiveContext(&receive_context);
	cipher_init(send_context, cipher, key, keylen, NULL, 0, CIPHER_ENCRYPT);
	cipher_init(receive_context, cipher, key, keylen, NULL, 0, CIPHER_DECRYPT);
}

#if 0
u_int
packet_get_encryption_key(u_char *key)
{
	if (key == NULL)
		return (ssh1_keylen);
	memcpy(key, ssh1_key, ssh1_keylen);
	return (ssh1_keylen);
}
#endif

/* Start constructing a packet to send. */
void
packet_start(u_char type)
{
	u_char buf[9];
	int len;
    Buffer *outgoing_packet;/*isiah*/
    Buffer *incoming_packet;/*isiah*/
	I32_T compat20;/*isiah*/

	DBG(debug("packet_start[%d]", type));
    SSHD_VM_GetSshCompat20(&compat20);
	len = compat20 ? 6 : 9;
	memset(buf, 0, len - 1);
	buf[len - 1] = type;
    SSHD_VM_GetSshOutgoingPacketBuffer(&outgoing_packet);
    SSHD_VM_GetSshIncomingPacketBuffer(&incoming_packet);
	buffer_clear(outgoing_packet);
	buffer_append(outgoing_packet, buf, len);
}

/* Append payload. */
void
packet_put_char(int value)
{
	char ch = value;
    Buffer *outgoing_packet;/*isiah*/

    SSHD_VM_GetSshOutgoingPacketBuffer(&outgoing_packet);
	buffer_append(outgoing_packet, &ch, 1);
}
void
packet_put_int(u_int value)
{
    Buffer *outgoing_packet;/*isiah*/

    SSHD_VM_GetSshOutgoingPacketBuffer(&outgoing_packet);
	buffer_put_int(outgoing_packet, value);
}
void
packet_put_string(const void *buf, u_int len)
{
    Buffer *outgoing_packet;/*isiah*/

    SSHD_VM_GetSshOutgoingPacketBuffer(&outgoing_packet);
	buffer_put_string(outgoing_packet, buf, len);
}
void
packet_put_cstring(const char *str)
{
    Buffer *outgoing_packet;/*isiah*/

    SSHD_VM_GetSshOutgoingPacketBuffer(&outgoing_packet);
	buffer_put_cstring(outgoing_packet, str);
}
void
packet_put_raw(const void *buf, u_int len)
{
    Buffer *outgoing_packet;/*isiah*/

    SSHD_VM_GetSshOutgoingPacketBuffer(&outgoing_packet);
	buffer_append(outgoing_packet, buf, len);
}
void
packet_put_bignum(BIGNUM * value)
{
    Buffer *outgoing_packet;/*isiah*/

    SSHD_VM_GetSshOutgoingPacketBuffer(&outgoing_packet);
	buffer_put_bignum(outgoing_packet, value);
}
void
packet_put_bignum2(BIGNUM * value)
{
    Buffer *outgoing_packet;/*isiah*/

    SSHD_VM_GetSshOutgoingPacketBuffer(&outgoing_packet);
	buffer_put_bignum2(outgoing_packet, value);
}

/*
 * Finalizes and sends the packet.  If the encryption key has been set,
 * encrypts the packet before sending.
 */

static void
packet_send1(void)
{
	u_char buf[8], *cp;
	int /*i,*/ padding, len;
	u_int checksum;
//	u_int32_t rand = 0;
    Buffer *outgoing_packet;/*isiah*/
    CipherContext *send_context;/*isiah*/
    Buffer *output;/*isiah*/

    SSHD_VM_GetSshOutgoingPacketBuffer(&outgoing_packet);
	SSHD_VM_GetSshSendContext(&send_context);
    SSHD_VM_GetSshOutputBuffer(&output);
	/*
	 * If using packet compression, compress the payload of the outgoing
	 * packet.
	 */
	if (packet_compression) {
		buffer_clear(&compression_buffer);
		/* Skip padding. */
		buffer_consume(outgoing_packet, 8);
		/* padding */
		buffer_append(&compression_buffer, "\0\0\0\0\0\0\0\0", 8);
		buffer_compress(outgoing_packet, &compression_buffer);
		buffer_clear(outgoing_packet);
		buffer_append(outgoing_packet, buffer_ptr(&compression_buffer),
		    buffer_len(&compression_buffer));
	}
	/* Compute packet length without padding (add checksum, remove padding). */
	len = buffer_len(outgoing_packet) + 4 - 8;

	/* Insert padding. Initialized to zero in packet_start1() */
	padding = 8 - len % 8;
	if (!(send_context->plaintext)) {
		cp = buffer_ptr(outgoing_packet);
/*isiah.2003-04-11*/
/*		for (i = 0; i < padding; i++) {
			if (i % 4 == 0)
				rand = arc4random();
			cp[7 - i] = rand & 0xff;
			rand >>= 8;
		}*/
		RAND_bytes(cp, padding);
	}
	buffer_consume(outgoing_packet, 8 - padding);

	/* Add check bytes. */
	checksum = ssh_crc32(buffer_ptr(outgoing_packet),
	    buffer_len(outgoing_packet));
	PUT_32BIT(buf, checksum);
	buffer_append(outgoing_packet, buf, 4);

#ifdef PACKET_DEBUG
	fprintf(stderr, "packet_send plain: ");
	buffer_dump(outgoing_packet);
#endif

	/* Append to output. */
	PUT_32BIT(buf, len);
	buffer_append(output, buf, 4);
	cp = buffer_append_space(output, buffer_len(outgoing_packet));
	cipher_crypt(send_context, cp, buffer_ptr(outgoing_packet),
	    buffer_len(outgoing_packet));

#ifdef PACKET_DEBUG
	fprintf(stderr, "encrypted: ");
	buffer_dump(output);
#endif

	buffer_clear(outgoing_packet);

	/*
	 * Note that the packet is now only buffered in output.  It won\'t be
	 * actually sent until packet_write_wait or packet_write_poll is
	 * called.
	 */
}

void
set_newkeys(int mode)
{
	Enc *enc;
	Mac *mac;
	Comp *comp;
	CipherContext *cc;
	int encrypt;
    CipherContext *receive_context;/*isiah*/
    CipherContext *send_context;/*isiah*/
    Newkeys **newkeys;/*isiah*/

	debug2("set_newkeys: mode %d", mode);

	if (mode == MODE_OUT) {
	    SSHD_VM_GetSshSendContext(&send_context);/*isiah*/
		cc = send_context;
		encrypt = CIPHER_ENCRYPT;
	} else {
	    SSHD_VM_GetSshReceiveContext(&receive_context);/*isiah*/
		cc = receive_context;
		encrypt = CIPHER_DECRYPT;
	}

	SSHD_VM_GetSshNewKey(&newkeys);
	if (newkeys[mode] != NULL) {
		debug("set_newkeys: rekeying");
		cipher_cleanup(cc);
		enc  = &newkeys[mode]->enc;
		mac  = &newkeys[mode]->mac;
		comp = &newkeys[mode]->comp;
		memset(mac->key, 0, mac->key_len);
		xfree(enc->name);
		xfree(enc->iv);
		xfree(enc->key);
		xfree(mac->name);
		xfree(mac->key);
		xfree(comp->name);
		xfree(newkeys[mode]);
	}
	newkeys[mode] = kex_get_newkeys(mode);
	if (newkeys[mode] == NULL)
		fatal("newkeys: no keys for mode %d", mode);
	enc  = &newkeys[mode]->enc;
	mac  = &newkeys[mode]->mac;
	comp = &newkeys[mode]->comp;
	if (mac->md != NULL)
		mac->enabled = 1;
	DBG(debug("cipher_init_context: %d", mode));
	cipher_init(cc, enc->cipher, enc->key, enc->key_len,
	    enc->iv, enc->block_size, encrypt);
	/* Deleting the keys does not gain extra security */
	/* memset(enc->iv,  0, enc->block_size);
	   memset(enc->key, 0, enc->key_len); */
	if (comp->type != 0 && comp->enabled == 0) {
		packet_init_compression();
		if (mode == MODE_OUT)
			buffer_compress_init_send(6);
		else
			buffer_compress_init_recv();
		comp->enabled = 1;
	}
}

/*
 * Finalize packet in SSH2 format (compress, mac, encrypt, enqueue)
 */
static void
packet_send2(void)
{
	u_char type, *cp, *macbuf = NULL;
	u_char padlen, pad;
	u_int packet_length = 0;
	u_int /*i,*/ len;
//	u_int32_t rand = 0;
	Enc *enc   = NULL;
	Mac *mac   = NULL;
	Comp *comp = NULL;
	int block_size;
    Newkeys **newkeys;/*isiah*/
    Buffer *outgoing_packet;/*isiah*/
    CipherContext *send_context;/*isiah*/
    Buffer *output;/*isiah*/
    u_int32_t send_seqnr; /*isiah*/

    SSHD_VM_GetSshOutgoingPacketBuffer(&outgoing_packet);
	SSHD_VM_GetSshNewKey(&newkeys);
    SSHD_VM_GetSshSendContext(&send_context);/*isiah*/
    SSHD_VM_GetSshOutputBuffer(&output);
	if (newkeys[MODE_OUT] != NULL) {
		enc  = &newkeys[MODE_OUT]->enc;
		mac  = &newkeys[MODE_OUT]->mac;
		comp = &newkeys[MODE_OUT]->comp;
	}
	block_size = enc ? enc->block_size : 8;

	cp = buffer_ptr(outgoing_packet);
	type = cp[5];

#ifdef PACKET_DEBUG
	fprintf(stderr, "plain:     ");
	buffer_dump(outgoing_packet);
#endif

	if (comp && comp->enabled) {
		len = buffer_len(outgoing_packet);
		/* skip header, compress only payload */
		buffer_consume(outgoing_packet, 5);
		buffer_clear(&compression_buffer);
		buffer_compress(outgoing_packet, &compression_buffer);
		buffer_clear(outgoing_packet);
		buffer_append(outgoing_packet, "\0\0\0\0\0", 5);
		buffer_append(outgoing_packet, buffer_ptr(&compression_buffer),
		    buffer_len(&compression_buffer));
		DBG(debug("compression: raw %d compressed %d", len,
		    buffer_len(outgoing_packet)));
	}

	/* sizeof (packet_len + pad_len + payload) */
	len = buffer_len(outgoing_packet);

	/*
	 * calc size of padding, alloc space, get random data,
	 * minimum padding is 4 bytes
	 */
	padlen = block_size - (len % block_size);
	if (padlen < 4)
		padlen += block_size;
	if (extra_pad) {
		/* will wrap if extra_pad+padlen > 255 */
		extra_pad  = roundup(extra_pad, block_size);
		pad = extra_pad - ((len + padlen) % extra_pad);
		debug3("packet_send2: adding %d (len %d padlen %d extra_pad %d)",
		    pad, len, padlen, extra_pad);
		padlen += pad;
		extra_pad = 0;
	}
	cp = buffer_append_space(outgoing_packet, padlen);
	if (enc && !(send_context->plaintext)) {
		/* random padding */
/*isiah.2003-04-11*/
/*		for (i = 0; i < padlen; i++) {
			if (i % 4 == 0)
				rand = arc4random();
			cp[i] = rand & 0xff;
			rand >>= 8;
		}*/
		RAND_bytes(cp, padlen);
	} else {
		/* clear padding */
		memset(cp, 0, padlen);
	}
	/* packet_length includes payload, padding and padding length field */
	packet_length = buffer_len(outgoing_packet) - 4;
	cp = buffer_ptr(outgoing_packet);
	PUT_32BIT(cp, packet_length);
	cp[4] = padlen;
	DBG(debug("send: len %d (includes padlen %d)", packet_length+4, padlen));

	/* compute MAC over seqnr and packet(length fields, payload, padding) */
	SSHD_VM_GetSshSendSequenceNumber(&send_seqnr);
	if (mac && mac->enabled) {
		macbuf = mac_compute(mac, send_seqnr,
		    buffer_ptr(outgoing_packet),
		    buffer_len(outgoing_packet));
		DBG(debug("done calc MAC out #%d", send_seqnr));
	}
	/* encrypt packet and append to output buffer. */
	cp = buffer_append_space(output, buffer_len(outgoing_packet));
	cipher_crypt(send_context, cp, buffer_ptr(outgoing_packet),
	    buffer_len(outgoing_packet));
	/* append unencrypted MAC */
	if (mac && mac->enabled)
		buffer_append(output, (char *)macbuf, mac->mac_len);
#ifdef PACKET_DEBUG
	fprintf(stderr, "encrypted: ");
	buffer_dump(output);
#endif
	/* increment sequence number for outgoing packets */
	if (++send_seqnr == 0) ;

#if 0 /* squid, does not need to log */
		log("outgoing seqnr wraps around");
#endif

    SSHD_VM_SetSshSendSequenceNumber(send_seqnr);
	buffer_clear(outgoing_packet);

	if (type == SSH2_MSG_NEWKEYS)
		set_newkeys(MODE_OUT);
}

void
packet_send(void)
{
    I32_T compat20;/*isiah*/

    SSHD_VM_GetSshCompat20(&compat20);
	if (compat20)
		packet_send2();
	else
		packet_send1();
	DBG(debug("packet_send done"));
}

/*
 * Waits until a packet has been received, and returns its type.  Note that
 * no other data is processed until this returns, so this function should not
 * be used during the interactive session.
 */

int
packet_read_seqnr(u_int32_t *seqnr_p)
{
	int type, len;
//	fd_set *setp; /*isiah*/
	fd_set setp; /*isiah*/
	char buf[8192];
	int ret;/*isiah*/
    I32_T connection_in;/*isiah.*/
    I32_T connection_out;/*isiah.*/
    I32_T compat20;/*isiah*/
    struct 	timeval     timeout;/*isiah*/

	DBG(debug("packet_read()"));

    SSHD_VM_GetSshConnectionSockId(&connection_in, &connection_out);
/*	setp = (fd_set *)xmalloc(howmany(connection_in+1, NFDBITS) *
	    sizeof(fd_mask));*//*isiah*/

	/* Since we are blocking, ensure that all written packets have been sent. */
	packet_write_wait();

	/* Stay in the loop until we have received a complete packet. */
    SSHD_VM_GetSshCompat20(&compat20);
	for (;;) {
		/* Try to read a packet from the buffer. */
		type = packet_read_poll_seqnr(seqnr_p);
		if (!compat20 && (
		    type == SSH_SMSG_SUCCESS
		    || type == SSH_SMSG_FAILURE
		    || type == SSH_CMSG_EOF
		    || type == SSH_CMSG_EXIT_CONFIRMATION))
			packet_check_eom();
		/* If we got a packet, return it. */
		if (type != SSH_MSG_NONE) {
//			xfree(setp); /*isiah*/
			return type;
		}
		/*
		 * Otherwise, wait for some data to arrive, add it to the
		 * buffer, and try again.
		 */
        do
        {
    		FD_ZERO(&setp);
    		FD_SET(connection_in, &setp);

           	timeout.tv_sec = SSHD_VM_GetNegotiationTimeout();   /*  no.  of seconds  */
            timeout.tv_usec = 0;                                /*  no. of micro seconds  */
        } while ((ret=select(connection_in + 1, &setp, NULL, NULL, &timeout)) == -1 &&
		         (errno == EAGAIN || errno == EINTR || errno == EWOULDBLOCK));

        if( ret <= 0 )
        {
            packet_disconnect("Authentication timeout\n");
        }
		/* Read data from the socket. */
		len = read(connection_in, buf, sizeof(buf));
		if (len == 0) {
#if 0 /* squid, does not need to log */
			log("Connection closed by %.200s", get_remote_ipaddr());
#endif
			fatal_cleanup();
		}
		if (len < 0)
//			fatal("Read from socket failed: %.100s", strerror(errno));/*isiah*/
			fatal("Read from socket failed: %d", len);/*isiah*/
		/* Append it to the buffer. */
		packet_process_incoming(buf, len);
	}
	/* NOTREACHED */
}

int
packet_read(void)
{
	return packet_read_seqnr(NULL);
}

/*
 * Waits until a packet has been received, verifies that its type matches
 * that given, and gives a fatal error and exits if there is a mismatch.
 */

void
packet_read_expect(int expected_type)
{
	int type;

	type = packet_read();
	if (type != expected_type)
		packet_disconnect("Protocol error: expected packet type %d, got %d",
		    expected_type, type);
}

/* Checks if a full packet is available in the data received so far via
 * packet_process_incoming.  If so, reads the packet; otherwise returns
 * SSH_MSG_NONE.  This does not wait for data from the connection.
 *
 * SSH_MSG_DISCONNECT is handled specially here.  Also,
 * SSH_MSG_IGNORE messages are skipped by this function and are never returned
 * to higher levels.
 */

static int
packet_read_poll1(void)
{
	u_int len, padded_len;
	u_char *cp, type;
	u_int checksum, stored_checksum;
    Buffer *input;/*isiah*/
    CipherContext *receive_context;/*isiah*/
    Buffer *incoming_packet;/*isiah*/

    SSHD_VM_GetSshInputBuffer(&input);
    SSHD_VM_GetSshReceiveContext(&receive_context);/*isiah*/
    SSHD_VM_GetSshIncomingPacketBuffer(&incoming_packet);
	/* Check if input size is less than minimum packet size. */
	if (buffer_len(input) < 4 + 8)
		return SSH_MSG_NONE;
	/* Get length of incoming packet. */
	cp = buffer_ptr(input);
	len = GET_32BIT(cp);
	if (len < 1 + 2 + 2 || len > 256 * 1024)
		packet_disconnect("Bad packet length %u.", len);
	padded_len = (len + 8) & ~7;

	/* Check if the packet has been entirely received. */
	if (buffer_len(input) < 4 + padded_len)
		return SSH_MSG_NONE;

	/* The entire packet is in buffer. */

	/* Consume packet length. */
	buffer_consume(input, 4);

	/*
	 * Cryptographic attack detector for ssh
	 * (C)1998 CORE-SDI, Buenos Aires Argentina
	 * Ariel Futoransky(futo@core-sdi.com)
	 */
	if (!(receive_context->plaintext) &&
	    detect_attack(buffer_ptr(input), padded_len, NULL) == DEATTACK_DETECTED)
		packet_disconnect("crc32 compensation attack: network attack detected");

	/* Decrypt data to incoming_packet. */
	buffer_clear(incoming_packet);
	cp = buffer_append_space(incoming_packet, padded_len);
	cipher_crypt(receive_context, cp, buffer_ptr(input), padded_len);

	buffer_consume(input, padded_len);

#ifdef PACKET_DEBUG
	fprintf(stderr, "read_poll plain: ");
	buffer_dump(incoming_packet);
#endif

	/* Compute packet checksum. */
	checksum = ssh_crc32(buffer_ptr(incoming_packet),
	    buffer_len(incoming_packet) - 4);

	/* Skip padding. */
	buffer_consume(incoming_packet, 8 - len % 8);

	/* Test check bytes. */
	if (len != buffer_len(incoming_packet))
		packet_disconnect("packet_read_poll1: len %d != buffer_len %d.",
		    len, buffer_len(incoming_packet));

	cp = (u_char *)buffer_ptr(incoming_packet) + len - 4;
	stored_checksum = GET_32BIT(cp);
	if (checksum != stored_checksum)
		packet_disconnect("Corrupted check bytes on input.");
	buffer_consume_end(incoming_packet, 4);

	if (packet_compression) {
		buffer_clear(&compression_buffer);
		buffer_uncompress(incoming_packet, &compression_buffer);
		buffer_clear(incoming_packet);
		buffer_append(incoming_packet, buffer_ptr(&compression_buffer),
		    buffer_len(&compression_buffer));
	}
	type = buffer_get_char(incoming_packet);
	return type;
}

static int
packet_read_poll2(u_int32_t *seqnr_p)
{
/*isiah.2003-11-27*/
/*    static u_int packet_length = 0;*/
    UI32_T packet_length = 0;
	u_int padlen, need;
	u_char *macbuf, *cp, type;
	int maclen, block_size;
	Enc *enc   = NULL;
	Mac *mac   = NULL;
	Comp *comp = NULL;
    Newkeys **newkeys;/*isiah*/
    Buffer *input;/*isiah*/
    CipherContext *receive_context;/*isiah*/
    Buffer *incoming_packet;/*isiah*/
    u_int32_t read_seqnr; /*isiah*/

	SSHD_VM_GetSshNewKey(&newkeys);
    SSHD_VM_GetSshInputBuffer(&input);
    SSHD_VM_GetSshReceiveContext(&receive_context);/*isiah*/
    SSHD_VM_GetSshIncomingPacketBuffer(&incoming_packet);
/*isiah.2003-11-27*/
    SSHD_VM_GetSshPacketLength(&packet_length);
	if (newkeys[MODE_IN] != NULL) {
		enc  = &newkeys[MODE_IN]->enc;
		mac  = &newkeys[MODE_IN]->mac;
		comp = &newkeys[MODE_IN]->comp;
	}
	maclen = mac && mac->enabled ? mac->mac_len : 0;
	block_size = enc ? enc->block_size : 8;

	if (packet_length == 0) {
		/*
		 * check if input size is less than the cipher block size,
		 * decrypt first block and extract length of incoming packet
		 */
		if (buffer_len(input) < block_size)
			return SSH_MSG_NONE;
		buffer_clear(incoming_packet);
		cp = buffer_append_space(incoming_packet, block_size);
		cipher_crypt(receive_context, cp, buffer_ptr(input),
		    block_size);
		cp = buffer_ptr(incoming_packet);
		packet_length = GET_32BIT(cp);

/*isiah.2003-11-27*/
        SSHD_VM_SetSshPacketLength(packet_length);
		if (packet_length < 1 + 4 || packet_length > 256 * 1024) {
			buffer_dump(incoming_packet);
			packet_disconnect("Bad packet length %ld.", (long)packet_length);
		}
		DBG(debug("input: packet len %u", packet_length+4));
		buffer_consume(input, block_size);
	}
	/* we have a partial packet of block_size bytes */
	need = 4 + packet_length - block_size;
	DBG(debug("partial packet %d, need %d, maclen %d", block_size,
	    need, maclen));
	if (need % block_size != 0)
		fatal("padding error: need %d block %d mod %d",
		    need, block_size, need % block_size);
	/*
	 * check if the entire packet has been received and
	 * decrypt into incoming_packet
	 */
	if (buffer_len(input) < need + maclen)
		return SSH_MSG_NONE;
#ifdef PACKET_DEBUG
	fprintf(stderr, "read_poll enc/full: ");
	buffer_dump(input);
#endif
	cp = buffer_append_space(incoming_packet, need);
	cipher_crypt(receive_context, cp, buffer_ptr(input), need);
	buffer_consume(input, need);
	/*
	 * compute MAC over seqnr and packet,
	 * increment sequence number for incoming packet
	 */
    SSHD_VM_GetSshReadSequenceNumber(&read_seqnr);
	if (mac && mac->enabled) {
		macbuf = mac_compute(mac, read_seqnr,
		    buffer_ptr(incoming_packet),
		    buffer_len(incoming_packet));
		if (memcmp(macbuf, buffer_ptr(input), mac->mac_len) != 0)
			packet_disconnect("Corrupted MAC on input.");
		DBG(debug("MAC #%d ok", read_seqnr));
		buffer_consume(input, mac->mac_len);
	}
	if (seqnr_p != NULL)
		*seqnr_p = read_seqnr;
	if (++read_seqnr == 0) ;
#if 0 /* squid, does not need to log */
		log("incoming seqnr wraps around");
#endif
    SSHD_VM_SetSshReadSequenceNumber(read_seqnr);

	/* get padlen */
	cp = buffer_ptr(incoming_packet);
	padlen = cp[4];
	DBG(debug("input: padlen %d", padlen));
	if (padlen < 4)
		packet_disconnect("Corrupted padlen %d on input.", padlen);

	/* skip packet size + padlen, discard padding */
	buffer_consume(incoming_packet, 4 + 1);
	buffer_consume_end(incoming_packet, padlen);

	DBG(debug("input: len before de-compress %d", buffer_len(incoming_packet)));
	if (comp && comp->enabled) {
		buffer_clear(&compression_buffer);
		buffer_uncompress(incoming_packet, &compression_buffer);
		buffer_clear(incoming_packet);
		buffer_append(incoming_packet, buffer_ptr(&compression_buffer),
		    buffer_len(&compression_buffer));
		DBG(debug("input: len after de-compress %d",
		    buffer_len(incoming_packet)));
	}
	/*
	 * get packet type, implies consume.
	 * return length of payload (without type field)
	 */
	type = buffer_get_char(incoming_packet);
	if (type == SSH2_MSG_NEWKEYS)
		set_newkeys(MODE_IN);
#ifdef PACKET_DEBUG
	fprintf(stderr, "read/plain[%d]:\r\n", type);
	buffer_dump(incoming_packet);
#endif
	/* reset for next packet */
	packet_length = 0;
/*isiah.2003-11-27*/
	SSHD_VM_SetSshPacketLength(packet_length);
	return type;
}

int
packet_read_poll_seqnr(u_int32_t *seqnr_p)
{
	u_int /*reason,*/ seqnr;
	u_char type;
	char *msg;
    I32_T compat20;/*isiah*/

    SSHD_VM_GetSshCompat20(&compat20);
	for (;;) {
		if (compat20) {
			type = packet_read_poll2(seqnr_p);
			if (type)
				DBG(debug("received packet type %d", type));
			switch (type) {
			case SSH2_MSG_IGNORE:
				break;
			case SSH2_MSG_DEBUG:
				packet_get_char();
				msg = packet_get_string(NULL);
				debug("Remote: %.900s", msg);
				xfree(msg);
				msg = packet_get_string(NULL);
				xfree(msg);
				break;
			case SSH2_MSG_DISCONNECT:
				/*reason = packet_get_int();*/
				msg = packet_get_string(NULL);
#if 0 /* squid, does not need to log */
				log("Received disconnect from %s: %u: %.400s",
				    get_remote_ipaddr(), reason, msg);
#endif
				xfree(msg);
				fatal_cleanup();
				break;
			case SSH2_MSG_UNIMPLEMENTED:
				seqnr = packet_get_int();
				debug("Received SSH2_MSG_UNIMPLEMENTED for %u",
				    seqnr);
				break;
			default:
				return type;
				break;
			}
		} else {
			type = packet_read_poll1();
			switch (type) {
			case SSH_MSG_IGNORE:
				break;
			case SSH_MSG_DEBUG:
				msg = packet_get_string(NULL);
				debug("Remote: %.900s", msg);
				xfree(msg);
				break;
			case SSH_MSG_DISCONNECT:
				msg = packet_get_string(NULL);
#if 0 /* squid, does not need to log */
				log("Received disconnect from %s: %.400s",
				    get_remote_ipaddr(), msg);
#endif
				fatal_cleanup();
				xfree(msg);
				break;
			default:
				if (type)
					DBG(debug("received packet type %d", type));
				return type;
				break;
			}
		}
	}
}

int
packet_read_poll(void)
{
	return packet_read_poll_seqnr(NULL);
}

/*
 * Buffers the given amount of input characters.  This is intended to be used
 * together with packet_read_poll.
 */

void
packet_process_incoming(const char *buf, u_int len)
{
    Buffer *input;/*isiah*/

    SSHD_VM_GetSshInputBuffer(&input);
	buffer_append(input, buf, len);
}

/* Returns a character from the packet. */

u_int
packet_get_char(void)
{
	char ch;
    Buffer *incoming_packet;/*isiah*/

    SSHD_VM_GetSshIncomingPacketBuffer(&incoming_packet);
	buffer_get(incoming_packet, &ch, 1);
	return (u_char) ch;
}

/* Returns an integer from the packet data. */

u_int
packet_get_int(void)
{
    Buffer *incoming_packet;/*isiah*/

    SSHD_VM_GetSshIncomingPacketBuffer(&incoming_packet);
	return buffer_get_int(incoming_packet);
}

/*
 * Returns an arbitrary precision integer from the packet data.  The integer
 * must have been initialized before this call.
 */

void
packet_get_bignum(BIGNUM * value)
{
    Buffer *incoming_packet;/*isiah*/

    SSHD_VM_GetSshIncomingPacketBuffer(&incoming_packet);
	buffer_get_bignum(incoming_packet, value);
}

void
packet_get_bignum2(BIGNUM * value)
{
    Buffer *incoming_packet;/*isiah*/

    SSHD_VM_GetSshIncomingPacketBuffer(&incoming_packet);
	buffer_get_bignum2(incoming_packet, value);
}

void *
packet_get_raw(int *length_ptr)
{
    Buffer *incoming_packet;/*isiah*/
    int bytes;

    SSHD_VM_GetSshIncomingPacketBuffer(&incoming_packet);
	bytes = buffer_len(incoming_packet);

	if (length_ptr != NULL)
		*length_ptr = bytes;
	return buffer_ptr(incoming_packet);
}

int
packet_remaining(void)
{
    Buffer *incoming_packet;/*isiah*/

    SSHD_VM_GetSshIncomingPacketBuffer(&incoming_packet);
	return buffer_len(incoming_packet);
}

/*
 * Returns a string from the packet data.  The string is allocated using
 * xmalloc; it is the responsibility of the calling program to free it when
 * no longer needed.  The length_ptr argument may be NULL, or point to an
 * integer into which the length of the string is stored.
 */

void *
packet_get_string(u_int *length_ptr)
{
    Buffer *incoming_packet;/*isiah*/

    SSHD_VM_GetSshIncomingPacketBuffer(&incoming_packet);
	return buffer_get_string(incoming_packet, length_ptr);
}

/*
 * Sends a diagnostic message from the server to the client.  This message
 * can be sent at any time (but not while constructing another message). The
 * message is printed immediately, but only if the client is being executed
 * in verbose mode.  These messages are primarily intended to ease debugging
 * authentication problems.   The length of the formatted message must not
 * exceed 1024 bytes.  This will automatically call packet_write_wait.
 */

void
packet_send_debug(const char *fmt,...)
{
	char buf[1024];
	va_list args;
	I32_T datafellows;/*isiah*/
    I32_T compat20;/*isiah*/

	SSHD_VM_GetSshDataFellows(&datafellows);
    SSHD_VM_GetSshCompat20(&compat20);
	if (compat20 && (datafellows & SSH_BUG_DEBUG))
		return;

	va_start(args, fmt);
//	vsnprintf(buf, sizeof(buf), fmt, args);
	vsprintf(buf, fmt, args);
	va_end(args);

	if (compat20) {
		packet_start(SSH2_MSG_DEBUG);
		packet_put_char(0);	/* bool: always display */
		packet_put_cstring(buf);
		packet_put_cstring("");
	} else {
		packet_start(SSH_MSG_DEBUG);
		packet_put_cstring(buf);
	}
	packet_send();
	packet_write_wait();
}

/*
 * Logs the error plus constructs and sends a disconnect packet, closes the
 * connection, and exits.  This function never returns. The error message
 * should not contain a newline.  The length of the formatted message must
 * not exceed 1024 bytes.
 */

void
packet_disconnect(const char *fmt,...)
{
	char buf[1024];
	va_list args;
//	static int disconnecting = 0;/*isiah*/
    I32_T compat20;/*isiah*/

#if 0
	if (disconnecting)	/* Guard against recursive invocations. */
		fatal("packet_disconnect called recursively.");
	disconnecting = 1;
#endif

	/*
	 * Format the message.  Note that the caller must make sure the
	 * message is of limited size.
	 */
	va_start(args, fmt);
//	vsnprintf(buf, sizeof(buf), fmt, args);
	vsprintf(buf, fmt, args);
	va_end(args);

	/* Display the error locally */
#if 0 /* squid, does not need to log */
	log("Disconnecting: %.100s", buf);
#endif
	/* Send the disconnect message to the other side, and wait for it to get sent. */
    SSHD_VM_GetSshCompat20(&compat20);
	if (compat20) {
		packet_start(SSH2_MSG_DISCONNECT);
		packet_put_int(SSH2_DISCONNECT_PROTOCOL_ERROR);
		packet_put_cstring(buf);
		packet_put_cstring("");
	} else {
		packet_start(SSH_MSG_DISCONNECT);
		packet_put_cstring(buf);
	}
	packet_send();
	packet_write_wait();

	/* Stop listening for connections. */
	channel_close_all();

	/* Close the connection. */
	packet_close();

	fatal_cleanup();
}

/* Checks if there is any buffered output, and tries to write some of the output. */

void
packet_write_poll(void)
{
    Buffer *output;/*isiah*/
    int len;
    I32_T connection_in;/*isiah.*/
    I32_T connection_out;/*isiah.*/

    SSHD_VM_GetSshOutputBuffer(&output);
	len = buffer_len(output);

	if (len > 0) {
        SSHD_VM_GetSshConnectionSockId(&connection_in, &connection_out);
		len = write(connection_out, buffer_ptr(output), len);
		if (len <= 0) {
/*			if (errno == EAGAIN)*/
			if (len == EAGAIN || len == EWOULDBLOCK)
				return;
			else
//				fatal("Write failed: %.100s", strerror(errno));/*isiah*/
				fatal("Write failed: %d", len);
		}
		buffer_consume(output, len);
	}
}

/*
 * Calls packet_write_poll repeatedly until all pending output data has been
 * written.
 */

void
packet_write_wait(void)
{
//	fd_set *setp; /*isiah*/
	fd_set setp; /*isiah*/
	int ret;/*isiah*/
    I32_T connection_in;/*isiah.*/
    I32_T connection_out;/*isiah.*/

    SSHD_VM_GetSshConnectionSockId(&connection_in, &connection_out);
/*	setp = (fd_set *)xmalloc(howmany(connection_out + 1, NFDBITS) *
	    sizeof(fd_mask));*/ /*isiah*/
	packet_write_poll();
	while (packet_have_data_to_write()) {
/*		memset(setp, 0, howmany(connection_out + 1, NFDBITS) *
		    sizeof(fd_mask));
		FD_SET(connection_out, setp);*/ /*isiah*/
		FD_ZERO(&setp);
		FD_SET(connection_out, &setp);
/*		while (select(connection_out + 1, NULL, setp, NULL, NULL) == -1 &&
		    (errno == EAGAIN || errno == EINTR))*//*isiah*/
		while ((ret=select(connection_out + 1, NULL, &setp, NULL, NULL)) == -1 &&
		       (errno == EAGAIN || errno == EINTR || errno == EWOULDBLOCK))
	    {
            /* for linux platform
             */
    		FD_ZERO(&setp); /* squid */
    		FD_SET(connection_out, &setp);
	    }

		packet_write_poll();
	}
//	xfree(setp); /*isiah*/
}

/* Returns true if there is buffered data to write to the connection. */

int
packet_have_data_to_write(void)
{
    Buffer *output;/*isiah*/

    SSHD_VM_GetSshOutputBuffer(&output);
	return buffer_len(output) != 0;
}

/* Returns true if there is not too much data to write to the connection. */

int
packet_not_very_much_data_to_write(void)
{
    Buffer *output;/*isiah*/
    I32_T interactive_mode = 0; /*isiah*/

    SSHD_VM_GetSshOutputBuffer(&output);
    SSHD_VM_GetSshInteractiveMode(&interactive_mode);
	if (interactive_mode)
		return buffer_len(output) < 16384;
	else
		return buffer_len(output) < 128 * 1024;
}

static void
packet_set_tos(int interactive)
{
	int tos = interactive ? IPTOS_LOWDELAY : IPTOS_THROUGHPUT; /*isiah*/

	int connection_in;

	if (!packet_connection_is_on_socket() ||
	    !packet_connection_is_ipv4())
		return;
/*	if (setsockopt(connection_in, IPPROTO_IP, IP_TOS, &tos,
	    sizeof(tos)) < 0)
		error("setsockopt IP_TOS %d: %.100s:",
		    tos, strerror(errno));*/ /*isiah*/
    connection_in = packet_get_connection_in();

    setsockopt(connection_in, IPPROTO_IP, IP_TOS, &tos, sizeof(tos));
}

/* Informs that the current session is interactive.  Sets IP flags for that. */

void
packet_set_interactive(int interactive)
{
//	static int called = 0;/*isiah.*/
    I32_T connection_in;/*isiah.*/
    I32_T connection_out;/*isiah.*/

/*	if (called)
		return;
	called = 1;*//*isiah.*/

	/* Record that we are in interactive mode. */
//	interactive_mode = interactive;/*isiah*/
    SSHD_VM_SetSshInteractiveMode(interactive);

	/* Only set socket options if using a socket.  */
	if (!packet_connection_is_on_socket())
		return;
	if (interactive)
	{
        SSHD_VM_GetSshConnectionSockId(&connection_in, &connection_out);
		set_nodelay(connection_in);
	}
	packet_set_tos(interactive);
}

/* Returns true if the current connection is interactive. */

int
packet_is_interactive(void)
{
    I32_T interactive_mode = 0; /*isiah*/

    SSHD_VM_GetSshInteractiveMode(&interactive_mode);
	return interactive_mode;
}

int
packet_set_maxsize(int s)
{
/*	static int called = 0;

	if (called) {
		log("packet_set_maxsize: called twice: old %d new %d",
		    max_packet_size, s);
		return -1;
	}
	if (s < 4 * 1024 || s > 1024 * 1024) {
		log("packet_set_maxsize: bad size %d", s);
		return -1;
	}
	called = 1;*/
	debug("packet_set_maxsize: setting to %d", s);
//	max_packet_size = s;/*isiah*/
    SSHD_VM_SetSshMaxPacketSize(s);
	return s;
}

/*isiah. add*/
I32_T packet_get_maxsize(void)
{
    I32_T max_packet_size = 32768; /*isiah*/

    SSHD_VM_GetSshMaxPacketSize(&max_packet_size);
    return max_packet_size;
}

/* roundup current message to pad bytes */
void
packet_add_padding(u_char pad)
{
	extra_pad = pad;
}

/*
 * 9.2.  Ignored Data Message
 *
 *   byte      SSH_MSG_IGNORE
 *   string    data
 *
 * All implementations MUST understand (and ignore) this message at any
 * time (after receiving the protocol version). No implementation is
 * required to send them. This message can be used as an additional
 * protection measure against advanced traffic analysis techniques.
 */
void
packet_send_ignore(int nbytes)
{
//	u_int32_t rand = 0;
	int temp = 0;
	int i;
    I32_T compat20;/*isiah*/

    SSHD_VM_GetSshCompat20(&compat20);
	packet_start(compat20 ? SSH2_MSG_IGNORE : SSH_MSG_IGNORE);
	packet_put_int(nbytes);
/*isiah.2003-04-11*/
	for (i = 0; i < nbytes; i++) {
/*		if (i % 4 == 0)
			rand = arc4random();
		packet_put_char(rand & 0xff);
		rand >>= 8;*/
		if (i % 2 == 0)
			temp = rand();
		packet_put_char(temp & 0xff);
		temp >>= 8;
	}
}
