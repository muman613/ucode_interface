/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmrandom.h
  @brief  

  Implements the C standard library pseudo-random number generator.

  @author Emmanuel Michon
  @date   2002-12-06
  @ingroup libcapi
*/

#ifndef __RMRANDOM_H__
#define __RMRANDOM_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup libcapi
 *  @{
 */

/**
   returns a random real with uniform law in the
   interval [0.0, 1.0[.

   The implementation should call a random number
   generator initializer at first call, so that two
   runs of the program do not generate the same output.

   The use of this function is not restricted.
       
   @return ReturnValue
*/
RM_LIBRARY_IMPORT_EXPORT RMreal RMRandom(void);

/**
   returns a random integer with a uniform law in
   the interval [0, max[.
   
   This function must not return the same results 
   during two different runs of the same program.

   The use of this function is not restricted.

   @param max
   @return ReturnValue
 */
RM_LIBRARY_IMPORT_EXPORT RMuint32 RMIntRandom(RMuint32 max);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMRANDOM_H__
