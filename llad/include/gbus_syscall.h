/*****************************************
 Copyright © 2004-2005
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   gbus_syscall.h
  @brief  
  
  8630 specific --- userland xpu software use this (xtasks, irq handler).
  
  At first, the implementation was syscall-based and very slow, hence
  the name of this file. But we may reenable it for some reason.
  
  Current implem is to use a direct uncached map of gbus at 0 
  (global entry of the xpu TLB).
  
  @author Emmanuel Michon
  @date   2005-03-02
*/

#ifndef __GBUS_SYSCALL_H__
#define __GBUS_SYSCALL_H__

static inline RMuint8  gbus_read_uint8 (struct gbus *h, RMuint32 byte_address)
{
	RMuint32 rc;

	rc=*((volatile RMuint8 *) (byte_address));

	return rc;
}

static inline RMuint16 gbus_read_uint16(struct gbus *h, RMuint32 byte_address)
{
	RMuint32 rc;

	rc=*((volatile RMuint16 *) (byte_address));
	
	return rc;
}

static inline RMuint32 gbus_read_uint32(struct gbus *h, RMuint32 byte_address)
{
	RMuint32 rc;

	rc=*((volatile RMuint32 *) (byte_address));

	return rc;
}

static inline void gbus_write_uint8 (struct gbus *h, RMuint32 byte_address, RMuint8  data)
{
	*((volatile RMuint8 *) (byte_address)) = data;
}

static inline void gbus_write_uint16(struct gbus *h, RMuint32 byte_address, RMuint16 data)
{
	*((volatile RMuint16 *) (byte_address)) = data;
}

static inline void gbus_write_uint32(struct gbus *h, RMuint32 byte_address, RMuint32 data)
{
	*((volatile RMuint32 *) (byte_address)) = data;
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

#endif /* __GBUS_SYSCALL_H__ */
