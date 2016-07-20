/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   minor.h
  See licensing details in LICENSING file  

  long description

  @author Emmanuel Michon
  @date   2001-12-10
*/

#ifndef __MINOR_H__
#define __MINOR_H__

struct pcilike {
	unsigned short vendor;
	unsigned short device;
	unsigned char revisionid;
	unsigned short subsystem_vendor;
	unsigned short subsystem_device;
	unsigned short pci_bus_id;
	unsigned int pci_class;
	unsigned int irq;
	int numberofregions;
	struct region {
		unsigned long physicaladdr;
		unsigned long size;
		unsigned long kernellandaddr; // filled by ioremap()
	} *regions;
};

struct realmagic_region {
	int locked;
	unsigned long size;
	unsigned long base_address;
	unsigned long long last_use;
};

struct realmagic_map {
	unsigned long region_count;
	struct realmagic_region *regions;
	unsigned long long tick;
};

struct realmagic_dmabuffer {
	unsigned long area_buffer_index; 
 	struct kc_atomic_t *refcount;
	unsigned long bus_addr;
	void *addr;
	unsigned long next_available_buffer;
};

struct realmagic_dmapool {
	unsigned long buffercount;
	unsigned long log2_buffersize;
	unsigned char *user_addr;
	struct kc_wait_queue_head_t *buffer_available_queue;
	unsigned long first_available_buffer;
	struct kc_atomic_t *available_buffer_count;
	struct kc_spinlock_t *buffer_lock;
	struct realmagic_dmabuffer *buffers;
};

struct realmagic_address {
	unsigned long bus_addr;
	void *addr;
	unsigned long used;
};

struct realmagicprivate;
typedef RMuint32 (*do_irq_func) (struct realmagicprivate *pR, int irq, struct kc_pt_regs * regs);
typedef void (*set_region_mapping_func) (struct realmagicprivate *pR, int pci_region, int region_idx, unsigned long addr);
typedef unsigned long (*get_region_mapping_func) (struct realmagicprivate *pR, int pci_region, int region_idx);
typedef void (*interrupt_func) (struct realmagicprivate *pR, unsigned long mask);

struct realmagic_opener {
	int mum_id;
	unsigned long open_count;
	unsigned long dmapool_usage_mask;
};

struct realmagicprivate {
	struct kc_devfs_handle_t *devfs_handle;
	struct file_operations *fops;
	struct pcilike pcilikeconfig;
	struct realmagic_map *pci_region_map;

	char *gbus_buf;
	unsigned long gbus_buf_size;
	struct kc_spinlock_t *gbus_lock;
	struct kc_semaphore_t *gbus_buf_sem;

	// PCI case: we need this for pci_alloc_consistent()/pci_free_consistent() (=struct pci_dev *pdev)
	void *hardware_interface_specific_data;
	
	struct kc_spinlock_t *openlock;
	unsigned long total_opencount;
	unsigned long lockbit;

	unsigned long bus_dmabase;
	char *kernellanddmabase;
	
	unsigned long irq_bits;
	struct kc_wait_queue_head_t *irq_queue;

	unsigned long max_dmapool_memory_size;
	unsigned long max_dmabuffer_log2_size;
	unsigned long dmapool_area_buffer_count;
	struct realmagic_address dmapool_area[MAXAREABUFFERCOUNT];
	unsigned long dmapool_usage_mask;
	unsigned long dmapool_mmap_mask;
	struct realmagic_dmapool dmapools[MAXDMAPOOL];

	unsigned long gbus_mask;
	do_irq_func do_irq;
	set_region_mapping_func set_region_mapping;
	get_region_mapping_func get_region_mapping;
	interrupt_func enable_interrupt;
	interrupt_func disable_interrupt;
	
	struct kc_tasklet_struct *tasklet1;
	unsigned long *tasklet_irq_status1;
	unsigned long tasklet_mask1;
	struct kc_tasklet_struct *tasklet2;
	unsigned long *tasklet_irq_status2;
	unsigned long tasklet_mask2;
	
	struct realmagic_opener openers[MAX_OPENERS];
};

extern struct realmagicprivate Rtable[MAXLLAD];

extern struct file_operations minor_fops;

#endif // __MINOR_H__
