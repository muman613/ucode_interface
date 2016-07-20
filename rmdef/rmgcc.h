/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmgcc.h
  @brief  

  long description

  @author Emmanuel Michon
  @date   2003-04-14
*/

#ifndef __RMGCC_H__
#define __RMGCC_H__

#define PURE_VIRTUAL =0

/* Per conclusion (11/16/2007 rmdef review) */
#define RM_PURE_VIRTUAL =0

#define RM_LIBRARY_IMPORT_EXPORT

#ifdef __cplusplus
#define RM_EXTERN_C extern "C"
#define RM_EXTERN_C_BLOCKSTART extern "C" {
#define RM_EXTERN_C_BLOCKEND }
#else // __cplusplus
#define RM_EXTERN_C
#define RM_EXTERN_C_BLOCKSTART
#define RM_EXTERN_C_BLOCKEND
#endif // __cplusplus

/* @{ */

/** maximum 32 bit unsigned integer value. */
#define MaxRMuint32 ((RMuint32)4294967295UL)
/** minimum 32 bit unsigned integer value. */
#define MinRMuint32 ((RMuint32)0UL)

/** maximum 32 bit signed integer value. */
#define MaxRMint32 ((RMint32)2147483647L)
/** minimum 32 bit signed integer value. */
#define MinRMint32 ((RMint32)-2147483647L-1L)

/** 64 bits long unsigned integer */
typedef unsigned long long RMuint64;
/** maximum 64 bit unsigned integer value. */
#define MaxRMuint64 ((RMuint64)18446744073709551615ULL)
/** minimum 64 bit unsigned integer value. */
#define MinRMuint64 ((RMuint64)0ULL)

/** 64 bits long integer */
typedef long long RMint64;
/** maximum 64 bit signed integer value. */
#define MaxRMint64 ((RMint64)9223372036854775807LL)
/** minimum 64 bit signed integer value. */
#define MinRMint64 ((RMint64)-9223372036854775807LL-1LL)

/* @} */

// usage of those is deprecated as of 2007 nov 16, see CodingStyle item C12 
#define F64X "%llx"
#define F64U "%llu"
#define F64D "%lld"

// cause an error at compilation if x!=y. Reason for seed: in C, you cannot typedef multiple times 
#define RMmustBeEqual(x,y,seed)                 \
typedef RMascii XXX ## seed ## LeftIsBiggerNow[(y)-(x)];           \
typedef RMascii XXX ## seed ## LeftIsSmallerNow[(x)-(y)];

#define RMleftMustBeSmaller(x,y,seed)                 \
typedef RMascii XXX ## seed ## LeftIsBiggerNow[(y)-(x)];           

#endif // __RMGCC_H__
