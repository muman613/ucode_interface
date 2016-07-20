/*****************************************
 Copyright (c) 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   gbus_spinlock.h
  @brief  

  linux-style locking
  
  The emhwlib runs on CPU and the interrupt handler runs either on XPU or on IPU.
  The emhwlib and the interrupt handler may compete for the same resource and
  they have to exclude each other by causing temporarily the other to busy loop.

  @author Emmanuel Michon
  @date   2003-07-17
*/

#ifndef __GBUS_SPINLOCK_H__
#define __GBUS_SPINLOCK_H__

#include "gbus_mutex.h"

RM_EXTERN_C_BLOCKSTART

static inline RMuint32 gbus_spin_lock_mutex_irq(struct gbus *pGBus, struct gbus_mutex *mutex, RMuint32 irq)
{
	gbus_mutex_lock(pGBus,mutex);

	return 0;
}

static inline void gbus_spin_unlock_mutex_irq(struct gbus *pGBus, struct gbus_mutex *mutex, RMuint32 flags)
{
	gbus_mutex_unlock(pGBus,mutex);
}

RM_EXTERN_C_BLOCKEND

#endif // __GBUS_SPINLOCK_H__
