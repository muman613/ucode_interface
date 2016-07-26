/*****************************************
 Copyright © 2001-2003
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   sock.h
  @brief

  @author Julien Soulier
  @date   2003-01-13
*/

#ifndef __SOCK_H__
#define __SOCK_H__

#include "rmdef/rmdef.h"

/* Sometime compiled as C++ in the <cvs_asic>tango/emulation/ */
RM_EXTERN_C_BLOCKSTART

struct sock;

/**
   creates a sock able to wait for a connection.

   (used by a server). queue_size determines the number of pending
   connections when waiting for one.

   @param port
   @param queue_size
*/
struct sock *sock_create(RMuint16 port, RMuint32 queue_size);

/**
   opens a sock and connects it to the port port on the internet address netaddress.
   (used by a client)

   @param port
   @param netaddress
*/
struct sock *sock_connect(RMuint16 port, RMascii *netaddress);

/**
   waits for a socket to be connected to sock h.
   once a socket is connected returns the connected socket.
   (used by a server)

   @param h
*/
struct sock *sock_wait_connection(struct sock *h);

/**
   waits for a socket to be connected to sock h, with a timeout of usecTimeout microseconds.
   once a socket is connected returns the connected socket.
   (used by a server)

   @param h
   @param usecTimeout
*/
struct sock *sock_wait_connection_with_timeout(struct sock *listening_sock, RMuint32 usecTimeout);


/**
   closes a previously opened sock.

   @param h
*/
void sock_close(struct sock *h);

/**
   reads count bytes from array buf from the opened sock sock.
   returns the number of bytes read or -1 if an error occured.

   @param h
   @param buf
   @param count
   @return
*/
RMint32 sock_read_buf(struct sock *h, RMuint8 *buf, RMuint32 count);

/**
   writes count bytes of array buf into the opened sock sock.
   returns the number of bytes read or -1 if an error occured.

   @param h
   @param buf
   @param count
   @return
*/
RMint32 sock_write_buf(struct sock *h, RMuint8 *buf, RMuint32 count);

/**
   reads a 32 bit integer from sock.
   returns the number of bytes read or -1 if an error occured.

   @param h
   @return
*/
RMint32 sock_read_uint32(struct sock *h, RMuint32 *val);

/**
   writes a 32 bit integer to sock
   returns the number of bytes read or -1 if an error occured.

   @param h
   @param val
*/
RMint32 sock_write_uint32(struct sock *h, RMuint32 val);

/**
   writes 2 32 bit integers to sock
   returns the number of bytes read or -1 if an error occured.

   @param h
   @param val1
   @param val2
*/
RMint32 sock_write_2_uint32(struct sock *h, RMuint32 val1, RMuint32 val2);

/**
   writes 2 32 bit integers to sock
   returns the number of bytes read or -1 if an error occured.

   @param h
   @param val1
   @param val2
   @param val3
*/
RMint32 sock_write_3_uint32(struct sock *h, RMuint32 val1, RMuint32 val2, RMuint32 val3);

RM_EXTERN_C_BLOCKEND

#endif // __SOCK_H__

