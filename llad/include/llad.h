/*****************************************
 Copyright � 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   llad.h
  @brief  
  
  llad stands for Low Level Acess Device

  a facility to acess the elementary registers of EM8xxx devices (see gbus.h)
  and program simple DMA transfers (see dmaxfer.h)

  @author Emmanuel Michon
  @date   2003-01-09
*/

#ifndef __LLAD_H__
#define __LLAD_H__

#include "rmdef/rmdef.h"
#include "rmchip/rmchip.h"

RM_EXTERN_C_BLOCKSTART

/* maximum number of llad devices per machine */
#define MAXLLAD 32

#define LOG2_LLAD_WAIT_MAMBIOS_SYSCALL          0
#define LOG2_LLAD_WAIT_WRITE_COMPLETE           1
// 2 is unused
#define LOG2_LLAD_GFX_INTERRUPT			3
#define LOG2_LLAD_SOFT_INTERRUPT		4
#define LOG2_LLAD_GNET0RX                       5
#define LOG2_LLAD_GNET1RX                       6
// Used by the remote driver in with_host mode
#define LOG2_LLAD_IR_REMOTE                     7
#define LOG2_LLAD_RPC_HOST_REQUEST              8
#define LOG2_LLAD_RPC_HOST_RESPONSE             9
#define LOG2_LLAD_RPC_TARGET_REQUEST            10
#define LOG2_LLAD_RPC_TARGET_RESPONSE           11
#define LOG2_LLAD_WAIT_XTASK1_INTERRUPT			12
#define LOG2_LLAD_WAIT_XTASK2_INTERRUPT			13
#define LOG2_LLAD_WAIT_XTASK3_INTERRUPT			14
#define LOG2_LLAD_WAIT_XTASK4_INTERRUPT			15

#define LLAD_WAIT_MAMBIOS_SYSCALL          (1 << LOG2_LLAD_WAIT_MAMBIOS_SYSCALL)
#define LLAD_WAIT_WRITE_COMPLETE           (1 << LOG2_LLAD_WAIT_WRITE_COMPLETE)
#define LLAD_GFX_INTERRUPT        	   (1 << LOG2_LLAD_GFX_INTERRUPT)
#define LLAD_SOFT_INTERRUPT        	   (1 << LOG2_LLAD_SOFT_INTERRUPT)
#define LLAD_GNET0RX                       (1 << LOG2_LLAD_GNET0RX)
#define LLAD_GNET1RX                       (1 << LOG2_LLAD_GNET1RX)
#define LLAD_IR_REMOTE                     (1 << LOG2_LLAD_IR_REMOTE)
#define LLAD_RPC_HOST_REQUEST              (1 << LOG2_LLAD_RPC_HOST_REQUEST)
#define LLAD_RPC_HOST_RESPONSE             (1 << LOG2_LLAD_RPC_HOST_RESPONSE)
#define LLAD_RPC_TARGET_REQUEST            (1 << LOG2_LLAD_RPC_TARGET_REQUEST)
#define LLAD_RPC_TARGET_RESPONSE           (1 << LOG2_LLAD_RPC_TARGET_RESPONSE)
#define LLAD_WAIT_XTASK1_INTERRUPT	   (1 << LOG2_LLAD_WAIT_XTASK1_INTERRUPT)
#define LLAD_WAIT_XTASK2_INTERRUPT	   (1 << LOG2_LLAD_WAIT_XTASK2_INTERRUPT)
#define LLAD_WAIT_XTASK3_INTERRUPT	   (1 << LOG2_LLAD_WAIT_XTASK3_INTERRUPT)
#define LLAD_WAIT_XTASK4_INTERRUPT	   (1 << LOG2_LLAD_WAIT_XTASK4_INTERRUPT)
struct llad;

#ifndef DUMMY_LLAD
/**
   Opens a low level access device using a device string.

   Device descrition can be:
      + device index when using mum (ex: "0")
      + host address (ex: "mambohost.asic.sdesigns.com")
      + ...

   Needed for further use of gbus_open() and dmaxfer_open()

   @param device  
*/
struct llad *llad_open(RMascii *device);

/**
   Closes a llad object

   @param h     
*/
void llad_close(struct llad *h);

