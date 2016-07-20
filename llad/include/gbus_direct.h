/*****************************************
 Copyright © 2004-2005
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   gbus_direct.h
  @brief  

  Most standalone code actually accesses gbus a trivial way

  @author Emmanuel Michon
  @date   2005-03-02
*/

#ifndef __GBUS_DIRECT_H__
#define __GBUS_DIRECT_H__

#ifdef UNDER_CE

#include <windows.h>
#include <oal.h>

static inline struct gbus *gbus_open(struct llad *h)
{
	return (struct gbus *) 1;
}

static inline void gbus_close(struct gbus *h)
{
	return;
}

static inline RMuint8 gbus_read_uint8 (struct gbus *h, RMuint32 byte_address)
{
	volatile RMuint8 *p;
	if (byte_address & 0x20000000)
		byte_address -= 0x14000000;
	p = (volatile RMuint8 *)OALPAtoUA(byte_address);
	return (RMuint8)(*p);
}

static inline RMuint16 gbus_read_uint16(struct gbus *h, RMuint32 byte_address)
{
	volatile RMuint16 *p;
	if (byte_address & 0x20000000)
		byte_address -= 0x14000000;
	p = (RMuint16 *)OALPAtoUA(byte_address);
	return (RMuint16)(*p);
}

static inline RMuint32 gbus_read_uint32(struct gbus *h, RMuint32 byte_address)
{
	volatile RMuint32 *p;
	if (byte_address & 0x20000000)
		byte_address -= 0x14000000;
	p = (RMuint32 *)OALPAtoUA(byte_address);
	return (RMuint32)(*p);
}

static inline void gbus_write_uint8 (struct gbus *h, RMuint32 byte_address, RMuint8  data)
{
	volatile RMuint8 *p;
	if (byte_address & 0x20000000)
		byte_address -= 0x14000000;
	p = (RMuint8 *)OALPAtoUA(byte_address);
	*p = data;
}

static inline void gbus_write_uint16(struct gbus *h, RMuint32 byte_address, RMuint16 data)
{
	volatile RMuint16 *p;
	if (byte_address & 0x20000000)
		byte_address -= 0x14000000;
	p = (RMuint16 *)OALPAtoUA(byte_address);
	*p = data;
}

static inline void gbus_write_uint32(struct gbus *h, RMuint32 byte_address, RMuint32 data)
{
	volatile RMuint32 *p;
	if (byte_address & 0x20000000)
		byte_address -= 0x14000000;
	p = (RMuint32 *)OALPAtoUA(byte_address);
	*p = data;
}

static inline void gbus_read_data8 (struct gbus *h, RMuint32 byte_address, RMuint8  *data, RMuint32 count)
{
	RMuint32 i;

	for (i=0 ; i<count ; i++) {
		*(data+i) = gbus_read_uint8(h, byte_address + i);
	}
}

static inline void gbus_read_data16(struct gbus *h, RMuint32 byte_address, RMuint16 *data, RMuint32 count)
{
	RMuint32 i;

	for (i=0 ; i<count ; i++) {
		*(data+i) = gbus_read_uint16(h, byte_address + 2*i);
	}
}

static inline void gbus_read_data32(struct gbus *h, RMuint32 byte_address, RMuint32 *data, RMuint32 count)
{
	RMuint32 i;

	for (i=0 ; i<count ; i++) {
		*(data+i) = gbus_read_uint32(h, byte_address + 4*i);
	}
}

static inline void gbus_write_data8 (struct gbus *h, RMuint32 byte_address, RMuint8  *data, RMuint32 count)
{
	RMuint32 i;

	for (i=0 ; i<count ; i++) {
		gbus_write_uint8(h, byte_address + i, *(data+i));
	}
}

static inline void gbus_write_data16(struct gbus *h, RMuint32 byte_address, RMuint16 *data, RMuint32 count)
{
	RMuint32 i;

	for (i=0 ; i<count ; i++) {
		gbus_write_uint16(h, byte_address + 2*i, *(data+i));
	}
}

static inline void gbus_write_data32(struct gbus *h, RMuint32 byte_address, RMuint32 *data, RMuint32 count)
{
	RMuint32 i;

	for (i=0 ; i<count ; i++) {
		gbus_write_uint32(h, byte_address + 4*i, *(data+i));
	}
}

