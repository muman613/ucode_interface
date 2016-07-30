/*****************************************
 Copyright � 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
   @addtogroup basictypes

   These are the Basic Cross Platform (cross-compiler, cross-OS, 
   cross-board, cross-microprocessor) types.
 */

/**
  @file   rmbtypes.h
  @ingroup basictypes
*/


#ifndef __RMBTYPES_H__
#define __RMBTYPES_H__

#include <stdint.h>

RM_EXTERN_C_BLOCKSTART

/** @{ */

/** Generic pointer */
#ifndef NULL
/** pointer not defined */
#define NULL (void *)(0)
#endif // NULL

/**
   Boolean type 

   Choice of unsigned char has been done long ago 
   and might not be that great as of 2011 (might prefer processor word size)
   Strictly speaking, TRUE should be !FALSE. Which means not necessarily 1, for instance, in Forth TRUE is -1.
   Do not write: if (x==TRUE). write if (x).
*/
#ifdef CLF_FIX34597
typedef int RMbool;
#else
typedef unsigned char RMbool;
#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif // TRUE

/** 8 bits long unsigned integer */
//typedef unsigned char RMuint8;
typedef uint8_t RMuint8;
/** Maximum value for an 8 bit unsigned integer. */
#define MaxRMuint8 ((RMuint8) 255)
/** Minimum value for an 8 bit unsigned integer. */
#define MinRMuint8 ((RMuint8) 0)

/** 8 bits long integer */
//typedef signed char RMint8;
typedef int8_t RMint8;
/** Maximum value for an 8 bit signed integer. */
#define MaxRMint8 ((RMint8) 127)
/** Minimum value for an 8 bit signed integer. */
#define MinRMint8 ((RMint8) -128)

/** 16 bits long unsigned integer */
//typedef unsigned short RMuint16;
typedef uint16_t RMuint16;
/** Maximum value for a 16 bit unsigned integer. */
#define MaxRMuint16 ((RMuint16)65535)
/** Minimum value for a 16 bit unsigned integer. */
#define MinRMuint16 ((RMuint16)0)

/** 16 bits long integer */
//typedef          short RMint16;
typedef int16_t RMint16;
/** Maximum value for a 16 bit signed integer. */
#define MaxRMint16 ((RMint16)32767)
/** Minimum value for a 16 bit signed integer. */
#define MinRMint16 ((RMint16)-32768)

typedef uint32_t RMuint32;
typedef int32_t RMint32;

// #if (defined __SIZEOF_LONG__ && __SIZEOF_LONG__==8) || (defined __LP64__ && __LP64__==1) 
// /*
  // partial support of 64bit compilers (bug#8634)
// 
  // __SIZEOF_LONG__ is not consistently defined between gcc versions.
// 
  // Use gcc -dM -E - < /dev/null 
  // to troubleshoot.
// 
  // still, having sizeof(long)==8 does not necessarily
  // imply sizeof(int)==4 but that's enforced in check_rmdef().
// */
// typedef unsigned int RMuint32;
// typedef          int RMint32;
// #else
// typedef unsigned long RMuint32;
// typedef          long RMint32;
// #endif

/** floating point number */
typedef double RMreal;

/** 7 bit us-ascii character */
#ifdef CLF_FIX34597
/*
  would have preferred

  typedef signed char RMascii;

  next line, but doing so breaks LARGE quantities of code (build with warning=error).
 */
typedef char RMascii;
#else
typedef char RMascii;
#endif

/** @} */

RM_EXTERN_C_BLOCKEND

#endif // __RMBTYPES_H__
