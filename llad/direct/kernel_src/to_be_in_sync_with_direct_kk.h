
/*
  THIS FILE MUST BE KEPT IN SYNC WITH:

  llad/direct/include/direct_kk.h

  NOTE: there should be a way to actually share the same file...
 */

#ifndef __TO_BE_IN_SYNC_WITH_DIRECT_KK_H__
#define __TO_BE_IN_SYNC_WITH_DIRECT_KK_H__



void mumk_register_tasklet(struct gbus *pgbus, struct kc_tasklet_struct *tasklet, unsigned long *irq_status, unsigned long irq_mask);
void mumk_unregister_tasklet(struct gbus *pgbus, struct kc_tasklet_struct *kctasklet);


void mumk_add_channel_handler_tasklet(struct gbus *PGBUS, struct kc_tasklet_struct *tasklet, unsigned long channel);
void mumk_remove_channel_handler_tasklet(struct gbus *PGBUS, struct kc_tasklet_struct *tasklet);


#endif //__TO_BE_IN_SYNC_WITH_DIRECT_KK_H__
