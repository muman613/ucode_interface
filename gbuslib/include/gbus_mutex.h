/*****************************************
 Copyright (c) 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   gbus_mutex.h
  @brief  

  describes the hardware mutex api

  @author Julien Soulier
  @date   2003-04-15
*/

#ifndef __GBUS_MUTEX_H__
#define __GBUS_MUTEX_H__



RM_EXTERN_C_BLOCKSTART

struct gbus_mutex;

static inline struct gbus_mutex *gbus_mutex_open(struct gbus *pgbus, RMuint32 gbus_addr)
{
	return (struct gbus_mutex *)gbus_addr;
}

static inline void gbus_mutex_close(struct gbus *pgbus, struct gbus_mutex *mutex)
{
}

static inline void gbus_mutex_lock(struct gbus *pgbus, struct gbus_mutex *mutex)
{
	while (gbus_read_uint32(pgbus, (RMuint32) mutex));
}

static inline void gbus_mutex_unlock(struct gbus *pgbus, struct gbus_mutex *mutex)
{
	gbus_write_uint32(pgbus, (RMuint32)mutex, 0);
}

static inline RMuint32 gbus_mutex_trylock(struct gbus *pgbus, struct gbus_mutex *mutex)
{
	return gbus_read_uint32(pgbus, (RMuint32) mutex);
} 

RM_EXTERN_C_BLOCKEND

#endif // __GBUS_MUTEX_H__
