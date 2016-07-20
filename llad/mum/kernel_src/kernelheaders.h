/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   kernelheaders.h
  @brief  

  long description

  @author Emmanuel Michon
  @date   2002-12-03
*/

#ifndef __KERNELHEADERS_H__
#define __KERNELHEADERS_H__

#include <linux/init.h>

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,19)
#include <linux/config.h>
#endif

#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/pci.h>
#include <linux/interrupt.h>
#include <linux/errno.h>
#include <linux/string.h>
#include <linux/mm.h>
#include <linux/tty.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/init.h>
#include <linux/vmalloc.h>

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,18)
#include <linux/devfs_fs_kernel.h>
#endif

#include <asm/uaccess.h>
#include <asm/system.h>
#include <asm/irq.h>
#include <asm/pgtable.h>
#include <asm/io.h>
#include <asm/bitops.h>
#include <asm/param.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,15)
#include <linux/moduleparam.h>
#endif

/*
This code is mips processor and kernel dependent: 
These CAC_ADDR and UNCAC_ADDR macros do not exist in kernels < 2.4.20
See /linux/include/asm-mips/page.h
*/
#if defined(CONFIG_MIPS) && (LINUX_VERSION_CODE < KERNEL_VERSION(2,4,20))
#define UNCAC_BASE 0xa0000000
#define UNCAC_ADDR(addr) ((addr) - PAGE_OFFSET + UNCAC_BASE)
#define CAC_ADDR(addr)   ((addr) - UNCAC_BASE + PAGE_OFFSET)
#endif // RMARCHID && LINUX_VERSION_CODE
#endif // __KERNELHEADERS_H__
