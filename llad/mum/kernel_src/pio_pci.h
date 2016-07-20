/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   pio_pci.h
  See licensing details in LICENSING file  

  @author Julien Soulier
  @date   2003-01-06
*/

#ifndef __PIO_PCI_H__
#define __PIO_PCI_H__

unsigned char  pci_read_uint8 (struct realmagicprivate *pR, unsigned long pci_region, unsigned long pci_offset);
unsigned short pci_read_uint16(struct realmagicprivate *pR, unsigned long pci_region, unsigned long pci_offset);
unsigned long  pci_read_uint32(struct realmagicprivate *pR, unsigned long pci_region, unsigned long pci_offset);

void pci_read_data8  (struct realmagicprivate *pR, unsigned long pci_region, unsigned long pci_offset, unsigned char *data, unsigned long count);
void pci_read_data16 (struct realmagicprivate *pR, unsigned long pci_region, unsigned long pci_offset, unsigned short *data, unsigned long count);
void pci_read_data32 (struct realmagicprivate *pR, unsigned long pci_region, unsigned long pci_offset, unsigned long *data, unsigned long count);

void pci_write_uint8 (struct realmagicprivate *pR, unsigned long pci_region, unsigned long pci_offset, unsigned char data);
void pci_write_uint16(struct realmagicprivate *pR, unsigned long pci_region, unsigned long pci_offset, unsigned short data);
void pci_write_uint32(struct realmagicprivate *pR, unsigned long pci_region, unsigned long pci_offset, unsigned long data);

void pci_write_data8 (struct realmagicprivate *pR, unsigned long pci_region, unsigned long pci_offset, unsigned char *data, unsigned long count);
void pci_write_data16(struct realmagicprivate *pR, unsigned long pci_region, unsigned long pci_offset, unsigned short *data, unsigned long count);
void pci_write_data32(struct realmagicprivate *pR, unsigned long pci_region, unsigned long pci_offset, unsigned long *data, unsigned long count);

#endif // __PIO_PCI_H__

