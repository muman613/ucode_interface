/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmsync.h
  @brief  

  This file describes the synchronization
  callbacks for functions requiring semaphores
  and critical sections.

  These functions are not implemented in rmdef,
  they are left to a higher level of API.

  To instanciate a memory manager you will need
  for instance to give a RMcriticalsectionOps *pCSops.
  If pCSops==NULL the memory manager will be created
  but will not be thread-safe.

  @author Emmanuel Michon
  @date   2003-02-11
*/

#ifndef __RMSYNC_H__
#define __RMSYNC_H__

RM_EXTERN_C_BLOCKSTART

typedef struct _RMcriticalsection *RMcriticalsection;

typedef struct {
	RMcriticalsection (*Create)(void);
	void (*Delete)(RMcriticalsection lpCriticalSection);
	void (*Enter)(RMcriticalsection lpCriticalSection);
	void (*Leave)(RMcriticalsection lpCriticalSection);
} RMcriticalsectionOps;

extern RMcriticalsectionOps g_critsec_ops;

typedef struct _RMsemaphore *RMsemaphore;

typedef struct {
	RMsemaphore (*Create)(RMuint32 lInitialCount);
	void (*Delete)(RMsemaphore x);
	void (*WaitFor)(RMsemaphore x);
	RMstatus (*TryWaitFor)(RMsemaphore x);
	void (*Release)(RMsemaphore x, RMuint32 lReleaseCount);
	RMuint32 (*GetValue)(RMsemaphore x);
} RMsemaphoreOps;

extern RMsemaphoreOps g_sem_ops;

typedef struct _RMtimeoutSemaphore *RMtimeoutSemaphore;

typedef struct {
	RMtimeoutSemaphore (*Create)(RMuint32 lInitialCount);
	void (*Delete)(RMtimeoutSemaphore x);
	RMstatus (*WaitFor)(RMtimeoutSemaphore x, RMuint64 microSec);
	void (*Release)(RMtimeoutSemaphore x, RMuint32 lReleaseCount);
	RMuint32 (*GetValue)(RMtimeoutSemaphore x);
} RMtimeoutSemaphoreOps;

extern RMtimeoutSemaphoreOps g_timeoutSem_ops;

RM_EXTERN_C_BLOCKEND

#endif // __RMSYNC_H__
