/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   rmsemaphores.h
  @ingroup libcapi
  @brief  Defines the API to manipulate semaphores.

  Semaphores  are  counters  for  resources  shared  between
  threads. The basic operations on semaphores are: 
  <ul>
  <li> increment the counter atomically
  <li> wait until the counter is non-null and decrement it atomically
  </ul>

  Some operating systems implement timeouts on semaphores; this is not
  handled here: blocking wait is infinite.

  Most of the times only 0 and 1 value are used, but more may occur.

  @author Emmanuel Michon
  @date   2001-01-26
*/

#ifndef __RMSEMAPHORES_H__
#define __RMSEMAPHORES_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup libcapi
 *  @{
 */

/// 
/**
   Creates and returns a handle to a semaphore object with initial
   value specified.

   @param lInitialCount 
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMsemaphore RMCreateSemaphore(RMuint32 lInitialCount);

/// 
/**
   Deletes the semaphore. 
   Unpredictable result if a thread is blocked on this semaphore.

   @param x       
*/
RM_LIBRARY_IMPORT_EXPORT void RMDeleteSemaphore(RMsemaphore x);

/// 
/**
   Waits for a semaphore to have a >0 value, then decreases count.
   This can be a blocking call.

   @param x       
*/
RM_LIBRARY_IMPORT_EXPORT void RMWaitForSemaphore(RMsemaphore x);

/// 
/**
   If the semaphore pointed to by sem has non-zero count, the count is
   atomically decreased and ReturnValue is RM_OK, RM_SEMAPHORELOCKED otherwise.
   
   This is a nonblocking call.

   @param x     
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMTryWaitForSemaphore(RMsemaphore x);

/// 
/**
   Releases the semaphore (increase value of specified count).

   Pay attention to the fact that RMReleaseSemaphore with
   lReleaseCount>1 must be atomic.

   @param x    
   @param lReleaseCount 
*/
RM_LIBRARY_IMPORT_EXPORT void RMReleaseSemaphore(RMsemaphore x, RMuint32 lReleaseCount);

/// 
/**
   Returns the value stored
   in the semaphore (at the instant of the call, let's call it t1). 
   It allows to know if the semaphore is taken or available without
   blocking --- but don't use this as a preliminary for 
   RMWaitForSemaphore (executed at t2), since value may have changed
   between t1 and t2.

   @param x       
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMuint32 RMGetSemaphoreValue(RMsemaphore x);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMSEMAPHORES_H__
