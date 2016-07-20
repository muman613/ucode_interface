/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   rmqueue.h
  @brief  Blocking FIFO queue

  This implements a thread-safe blocking FIFO queue.

  The maximum number of items stored in the queue maxItems is specified at
  creation time. Items are generic pointers.

  Removing functions are blocking until one item is available in the queue.
  
  Inserting functions are blocking if the number of items stored in
  the queue is maxItems.

  Guaranteed to work in the following scenario:
  - only one thread producing.
  - only one thread consuming.

  Multiple consumers, multiple producers, schemes are not heavily tested.

  @author Julien Soulier, Emmanuel Michon
  @date   2001-02-07
  @ingroup rmcoreapi
*/

#ifndef __RMQUEUE_H__
#define __RMQUEUE_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup rmcoreapi
 *  @{
 */

typedef struct _RMqueue *RMqueue;

/// 
/**
   Creates a queue

   @param maxItems      
   @param pCSops: must provide valid callbacks for correct operation                
   @param pSemops: must provide valid callbacks for correct operation               
   @return a handle to the RMqueue.
*/
RMqueue RMCreateQueue(RMuint32 maxItems,RMcriticalsectionOps *pCSops,RMsemaphoreOps *pSemops);

/// 
/**
   Deletes the queue and frees all allocated memory.
   It is under the responsibility of the user not to free
   the queue when a thread is blocked on Read/Write operation.

   It must be empty or RMPanic.

   @param queue 
*/
RM_LIBRARY_IMPORT_EXPORT void RMDeleteQueue(RMqueue queue);

/// 
/**
   Adds an item in the queue at the first place.
   Blocking call if queue is full.

   @param queue 
   @param item   
*/
RM_LIBRARY_IMPORT_EXPORT void RMInsertFirstQueue(const RMqueue queue, void * item);

/// 
/**
   Adds an item in the queue at the last place.
   Blocking call if queue is full.

   @param queue 
   @param item   
*/
RM_LIBRARY_IMPORT_EXPORT void RMInsertLastQueue(const RMqueue queue, void * item);

/// 
/**
   Gets the last item of the queue and removes it.
   Blocking call if queue is empty.

   @param queue 
   @param item   
*/
RM_LIBRARY_IMPORT_EXPORT void RMRemoveFirstQueue(const RMqueue queue, void **item);

/// 
/**
   Gets the last item of the queue and removes it.
   Blocking call if queue is empty.

   @param queue 
   @param item   
*/
RM_LIBRARY_IMPORT_EXPORT void RMRemoveLastQueue(const RMqueue queue, void **item);

/**
   This function allow the user to enumerate each item from the 
   queue. To start the iteration the content of the cookie pointer must
   be NULL.

   @param queue the core queue.  
   @param item the next item found.
   @param cookie *cookie = queue to start the iteration 
   @return RM_OK on success, RM_QUEUEENDS if *cookie is already the last item, RM_ERROR
   when the iteration is finished
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMGetNextItemQueue(RMqueue queue, void **item, void **cookie);


/**
   This functions is udes to remove an element while iterating in the
   element queue via RMGetNextItemQueue. (complexity = O(1))

   If cookie is set to bogus values you will RMPanic()

   @param queue the core queue 
   @param cookie the cookie value of the last RMGetNextItemQueue.       
*/
RM_LIBRARY_IMPORT_EXPORT void RMRemoveCookieItemQueue(RMqueue queue, void **cookie);

/**
   Insert the item in the queue just before the last item got from
   RMGetNextItemQueue. If the cookie comes from a failed call to
   RMGetNextItemQueue the item is inserted at the end of the queue.

   If the user goes on in the RMGetNextItemQueue() loop he will get the freshly 
   inserted item.

   If cookie is set to bogus values you will RMPanic()
   Blocking call when queue is full.

   @param queue  the queue
   @param item  the item to insert
   @param cookie cookie from last call to RMGetNextItemQueue    
*/
RM_LIBRARY_IMPORT_EXPORT void RMInsertCookieItemQueue(RMqueue queue,void *item,void **cookie);

/// 
/**
   Shows the last item of the queue. Do not remove it from the queue.
   Non-blocking call.

   @param queue 
   @param item  
   @return RM_OK on success, other if empty
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMShowLastQueue(const RMqueue queue, void **item);

/// 
/**
   Shows the first item of the queue. Do not remove it from the queue.
   Non-blocking call.

   @param queue 
   @param item  
   @return RM_OK on success, other if empty
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMShowFirstQueue(const RMqueue queue, void **item);

/// 
/**
   Shows the last item of the queue. Do not remove it from the queue.
   Blocking call.

   @param queue 
   @param item  
*/
RM_LIBRARY_IMPORT_EXPORT void RMBlockingShowLastQueue(const RMqueue queue, void **item);

///
/**
   If there are many consumers on the queue, using this call
   is of course dangerous but otherwise, it works pretty well.

   @param queue the queue
   @returns the number of items in the queue.
 */
RM_LIBRARY_IMPORT_EXPORT RMuint32 RMGetCountQueue (const RMqueue queue);

///
/**
   @param queue the queue
   @returns the max number of items in the queue.
 */
RM_LIBRARY_IMPORT_EXPORT RMuint32 RMGetMaxCountQueue (const RMqueue queue);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMQUEUE_H__
