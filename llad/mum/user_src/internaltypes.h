/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   internaltypes.h
  @brief  

  long description

  @author Julien Soulier
  @date   2003-12-02
*/

#ifndef __INTERNALTYPES_H__
#define __INTERNALTYPES_H__

#define ALLOW_OS_CODE 1

#include "rmdef/rmdef.h"

struct llad {
	int fd;
};

struct gbus {
	int fd;
	RMuint32 region_count;
	RMuint32 region_size;
	RMuint8* base_address;
};

struct dmacpy {
	int fd;
	RMuint32 size;
	RMuint8 *user_buf;
	RMuint32 bus_address;
};

struct dmapool {
	int fd;
	unsigned long id;
	void *user_addr;
	unsigned long size;
};

#endif // __INTERNALTYPES_H__
