/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmenv.h
  @brief  

  Implements the C standard library getenv function.

  @author Emmanuel Michon
  @date   2003-02-10
  @ingroup libcapi
*/

#ifndef __RMENV_H__
#define __RMENV_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup libcapi
 *  @{
 */

/// 
/**
   (HACK)
   Gets a pointer to the value of the environment variable var value.

   @param var   
*/
RM_LIBRARY_IMPORT_EXPORT RMascii *RMGetEnv(const RMascii *var);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMENV_H__
