/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   rmcriticalsections.h
  @ingroup libcapi
  @brief  Defines the API to manipulate critical section.

  A critical section is a section of code you want to protect 
  against simultaneous execution by two different threads.
  
  At the beginning, call RMEnterCriticalSection
  At the end, call RMLeaveCriticalSection
  
  __SUBTILITY__ A thread can enter a critical section it owns
  more than once (example: recursion). Thus, critical sections include
  a nesting counter to keep track of recursion level.
  
  A critical section is equivalent to a mutex with recursion (primitive on
  certain OS).
  
  The situation where RMEnterCriticalSection/RMLeaveCriticalSection calls
  are unbalanced is inconsistent.
  Especially, if you run RMLeaveCriticalSection, that's because you called
  RMEnterCriticalSection first. Thus, you can't call RMLeaveCriticalSection
  on a critical section you don't own, and this causes a RMPanic with:
  RM_ERRORINCONSISTENTCRITICALSECTIONCALL.
  
  @author Emmanuel Michon
  @date   2001-01-26
*/

#ifndef __RMCRITICALSECTIONS_H__
#define __RMCRITICALSECTIONS_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup libcapi
 *  @{
 */

/**
   Creates a new critical section object and returns a handle to it.

   @return handle to the newly created critical section.
*/
RM_LIBRARY_IMPORT_EXPORT RMcriticalsection RMCreateCriticalSection(void);

#define MAX_PRIMITIVE_CRITICALSECTION_SIZE 24

/// 
/**
   Creates a new critical section object at the specified position p.

   The size of the operating system critical section must 
   not exceed MAX_PRIMITIVE_CRITICALSECTION_SIZE.
   
   Such a critical section must be deleted with RMPlacementDeleteCriticalSection().
   
   @param p     
   @return points to the same address as p...
*/
RM_LIBRARY_IMPORT_EXPORT RMcriticalsection RMPlacementCreateCriticalSection(RMuint8 *p);

/**
   Deletes an existing critical section.

   Unpredictable result if the critical section is in use (owned).

   @param lpCriticalSection     
*/
RM_LIBRARY_IMPORT_EXPORT void RMDeleteCriticalSection(RMcriticalsection lpCriticalSection);

/// 
/**
   Deletes an existing critical section obtained through RMPlacementCreateCriticalSection().

   Unpredictable result if the critical section is in use (owned).

   @param lpCriticalSection     
*/
RM_LIBRARY_IMPORT_EXPORT void RMPlacementDeleteCriticalSection(RMcriticalsection lpCriticalSection);


/**
   If the critical section is not owned, make it ours and enter immediately.

   If the critical section is owned by us, enter immediately and count nesting.

   If the critical section is owned by another thread, wait infinitely 
   until it's not owned anymore.

   @param lpCriticalSection     
*/
RM_LIBRARY_IMPORT_EXPORT void RMEnterCriticalSection(RMcriticalsection lpCriticalSection);


/**
   Leaves the critical section we are in. Must match a balanced RMEnterCriticalSection.

   @param lpCriticalSection     
*/
RM_LIBRARY_IMPORT_EXPORT void RMLeaveCriticalSection(RMcriticalsection lpCriticalSection);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMCRITICALSECTIONS_H__
