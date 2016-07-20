/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   kdmapool.h
  @brief  

  long description

  @author Julien Soulier
  @date   2003-02-25
*/

#ifndef __KDMAPOOL_H__
#define __KDMAPOOL_H__

int kdmapool_init(struct llad *h);
void kdmapool_deinit(struct llad *h);
long kdmapool_check_valid(struct llad *h, unsigned long dmapool_id);
long kdmapool_check_opened(struct llad *h, unsigned long dmapool_id);
int kdmapool_open(struct llad *h, void *area, unsigned long buffercount, unsigned long buffersize);
int kdmapool_close(struct llad *h, unsigned long dmapool_id);
int kdmapool_reset(struct llad *h, unsigned long dmapool_id);
int kdmapool_mmap(struct llad *h, struct kc_vm_area_struct *vma, unsigned long dmapool_id,unsigned long start,int size,struct kc_pgprot_t *prot);
int kdmapool_getinfo(struct llad *h, unsigned long dmapool_id, unsigned long *size);
unsigned char *kdmapool_getbuffer(struct llad *h, unsigned long dmapool_id, unsigned long *timeout_us);
unsigned long kdmapool_get_available_buffer_count(struct llad *h, unsigned long dmapool_id);
unsigned long kdmapool_get_bus_address(struct llad *h, unsigned long dmapool_id, unsigned char *ptr, unsigned long size);
unsigned char *kdmapool_get_virt_address(struct llad *h, unsigned long dmapool_id, unsigned long bus_addr, unsigned long size);
int kdmapool_acquire(struct llad *h, unsigned long dmapool_id, unsigned long bus_address);
int kdmapool_release(struct llad *h, unsigned long dmapool_id, unsigned long bus_address);

#endif // __KDMAPOOL_H__
