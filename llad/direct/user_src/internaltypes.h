/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   internaltypes.h
  @brief  

  <long description>

  @author Julien Soulier
  @date   2005-02-01
*/

#ifndef __INTERNALTYPES_H__
#define __INTERNALTYPES_H__

#define ALLOW_OS_CODE 1

#include "rmdef/rmdef.h"

#define DIRECT_MAX_MMAP_COUNT 512

struct llad {
	int fd;
	RMuint32 kernel_page_size;
};

struct gbus {
	int fd;
	RMuint8 *base_address[DIRECT_MAX_MMAP_COUNT];
	RMuint32 system_page_count[DIRECT_MAX_MMAP_COUNT];
	unsigned long region_count;
	unsigned long region_size;
	RMuint32 kernel_page_size;
};

#endif // __INTERNALTYPES_H__
