/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmmm.h
  @brief  

  Prototypes for usual memory management primitives.
  These prototypes are not implemented in rmdef.

  Alternatively, you can choose:

  - to use rmmemorymanager project to have a self-containted
  implementation

  - or to simply implement these as wrappers around the operating
  system's malloc(), free(), memset(), memcpy(), memcmp().

  @author Emmanuel Michon
  @date   2003-02-11
*/

#ifndef __RMMM_H__
#define __RMMM_H__

RM_EXTERN_C_BLOCKSTART

/// 
/**
   Request of allocation of size zero is considered as a bug.

   @param size  
*/
void *RMMalloc(RMuint32 size);

/// 
/**
   Freeing twice the same ptr is considered as a bug.

   @param ptr   
*/
void RMFree(void *ptr);

/// 
/**
   equivalent of 
   here=RMMalloc(nmemb*size); RMMemset(here,0,nmemb*size); return here;

   @param nmemb 
   @param size  
*/
void *RMCalloc(RMuint32 nmemb,RMuint32 size);
     
/**
   Fills memory at position s with n times the byte c.

   @param s     
   @param c     
   @param n     
*/
void *RMMemset(void *s, RMuint8 c, RMuint32 n);

/**
   man memcpy

   @param dest  
   @param src   
   @param n     
*/
void *RMMemcpy(void *dest,const void *src,RMuint32 n);

/// 
/**
   man memcmp

   @param s1    
   @param s2    
   @param n     
*/
RMint32 RMMemcmp(const void *s1, const void *s2,RMuint32 n);

/**
   man realloc

   @param ptr    
   @param size    
*/
void *RMRealloc(void *ptr, RMuint32 size);

RM_EXTERN_C_BLOCKEND

#endif // __RMMM_H__
