/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   region_map.h
  @brief  

  @author Julien Soulier
  @date   2003-01-06
*/

#ifndef __REGION_MAP_H__
#define __REGION_MAP_H__

/* maps an address into one of the PCI regions
   returns the offset to the PCI PIO base
 */
unsigned long region_map_address(struct realmagicprivate *pR, 
				 unsigned long pci_region,    /* pci region */
				 unsigned long byte_address,  /* addres in device address space */
				 unsigned long byte_size,     /* size to map */
				 unsigned long *mapped_size); /* size mapped successfully */


/* Locks a specific region to a gbus address
   returns 0 on success or negative integer on error;
 */
int region_lock_area(struct realmagicprivate *pR, 
		     unsigned long pci_region,    /* pci region */
		     unsigned long *region_index, /* number of the region to be reserved */
		     unsigned long byte_address,  /* addres in device address space */
		     unsigned long size,
		     unsigned long *region_count, 
		     unsigned long *offset); 

/* unlocks a previously locked region */
int region_unlock(struct realmagicprivate *pR, 
		  unsigned long pci_region,    /* pci region */
		  unsigned long region_index); /* number of the region to be released */

int region_get_area(struct realmagicprivate *pR, 
		    unsigned long pci_region,    /* pci region */
		    unsigned long byte_address, 
		    unsigned long size, 
		    unsigned long *region_index,
		    unsigned long *region_count,
		    unsigned long *offset);

#endif // __REGION_MAP_H__
