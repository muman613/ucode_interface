/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   struct.h
  @brief  

  @author Julien Soulier
  @date   2003-01-14
*/

#ifndef __STRUCT_H__
#define __STRUCT_H__

#include <pthread.h>

struct llad {
	struct sock *sd;
	char *hostname;
	RMuint32 device;
};

struct gbus {
	struct sock *sd;
	pthread_mutex_t *gbus_lock;
};

struct dmacpy {
	struct sock *sd;
	RMuint8 *remote_buf;
	RMuint8 *local_buf;
};

#endif // __STRUCT_H__
