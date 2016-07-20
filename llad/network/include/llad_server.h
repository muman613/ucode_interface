/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   server.h
  @brief  

  long description

  @author Julien Soulier
  @date   2003-01-15
*/

#ifndef __SERVER_H__
#define __SERVER_H__

#include "sock.h"
#include "../../include/llad.h"
#include "../../include/gbus.h"
#include "../../include/dmacpy.h"
#include <pthread.h>

#define SOCK_LLAD_PORT   1664 
#define SOCK_LLAD_SERVICE   0
#define SOCK_GBUS_SERVICE   1
#define SOCK_DMACPY_SERVICE 2

void llad_server(struct llad *h, struct sock *sd);
void gbus_server(struct gbus *pgbus, struct sock *sd, pthread_mutex_t *gbus_lock);
void dmacpy_server(struct dmacpy *h, struct sock *sd);

#endif // __SERVER_H__
