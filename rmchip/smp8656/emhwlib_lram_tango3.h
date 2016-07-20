/*****************************************
 Copyright © 2004-2007
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   emhwlib_lram_tango3.h
  @brief  

  Map of the localram (8KBytes)

  Traditionnally the start of localram is used to setup
  a few kilobytes bootstrap routine code+data
  (cache init, tlb init, load something bigger to DRAM, jump there).

  Fixed offsets are defined in this file as communication devices
  between hardware blocks.
  Even debug locations must be present here.

  The bootstrap routine is expected to preserve these and setup
  its stack under LR_STACKTOP.

  Keep addresses increasing in this file.

  See emhwlib_resources_shared.h how some resources bw. 0 and 0x100 are used already
  only when uCLinux is up with irq handler running

  @author Sebastien Beysserie
  @date   2007-06-26
*/

#ifndef __EMHWLIB_LRAM_TANGO3_H__
#define __EMHWLIB_LRAM_TANGO3_H__

/*
  Leaving 1024 bytes for some startup code and stack
  as long as the value of this symbol moves only up with time, backward compatibility is ok 

  backward compatibility has been broken to manage bug#30959 (move stacktop from 0x900 to 0x400). em2011mar23
*/
#define LR_STACKTOP              0x00000400

/*
  8910/8920 cpu has many cores, ezboot runs on one, and the others are stationed in the trampoline,
  looping cached (one nop every other insn) with HB update once in a while.

  512 bytes available, must be preserved throughout SoC uptime.
 */
#define LR_TRAMPOLINE            0x00000700
#define LR_CPULAUNCH_STRUCTS     0x00000700
#define LR_CPULAUNCH_CODE        0x00000780

#define LR_XOS2K_C2X             0x00000900
#define LR_XOS2K_X2C             0x00000a00
#define LR_XOS2K_I2X             0x00000b00
#define LR_XOS2K_X2I             0x00000c00
#define LR_XOS2K_END             0x00000d00

#define LR_VSYNC_STRUCT          0x00000d00
/* between those irq handler world */
#define LR_VSYNC_STRUCT_END      0x00001900

#define LR_HB_CPU1               0x00001944
#define LR_HB_CPU2               0x00001948
#define LR_HB_CPU3               0x0000194c
#define LR_CPU_BOOTSEL           0x00001950 /* relying on the fact the soft reset & cpu bist does not clear lram */
#define LR_CPU_PERF0_CTRL        0x00001954
#define LR_CPU_PERF0_CNT         0x00001958
#define LR_CPU_PERF1_CTRL        0x0000195c
#define LR_CPU_PERF1_CNT         0x00001960
#define LR_HB_AUDIO2             0x00001964 /* to check if AUDIO2 will coexist with DEMUX1 */
#define LR_SUSPEND_ACK_AUDIO2    0x00001968
#define LR_HB_DEMUX1             0x0000196c
#define LR_SUSPEND_ACK_DEMUX1    0x00001970
#define LR_IOS_F_SYS_HZ          0x00001974 /* system frequency in Hz, calculated in irq_handler_init based on hardware registers settings. Written by thimble starting from 8734 (bug#39996). */
/* 0x20 = 32 bytes unused */

#define LR_ZBOOTXENV_LOCATION    0x00001994
#define LR_BAT_D0                0x00001998
#define LR_BAT_D1                0x0000199c

/* rather use the http://bugs.soft.sdesigns.com/twiki/bin/view/Main/SevenSegmentDisplay if you can */
#define LR_ZBOOT_STAGE           0x000019a0 

#define LR_ARMOR_TO_S1GA         0x000019a0

#define LR_CHANNEL_INDEX         0x000019a4
#define LR_HB_IPU                0x000019a8
#define LR_ARMOR_GA              0x000019a8 /* Same place as LR_HB_IPU, used to communicate, from stage0 to stage1, the location of armor.
					       Only used in `xboot4/freezer/cpusecureboot_step22to33_body.c`, step#23.
					       Afterwards this is LR_HB_IPU again. */
#define LR_PCI_INTERRUPT_ENABLE  0x000019ac
#define LR_HOST_INTERRUPT_STATUS 0x000019b0
#define LR_DRAM_DMA_SUSPEND      0x000019b4
#define LR_SUSPEND_ACK_MPEG0     0x000019b8
#define LR_SUSPEND_ACK_MPEG1     0x000019bc
#define LR_SUSPEND_ACK_AUDIO0    0x000019c0
#define LR_SUSPEND_ACK_AUDIO1    0x000019c4
#define LR_SUSPEND_ACK_DEMUX0    0x000019c8
#define LR_SUSPEND_ACK_IH        0x000019cc
#define LR_HB_IH                 0x000019d0
#define LR_HB_HOST               0x000019d4
#define LR_HB_CPU                0x000019d8
#define LR_HB_MPEG0              0x000019dc
#define LR_HB_MPEG1              0x000019e0
#define LR_HB_AUDIO0             0x000019e4
#define LR_HB_AUDIO1             0x000019e8
#define LR_HB_DEMUX0             0x000019ec
#define LR_IREJECT_STATUS        0x000019f0
#define LR_HB_VSYNC              0x000019f4
#define LR_SW_VAL_VSYNC_COUNT    0x000019f8 /* this location is used to count captured VSYNC */
#define LR_SW_VAL_PIXEL_ADDR     0x000019fc /* this location is used to store a pixel address to write the frame count */

#define LR_XENV2_RW              0x00001a00 /* up to 628 bytes */

#define LR_XOS_DUMP              0x00001c74 /* xtask dump --- might change */
#define LR_UART_SYNC_XPU_BUSY    0x00001c78
#define LR_MLC_GF15              0x00001c7c /* 28 bytes... to 0x..98 */

#define LR_XENV2_RO              0x00001d00 /* up to the end, 628 bytes. This area is written by xpu, r.o. for others */

#define LR_OTP_SCBA              0x00001f68
#define LR_OTP_LOCKS             0x00001f6c
#define LR_IPU_BORG              0x00001f70 /* where ipu stage0 was pulled from */
#define LR_IPU_EBORG             LR_XENV2_RO /* see bug#31464 comment 108 */
#define LR_XOS_SECOND_COUNT      0x00001f74 /* second counter */
#define LR_XOS_SECOND_COUNT_ATX  0x00001f78 /* value of xtal cnt at last update of second counter */
#define LR_XOS_F_SYS_HZ          0x00001f7c /* system frequency in Hz, measured by XOS - it is not 100% accurate. Obsolete AND inaccurate starting from 8734 (bug#39996). */
#define LR_XOS_C2X_RO            0x00001f80 /* xos trusted copies of channel structures */
#define LR_XOS_X2C_RO            0x00001fa0
#define LR_XOS_I2X_RO            0x00001fc0
#define LR_XOS_X2I_RO            0x00001fe0

/* for backward compatibility */
#define LR_HB_DEMUX              LR_HB_DEMUX0
#define LR_SUSPEND_ACK_DEMUX     LR_SUSPEND_ACK_DEMUX0

#define LR_HB_XPU LR_XOS_SECOND_COUNT

#define LR_HB_CPU0 LR_HB_CPU

#define LRRO_SIZE (LR_XOS_SECOND_COUNT-LR_XENV2_RO)
#define LRRW_SIZE (LR_XOS_DUMP-LR_XENV2_RW)

#define XMJ_VAX (FG_SIZE-20)

#endif // __EMHWLIB_LRAM_TANGO3_H__
