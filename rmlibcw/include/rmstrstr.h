/*****************************************
 Copyright (c) 2006
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmstrstr.h
  @brief  Implementation of the C String library strstr function

  @author Alan Liddeke
  @date   2006-3-23
  @ingroup libcapi
*/

#ifndef __RMSTRSTR_H__
#define __RMSTRSTR_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup libcapi
 *  @{
 */

/** strstr
 *  
 *  This function implements the same functionality as the C "string.h"
 *  method "strstr".
 *
 *  @param region
 *  @param searchStr 
 */
RMascii* RMSearchAscii(RMascii *region, RMascii *searchStr);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMSTRSTR_H__
