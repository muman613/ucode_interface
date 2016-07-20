/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmstatustostring.h
  @brief  Transforms an error code to a string

  @author Emmanuel Michon
  @date   2002-11-07
  @ingroup rmcoreapi
*/

#ifndef __RMSTATUSTOSTRING_H__
#define __RMSTATUSTOSTRING_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup rmcoreapi
 *  @{
 */

/** Returns the error as a human-readable string */
RM_LIBRARY_IMPORT_EXPORT const RMascii *RMstatusToString (RMstatus error);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMSTATUSTOSTRING_H__
