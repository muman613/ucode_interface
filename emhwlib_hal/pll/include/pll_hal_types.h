/*
 * emhwlib_hal/pll/include/pll_hal_types.h
 *
 * Copyright (c) 2005 Sigma Designs, Inc. 
 * All Rights Reserved. Proprietary and Confidential.
 *
 */
 
/**
  @file emhwlib_hal/pll/include/pll_hal_types.h
  @brief clock generation and routing HAL
  
  @author Christian Wolff
*/

#ifndef __EMHWLIBHAL_PLL_TYPES_H__
#define __EMHWLIBHAL_PLL_TYPES_H__

#include "rmdef/rmdef.h"

#define PLL_REGSET_MAX 16

struct PLLRegSet {
	RMuint32 entries;  /* number of entries in addr[] and data[] */
	RMuint32 addr[PLL_REGSET_MAX];  /* GBus address of the register */
	RMuint32 data[PLL_REGSET_MAX];  /* content of register */
};

/* List of available PLL generators and Clean dividers */
/* Application is urged to use a define from rmdef/rmfeatures.h, 
   which specifies one enum PLLGen based on the chip */
enum PLLGen {
	PLLGen_pll_0,  // PLL 0
	PLLGen_pll_1,  // PLL 1
	PLLGen_pll_2,  // PLL 2
	PLLGen_pll_3,  // PLL 3
	PLLGen_cd_0,   // Clean Divider 0
	PLLGen_cd_1,   // Clean Divider 1
	PLLGen_cd_2,   // Clean Divider 2
	PLLGen_cd_3,   // Clean Divider 3
	PLLGen_cd_4,   // Clean Divider 4
	PLLGen_cd_5,   // Clean Divider 5
	PLLGen_cd_6,   // Clean Divider 6
	PLLGen_cd_7,   // Clean Divider 7
	PLLGen_cd_8,   // Clean Divider 8
	PLLGen_cd_9,   // Clean Divider 9
	PLLGen_cd_10,  // Clean Divider 10
	PLLGen_cd_11,  // Clean Divider 11
};

/* List of outputs of a PLL or post divider of a CD */
enum PLLOut {
	PLLOut_0,  // direct output of a PLL or CD
	PLLOut_1,  // post divider 1 output of a PLL, CD / 2, CD8: VO0 = CD8 / 2, HDMI = CD8 direct
	PLLOut_2,  // post divider 2 output of a PLL, CD / 4, CD8: VO0 = CD8 / 4, HDMI = CD8 direct
	PLLOut_3,  // CD8: VO0 = CD8 / 2, HDMI = CD8 / 2
	PLLOut_4,  // CD8: VO0 = CD8 / 4, HDMI = CD8 / 2
};

/* List of available clock sources. Not all sources are available on all systems */
enum PLLSource {
	/* --- maintain this order from pwrdwn to VI1 */
	PLLSource_pwrdwn, // shut off PLL
	PLLSource_xtal,   // crystal clock, nominal XTAL_HZ (e.g. 27 MHz)
	PLLSource_vcxo0,  // clock from voltage controlled crystal oscillator 0
	PLLSource_vcxo1,  // clock from voltage controlled crystal oscillator 1
	PLLSource_RClk0,  // RClk0 input (e.g. external audio capture clock)
	PLLSource_RClk1,  // RClk1 input
	PLLSource_VI0,    // Video Input 0 (GraphicInput)
	PLLSource_VI1,    // Video Input 1 (VideoInput)
	/* --- */
	PLLSource_SPDIF0, // MClk extracted from SPDIF input 0
	PLLSource_SPDIF1, // MClk extracted from SPDIF input 1
};

/* List of clock signals in the system */
enum ClockSignal {
	ClockSignal_sys,   // System clock
	ClockSignal_cpu,   // CPU clock, may be different from sys_clk on 8630 and up
	ClockSignal_vdec,  // VDec DSP clock
	ClockSignal_RClk0, // RClk0 output
	ClockSignal_RClk1, // RClk1 output
	ClockSignal_RClk2, // RClk2 output
	ClockSignal_RClk3, // RClk3 output
	/* --- maintain this order from VO0 to rclk */
	ClockSignal_VO0,   // Video Output 0 (DigitalOut)
	ClockSignal_VO1,   // Video Output 1 (MainAnalogOut)
	ClockSignal_VO2,   // Video Output 2 (ComponentOut)
	ClockSignal_VO3,   // Video Output 3 (CompositeOut)
	ClockSignal_AO0,   // Audio DSP 0
	ClockSignal_AO1,   // Audio DSP 1
	ClockSignal_rclk,  // rclk out
	ClockSignal_sel,   // sel clock
	/* --- */
	ClockSignal_sdio,  // sdio clock
	ClockSignal_CD,    // Clean Divider clock
	ClockSignal_USB,   // USB clock in Host Interface
	ClockSignal_SATA,  // SATA clock in Host Interface
	ClockSignal_eth,   // Ethernet clock in Host Interface
	ClockSignal_AO2,   // Audio DSP 2 (stereo / VoIP)
	ClockSignal_GPU0,  // GPU 0
	ClockSignal_GPU1,  // GPU 1
};




/* List of clock counters. Not all counters are available on all systems */
enum ClockCounter {
	ClockCounter_sys_clk, 
	ClockCounter_xtal_in, 
	ClockCounter_vcxo0_in, 
	ClockCounter_vcxo1_in, 
	ClockCounter_rclk_out, 
	ClockCounter_sel_clk, 
	ClockCounter_rnd, 
	ClockCounter_0, 
	ClockCounter_1, 
	ClockCounter_2, 
	ClockCounter_3, 
	ClockCounter_4
};

/* Clocks that can be routed to ClockCounter_0 through _4 */
enum ClockCounterSource {
	ClockCounterSource_cd0 = 1,  // CD0 / 4
	ClockCounterSource_cd1,      // CD1 / 4
	ClockCounterSource_vcxo0,    // VCXO0 in
	ClockCounterSource_vcxo1,    // VCXO1 in
	ClockCounterSource_cd4,      // CD4 / 4
	ClockCounterSource_cd5,      // CD5 / 4
	ClockCounterSource_cd6,      // CD6 / 4
	ClockCounterSource_cd7,      // CD7 / 4
	ClockCounterSource_cd8,      // CD8 / 4
	ClockCounterSource_cd9,      // CD9 / 4
	ClockCounterSource_cd10,     // CD10 / 4
	ClockCounterSource_vi0,      // VideoIn0 clk (GraphicInput)
	ClockCounterSource_vi1,      // VideoIn1 clk (VideoInput)
	ClockCounterSource_pll1_1,   // PLL 1, post divider 1
	ClockCounterSource_pll2_1    // PLL 2, post divider 1
};

#endif /* __EMHWLIBHAL_PLL_TYPES_H__ */

