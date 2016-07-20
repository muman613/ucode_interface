 /*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   mum_uk.h
  @brief  

  This file is the part of the mum driver interface
  that is shared between Userland and Kernelland
  
  Defines ioctl numbers and common structures.

  @author Emmanuel Michon
  @date   2002-11-13
*/

#ifndef __MUM_UK_H__
#define __MUM_UK_H__

#define MUM_MAJOR 126
#define MUM_DEVICE_NAME "mum"
#define MUM_VERSION 18


/* IOCTL number definition */

#define MUM_IOCTL_MAGIC 'M'

#define MUM_IOCTL_VERSION_HANDSHAKE            _IOW( MUM_IOCTL_MAGIC,  1, int)
/*
  give to this ioctl a pointer to a `waitable' struct h:
  
  The ioctl() will block until:
  - we reach h.timeout_microsecond, in this case h.mask is updated to zero
  or
  - a signal has been received (^C), in this case h.mask is updated to zero
  or
  - one of the bits of mask has been signalled, in this case h.mask is set to this bit

  timeout_microsecond is in microseconds, but the kernel cannot do finer than
  one timeslice (10000 microseconds on i386).
 */
#define MUM_IOCTL_WAIT                         _IOWR(MUM_IOCTL_MAGIC, 2, struct waitable)
#define MUM_IOCTL_LLAD_ENABLE_INTERRUPT        _IOW( MUM_IOCTL_MAGIC, 3, unsigned long)
#define MUM_IOCTL_LLAD_DISABLE_INTERRUPT       _IOW( MUM_IOCTL_MAGIC, 4, unsigned long)

#define MUM_IOCTL_DEBUG                        _IOWR(MUM_IOCTL_MAGIC, 5, unsigned long long)

#define MUM_IOCTL_LLAD_GET_OPEN_COUNT          _IOR( MUM_IOCTL_MAGIC,  9, unsigned long)
#define MUM_IOCTL_LLAD_GET_CONFIG              _IOW( MUM_IOCTL_MAGIC, 10, struct llad_get_config)
#define MUM_IOCTL_GBUS_READ_UINT8              _IOR( MUM_IOCTL_MAGIC, 11, struct gbus_uint8)
#define MUM_IOCTL_GBUS_READ_UINT16             _IOR( MUM_IOCTL_MAGIC, 12, struct gbus_uint16)
#define MUM_IOCTL_GBUS_READ_UINT32             _IOR( MUM_IOCTL_MAGIC, 13, struct gbus_uint32)
#define MUM_IOCTL_GBUS_READ_DATA8              _IOWR(MUM_IOCTL_MAGIC, 14, struct gbus_data8)
#define MUM_IOCTL_GBUS_READ_DATA16             _IOWR(MUM_IOCTL_MAGIC, 15, struct gbus_data16)
#define MUM_IOCTL_GBUS_READ_DATA32             _IOWR(MUM_IOCTL_MAGIC, 16, struct gbus_data32)
#define MUM_IOCTL_GBUS_WRITE_UINT8             _IOW( MUM_IOCTL_MAGIC, 17, struct gbus_uint8)
#define MUM_IOCTL_GBUS_WRITE_UINT16            _IOW( MUM_IOCTL_MAGIC, 18, struct gbus_uint16)
#define MUM_IOCTL_GBUS_WRITE_UINT32            _IOW( MUM_IOCTL_MAGIC, 19, struct gbus_uint32)
#define MUM_IOCTL_GBUS_WRITE_DATA8             _IOW( MUM_IOCTL_MAGIC, 20, struct gbus_data8)
#define MUM_IOCTL_GBUS_WRITE_DATA16            _IOW( MUM_IOCTL_MAGIC, 21, struct gbus_data16)
#define MUM_IOCTL_GBUS_WRITE_DATA32            _IOW( MUM_IOCTL_MAGIC, 22, struct gbus_data32)
#define MUM_IOCTL_GBUS_GET_REGIONS_INFO        _IOR( MUM_IOCTL_MAGIC, 23, struct gbus_regions_info)
#define MUM_IOCTL_GBUS_LOCK_AREA               _IOWR(MUM_IOCTL_MAGIC, 24, struct gbus_lock_area)
#define MUM_IOCTL_GBUS_UNLOCK_REGION           _IOW( MUM_IOCTL_MAGIC, 25, unsigned long)
#define MUM_IOCTL_GBUS_GET_LOCKED_AREA         _IOWR(MUM_IOCTL_MAGIC, 26, struct gbus_lock_area)

