/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   rmnames.h
  @brief  Transforms enum types to a string

  @author Julien Soulier
  @date   2001-11-15
  @ingroup rmcoreapi
*/

#ifndef __RMNAMES_H__
#define __RMNAMES_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup rmcoreapi
 *  @{
 */

/** Returns a string describing the error if OUTPUT_ERROR_STRING is defined. */
RM_LIBRARY_IMPORT_EXPORT const RMascii *RMstatusToString (RMstatus error);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMNAMES_H__
