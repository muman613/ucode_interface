/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmcorequeue.h
  @brief  

  This implementation, in the general case, is not thread safe except

  - if one thread uses RMInsertFirstCoreQueue() and another thread uses
  RMRemoveLastCoreQueue() and queue is not full XXX make this clear! hack

  @author Emmanuel Michon
  @date   2002-06-25
  @ingroup rmcoreapi
*/

#ifndef __RMCOREQUEUE_H__
#define __RMCOREQUEUE_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup rmcoreapi
 *  @{
 */

typedef struct _RMcoreQueue *RMcoreQueue;

/// 
/**
   Creates a corequeue

   @param maxItems : maximum number of items
   @return handle to the corequeue
*/
RM_LIBRARY_IMPORT_EXPORT RMcoreQueue RMCreateCoreQueue(RMuint32 maxItems);

/// 
/**
   Deletes the corequeue 

   It must be empty or RMPanic.

   @param corequeue 
*/
RM_LIBRARY_IMPORT_EXPORT void RMDeleteCoreQueue(RMcoreQueue corequeue);

/// 
/**
   Adds an item in the corequeue at the first place.

   @param corequeue     
   @param item  
   @return RM_OK on success, other if full
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMInsertFirstCoreQueue(const RMcoreQueue corequeue, void * item);

/// 
/**
   Adds an item in the corequeue at the last place.

   @param corequeue     
   @param item  
   @return RM_OK on success, other if full
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMInsertLastCoreQueue(const RMcoreQueue corequeue, void * item);

/// 
/**
   Gets the last item of the corequeue and removes it.

   @param corequeue     
   @param item  
   @return RM_OK on success, other if empty
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMRemoveFirstCoreQueue(const RMcoreQueue corequeue, void **item);

/// 
/**
   Gets the last item of the corequeue and removes it.

   @param corequeue     
   @param item  
   @return RM_OK on success, other if empty
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMRemoveLastCoreQueue(const RMcoreQueue corequeue, void **item);

/**
   This function allows the user to enumerate each item from the 
   corequeue. To start the iteration the content of the cookie pointer must
   be NULL.

   @param corequeue the core corequeue.  
   @param item the next item found.
   @param cookie *cookie = corequeue to start the iteration 
   @return RM_OK on success, other if iteration is over
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMGetNextItemCoreQueue(RMcoreQueue corequeue, void **item, void **cookie);


/**
   This functions is used to remove an element while iterating in the
   element corequeue via RMGetNextItemCoreQueue(). cookie is left pointing
   to the next queue item.

   @param corequeue the core corequeue 
   @param cookie the cookie value of the last RMGetNextItemCoreQueue.       
   @return RM_OK on success, other if cookie is invalid
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMRemoveCookieItemCoreQueue(RMcoreQueue corequeue, void **cookie);

/**
   This function is used to insert a new element in the queue just
   before the last item received by RMGetNextItemCoreQueue. (complexity = O(1))

   If the cookie comes from a failed call to
   RMGetNextItemQueue the item is inserted at the end of the list.

   If the user goes on in the RMGetNextItemCoreQueue() loop he will get the freshly 
   inserted item.

   @param queue  the core queue
   @param item  the item to insert
   @param cookie the cookie value of the last RMGetNextItemCoreQueue       
   @return RM_OK on success, other on error
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMInsertCookieItemCoreQueue(RMcoreQueue corequeue, void *item, void **cookie);

/// 
/**
   Shows the last item of the corequeue. Do not remove it from the corequeue.

   @param corequeue 
   @param item   
   @return RM_OK on success, other if empty
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMShowLastCoreQueue(const RMcoreQueue corequeue, void **item);

/// 
/**
   Shows the first item of the corequeue. Do not remove it from the corequeue.

   @param corequeue 
   @param item   
   @return RM_OK on success, other if empty
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMShowFirstCoreQueue(const RMcoreQueue corequeue, void **item);

///
/**
   @param corequeue the corequeue
   @returns the number of items in the corequeue
 */
RM_LIBRARY_IMPORT_EXPORT RMuint32 RMGetCountCoreQueue (const RMcoreQueue corequeue);

///
/**
   @param corequeue the corequeue
   @returns the max number of items in the corequeue
 */
RM_LIBRARY_IMPORT_EXPORT RMuint32 RMGetMaxCountCoreQueue (const RMcoreQueue corequeue);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMCOREQUEUE_H__
