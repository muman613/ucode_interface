/*****************************************
 Copyright � 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   mum_kk.h
  @brief  

  long description

  @author Julien Soulier
  @date   2003-05-16
*/

#ifndef __MUM_KK_H__
#define __MUM_KK_H__

/**
   long-description

   @param pgbus 
   @param tasklet       
   @param irq_status       
   @param mask
*/
void mumk_register_tasklet(struct gbus *pgbus, struct kc_tasklet_struct *tasklet, RMuint32 *irq_status, RMuint32 mask);

/**
   long-description

   @param pgbus 
   @param kctasklet     
*/
void mumk_unregister_tasklet(struct gbus *pgbus, struct kc_tasklet_struct *kctasklet);


/**
   long-description

   @param pgbus 
   @param tasklet       
   @param channel
*/
void mumk_add_channel_handler_tasklet(struct gbus *pgbus, struct kc_tasklet_struct *tasklet, unsigned int channel);

/**
   long-description

   @param pgbus 
   @param kctasklet     
*/
void mumk_remove_channel_handler_tasklet(struct gbus *pgbus, struct kc_tasklet_struct *kctasklet);


/**
   -long description-

   @param index 
*/
void * mumk_get_pcidev(int index);

#endif // __MUM_KK_H__
