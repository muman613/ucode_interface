/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   rmpool.h
  @brief  

  The same as RMcorePool with critical section added.

  @author Julien Soulier
  @date   2002-06-25
  @ingroup rmcoreapi
*/

#ifndef __RMPOOL_H__
#define __RMPOOL_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup rmcoreapi
 *  @{
 */

typedef enum {
	RM_POOL_NONBLOCKING = 0, 
	RM_POOL_BLOCKING
} RMpoolType;

/** type used to handle a thread safe pool */
typedef struct _RMpool *RMpool;

/**
   Creates a pool : consisting on an allocation of a corePool plus 
   a critical section for thread safety.

   @param alignment     
   @param nObjects      
   @param objectSize    
   @param poolType indicates if the RMBorrowObjectFromPool is blocking or not   
   @param pCSops: must provide valid callbacks for correct operation          
   @param pSemops: must provide valid callbacks for correct operation            
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMpool RMCreatePool(RMalignment alignment,RMuint32 nObjects,RMuint32 objectSize, RMpoolType poolType,RMcriticalsectionOps *pCSops,RMsemaphoreOps *pSemops);


/**
   Creates a pool: consisting on an allocation of a corePool plus 
   a critical section for thread safety.
   The area is not allocated inside the call but is passed as parameter.

   @param alignment     
   @param area  
   @param areaSize      
   @param objectSize    
   @param poolType   indicates if the RMBorrowObjectFromPool is blocking or not   
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMpool RMCreatePoolInArea(RMalignment alignment, const RMuint8 *area, RMuint32 areaSize, RMuint32 objectSize, RMpoolType poolType);


/**
   Deletes the pool and all memory associated.

   @param pool  
*/
RM_LIBRARY_IMPORT_EXPORT void RMDeletePool(RMpool pool);


/**
   Returns a pointer to an unused object in the pool in *pObject

   If the pool was created in blocking mode, blocks until an object is available.
   Otherwise, RMPanic(FATALCOREPOOLOVERFLOW) if no object is left.

   @param pool  
   @param pObject       
*/
RM_LIBRARY_IMPORT_EXPORT void RMBorrowObjectFromPool(RMpool pool, void **pObject);


/**
   Notifies the pool we are done with a given object.

   (C++ users: if the RMpool is used to carry C++ objects you
   may have to manually ``reset'' the object some way so that it looks fresh
   before calling this function)

   @param pool  
   @param object        
*/
RM_LIBRARY_IMPORT_EXPORT void RMReturnObjectToPool(RMpool pool,void *object);


/**
   Returns the number of non-borrowed objects in the pool

   @param pool  
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMuint32 RMGetAvailableCountPool(RMpool pool);


/**
   Returns the object stored at index. The object can be borrowed or not.

   @param pool  
   @param index 
*/
RM_LIBRARY_IMPORT_EXPORT void *RMGetObjectFromPoolByIndex(RMpool pool, RMuint32 index);

/**
   Returns the index of the object. The object can be borrowed or not.

   @param pool  
   @param object        
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMuint32 RMGetPoolObjectIndex(RMpool pool, void *object);

/**
   Returns the max amount object in the pool.

   @param pool  
   @param object        
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMuint32 RMGetPoolMaxObject(RMpool pool);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMPOOL_H__
