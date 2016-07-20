/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmcorepool.h
  @brief

  Implementation of a memory pool

  Not thread safe.

  @author Emmanuel Michon
  @date   2002-06-25
  @ingroup rmcoreapi
*/

#ifndef __RMCOREPOOL_H__
#define __RMCOREPOOL_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup rmcoreapi
 *  @{
 */

typedef struct _RMcorePool *RMcorePool;


/**
   Creates a core pool: consisting on an allocation of a chunk of
   memory cut in boxes valid to store nObjects objects of size
   objectSize.

   The alignment must be the same, or less restrictive RM_MACHINEALIGNMENT

   @param alignment  alignement constraint on the allocated elements.
   @param nObjects number of elements present in the corepool.
   @param objectSize size of each element of the corepool.
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMcorePool RMCreateCorePool(RMalignment alignment,RMuint32 nObjects,RMuint32 objectSize);

/**
   Creates a core pool: consisting on an allocation of a chunk of
   memory cut in boxes valid to store nObjects objects of size
   objectSize.

   The alignment must be the same, or less restrictive RM_MACHINEALIGNMENT

   @param alignment alignement constraint on the allocated elements.
   @param buffer buffer in which the corepool elements are allocated. This buffer will not be
                 RMFreed upon Deletion of the corepool. The user is expected to delete it himself.
   @param areaSize size of the area
   @param objectSize size of the elements which will be allocated by the corepool
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMcorePool RMCreateCorePoolInArea(RMalignment alignment,const RMuint8 *area, 
							   RMuint32 areaSize, RMuint32 objectSize);


/**
   Deletes the corepool.

   If it was obtained through RMCreateCorePool() memory is RMFree()'d.

   All corepool objects must have been RMReturnObjectToCorePool()'d or: RMPanic(). This very
   common message is the equivalent of a memory leak for objects stored in a corepool (pool leaks)

   @param corepool  
*/
RM_LIBRARY_IMPORT_EXPORT void RMDeleteCorePool(RMcorePool corepool);


/**
   Returns a pointer to an unused object in the corepool in *pObject

   Will RMPanic(RM_FATALCOREPOOLOVERFLOW) if no object is left

   @param corepool  
   @param pObject       
*/
RM_LIBRARY_IMPORT_EXPORT void RMBorrowObjectFromCorePool(RMcorePool corepool, void **pObject);


/**
   Notifies the corepool we are done with a given object.

   NOTHING PREVENTS THE USER FROM RETURNING THE SAME POINTER MULTIPLE TIMES, THIS
   WILL HAVE BAD CONSEQUENCES

   (C++ users: if the RMcorePool is used to carry C++ objects you
   may have to manually ``reset'' the object some way so that it looks fresh
   before calling this function)

   @param corepool  
   @param object        
*/
RM_LIBRARY_IMPORT_EXPORT void RMReturnObjectToCorePool(RMcorePool corepool,void *object);


/**
   Returns the number of non-borrowed objects in the corepool

   @param corepool  
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMuint32 RMGetAvailableCountCorePool(RMcorePool corepool);

/// 
/**
   Returns in borrowedOnes an array of borrowed objects, of length *pBorrowedCount

   Caller has to RMMalloc() borrowedOnes before calling to the max size of the pool
   and RMFree() this array after use.

   @param pool  
   @param borrowedOnes  
   @param pBorrowedCount        
*/
RM_LIBRARY_IMPORT_EXPORT void RMGetArrayOfBorrowedOnesCorePool(RMcorePool pool,void **borrowedOnes,RMuint32 *pBorrowedCount);

/**
   Returns the object stored at index. The object can be borrowed or not.

   @param pool  
   @param index 
*/
RM_LIBRARY_IMPORT_EXPORT void *RMGetObjectFromCorePoolByIndex(RMcorePool pool, RMuint32 index);

/**
   Returns the index of the object. The object can be borrowed or not.

   @param pool  
   @param object        
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMuint32 RMGetCorePoolObjectIndex(RMcorePool pool, void *object);

/**
   Returns the max amount object in the corepool.

   @param pool  
   @param object        
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMuint32 RMGetCorePoolMaxObject(RMcorePool pool);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMCOREPOOL_H__
