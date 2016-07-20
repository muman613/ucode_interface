/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   rmdynamicloader.h
  @brief  Describes the API to load dynamic library.

  @author Emmanuel Michon
  @date   2001-02-08
  @ingroup libcapi
*/

#ifndef __RMDYNAMICLOADER_H__
#define __RMDYNAMICLOADER_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup libcapi
 *  @{
 */

typedef struct _RMdll *RMdll; 

/**
   opens a dynamic library (.dll or .so) for getting symbols inside it.

   @param filename      
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMOpenDynamicLibrary(const RMnonAscii *filename,RMdll *library);


/**
   gets the address of the symbol given as a string in the specified library.

   @param library       
   @param theSymbolString       
   @param theSymbol     
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMGetSymbolFromDynamicLibrary(RMdll library, const RMascii *symbol,void * *theSymbol);


/**
   closes the dynamic library.

   @param library       
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMCloseDynamicLibrary(RMdll library);


/**
   Forges the name of the dll file the module loader will try to access
   from the module name.
   Linux way:   RMDESCRIPTORDECODER becomes rmdescriptordecoder.so 
   Windows way: RMDESCRIPTORDECODER becomes caRMDESCR.dll (case is not important)

   The returned string has to be RMFreeNonAscii'd after usage.

   @param moduleName    
*/
RM_LIBRARY_IMPORT_EXPORT RMnonAscii *RMForgeDLLNameFromModuleName(const RMascii *moduleName);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMDYNAMICLOADER_H__
