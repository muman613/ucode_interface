/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   rmnonascii.h
  @brief  Describes the API to manipulate Unicode strings.

  @author Mathieu Lacage
  @date   2001-02-08
  @ingroup libcapi
*/

#ifndef __RMNONASCII_H__
#define __RMNONASCII_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup libcapi
 *  @{
 */

/**
   Converts a 7 bit ascii string to a nonAscii string.
   The result is NULL if the input ascii string is
   not a 7-bit ascii string.
   The result must be freed with RMFreeNonAscii
 */
RM_LIBRARY_IMPORT_EXPORT RMnonAscii *RMnonAsciiFromAscii (const RMascii *string);

/**
   Converts a non ascii string to a 7 bit ascii string if possible.
   The result must be freed with RMFreeAscii.
 */
RM_LIBRARY_IMPORT_EXPORT RMascii *RMnonAsciiToAscii (const RMnonAscii *string);

/**
   Frees a nonAscii string returned by the function above.
 */
RM_LIBRARY_IMPORT_EXPORT void RMFreeNonAscii (RMnonAscii *string);

/**
   @param string
   @returns a copy of the input string which must be 
            freed with RMFreeNonAscii.
 */
RM_LIBRARY_IMPORT_EXPORT RMnonAscii *RMMallocAndDuplicateNonAscii (const RMnonAscii *string);

/**
   @param string a non ascii string.
   @returns the size in bytes of the string buffer.
 */
RM_LIBRARY_IMPORT_EXPORT RMuint32 RMnonAsciiLength (const RMnonAscii *string);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMNONASCII_H__
