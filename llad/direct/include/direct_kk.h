/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   direct_kk.h
  @brief  

  long description

  @author Emmanuel Michon
  @date   2003-10-15
*/

#ifndef __DIRECT_KK_H__
#define __DIRECT_KK_H__


void mumk_register_tasklet(struct gbus *pgbus, struct kc_tasklet_struct *tasklet, unsigned long *irq_status, unsigned long irq_mask);
void mumk_unregister_tasklet(struct gbus *pgbus, struct kc_tasklet_struct *kctasklet);


void mumk_add_channel_handler_tasklet(struct gbus *PGBUS, struct kc_tasklet_struct *tasklet, unsigned long channel);
void mumk_remove_channel_handler_tasklet(struct gbus *PGBUS, struct kc_tasklet_struct *tasklet);


#endif // __DIRECT_KK_H__
