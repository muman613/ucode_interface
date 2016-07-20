
/*
  THIS FILE MUST BE KEPT IN SYNC WITH:

  llad/direct/include/direct_uk.h

  NOTE: there should be a way to actually share the same file...
 */

#ifndef __TO_BE_IN_SYNC_WITH_DIRECT_UK_H__
#define __TO_BE_IN_SYNC_WITH_DIRECT_UK_H__

#define DIRECT_MAJOR 126
#define DIRECT_DEVICE_NAME "mum0"

#define DIRECT_IOCTL_WAIT                 2
#define DIRECT_IOCTL_ENABLE_INTERRUPT     3
#define DIRECT_IOCTL_DISABLE_INTERRUPT    4
#define DIRECT_IOCTL_LLAD_GET_CONFIG     10
#define DIRECT_IOCTL_LLAD_GET_OPEN_COUNT 11

#define DIRECT_IOCTL_DMAPOOL_OPEN                  33
#define DIRECT_IOCTL_DMAPOOL_CLOSE                 34
#define DIRECT_IOCTL_DMAPOOL_RESET                 42
#define DIRECT_IOCTL_DMAPOOL_GET_BUFFER            36
#define DIRECT_IOCTL_DMAPOOL_GET_PHYSICAL_ADDRESS  37
#define DIRECT_IOCTL_DMAPOOL_GET_VIRTUAL_ADDRESS   35
#define DIRECT_IOCTL_DMAPOOL_ACQUIRE               38
#define DIRECT_IOCTL_DMAPOOL_RELEASE               39
#define DIRECT_IOCTL_DMAPOOL_WRITEBACK_CACHE       40
#define DIRECT_IOCTL_DMAPOOL_INVALIDATE_CACHE      41
#define DIRECT_IOCTL_DMAPOOL_GET_AVAILABLE_BUFFER_COUNT 43

#define DIRECT_IOCTL_GBUS_READ_UINT8               50
#define DIRECT_IOCTL_GBUS_READ_UINT16              51
#define DIRECT_IOCTL_GBUS_READ_UINT32              52
#define DIRECT_IOCTL_GBUS_READ_DATA8               53
#define DIRECT_IOCTL_GBUS_READ_DATA16              54
#define DIRECT_IOCTL_GBUS_READ_DATA32              55
#define DIRECT_IOCTL_GBUS_WRITE_UINT8              56
#define DIRECT_IOCTL_GBUS_WRITE_UINT16             57
#define DIRECT_IOCTL_GBUS_WRITE_UINT32             58
#define DIRECT_IOCTL_GBUS_WRITE_DATA8              59
#define DIRECT_IOCTL_GBUS_WRITE_DATA16             60
#define DIRECT_IOCTL_GBUS_WRITE_DATA32             61

#define DIRECT_IOCTL_GBUS_LOCK_AREA                70
#define DIRECT_IOCTL_GBUS_GET_LOCKED_AREA          71
#define DIRECT_IOCTL_GBUS_UNLOCK_REGION            72
#define DIRECT_IOCTL_GBUS_GET_REGIONS_INFO         73
#define DIRECT_IOCTL_GBUS_MMAP_REGION              74
#define DIRECT_IOCTL_GBUS_GET_SYSTEM_PAGE_COUNT    75

#define DIRECT_IOCTL_FORCE_ROM_UB                  76

#define DIRECT_IOCTL_WAIT_CHANNELS                 77

#define DIRECT_IOCTL_CACHE_DUMP                    78

#define DIRECT_IOCTL_KERNEL_PAGE_SIZE              79

#define DIRECT_IOCTL_REGION_WRITEBACK_CACHE        80
#define DIRECT_IOCTL_REGION_INVALIDATE_CACHE       81


#define DIRECT_MMAP_CACHED        0x80000000
#define DIRECT_MMAP_MASK          0x7f000000
#define DIRECT_MMAP_DMAPOOL       0x02000000
#define DIRECT_MMAP_REGION        0x03000000
#define DIRECT_MMAP_DMAPOOL_SHIFT 14
#define DIRECT_MMAP_REGION_SHIFT  14

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
	unsigned char __user *data;
	unsigned long count;
};

struct gbus_data16 {
	unsigned long byte_address;
	unsigned short __user *data;
	unsigned long count;
};

struct gbus_data32 {
	unsigned long byte_address;
	unsigned long __user *data;
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

struct gbus_region_count {
	unsigned long region_index;
	unsigned long region_count;
};

struct gbus_user_buffer {
	unsigned long virtual_address;
	unsigned long size;
};

struct waitable {
        unsigned long timeout_microsecond; // no way to specify ``infinite'', sorry.
        unsigned long mask;
}; 

struct wait_channels {
        unsigned long timeout_microsecond;
	unsigned long *channel_array; 
	unsigned long channel_count; /* no more than LLAD_MAX_WAIT_CHANNELS, thanks */
	unsigned long active;
}; 


struct llad_get_config {
	char *ConfigName;
	unsigned long ConfigNameSize;
};

struct kdmapool_dimension {
	unsigned long area;
	unsigned long buffercount;
	unsigned long buffersize;
	unsigned long dmapool_id;
};

struct kdmapool_getbuffer {
	unsigned long dmapool_id;
	unsigned char *ptr;
	unsigned long timeout_microsecond;
};

struct kdmapool_userbuffer {
	unsigned long dmapool_id;
	unsigned char *ptr;
	unsigned long size;
	unsigned long physical_address;
};

struct kdmapool_buffercount {
	unsigned long dmapool_id;
	unsigned long buffer_count;
};

struct kdmapool_physbuffer {
	unsigned long dmapool_id;
	unsigned long physical_address;
};

struct kdmapool_reset {
	unsigned long dmapool_id;
	unsigned long acquired_count;
};



#endif //__TO_BE_IN_SYNC_WITH_DIRECT_UK_H__
