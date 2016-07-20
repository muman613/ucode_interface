/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   devices.h
  @brief  

  @author Julien Soulier
  @date   2002-12-23
*/

#ifndef __DEVICES_H__
#define __DEVICES_H__

enum realmagic_chip {
        chip_quasar,
	chip_jasper,
	chip_mambo,
	chip_tango,
	chip_tango2,
	chip_tango3
};

void init_device_specific_data(struct realmagicprivate *pR, enum realmagic_chip chip, unsigned int revision_id);
void delete_device_specific_data(struct realmagicprivate *pR);

RMuint32 quasar_do_irq(struct realmagicprivate *pR, int irq, struct kc_pt_regs * regs);
void quasar_set_region_mapping(struct realmagicprivate *pR, int pci_region, int region_idx, unsigned long addr);
unsigned long quasar_get_region_mapping(struct realmagicprivate *pR, int pci_region, int region_idx);
void quasar_enable_interrupt(struct realmagicprivate *pR, unsigned long mask);
void quasar_disable_interrupt(struct realmagicprivate *pR, unsigned long mask);

RMuint32 jasper_do_irq(struct realmagicprivate *pR, int irq, struct kc_pt_regs * regs);
void jasper_set_region_mapping(struct realmagicprivate *pR, int pci_region, int region_idx, unsigned long addr);
unsigned long jasper_get_region_mapping(struct realmagicprivate *pR, int pci_region, int region_idx);
void jasper_enable_interrupt(struct realmagicprivate *pR, unsigned long mask);
void jasper_disable_interrupt(struct realmagicprivate *pR, unsigned long mask);

RMuint32 mambo_do_irq(struct realmagicprivate *pR, int irq, struct kc_pt_regs * regs);
void mambo_set_region_mapping(struct realmagicprivate *pR, int pci_region, int region_idx, unsigned long addr);
unsigned long mambo_get_region_mapping(struct realmagicprivate *pR, int pci_region, int region_idx);
void mambo_enable_interrupt(struct realmagicprivate *pR, unsigned long mask);
void mambo_disable_interrupt(struct realmagicprivate *pR, unsigned long mask);

RMuint32 tango_do_irq(struct realmagicprivate *pR, int irq, struct kc_pt_regs * regs);
void tango_set_region_mapping(struct realmagicprivate *pR, int pci_region, int region_idx, unsigned long addr);
unsigned long tango_get_region_mapping(struct realmagicprivate *pR, int pci_region, int region_idx);
void tango_enable_interrupt(struct realmagicprivate *pR, unsigned long mask);
void tango_disable_interrupt(struct realmagicprivate *pR, unsigned long mask);

#endif // __DEVICES_H__
