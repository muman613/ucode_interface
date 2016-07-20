/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   gbus_host_interrupt.h
  @brief  describes how to handle maskable interrupts in software 

  @author Julien Soulier
  @date   2003-08-06
*/

#ifndef __GBUS_HOST_INTERRUPT_H__
#define __GBUS_HOST_INTERRUPT_H__

#include "llad/include/gbus.h"
#include "gbus_spinlock.h"


#ifdef RMBUILD_USE_HWLIB_V2
#include "emhwlib_v2/include/emhwlib_event.h"
#include "emhwlib_v2/include/emhwlib_resources.h"
#else
#include "emhwlib/include/emhwlib_event.h"
#include "emhwlib/include/emhwlib_resources.h"
#endif

RM_EXTERN_C_BLOCKSTART

/**
   Raises a PCI interrupt if the corresponding bit is also enabled.
   NEVER CALL THIS FUNCTION FROM THE PC.

   @param pGBus 
   @param mask	
*/
static inline void gbus_set_host_interrupt(struct gbus *pGBus, RMuint32 mask)
{
	RMuint32 flags;
	RMuint32 enable, status;

	flags=gbus_spin_lock_mutex_irq(pGBus, PCI_IRQ_MUTEX, 0xffffffff);

	enable = gbus_read_uint32(pGBus, PCI_INTERRUPT_ENABLE);
	enable &= mask;

#if (EM86XX_MODE==EM86XX_MODEID_WITHHOST)
	
	status = gbus_read_uint32(pGBus, REG_BASE_host_interface+PCI_irq_set);
	status |= enable;
	gbus_write_uint32(pGBus, REG_BASE_host_interface+PCI_irq_set, status);
				
#elif (EM86XX_MODE==EM86XX_MODEID_STANDALONE)

	status = gbus_read_uint32(pGBus, HOST_INTERRUPT_STATUS);
	status |= enable;
	gbus_write_uint32(pGBus, HOST_INTERRUPT_STATUS, status);
	
	gbus_write_uint32(pGBus, REG_BASE_cpu_block + CPU_irq_softset, SOFT_IRQ_ORIGIN_PT110);
	
#else //EM86XX_MODE
	NOT_COMPILABLE;
#endif //EM86XX_MODE
	
	gbus_spin_unlock_mutex_irq(pGBus, PCI_IRQ_MUTEX, flags);
}

static inline void gbus_enable_host_interrupt(struct gbus *pGBus, RMuint32 mask)
{
	RMuint32 flags;
	RMuint32 enable;

	flags=gbus_spin_lock_mutex_irq(pGBus, PCI_IRQ_MUTEX, 0xffffffff);

	enable = gbus_read_uint32(pGBus, PCI_INTERRUPT_ENABLE);
	enable |= mask;
	gbus_write_uint32(pGBus, PCI_INTERRUPT_ENABLE, enable);

	gbus_spin_unlock_mutex_irq(pGBus, PCI_IRQ_MUTEX, flags);
}

static inline void gbus_disable_host_interrupt(struct gbus *pGBus, RMuint32 mask)
{
	RMuint32 flags;
	RMuint32 enable;
	
	flags=gbus_spin_lock_mutex_irq(pGBus, PCI_IRQ_MUTEX, 0xffffffff);

	enable = gbus_read_uint32(pGBus, PCI_INTERRUPT_ENABLE);
	enable &= ~mask;
	gbus_write_uint32(pGBus, PCI_INTERRUPT_ENABLE, enable);

#if (EM86XX_MODE==EM86XX_MODEID_WITHHOST)

	gbus_write_uint32(pGBus, REG_BASE_host_interface+PCI_irq_clear, mask);

#elif (EM86XX_MODE==EM86XX_MODEID_STANDALONE)
	
	{
		RMuint32 status; 

		status = gbus_read_uint32(pGBus, HOST_INTERRUPT_STATUS);
		status &= ~mask;
		gbus_write_uint32(pGBus, HOST_INTERRUPT_STATUS, status);
	}
	
#else //EM86XX_MODE

	NOT_COMPILABLE;
	
#endif //EM86XX_MODE
	
	gbus_spin_unlock_mutex_irq(pGBus, PCI_IRQ_MUTEX, flags);
}

RM_EXTERN_C_BLOCKEND

#endif // __GBUS_HOST_INTERRUPT_H__
