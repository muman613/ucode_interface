/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   dmacpy.h
  @brief  

  @author Julien Soulier
  @date   2003-01-15
*/

#ifndef __DMACPY_H__
#define __DMACPY_H__

#include "llad.h"
#include "rmdef/rmdef.h"

struct dmacpy;

#ifndef LLAD_DIRECT

/**
   Creates a dmacpy handle

   @param h     
*/
struct dmacpy *dmacpy_open(struct llad *h);

/**
   Deletes a dmacpy handle

   @param h     
*/
void dmacpy_close(struct dmacpy *h);

/**
   gives the available dma size and dma physical address.

   @param h     
   @param size
   @param physical_address
   @return 
*/
void dmacpy_get_info(struct dmacpy *h, RMuint32 *size, RMuint32 *physical_address);

/**
   writes size bytes of data array data to position offset bytes in dma buffer.

   @param h     
   @param offset        
   @param data  
   @param size  
*/
void dmacpy_write_data(struct dmacpy *h, RMuint32 offset, RMuint8 *data, RMuint32 size);

/**
   reads size bytes from offset position in dma buffer to data array data.

   @param h     
   @param offset        
   @param data  
   @param size	
*/
void dmacpy_read_data(struct dmacpy *h, RMuint32 offset, RMuint8 *data, RMuint32 size);

#else // LLAD_DIRECT

static inline struct dmacpy *dmacpy_open(struct llad *h)
{
	return (struct dmacpy *) 1;
}

static inline void dmacpy_close(struct dmacpy *h)
{
	return;
}

static inline void dmacpy_get_info(struct dmacpy *h, RMuint32 *size, RMuint32 *physical_address)
{
	size = 0;
	physical_address = 0;
	return;
}

static inline void dmacpy_write_data(struct dmacpy *h, RMuint32 offset, RMuint8 *data, RMuint32 size)
{
	return;
}

static inline void dmacpy_read_data(struct dmacpy *h, RMuint32 offset, RMuint8 *data, RMuint32 size)
{
	return;
}
#endif // LLAD_DIRECT

#endif // __DMACPY_H__
