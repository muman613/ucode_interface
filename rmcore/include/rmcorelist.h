/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmcorelist.h

  @brief this is the interface of the core list. It implements the
  basic functionnality to handle a list. The RMlist is based on this
  list.

  @author Julien Soulier
  @date   2002-06-25
   @ingroup rmcoreapi
*/

#ifndef __RMCORELIST_H__
#define __RMCORELIST_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup rmcoreapi
 *  @{
 */

typedef struct _RMcoreList *RMcoreList;

/**
   Entry point on the core list.

   @param void  
   @return the created core list or NULL if the call failed.
*/
RM_LIBRARY_IMPORT_EXPORT RMcoreList RMCreateCoreList(void);


/**
   Delete the previously created list. The list must be empty before
   deleting it.

   @param list the core list 
*/
RM_LIBRARY_IMPORT_EXPORT void RMDeleteCoreList(RMcoreList list);


/**
   Insert an item in the core list at the first place. (complexity = O(1))

   @param list  the core list.
   @param item  the item to insert.
*/
RM_LIBRARY_IMPORT_EXPORT void RMInsertFirstCoreList(RMcoreList list,void *item);


/**
   Insert an item in the core list at the last place. This call steps in all
   elements in the list. (complexity = O(n))

   @param list  the core list.
   @param item  the item to insert.
*/
RM_LIBRARY_IMPORT_EXPORT void RMInsertLastCoreList(RMcoreList list,void *item);


/**
   Remove from the core list the first element. (complexity = O(1))

   @param list  the core list
   @param item  the item removed
   @return RM_OK on success RM_LISTISEMPTY if the core list has no element.
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMRemoveFirstCoreList(RMcoreList list, void **item);


/**
   Remove from the core list the last element. This call steps in all
   elements in the list. (complexity = O(n))

   @param list  the core list
   @param item  the item removed
   @return RM_OK on success RM_LISTISEMPTY if the core list has no element.
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMRemoveLastCoreList(RMcoreList list, void **item);


/**
   Reverse the order for each element in the list. This call steps in all
   elements in the list. (complexity = O(n))

   @param list  the core list.
*/
RM_LIBRARY_IMPORT_EXPORT void RMReverseCoreList(RMcoreList list);


/**
   This function allow the user to enumerate each item from the core
   list. To start the iteration the content of the cookie pointer must
   be NULL.
   (complexity = O(1))

   @param list the core list.  
   @param item the next item found.
   @param cookie *cookie = NULL to start the iteration 
   @return RM_OK on success RM_LISTISEMPTY if the core list has no element, RM_ERROR
   when the iteration is finished
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMGetNextItemCoreList(RMcoreList list, void **item, void **cookie);


/**
   This function is used to remove an element while iterating in the
   element list via RMGetNextItemCoreList. (complexity = O(1))

   @param list the core list 
   @param cookie the cookie value of the last RMGetNextItemCoreList.       
   @return RM_OK on success RM_LISTISEMPTY if the core list has no element, RM_ERROR
   if the cookie is invalid.
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMRemoveCookieItemCoreList(RMcoreList list, void **cookie); 


/**
   This function is used to insert a new element in the list just
   before the last item received by RMGetNextItemCoreList. (complexity = O(1))

   If the cookie comes from a failed call to
   RMGetNextItemList the item is inserted at the end of the list.

   If the user goes on in the RMGetNextItemCoreList() loop he will get the freshly 
   inserted item.

   @param list  the core list
   @param item  the item to insert
   @param cookie the cookie value of the last RMGetNextItemCoreList       
   @return RM_OK on success RM_LISTISEMPTY if the core list has no element, RM_ERROR
   if the cookie is invalid.
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMInsertCookieItemCoreList(RMcoreList list, void *item, void **cookie);

/**
   fill the item argument with the last item in the core
   list. (complexity = O(n))

   @param list  the core list.
   @param item  the last item.
   @return RM_OK on success RM_LISTISEMPTY if the core list has no element.
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMShowLastItemCoreList(RMcoreList list, void **item);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMCORELIST_H__
