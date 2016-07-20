/*****************************************
 Copyright (c) 2006
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmstrcmp.h
  @brief  

  @author Alan Liddeke
  @date   2006-3-23
*/

#ifndef __RMSTRCMP_H__
#define __RMSTRCMP_H__

RM_EXTERN_C_BLOCKSTART

/** strcmp 
 *  
 *  This function implements the same functionality as the C "string.h"
 *  method "strcmp".
 *
 *  @param str1 
 *  @param str2 
 */
int RMMatchAscii(RMascii *str1, RMascii *str2);


/** strncmp 
 *  
 *  This function implements the same functionality as the C "string.h"
 *  method "strncmp".
 *
 *  @param str1 
 *  @param str2 
 *  @param size
 */

int RMMatchNAscii(RMascii *str1, RMascii *str2, RMuint32 size);

RM_EXTERN_C_BLOCKEND

#endif // __RMSTRCMP_H__
