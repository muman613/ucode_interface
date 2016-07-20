/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmsprintf.h
  @brief  Implementation of formatted string output

  @author Emmanuel Michon
  @date   2002-12-17
  @ingroup libcapi
*/

#ifndef __RMSPRINTF_H__
#define __RMSPRINTF_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup libcapi
 *  @{
 */

/**
   equivalent to printf but write output in string dest instead of STDOUT.
   No size overflow detection is made.

   @param dest  
   @param fmt   
   @param  ...  
*/
void RMPrintAscii(RMascii *dest, const RMascii *fmt, ...);

/** 
    equivalent to snprintf

    from 'man snprintf'

       The functions snprintf and vsnprintf do not write more  than
       size  bytes (including the trailing '\0').  If the output was truncated
       due to this limit then the return value is  the  number  of  characters
       (not  including the trailing '\0') which would have been written to the
       final string if enough space had been available. Thus, a  return  value
       of  size  or  more means that the output was truncated. (See also below
       under NOTES.)  If an output error is encountered, a negative  value  is
       returned.

    @param dest
    @param size
    @param fmt
    @param ...
    @return number of bytes that should have been written
*/

RMint32 RMPrintNAscii(RMascii *dest, RMuint32 size, const RMascii *fmt, ...);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMSPRINTF_H__
