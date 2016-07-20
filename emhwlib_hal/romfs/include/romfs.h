/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   romfs.h
  @brief  

  <long description>

  @author Julien Soulier
  @date   2004-12-07
*/

#ifndef __ROMFS_H__
#define __ROMFS_H__

/**
   Look for the absolute filename inside the romfs starting at address fs.

   @param pGBus 
   @param fs    
   @param path  
   @param addr  
   @param size  
   @return <ReturnValue>
*/
RMstatus ROMFS_Lookup_File(struct gbus *pGBus, RMuint32 fs, RMascii *filename, RMuint32 *addr, RMuint32 *size);  

#endif // __ROMFS_H__