/**
   Returns the llad configuration. Can PCI information for mum
   implementation or hostname server for network information.

   @param h     
   @param config_name
   @param config_size
   @return 
*/
void llad_get_config(struct llad *h, RMascii* config_name, RMuint32 config_size);

/**
   Returns the number of active llad_open.

   @param h     
   @return 
*/
RMuint32 llad_get_open_count(struct llad *h);

/**
   Tries to lock access to the llad. The returns value is the number
   of already opened llad on the same device (without counting this
   instance, 1 means there is one other instance). If no other llad is
   opened 0 is returned, and no llad can be opened until it is
   unlocked.

   @param h     
   @return 
*/
RMuint32 llad_lock(struct llad *h);

/**
   Unlocks a previously locked llad.

   @param h     
*/
void llad_unlock(struct llad *h);

/**
   Waits for at least one interrupt which bit is set in the or'ed
   field mask with timeout *timeout_microsecond.

   If at least one of the IRQ set in mask happens within *timeout_microsecond,
   *timeout_microsecond is set to the time left until timeout and the
   returned value is the or'ed field of all interrupts which happened
   during the interval and that were previously set in the mask.

   If timeout is reached, *timeout_microsecond and the returned value are zero.

   @param h     
   @param mask
   @param timeout_microsecond: truncated to an entire number of timeslices.
    If less than one timeslice (usually 10ms), treated as zero.
   @return 
*/
RMuint32 llad_wait_interrupt(struct llad *h, RMuint32 mask, RMuint32 *timeout_microsecond);

/**
   enables all interrupts which bit is set in mask. Then user can wait
   for one of them with llad_wait_interrupt. By default all interrupts
   are enabled.

   @param h     
   @param mask  
*/
void llad_enable_interrupt(struct llad *h, RMuint32 mask);

/**
   disables all interrupts which bit is set in mask. Then the user
   cannot wait for the interrupt with llad_wait_interrupt. By default
   no interrupt is disabled.

   @param h     
   @param mask  
*/
void llad_disable_interrupt(struct llad *h, RMuint32 mask);

/**
   jumps to ub in the ROM and never comes back
   @param h     
*/
void llad_force_rom_ub(struct llad *h);

/**
   dumps cache tags to dst
   @param h
   @param dst
*/
void llad_cache_dump(struct llad *h, RMuint32 *dst);

/**
   Waits until one of these two conditions becomes true:

   1) One of the channels in channel_array has received a command.
   2) An interval greater than timeout_microseconds is elapsed.

   If at least one of the channels receive commands (or had pending commands) 
   before the timeout is reached, the functions returns RM_OK and 
   active_channel contains the index of the first channel that 
   received a command.

   If the timeout is reached, the function returns RM_TIMEOUT, and the
   value of active_channel is unpredictable.

   @param h     
   @param channel_array
   @param channel_count
   @param timeout_microseconds
   @param active_channel
   @return 
*/

#define LLAD_MAX_WAIT_CHANNELS 32
RMstatus llad_wait_channels(struct llad *h, RMuint32 *channel_array, RMuint32 channel_count, RMuint32 timeout_microsecond, RMuint32 *active_channel);



#else // DUMMY_LLAD

static inline struct llad *llad_open(RMascii *device)
{
	return (struct llad *) 1;
}

static inline void llad_close(struct llad *h)
{
	return;
}

static inline void llad_get_config(struct llad *h, RMascii* config_name, RMuint32 config_size)
{
	if (config_size > 0)
		config_name[0] = '\0';
}

static inline RMuint32 llad_get_open_count(struct llad *h)
{
	return 1;
}

static inline RMuint32 llad_lock(struct llad *h)
{
	return 0;
}

static inline void llad_unlock(struct llad *h)
{
	return;
}

static inline RMuint32 llad_wait_interrupt(struct llad *h, RMuint32 mask, RMuint32 *timeout_microsecond)
{
	return 0;
}

static inline void llad_enable_interrupt(struct llad *h, RMuint32 mask)
{
	return;
}

static inline void llad_disable_interrupt(struct llad *h, RMuint32 mask)
{
	return;
}


#endif // DUMMY_LLAD

RM_EXTERN_C_BLOCKEND

#endif // __LLAD_H__
