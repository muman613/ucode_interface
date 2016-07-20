#ifndef __DIRECTPOOL_H__
#define __DIRECTPOOL_H__

#include <linux/wait.h>

#include "gbus.h"

#define MAXDMAPOOL 32
#define MAXAREABUFFERCOUNT (1024)

struct buffer_info {
	unsigned long area_buffer_index; 
	atomic_t ref_count;
	void *addr;

	unsigned long bus_addr;

	unsigned long next_free;
};

struct kdmapool_address {
	void *addr;
	unsigned long used;

	unsigned long bus_addr;

};

struct kdmapool {
	unsigned char *area;

	unsigned char *user_addr;

	unsigned long log2_buffersize;
	struct buffer_info *buf_info;
        spinlock_t lock;
	unsigned long buffercount;
	unsigned long buffersize;
	atomic_t available_buffer_count;
	wait_queue_head_t queue;
	unsigned long first_free;
	unsigned long last_free;
};
#endif /* __DIRECTPOOL_H__ */