static inline RMstatus gbus_lock_area(struct gbus *h, RMuint32 *region_index, RMuint32 byte_address, RMuint32 size, RMuint32 *region_count, RMuint32 *offset)
{
	*region_index = byte_address;
	*region_count = 1;
	*offset = 0;

	return RM_OK;
}

static inline RMstatus gbus_get_locked_area(struct gbus *h, RMuint32 byte_address, RMuint32 size, RMuint32 *region_index, RMuint32 *region_count, RMuint32 *offset)
{
	*region_index = byte_address;
	*region_count = 1;
	*offset = 0;

	return RM_OK;
}

static inline RMstatus gbus_unlock_region(struct gbus *h, RMuint32 region_index)
{
	return RM_OK;
}

static inline RMuint8 *gbus_map_region(struct gbus *h, RMuint32 region_index)
{
	return (RMuint8 *) region_index;
}

#else

static inline struct gbus *gbus_open(struct llad *h)
{
	return (struct gbus *) 1;
}

static inline void gbus_close(struct gbus *h)
{
	return;
}



/*
  gbus_read/write_uint() are real functions implemented and exported by the kernel
 */
RMuint8  gbus_read_uint8 (struct gbus *h, RMuint32 byte_address);
RMuint16 gbus_read_uint16(struct gbus *h, RMuint32 byte_address);
RMuint32 gbus_read_uint32(struct gbus *h, RMuint32 byte_address);
void gbus_write_uint8 (struct gbus *h, RMuint32 byte_address, RMuint8  data);
void gbus_write_uint16(struct gbus *h, RMuint32 byte_address, RMuint16 data);
void gbus_write_uint32(struct gbus *h, RMuint32 byte_address, RMuint32 data);


static inline void gbus_read_data8 (struct gbus *h, RMuint32 byte_address, RMuint8  *data, RMuint32 count)
{
	RMuint32 i;

	for (i=0 ; i<count ; i++) {
		*(data+i) = gbus_read_uint8(h, byte_address + i);
	}
}

static inline void gbus_read_data16(struct gbus *h, RMuint32 byte_address, RMuint16 *data, RMuint32 count)
{
	RMuint32 i;

	for (i=0 ; i<count ; i++) {
		*(data+i) = gbus_read_uint16(h, byte_address + 2*i);
	}
}

static inline void gbus_read_data32(struct gbus *h, RMuint32 byte_address, RMuint32 *data, RMuint32 count)
{
	RMuint32 i;

	for (i=0 ; i<count ; i++) {
		*(data+i) = gbus_read_uint32(h, byte_address + 4*i);
	}
}

static inline void gbus_write_data8 (struct gbus *h, RMuint32 byte_address, const RMuint8  *data, RMuint32 count)
{
	RMuint32 i;

	for (i=0 ; i<count ; i++) {
		gbus_write_uint8(h, byte_address + i, *(data+i));
	}
}

static inline void gbus_write_data16(struct gbus *h, RMuint32 byte_address, const RMuint16 *data, RMuint32 count)
{
	RMuint32 i;

	for (i=0 ; i<count ; i++) {
		gbus_write_uint16(h, byte_address + 2*i, *(data+i));
	}
}

static inline void gbus_write_data32(struct gbus *h, RMuint32 byte_address, const RMuint32 *data, RMuint32 count)
{
	RMuint32 i;

	for (i=0 ; i<count ; i++) {
		gbus_write_uint32(h, byte_address + 4*i, *(data+i));
	}
}


/*
  these functions are exported by llad.ko
*/

RMstatus gbus_lock_area(struct gbus *h, RMuint32 *region_index, RMuint32 byte_address, RMuint32 size, RMuint32 *region_count, RMuint32 *offset);
/*
  note: gbus_get_locked_area will always return "region_count=1", use gbus_get_page_count_for_region to get the amount of pages in the region
*/
RMstatus gbus_get_locked_area(struct gbus *h, RMuint32 byte_address, RMuint32 size, RMuint32 *region_index, RMuint32 *region_count, RMuint32 *offset);
RMstatus gbus_get_page_count_for_region(struct gbus *h, RMuint32 region_index, RMuint32 *page_count);
RMstatus gbus_unlock_region(struct gbus *h, RMuint32 region_index);



#endif /* UNDER_CE */

#endif /* __GBUS_DIRECT_H__ */
