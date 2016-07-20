/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file rmnonasciitype.h
  @ingroup basictypes
*/

/**
   @addtogroup basictypes
   @{ 
 */

#ifndef __RMNONASCIITYPE_H__
#define __RMNONASCIITYPE_H__

#if ((RMCOMPILERID==RMCOMPILERID_GCC) || (RMCOMPILERID==RMCOMPILERID_ARMELF_GCC) || (RMCOMPILERID==RMCOMPILERID_MIPSEL_GCC))

/** This opaque type represents a platform-dependent non-ascii string type.
      - On Linux: this is an ascii string.
      - On WinCE: this is a UTF-16 string (ie: standard winCE unicode string)
      - On other win32 systems: this is either a UTF-16 or a variable-size encoded string,
        depending on how the library was built.
 */
typedef RMuint8 RMnonAscii;
/**
   This macro is a platform-dependent macro which tags strings as being nonascii.
     - On Linux, this just casts normal ascii strings to the non-ascii type
     - On WinCE, this ensures the compiler encodes this string as UTF-16
     - On other win32 systems, this ensures the compiler encodes this string
       as the choosen non-ascii type.
 */
#define RMNONASCII(x) ((RMnonAscii *)(x))

/** @} */

#elif (RMCOMPILERID==RMCOMPILERID_VISUALC)

// ! hack --- this is untested

#ifdef _UNDER_WINCE_
// wince has only unicode APIs.
#define RMNONASCIIBUILD
#endif


#ifdef RMNONASCIIBUILD
#ifndef UNICODE
#define UNICODE
#endif
#ifndef _UNICODE
#define _UNICODE
#endif
typedef RMuint16 RMnonAscii;
#define RMNONASCII(x) L#x

#else 

typedef RMint8 RMnonAscii;
#define RMNONASCII(x) (x)

#endif // RMNONASCIIBUILD

#else
// others not handled
NOTCOMPILABLE
#endif 

#endif // __RMNONASCIITYPE_H__
