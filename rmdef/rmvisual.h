/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmvisual.h
  @brief  

  long description

  @author Emmanuel Michon
  @date   2003-04-14
*/

#ifndef __RMVISUAL_H__
#define __RMVISUAL_H__

#define PURE_VIRTUAL =0

/* Per conclusion (11/16/2007 rmdef review) */
#define RM_PURE_VIRTUAL =0

//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
#ifdef RM_LIBRARY_SELF_COMPILING
#define RM_LIBRARY_IMPORT_EXPORT __declspec(dllexport)
#else
#define RM_LIBRARY_IMPORT_EXPORT /* used to be: __declspec(dllimport) */
#endif

#ifdef _WINLIB_
#ifdef __cplusplus
#define RM_EXTERN_C extern "C"
#define RM_EXTERN_C_BLOCKSTART extern "C" {
#define RM_EXTERN_C_BLOCKEND }
#else //__cplusplus
#define RM_EXTERN_C
#define RM_EXTERN_C_BLOCKSTART
#define RM_EXTERN_C_BLOCKEND
#endif //__cplusplus
#else //_WINLIB_
#ifdef __cplusplus
#define RM_EXTERN_C extern "C" __declspec(dllexport)
#define RM_EXTERN_C_BLOCKSTART extern "C" __declspec(dllexport) {
#define RM_EXTERN_C_BLOCKEND }
#else //__cplusplus
#define RM_EXTERN_C __declspec(dllexport)
#define RM_EXTERN_C_BLOCKSTART __declspec(dllexport) {
#define RM_EXTERN_C_BLOCKEND }
#endif //__cplusplus
#endif //_WINLIB_
#define inline _inline
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////

#define MaxRMuint32 ((RMuint32)4294967295)
#define MinRMuint32 ((RMuint32)0)

#define MaxRMint32 ((RMint32)2147483647)
#define MinRMint32 ((RMint32)-2147483647-1)

/** 64 bits long unsigned integer */
typedef unsigned __int64 RMuint64;
#define MaxRMuint64 ((RMuint64)18446744073709551615)
#define MinRMuint64 ((RMuint64)0)

/** 64 bits long integer */
typedef __int64 RMint64;
#define MaxRMint64 ((RMint64)9223372036854775807)
#define MinRMint64 ((RMint64)-9223372036854775807-1)

// usage of those is deprecated as of 2007 nov 16, see CodingStyle item C12 
#define F64X "%I64x"
#define F64U "%I64u"
#define F64D "%I64d"

#define RMmustBeEqual(x,y,seed) 
#define RMleftMustBeSmaller(x,y,seed)

#pragma warning(disable:4244)
#pragma warning(disable:4146)

#endif // __RMVISUAL_H__
