/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   mum_k.h
  @brief  

  long description

  @author Emmanuel Michon
  @date   2002-11-13
*/

#ifndef __MUM_K_H__
#define __MUM_K_H__

int mumk_init(struct realmagicprivate *pR);
void mumk_cleanup(struct realmagicprivate *pR);

void mumk_wait(struct realmagicprivate *pR,struct waitable *h);

int mumk_mmap_dma(struct realmagicprivate *pR,struct kc_vm_area_struct *vma,unsigned long start,int size,struct kc_pgprot_t *prot);

#endif // __MUM_K_H__
