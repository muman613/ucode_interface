/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   rmlist.h
  @brief  Implementation of a simple linked list

  No limit to the number of nodes. A RMMalloc happens at each insertion.

  [Implementation detail (informative only): unlike elementary 
  linked-list implementations, RMlist is not directly a 
  pointer to the first node]
  
  This list works with only with one thread consumer and another
  thread producer. If only one thread uses a list, you must use the
  RMcoreList.

  @author Julien Soulier, Emmanuel Michon (reentrancy)
  @date   2001-17-10
  @ingroup rmcoreapi
*/

#ifndef __RMLIST_H__
#define __RMLIST_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup rmcoreapi
 *  @{
 */

/** type used to handle a list */
typedef struct _RMlist *RMlist;

/**
   Creates a list.

   @param pCSops: must provide valid callbacks for correct operation        
   @param pSemops: must provide valid callbacks for correct operation   
   @return the new list
*/
RM_LIBRARY_IMPORT_EXPORT RMlist RMCreateList(RMcriticalsectionOps *pCSops,RMsemaphoreOps *pSemops);

/**
   Deletes a list. It must be empty.

   @param list  the list
*/
RM_LIBRARY_IMPORT_EXPORT void RMDeleteList(RMlist list);


/**
   Inserts at first place. Cannot block.

   @param list the list
   @param item item to insert
*/
RM_LIBRARY_IMPORT_EXPORT void RMInsertFirstList(RMlist list,void *item);


/**
   Inserts at last place. Cannot block.

   @param list the list
   @param item item to insert
*/
RM_LIBRARY_IMPORT_EXPORT void RMInsertLastList(RMlist list,void *item);


/**
   Returns the first element and removes it from the list. 
   Blocks if list is empty.

   @param list the list 
   @param item the removed item
*/
RM_LIBRARY_IMPORT_EXPORT void RMRemoveFirstList(RMlist list, void **item);


/**
   Returns the last element and removes it from the list. 
   Blocks if list is empty.

   @param list the list 
   @param item the removed item
*/
RM_LIBRARY_IMPORT_EXPORT void RMRemoveLastList(RMlist list, void **item);  


/**
   Returns the last element and does not remove it from the list. 
   Does not block.

   @param list the list.
   @param item the last item of the list.
   @return RM_LISTISEMPTY if list is empty.
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMShowLastList(RMlist list, void **item);


/**
   Returns the number of elements stored in the list.

   @param list  
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMuint32 RMGetCountList(RMlist list);


/**
   Reverses the order of the item in the list.

   @param list  
*/
RM_LIBRARY_IMPORT_EXPORT void RMReverseList(RMlist list);


/**
   Iterator function. To start iteration from the beginning cookie
   content must the list itself : *cookie = NULL
   
   @param list  the list
   @param item  the next item found
   @param cookie *cookie = NULL to start iteration       
   @return RM_ERROR when there is no more item.
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMGetNextItemList(RMlist list, void **item, void **cookie);


/**
   Remove the item in the list referenced by cookie. This means the
   item got from the last call to RMGetNextItemList.

   @param list  the list
   @param cookie  cookie from last call to RMGetNextItemList
*/
RM_LIBRARY_IMPORT_EXPORT void RMRemoveCookieItemList(RMlist list, void **cookie);


/**
   Insert the item in the list just before the last item got from
   RMGetNextItemList. If the cookie comes from a failed call to
   RMGetNextItemList the item is inserted at the end of the list.

   If the user goes on in the RMGetNextItemList() loop he will get the freshly 
   inserted item.

   @param list  the list
   @param item  the item to insert
   @param cookie cookie from last call to RMGetNextItemList    
*/
RM_LIBRARY_IMPORT_EXPORT void RMInsertCookieItemList(RMlist list, void *item, void **cookie);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMLIST_H__
