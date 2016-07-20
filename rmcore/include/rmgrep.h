/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmgrep.h
  @brief  

  This API provides some limited grep functionality.

  @author Emmanuel Michon
  @date   2002-07-25
  @ingroup rmcoreapi
*/

#ifndef __RMGREP_H__
#define __RMGREP_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup rmcoreapi
 *  @{
 */

#define RMGREP_MPEG2_EOS 0xb7
#define RMGREP_MPEG2_FINAL_EOS 0xb9
#define RMGREP_MPEG2_BEGIN_GOP 0xb8
#define RMGREP_MPEG2_PACK_START_CODE 0xba
#define RMGREP_MPEG2_SYSTEM_HEADER_START_CODE 0xbb

typedef enum {
        RMGREP_NOTHING=2963, // never rely on first values
        RMGREP_GOT_00xxxxxx,
        RMGREP_GOT_0000xxxx,
        RMGREP_GOT_000001xx,
} RMGrepStartCode_state;

/// 
/**
   Goes thru the buffer looking for the first startcode (four bytes matching 0x00 0x00 0x01 0xXX).

   If no such sequence is found, returns -1

   If found:
   - *pResult is set to 0xXX
   - *pState is reset to RMGREP_NOTHING
   - the function returns the offset of THE FIRST BYTE FOLLOWING THE SEQUENCE
 
   This function is meant to run properly if, unfortunately, the sequence spans over two
   buffers. For this purpose, the state has to be initialized externally to RMGREP_NOTHING and
   given at each call to RMGrepAnyStartCode.

   @param buf   
   @param size  
   @param pResult       
   @param pState        
   @return ReturnValue
*/
RM_LIBRARY_IMPORT_EXPORT RMint32 RMGrepAnyStartCode(RMuint8 *buf,
						    RMint32 size, 
						    RMuint8 *pResult,
						    RMGrepStartCode_state *pState);

/// 
/**
   Goes thru the buffer looking for the startcode 0x00 0x00 0x01 desiredStartCode
   
   If no such sequence is found, returns -1
   
   If found:
   - *pState is reset to RMGREP_NOTHING
   - the function returns the offset of THE FIRST BYTE FOLLOWING THE SEQUENCE
   
   This function is meant to run properly if, unfortunately, the sequence spans over two
   buffers. For this purpose, the state has to be initialized externally to RMGREP_NOTHING and
   given at each call to RMGrepSpecificStartCode.
   
   @param buf   
   @param size  
   @param desiredStartCode      
   @param pState        
   @return ReturnValue
*/
RM_LIBRARY_IMPORT_EXPORT RMint32 RMGrepSpecificStartCode(RMuint8 *buf,
							 RMint32 size, 
							 RMuint8 desiredStartCode,
							 RMGrepStartCode_state *pState);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMGREP_H__
