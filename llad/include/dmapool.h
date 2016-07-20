/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   dmapool.h
  @brief  

  describes the api to handle a pool of dma buffers for asynchronous
  data transfer.

  @author Julien Soulier
  @date   2003-02-17
*/

#ifndef __DMAPOOL_H__
#define __DMAPOOL_H__

#include "llad.h"
#include "rmdef/rmdef.h"

struct dmapool;

/**
   Creates a pool of buffercount dma buffers of 2^log2_buffersize
   bytes each.  This implies buffersize is a power of 2 and
   log2_buffersize must be greater or equal than 12. (4KB, page size limit)
   To get the actual total dmapool size call dmapool_get_info.
   If area is not NULL the dmapool is allocated in the area.
   (This is only used in standalone case for no copy transfers)

   @param h     
   @param area
   @param buffercount   
   @param log2_buffersize
*/
struct dmapool *dmapool_open(struct llad *h, void *area, RMuint32 buffercount, RMuint32 log2_buffersize);

/**
   Deletes a pool of dma buffers previously created by dmapool_open

   @param h     
*/
void dmapool_close(struct dmapool *h);

/**
   Resets the dmapool. This makes the dmapool as newly opened.
   Returns the number of buffers still acquired while calling reset.
   The call succeeds only if the return value is 0. 
  
   @param h     
   @return 
*/
RMuint32 dmapool_reset(struct dmapool *h);

/**
   returns an id associated to the dmapool.

   @param h     
   @return 
*/
RMuint32 dmapool_get_id(struct dmapool *h);

/**
   Gets information about the dma buffer pool.
   *size is the total size in bytes of the pool.
 
   @param h     
   @param size  
*/
void dmapool_get_info(struct dmapool *h, RMuint32 *size);

/**
   Returns the virtual address of an available buffer. If no buffer is
   available the call waits at most *timeout_microsecond microseconds
   for an available buffer.  
   If no available was found NULL is returned, otherwise the buffer's
   reference counter is set to one.
   On return *timeout_microsecond is updated with the time left. (a
   value of 0 means timeout was reached)

   @param h     
   @param timeout_microsecond
*/
RMuint8 *dmapool_get_buffer(struct dmapool *h, RMuint32 *timeout_microsecond);

/**
   Returns the number of free buffers in the pool that are ready to be
   got. In a single threaded environnement, a positive value means
   that next get_buffer will return immediately.

   @param h     
   @return
*/
RMuint32 dmapool_get_available_buffer_count(struct dmapool *h);

/**
   Call this function before sending the buffer to the hardware to:
      1) check the virtual address ptr and size are valids,
      2) get the physical address of ptr as the returned value.
      
   if the check fails, return 0 as physical address

   @param h     
   @param ptr   
   @param size  
   @return 
*/
RMuint32 dmapool_get_physical_address(struct dmapool *h, RMuint8 *ptr, RMuint32 size);

/**
   Call this function when receiving a buffer from the hardware to:
      1) check the physical address bus_addr and size are valids,
      2) get the virtual address of bus_addr as the returned value.
      
   if the check fails, return NULL as virtual address

   @param h     
   @param physical_addr
   @param size  
   @return 
*/
RMuint8 *dmapool_get_virtual_address(struct dmapool *h, RMuint32 physical_addr, RMuint32 size);

/**
   Increments the reference counter of the buffer "owning" the physical
   address physical_address. 

   @param h     
   @param physical_address      
*/
RMstatus dmapool_acquire(struct dmapool *h, RMuint32 physical_address);

/**
   Decrements the reference counter of the buffer "owning" the physical
   address physical_address. Once the reference counter is 0, the
   buffer becomes available for next dmapool_get_buffer call.

   @param h     
   @param physical_address      
*/
RMstatus dmapool_release(struct dmapool *h, RMuint32 physical_address);

/**
   Flush the cache for the given physical address and size parameters

   @param h 
   @param physical_address
   @param size
*/
void dmapool_writeback_cache(struct dmapool *h, RMuint32 physical_address, RMuint32 size);

/**
   Invalidate the cache for the given physical address and size parameters

   @param h 
   @param physical_address
   @param size
*/
void dmapool_invalidate_cache(struct dmapool *h, RMuint32 physical_address, RMuint32 size);



#endif // __DMAPOOL_H__
