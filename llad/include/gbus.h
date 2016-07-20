/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   gbus.h
  @brief  

  long description

  @author Emmanuel Michon
  @date   2003-01-09
*/

#ifndef __GBUS_H__
#define __GBUS_H__

#include "llad.h"

RM_EXTERN_C_BLOCKSTART

struct gbus;

#if ((defined LLAD_DIRECT) && (! defined LLAD_DECLARATION_ONLY))

#include "gbus_direct.h"

#elif ((defined LLAD_SYSCALL) && (! defined LLAD_DECLARATION_ONLY))

#include "gbus_syscall.h"

#else

/**
   Creates a gbus handle

   @param h     
*/
struct gbus *gbus_open(struct llad *h);

/**
   Deletes a gbus handle

   @param h     
*/
void gbus_close(struct gbus *h);

/**
   Returns the RMuint8 read at address byte_address on gbus.

   In case of error, the function will call RMPanic(RM_FATAL_GBUS) and the
   program should stop immediately

   Similar functions exist for RMuint16 and RMuint32

   @param h     
   @param byte_address  
   @return ReturnValue
*/
RMuint8  gbus_read_uint8 (struct gbus *h, RMuint32 byte_address);
RMuint16 gbus_read_uint16(struct gbus *h, RMuint32 byte_address);
RMuint32 gbus_read_uint32(struct gbus *h, RMuint32 byte_address);

/**
   Writes the given RMuint8 data at address byte_address on gbus.

   In case of error, the function will call RMPanic(RM_FATAL_GBUS) and the
   program should stop immediately

   Similar functions exist for RMuint16 and RMuint32

   @param h     
   @param byte_address  
   @param data  
*/
void gbus_write_uint8 (struct gbus *h, RMuint32 byte_address, RMuint8  data);
void gbus_write_uint16(struct gbus *h, RMuint32 byte_address, RMuint16 data);
void gbus_write_uint32(struct gbus *h, RMuint32 byte_address, RMuint32 data);

/**
   Reads from gbus count records of RMuint8 at byte_address, to be
   stored to the array pointed to by data.

   In case of error, the function will call RMPanic(RM_FATAL_GBUS) and the
   program should stop immediately

   Similar functions exist for RMuint16 and RMuint32

   @param h     
   @param byte_address  
   @param data  
   @param count	
*/
void gbus_read_data8 (struct gbus *h, RMuint32 byte_address, RMuint8  *data, RMuint32 count);
void gbus_read_data16(struct gbus *h, RMuint32 byte_address, RMuint16 *data, RMuint32 count);
void gbus_read_data32(struct gbus *h, RMuint32 byte_address, RMuint32 *data, RMuint32 count);

/**
   Writes to gbus count records of RMuint8 at byte_address, to be 
   read from the array pointed to by data.

   In case of error, the function will call RMPanic(RM_FATAL_GBUS) and the
   program should stop immediately

   Similar functions exist for RMuint16 and RMuint32

   @param h     
   @param byte_address  
   @param data  
   @param count	
*/
void gbus_write_data8 (struct gbus *h, RMuint32 byte_address, const RMuint8  *data, RMuint32 count);
void gbus_write_data16(struct gbus *h, RMuint32 byte_address, const RMuint16 *data, RMuint32 count);
void gbus_write_data32(struct gbus *h, RMuint32 byte_address, const RMuint32 *data, RMuint32 count);

/**
   Locks an area [byte_address , byte_addres + size[ inside the pci
   region. It allows then to map the area in the program address space
   to directly write bytes inside the chip DRAM. This is particulary
   useful for OSD or Frame Buffer.

   On sucess *region_index contains the index of the first region used
   to map the area, and *region_count contains the number of regions
   needed. *offset contains the offset from the base address of the
   region *region_index of byte_address.

   When calling gbus_lock_area with a non 0 *region_index, the call
   will try to lock the area without modifying *region_index, if it
   cannot then the call fails. Otherwise, if *region_index is 0, then
   the call will try to find the first available *region_index to map
   the area. If there is none then the call fails.

   @param h 
   @param region_index 
   @param byte_address 
   @param size 
   @param region_count 
   @param offset 
   @return ReturnValue
*/
RMstatus gbus_lock_area(struct gbus *h, RMuint32 *region_index, RMuint32 byte_address, RMuint32 size, RMuint32 *region_count, RMuint32 *offset);

/**
   Finds if the area has been previously locked with a call to
   gbus_lock_area.  If the area is locked, then the call fills up
   *region_index, *region_count and *offset.  Refer to gbus_lock_area
   for the meaning of these variables.

   @param h     
   @param byte_address       
   @param size  
   @param region_index  
   @param region_count  
   @param offset        
   @return ReturnValue
*/
RMstatus gbus_get_locked_area(struct gbus *h, RMuint32 byte_address, RMuint32 size, RMuint32 *region_index, RMuint32 *region_count, RMuint32 *offset); 

/**
   Unlocks a region mapping obtained thru gbus_lock_area.
   If region_index is invalid returns RM_ERROR, else returns RM_OK.

   @param h     
   @param region_index  
*/
RMstatus gbus_unlock_region(struct gbus *h, RMuint32 region_index);

/**
   Returns the address (in caller address space) of the region
   region_index. Used with gbus_lock_area, it allows one to map a
   portion of cached DRAM inside the caller address space.

   return NULL on error.

   @param h     
   @param region_index  
   @param region_count
*/
RMuint8 *gbus_map_region_cached(struct gbus *h, RMuint32 region_index, RMuint32 region_count);

/**
   Returns the address (in caller address space) of the region
   region_index. Used with gbus_lock_area, it allows one to map a
   portion of DRAM inside the caller address space.

   return NULL on error.

   @param h     
   @param region_index  
   @param region_count
*/
RMuint8 *gbus_map_region(struct gbus *h, RMuint32 region_index, RMuint32 region_count);

/**
   Unmaps previously mapped regions.

   @param h     
   @param address  
   @param size
*/
void gbus_unmap_region(struct gbus *h, RMuint8 *address, RMuint32 size);

/**
   Writeback the cache for the given address and size

   @param h 
   @param virtual_address
   @param size
*/
void gbus_writeback_cache_region(struct gbus *h, RMuint32 virtual_address, RMuint32 size);

/**
   Invalidate the cache for the given address and size

   @param h 
   @param virtual_address
   @param size
*/
void gbus_invalidate_cache_region(struct gbus *h, RMuint32 virtual_address, RMuint32 size);

#endif

RM_EXTERN_C_BLOCKEND

#endif // __GBUS_H__

