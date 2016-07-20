/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   rmtimeoutsemaphore.h
  @brief  

  Description of timeout semaphores

  @author Julien Soulier
  @date   2002-09-03
  @ingroup libcapi
*/

#ifndef __RMTIMEOUTSEMAPHORE_H__
#define __RMTIMEOUTSEMAPHORE_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup libcapi
 *  @{
 */

/**
   Creates a timeout semaphore. An initial count of 0 means the
   semaphore is locked when it is created.

   @param initialCount  
   @return the newly created timeout semaphore
*/
RM_LIBRARY_IMPORT_EXPORT RMtimeoutSemaphore RMCreateTimeoutSemaphore(RMuint32 initialCount);


/**
   Destroy the timeout semaphore.

   @param tos   
*/
RM_LIBRARY_IMPORT_EXPORT void RMDeleteTimeoutSemaphore(RMtimeoutSemaphore tos);


/**
   Wait for the semaphore to be released. If after timeout seconds the
   semaphore is still locked the call returns with the value
   RM_TOS_TIMEOUT.  Otherwise if the semaphore is unlocked before
   timeout seconds, the call returns immediately with the value RM_TOS_EVENT.
   A microsec value of 0 means no timeout an this call wait indefinitely.

   @param tos   
   @param microsec      
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMWaitForTimeoutSemaphore(RMtimeoutSemaphore tos, RMuint64 microsec);


/**
   Release the semaphore of releaseCount units.

   @param tos   
   @param releaseCount  
*/
RM_LIBRARY_IMPORT_EXPORT void RMReleaseTimeoutSemaphore(RMtimeoutSemaphore tos, RMuint32 releaseCount);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMTIMEOUTSEMAPHORE_H__
