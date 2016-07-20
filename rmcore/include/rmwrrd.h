/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   rmwrrd.h
  @brief Generic circular buffer with read & write pointers

  Empty when rd==wr

  NON BLOCKING ALGORITHMS, MULTITHREAD SAFE

  @author Emmanuel Michon
  @date   2002-02-18
  @ingroup rmcoreapi
*/

#ifndef __RMWRRD_H__
#define __RMWRRD_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup rmcoreapi
 *  @{
 */

typedef struct tagRMwrrd *RMwrrd;

typedef void *(RMMemcpyLike)(void * const dest, const void *src, RMuint32 n);

/**
   Creates a circular buf from a regular memory area.
   Don't be afraid of WriteF and ReadF, most implementations use RMMemcpy.
   (The kernel land implementation needs to use copy_to_user in Read part so
   we needed a convenient way to do so)

   THREAD SAFETY. When the program is not multithreaded, it is safe to
   give pCSops=(RMcriticalsectionOps *)NULL. Otherwise, give valid callbacks here for correct
   operation. *pCSops should be reachable until destruction.
   
   @param address       
   @param size  
   @param WriteF        
   @param ReadF 
   @param pCSops        
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMwrrd RMCreateWRRD(RMuint8 *address,RMuint32 size,RMMemcpyLike WriteF,RMMemcpyLike ReadF,RMcriticalsectionOps *pCSops);

/// 
/**
   Self explanatory

   @param h     
*/
RM_LIBRARY_IMPORT_EXPORT void RMDeleteWRRD(RMwrrd h);

/// 
/**
   Tries to write source data to the buffer. Does not
   block; return the number of bytes that could actually be written.

   @param h     
   @param sourceData    
   @param desiredWriteLength    
   @return actually written bytes.
*/
RM_LIBRARY_IMPORT_EXPORT RMuint32 RMWriteWRRD(RMwrrd h,RMuint8 *sourceData,RMuint32 desiredWriteLength);

/// 
/**
   Tries to read source data from the buffer. Does not
   block; return the number of bytes that could actually be read.
   
   @param h     
   @param targetData    
   @param desiredReadLength     
   @return actually read bytes.
*/
RM_LIBRARY_IMPORT_EXPORT RMuint32 RMReadWRRD(RMwrrd h,RMuint8 *targetData,RMuint32 desiredReadLength);

/// 
/**
   Report the used bytes count in the buffer at the time of the call.
   Another thread may change it immediately afterwards depending on
   how Write/Read calls are used.

   @param h     
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMuint32 RMReportUsedWRRD(RMwrrd h);
 
/// 
/**
   Reset write and read pointer

   @param h     
*/
RM_LIBRARY_IMPORT_EXPORT void RMResetWRRD(RMwrrd h);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMWRRD_H__