#define MUM_IOCTL_GET_DMA_INFO                 _IOW( MUM_IOCTL_MAGIC, 30, struct mumdmainfo)
#define MUM_IOCTL_LLAD_LOCK                    _IOR( MUM_IOCTL_MAGIC, 31, unsigned long)
#define MUM_IOCTL_LLAD_UNLOCK                  _IO(  MUM_IOCTL_MAGIC, 32)

#define MUM_IOCTL_DMAPOOL_OPEN                 _IOWR(MUM_IOCTL_MAGIC, 33, struct dmapool_dimension)
#define MUM_IOCTL_DMAPOOL_CLOSE                _IOR( MUM_IOCTL_MAGIC, 34, unsigned long)
#define MUM_IOCTL_DMAPOOL_GET_VIRTUAL_ADDRESS  _IOWR(MUM_IOCTL_MAGIC, 35, struct dmapool_userbuffer)
#define MUM_IOCTL_DMAPOOL_GET_BUFFER           _IOWR(MUM_IOCTL_MAGIC, 36, struct dmapool_getbuffer)
#define MUM_IOCTL_DMAPOOL_GET_PHYSICAL_ADDRESS _IOWR(MUM_IOCTL_MAGIC, 37, struct dmapool_userbuffer)
#define MUM_IOCTL_DMAPOOL_ACQUIRE              _IOWR(MUM_IOCTL_MAGIC, 38, struct dmapool_physbuffer)
#define MUM_IOCTL_DMAPOOL_RELEASE              _IOR( MUM_IOCTL_MAGIC, 39, struct dmapool_physbuffer)

/* For brain-dead caches (non DMA consistent), we need those 2 IOCTLS */
#define MUM_IOCTL_FLUSH_CACHE                  _IOW( MUM_IOCTL_MAGIC, 40, struct mumdmainfo)
#define MUM_IOCTL_INVALIDATE_CACHE             _IOW( MUM_IOCTL_MAGIC, 41, struct mumdmainfo)

/* more DMAPOOL ioctl */
#define MUM_IOCTL_DMAPOOL_RESET                _IOWR(MUM_IOCTL_MAGIC, 42, struct dmapool_reset)
#define MUM_IOCTL_DMAPOOL_GET_AVAILABLE_BUFFER_COUNT _IOWR( MUM_IOCTL_MAGIC, 43, struct dmapool_buffercount)

// to map various areas, call mmap with last arg=
#define MUM_MMAP_DMAMASK       0xfff00000
#define MUM_MMAP_DMABASE       0x00100000
#define MUM_MMAP_DMAPOOL       0x00200000
#define MUM_MMAP_DMAPOOL_SHIFT 14
#define MUM_MMAP_PCI_REGION_0  0x00300000


struct mumdmainfo {
	unsigned long bus_addr;
	unsigned long size;
};

struct waitable {
        unsigned long timeout_microsecond; // no way to specify ``infinite'', sorry.
        unsigned long mask;
}; 

struct llad_get_config {
	char *ConfigName;
	unsigned long ConfigNameSize;
};

struct gbus_uint8 {
	unsigned long byte_address;
	unsigned char data;
};

struct gbus_uint16 {
	unsigned long byte_address;
	unsigned short data;
};

struct gbus_uint32 {
	unsigned long byte_address;
	unsigned long data;
};

struct gbus_data8 {
	unsigned long byte_address;
	unsigned char *data;
	unsigned long count;
};

struct gbus_data16 {
	unsigned long byte_address;
	unsigned short *data;
	unsigned long count;
};

struct gbus_data32 {
	unsigned long byte_address;
	unsigned long *data;
	unsigned long count;
};

struct gbus_regions_info {
	unsigned long region_count;
	unsigned long region_size;
};

struct gbus_lock_area {
	unsigned long byte_address;
	unsigned long size;
	unsigned long offset;
	unsigned long region_index;
	unsigned long region_count;
};

struct dmapool_dimension {
	unsigned long buffercount;
	unsigned long buffersize;
	unsigned long dmapool_id;
};

struct dmapool_getbuffer {
	unsigned long dmapool_id;
	unsigned char *ptr;
	unsigned long timeout_microsecond;
};

struct dmapool_buffercount {
	unsigned long dmapool_id;
	unsigned long buffer_count;
};

struct dmapool_userbuffer {
	unsigned long dmapool_id;
	unsigned char *ptr;
	unsigned long size;
	unsigned long physical_address;
};

struct dmapool_physbuffer {
	unsigned long dmapool_id;
	unsigned long physical_address;
};

struct dmapool_reset {
	unsigned long dmapool_id;
	unsigned long acquired_count;
};	

#endif // __MUM_UK_H__
