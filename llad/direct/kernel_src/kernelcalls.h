/*
Copyright (C) 2003  Sigma Designs, Inc.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __KERNELCALLS_H__
#define __KERNELCALLS_H__

#include "gbus.h"

#ifndef TRUE
#define TRUE  1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define kc_logging_copy_to_user(ua,ka,n) (                                      	\
{                                                                               	\
        int rc;                                                                 	\
                                                                                	\
        rc=kc_copy_to_user(ua,ka,n);                                            	\
                                                                                	\
        if (rc!=0) kc_printk("failed copy_to_user (returns %d/%d)\n",rc,(int)n);     	\
                                                                                	\
        rc;                                                                     	\
}                                                                               	\
)

#define kc_logging_copy_from_user(ka,ua,n) (                                    	\
{                                                                               	\
        int rc;                                                                 	\
                                                                                	\
        rc=kc_copy_from_user(ka,ua,n);                                          	\
                                                                                	\
        if (rc!=0) kc_printk("failed copy_from_user (returns %d/%d)\n",rc,(int)n);   	\
                                                                                	\
        rc;                                                                     	\
}                                                                               	\
)

/* the following will never be precised more than this */
struct kc_vm_area_struct;
struct kc_pgprot_t;
struct kc_spinlock_t;
struct kc_semaphore_t;
struct kc_wait_queue_head_t;
struct kc_atomic_t;
struct kc_dma_addr_t;
struct kc_tasklet_struct;
struct kc_page;
struct kc_pt_regs;
struct kc_devfs_handle_t;

// module register/unregister
struct kc_devfs_handle_t *kc_devfs_register(struct kc_devfs_handle_t *dir, const char *name, unsigned int flags, unsigned int major, unsigned int minor, unsigned long mode, void *ops, void *info);
void kc_devfs_unregister(struct kc_devfs_handle_t *de);

//VM
void * kc_vmalloc(unsigned long size);
void kc_vfree(void *addr);

// time
unsigned long kc_jiffies(void);
unsigned long US_TO_JIFFIES(unsigned long u);
unsigned long JIFFIES_TO_US(unsigned long j);
void kc_mdelay(unsigned long n);
void kc_udelay(unsigned long n);
unsigned long kc_gettimems(void);
unsigned long long kc_gettimeus(void);

int kc_printk(const char * fmt, ...);
int kc_sprintf(char * buf, const char * fmt, ...);
int kc_sscanf(const char * buf, const char * fmt, ...);

int kc_remap_page_range(struct kc_vm_area_struct *vma,unsigned long from, unsigned long to, unsigned long size, struct kc_pgprot_t *prot);

//User space com
unsigned long kc_copy_to_user(void *to, const void *from, unsigned long n);
unsigned long kc_copy_from_user(void *to, const void *from, unsigned long n);

// tophalf & tasklet
void kc_tasklet_init(struct kc_tasklet_struct **t,void (*func)(unsigned long), unsigned long data);
void kc_tasklet_deinit(struct kc_tasklet_struct *t);
void kc_tasklet_disable(struct kc_tasklet_struct *t);

// spinlocks
void kc_spin_lock_init(struct kc_spinlock_t **lock);
void kc_spin_lock_deinit(struct kc_spinlock_t *lock);

void kc_spin_lock(struct kc_spinlock_t *lock);
void kc_spin_unlock(struct kc_spinlock_t *lock);

void kc_spin_lock_bh(struct kc_spinlock_t *lock);
void kc_spin_unlock_bh(struct kc_spinlock_t *lock);

void kc_spin_lock_irq(struct kc_spinlock_t *lock);
void kc_spin_unlock_irq(struct kc_spinlock_t *lock);

void kc_spin_lock_irqsave(struct kc_spinlock_t *lock,unsigned long *);
void kc_spin_unlock_irqrestore(struct kc_spinlock_t *lock,unsigned long);

// semaphores
void kc_semaphore_init(struct kc_semaphore_t **sem, int val);
void kc_semaphore_deinit(struct kc_semaphore_t *sem);

void kc_down(struct kc_semaphore_t *sem);
int kc_down_interruptible(struct kc_semaphore_t *sem);
int kc_down_trylock(struct kc_semaphore_t *sem);
void kc_up(struct kc_semaphore_t *sem);

// wait queues
void kc_init_waitqueue_head(struct kc_wait_queue_head_t **q);
void kc_deinit_waitqueue_head(struct kc_wait_queue_head_t *q);
void kc_wake_up_interruptible(struct kc_wait_queue_head_t *q);
long kc_interruptible_sleep_on_timeout(struct kc_wait_queue_head_t *q,  signed long timeout);
long kc_wait_event_interruptible_timeout(struct kc_wait_queue_head_t *wq,
	unsigned int (*condition)(void *cookie), signed long timeout,void *cookie);
int kc_signal_pending_current(void);
int kc_currentpid(void);
void kc_poll_wait(void *filp, struct kc_wait_queue_head_t *q, void *wait);

// atomic
void kc_atomic_init(struct kc_atomic_t **v);
void kc_atomic_deinit(struct kc_atomic_t *v);
int kc_atomic_read(struct kc_atomic_t *v);
void kc_atomic_set(struct kc_atomic_t *v,int i);
void kc_atomic_inc(struct kc_atomic_t *v);
int kc_atomic_add_negative(int i, struct kc_atomic_t *v);
int kc_atomic_dec_and_test(struct kc_atomic_t *v);

// bitops
int kc_test_and_set_bit(int nr, volatile void * addr);
int kc_test_and_clear_bit(int nr, volatile void * addr);
void kc_clear_bit(int nr, volatile void * addr);
int kc_test_bit(int nr, volatile void * addr);
void kc_set_bit(int nr, volatile void * addr);

// string
void *kc_memcpy(void * const dest, const void *src, unsigned long n);
void * kc_memset(void *,int,unsigned int);
int kc_memcmp(const void *,const void *,unsigned int);
char * kc_strncpy(char *,const char *, unsigned int);
char * kc_strcat(char *, const char *);
char * kc_strcpy(char *,const char *);
unsigned int kc_strlen(const char *);
int kc_strnicmp(const char *, const char *, unsigned int);

// cache
void kc_writeback_cache(void *pData, unsigned int size);
void kc_invalidate_cache(void *pData, unsigned int size);
void kc_writeback_cache_virtual(void *pData, unsigned int size);
void kc_invalidate_cache_virtual(void *pData, unsigned int size);

/* virt/bus/phy/page conversion */
struct kc_page * kc_virt_to_page(unsigned long addr);
unsigned long kc_virt_to_phys(unsigned long addr);
unsigned long kc_virt_to_bus(unsigned long addr);
unsigned long kc_phys_to_virt(unsigned long addr);

#endif // __KERNELCALLS_H__
