/******************************************************/
/* This file is generated automatically, DO NOT EDIT! */
/******************************************************/
/*
 * smp8682/rmchip_registers_smp8682.h
 *
 * Copyright (c) 2001-2012 Sigma Designs, Inc. 
 * All Rights Reserved. Proprietary and Confidential.
 *
 */
 
/**
  @file smp8682/rmchip_registers_smp8682.h
  @brief emhwlib generated file
   
  @author Sigma Designs Software Engineering Team
  @ingroup hwlproperties
*/

#ifndef __RMCHIP_REGISTERS_SMP8682_H__
#define __RMCHIP_REGISTERS_SMP8682_H__

/* Registers definitions for smp8682 */

/* AudioCapture registers */
#define audio_SI_L0_DATA 0x3e40 /* width RMuint32 */
#define audio_SI_R0_DATA 0x3e41 /* width RMuint32 */
#define audio_SI_STATUS 0x3e42 /* width RMuint32 */
#define audio_SI_CONF 0x3e43 /* width RMuint32 */
#define audio_SI_SPDIF_STATUS 0x3e44 /* width RMuint32 */
/* AudioCapture registers done */

/* AudioDecoder registers */
/* AudioDecoder registers done */

/* AudioEncoder registers */
/* AudioEncoder registers done */

/* AudioEngine registers */
#define REG_BASE_audio_engine_0 0x000c0000 /* width RMuint32 */
#define MEM_BASE_audio_engine_0 0x00180000 /* width RMuint32 */
#define PMEM_BASE_audio_engine_0 0x00180000 /* width RMuint32 */
#define DMEM_BASE_audio_engine_0 0x00190000 /* width RMuint32 */
#define REG_BASE_audio_engine_1 0x000d0000 /* width RMuint32 */
#define MEM_BASE_audio_engine_1 0x001a0000 /* width RMuint32 */
#define PMEM_BASE_audio_engine_1 0x001a0000 /* width RMuint32 */
#define DMEM_BASE_audio_engine_1 0x001b0000 /* width RMuint32 */
#define REG_BASE_audio_engine_2 0x000b0000 /* width RMuint32 */
#define MEM_BASE_audio_engine_2 0x00160000 /* width RMuint32 */
#define PMEM_BASE_audio_engine_2 0x00160000 /* width RMuint32 */
#define DMEM_BASE_audio_engine_2 0x00170000 /* width RMuint32 */
#define audio_SO_L0_DATA 0x3e00 /* width RMuint32 */
#define audio_SO_R0_DATA 0x3e01 /* width RMuint32 */
#define audio_SO_L1_DATA 0x3e02 /* width RMuint32 */
#define audio_SO_R1_DATA 0x3e03 /* width RMuint32 */
#define audio_SO_L2_DATA 0x3e04 /* width RMuint32 */
#define audio_SO_R2_DATA 0x3e05 /* width RMuint32 */
#define audio_SO_LS_DATA 0x3e06 /* width RMuint32 */
#define audio_SO_RS_DATA 0x3e07 /* width RMuint32 */
#define audio_SO_CH_INTR 0x3e08 /* width RMuint32 */
#define audio_SO_CH_CTRL 0x3e09 /* width RMuint32 */
#define audio_SO_SPDIF_CH_STAT 0x3e0a /* width RMuint32 */
#define audio_SO_L3_DATA 0x3e0b /* width RMuint32 */
#define audio_SO_R3_DATA 0x3e0c /* width RMuint32 */
#define audio_SO_L4_DATA 0x3e0d /* width RMuint32 */
#define audio_SO_AUDIO_CLK_DIV 0x3e0e /* width RMuint32 */
#define audio_SO_R4_DATA 0x3e0f /* width RMuint32 */
#define audio_mutex0 0x3e90 /* width RMuint32 */
#define audio_mutex1 0x3e91 /* width RMuint32 */
#define audio_mutex2 0x3e92 /* width RMuint32 */
#define audio_mutex3 0x3e93 /* width RMuint32 */
#define audio_mutex4 0x3e94 /* width RMuint32 */
#define audio_mutex5 0x3e95 /* width RMuint32 */
#define audio_mutex6 0x3e96 /* width RMuint32 */
#define audio_mutex7 0x3e97 /* width RMuint32 */
#define audio_MBUSIF_w0_add 0x3ec0 /* width RMuint32 */
#define audio_MBUSIF_w0_cnt 0x3ec1 /* width RMuint32 */
#define audio_MBUSIF_w0_skip 0x3ec2 /* width RMuint32 */
#define audio_MBUSIF_w0_cmd 0x3ec3 /* width RMuint32 */
#define audio_MBUSIF_r0_add 0x3ed0 /* width RMuint32 */
#define audio_MBUSIF_r0_cnt 0x3ed1 /* width RMuint32 */
#define audio_MBUSIF_r0_skip 0x3ed2 /* width RMuint32 */
#define audio_MBUSIF_r0_cmd 0x3ed3 /* width RMuint32 */
#define audio_GBUSIF_MAIN_WADD 0x3ea0 /* width RMuint32 */
#define audio_GBUSIF_MAIN_RADD 0x3ea1 /* width RMuint32 */
#define audio_GBUSIF_MAIN_BYTE 0x3ea2 /* width RMuint32 */
#define audio_GBUSIF_MAIN_WORD 0x3ea3 /* width RMuint32 */
#define audio_GBUSIF_MAIN_DWORD 0x3ea4 /* width RMuint32 */
#define audio_GBUSIF_MAIN_STATUS 0x3ea5 /* width RMuint32 */
#define audio_GBUSIF_ISR_WADD 0x3ea8 /* width RMuint32 */
#define audio_GBUSIF_ISR_RADD 0x3ea9 /* width RMuint32 */
#define audio_GBUSIF_ISR_BYTE 0x3eaa /* width RMuint32 */
#define audio_GBUSIF_ISR_WORD 0x3eab /* width RMuint32 */
#define audio_GBUSIF_ISR_DWORD 0x3eac /* width RMuint32 */
#define audio_GBUSIF_ISR_STATUS 0x3ead /* width RMuint32 */
#define audio_MISC_dr_mode 0x3e80 /* width RMuint32 */
#define audio_MISC_dr_length 0x3e81 /* width RMuint32 */
#define audio_MISC_dr_address 0x3e82 /* width RMuint32 */
#define audio_MISC_dw_mode 0x3e84 /* width RMuint32 */
#define audio_MISC_dw_length 0x3e85 /* width RMuint32 */
#define audio_MISC_dw_address 0x3e86 /* width RMuint32 */
#define audio_MISC_reset0 0x3e88 /* width RMuint32 */
#define audio_MISC_reset1 0x3e89 /* width RMuint32 */
#define audio_MISC_interrupt 0x3e8A /* width RMuint32 */
#define audio_MISC_timer_div 0x3e8B /* width RMuint32 */
#define audio_MISC_timer_count 0x3e8C /* width RMuint32 */
#define audio_MISC_ALTERNATIVE_IO 0x3E8D /* width RMuint32 */
#define audio_MISC_GROUND_I2S_IO 0x3E8E /* width RMuint32 */
#define audio_MISC_GROUND_SPDIF_IO 0x3E8F /* width RMuint32 */
#define audio_MISC_I2S_IO_SOURCE_SEL 0x3E98 /* width RMuint32 */
#define audio_MISC_VERSION_REVISION 0x3E9F /* width RMuint32 */
#define audio_MISC_UNRESET_MASK 0xc300 /* width RMuint32 */
#define audio_MISC_RESET_MASK 0xc3c3 /* width RMuint32 */
#define audio_SP_init 0x1ffe /* width RMuint32 */
/* AudioEngine registers done */

/* AudioOutputCapture registers */
/* AudioOutputCapture registers done */

/* AudioWatermark registers */
/* AudioWatermark registers done */

/* CCFifo registers */
/* CCFifo registers done */

/* ChannelService registers */
/* ChannelService registers done */

/* CPUBlock registers */
#define REG_BASE_cpu_block 0x00060000 /* width RMuint32 */
#define CPU_time0_load 0xc500 /* width RMuint32 */
#define CPU_time0_value 0xc504 /* width RMuint32 */
#define CPU_time0_ctrl 0xc508 /* width RMuint32 */
#define CPU_time0_clr 0xc50c /* width RMuint32 */
#define CPU_time1_load 0xc600 /* width RMuint32 */
#define CPU_time1_value 0xc604 /* width RMuint32 */
#define CPU_time1_ctrl 0xc608 /* width RMuint32 */
#define CPU_time1_clr 0xc60c /* width RMuint32 */
#define CPU_rtc_data 0xc800 /* width RMuint32 */
#define CPU_rtc_match 0xc804 /* width RMuint32 */
#define CPU_rtc_stat 0xc808 /* width RMuint32 */
#define CPU_rtc_load 0xc80c /* width RMuint32 */
#define CPU_rtc_ctrl 0xc810 /* width RMuint32 */
#define CPU_irq_status 0xe000 /* width RMuint32 */
#define CPU_irq_rawstat 0xe004 /* width RMuint32 */
#define CPU_irq_enableset 0xe008 /* width RMuint32 */
#define CPU_irq_enableclr 0xe00c /* width RMuint32 */
#define CPU_irq_softset 0xe010 /* width RMuint32 */
#define CPU_irq_softclr 0xe014 /* width RMuint32 */
#define CPU_irq_status_hi 0xe018 /* width RMuint32 */
#define CPU_irq_rawstat_hi 0xe01c /* width RMuint32 */
#define CPU_irq_enableset_hi 0xe020 /* width RMuint32 */
#define CPU_irq_enableclr_hi 0xe024 /* width RMuint32 */
#define CPU_fiq_status 0xe100 /* width RMuint32 */
#define CPU_fiq_rawstat 0xe104 /* width RMuint32 */
#define CPU_fiq_enableset 0xe108 /* width RMuint32 */
#define CPU_fiq_enableclr 0xe10c /* width RMuint32 */
#define CPU_fiq_softset 0xe110 /* width RMuint32 */
#define CPU_fiq_softclr 0xe114 /* width RMuint32 */
#define CPU_fiq_status_hi 0xe118 /* width RMuint32 */
#define CPU_fiq_rawstat_hi 0xe11c /* width RMuint32 */
#define CPU_fiq_enableset_hi 0xe120 /* width RMuint32 */
#define CPU_fiq_enableclr_hi 0xe124 /* width RMuint32 */
#define CPU_edge_status 0xe200 /* width RMuint32 */
#define CPU_edge_rawstat 0xe204 /* width RMuint32 */
#define CPU_edge_config_rise 0xe208 /* width RMuint32 */
#define CPU_edge_config_fall 0xe20c /* width RMuint32 */
#define CPU_SOFT_INT 0x00000001 /* width RMuint32 */
#define CPU_UART0_INT 0x00000002 /* width RMuint32 */
#define CPU_UART1_INT 0x00000004 /* width RMuint32 */
#define CPU_TIMER0_INT 0x00000020 /* width RMuint32 */
#define CPU_TIMER1_INT 0x00000040 /* width RMuint32 */
#define CPU_HOST_MBUS_W0_INT 0x00000200 /* width RMuint32 */
#define CPU_HOST_MBUS_W1_INT 0x00000400 /* width RMuint32 */
#define CPU_HOST_MBUS_R0_INT 0x00000800 /* width RMuint32 */
#define CPU_HOST_MBUS_R1_INT 0x00001000 /* width RMuint32 */
#define CPU_PCI_INTA 0x00002000 /* width RMuint32 */
#define CPU_PCI_INTB 0x00004000 /* width RMuint32 */
#define CPU_PCI_INTC 0x00008000 /* width RMuint32 */
#define CPU_PCI_INTD 0x00010000 /* width RMuint32 */
#define CPU_PCI_FAULT_INT 0x00100000 /* width RMuint32 */
#define CPU_INFRARED_INT 0x00200000 /* width RMuint32 */
#define CPU_SFLA_INT 0x00000010 /* width RMuint32 */
#define CPU_DVD_INT 0x00000080 /* width RMuint32 */
#define CPU_ETH_INT 0x00000100 /* width RMuint32 */
#define CPU_DMAIDE_INT 0x00020000 /* width RMuint32 */
#define CPU_IDE_INT 0x00040000 /* width RMuint32 */
#define CPU_FRONTPANEL_INT 0x00080000 /* width RMuint32 */
#define CPU_I2C_INT 0x00400000 /* width RMuint32 */
#define CPU_GFX_ACCEL_INT 0x00800000 /* width RMuint32 */
#define CPU_VSYNC0_INT 0x01000000 /* width RMuint32 */
#define CPU_VSYNC1_INT 0x02000000 /* width RMuint32 */
#define CPU_VSYNC2_INT 0x04000000 /* width RMuint32 */
#define CPU_VSYNC3_INT 0x08000000 /* width RMuint32 */
#define CPU_VSYNC4_INT 0x10000000 /* width RMuint32 */
#define CPU_VSYNC4BKEND_INT 0x20000000 /* width RMuint32 */
#define CPU_VSYNC5_INT 0x40000000 /* width RMuint32 */
#define CPU_VSYNC5BKEND_INT 0x80000000 /* width RMuint32 */
#define CPU_SMARTCARD_HI_INT 0x00000001 /* width RMuint32 */
#define CPU_HDMI_HI_INT 0x00000002 /* width RMuint32 */
#define CPU_HDMI_I2C_HI_INT 0x00000004 /* width RMuint32 */
#define CPU_VBUS_W0_HI_INT 0x00000008 /* width RMuint32 */
#define CPU_VBUS_W3_HI_INT 0x00000010 /* width RMuint32 */
#define CPU_ETH_PHY_HI_INT 0x00000020 /* width RMuint32 */
#define CPU_ETH_MAC_HI_INT 0x00000040 /* width RMuint32 */
#define CPU_USB_OHCI_MAC_HI_INT 0x00000080 /* width RMuint32 */
#define CPU_USB_EHCI_MAC_HI_INT 0x00000100 /* width RMuint32 */
#define LOG2_CPU_SOFT_INT 0 /* width RMuint32 */
#define LOG2_CPU_UART0_INT 1 /* width RMuint32 */
#define LOG2_CPU_UART1_INT 2 /* width RMuint32 */
#define LOG2_CPU_TIMER0_INT 5 /* width RMuint32 */
#define LOG2_CPU_TIMER1_INT 6 /* width RMuint32 */
#define LOG2_CPU_DVD_INT 7 /* width RMuint32 */
#define LOG2_CPU_RTC_INT 8 /* width RMuint32 */
#define LOG2_CPU_HOST_MBUS_W0_INT 9 /* width RMuint32 */
#define LOG2_CPU_HOST_MBUS_W1_INT 10 /* width RMuint32 */
#define LOG2_CPU_HOST_MBUS_R0_INT 11 /* width RMuint32 */
#define LOG2_CPU_HOST_MBUS_R1_INT 12 /* width RMuint32 */
#define LOG2_CPU_PCI_INTA 13 /* width RMuint32 */
#define LOG2_CPU_PCI_INTB 14 /* width RMuint32 */
#define LOG2_CPU_PCI_INTC 15 /* width RMuint32 */
#define LOG2_CPU_PCI_INTD 16 /* width RMuint32 */
#define LOG2_CPU_DMAIDE_INT 17 /* width RMuint32 */
#define LOG2_CPU_IDE_INT 18 /* width RMuint32 */
#define LOG2_CPU_FRONTPANEL_INT 19 /* width RMuint32 */
#define LOG2_CPU_PCI_FAULT_INT 20 /* width RMuint32 */
#define LOG2_CPU_INFRARED_INT 21 /* width RMuint32 */
#define LOG2_CPU_I2C_INT 22 /* width RMuint32 */
#define LOG2_CPU_GFX_ACCEL_INT 23 /* width RMuint32 */
#define LOG2_CPU_VSYNC0_INT 24 /* width RMuint32 */
#define LOG2_CPU_VSYNC1_INT 25 /* width RMuint32 */
#define LOG2_CPU_VSYNC2_INT 26 /* width RMuint32 */
#define LOG2_CPU_VSYNC3_INT 27 /* width RMuint32 */
#define LOG2_CPU_VSYNC4_INT 28 /* width RMuint32 */
#define LOG2_CPU_VSYNC4BKEND_INT 29 /* width RMuint32 */
#define LOG2_CPU_VSYNC5_INT 30 /* width RMuint32 */
#define LOG2_CPU_VSYNC5BKEND_INT 31 /* width RMuint32 */
#define LOG2_CPU_SMARTCARD_INT 32 /* width RMuint32 */
#define LOG2_CPU_HDMI_INT 33 /* width RMuint32 */
#define LOG2_CPU_HDMI_I2C_INT 34 /* width RMuint32 */
#define LOG2_CPU_VBUS_W0_INT 35 /* width RMuint32 */
#define LOG2_CPU_VBUS_W3_INT 36 /* width RMuint32 */
#define LOG2_CPU_ETH_PHY_INT 37 /* width RMuint32 */
#define LOG2_CPU_ETH_MAC_INT 38 /* width RMuint32 */
#define LOG2_CPU_USB_OHCI_INT 39 /* width RMuint32 */
#define LOG2_CPU_USB_EHCI_INT 40 /* width RMuint32 */
#define LOG2_CPU_SATA_INT 41 /* width RMuint32 */
#define LOG2_CPU_DMASATA_INT 42 /* width RMuint32 */
#define LOG2_XPU_W0_INT 43 /* width RMuint32 */
#define LOG2_XPU_R0_INT 44 /* width RMuint32 */
#define LOG2_XPU_W_SP_INT 45 /* width RMuint32 */
#define LOG2_XPU_R_SP_INT 46 /* width RMuint32 */
#define LOG2_CPU_GPIO24_INT 47 /* width RMuint32 */
#define LOG2_CPU_GPIO25_INT 48 /* width RMuint32 */
#define LOG2_CPU_GPIO26_INT 49 /* width RMuint32 */
#define LOG2_CPU_GPIO27_INT 50 /* width RMuint32 */
#define LOG2_CPU_VBUS_W4_INT 51 /* width RMuint32 */
#define LOG2_CPU_SMARTCARD1_INT 52 /* width RMuint32 */
#define LOG2_CPU_HDMI_CEC_INT 53 /* width RMuint32 */
#define LOG2_CPU_SATA1_INT 54 /* width RMuint32 */
#define LOG2_CPU_DMASATA1_INT 55 /* width RMuint32 */
#define LOG2_CPU_ETH_PHY1_INT 56 /* width RMuint32 */
#define LOG2_CPU_ETH_MAC1_INT 57 /* width RMuint32 */
#define LOG2_CPU_HOST_MBUS_W2_INT 58 /* width RMuint32 */
#define LOG2_CPU_HOST_MBUS_R2_INT 59 /* width RMuint32 */
#define LOG2_CPU_SDIO0_INT 60 /* width RMuint32 */
#define LOG2_CPU_SDIO1_INT 61 /* width RMuint32 */
#define LOG2_CPU_SPI_INT 62 /* width RMuint32 */
#define LOG2_CPU_UART2_INT 63 /* width RMuint32 */
#define CPU_edge_status_hi 0xe220 /* width RMuint32 */
#define CPU_edge_rawstat_hi 0xe224 /* width RMuint32 */
#define CPU_edge_config_rise_hi 0xe228 /* width RMuint32 */
#define CPU_edge_config_fall_hi 0xe22c /* width RMuint32 */
#define CPU_irq_status_hi 0xe018 /* width RMuint32 */
#define CPU_irq_rawstat_hi 0xe01c /* width RMuint32 */
#define CPU_irq_enableset_hi 0xe020 /* width RMuint32 */
#define CPU_irq_enableclr_hi 0xe024 /* width RMuint32 */
#define CPU_fiq_status_hi 0xe118 /* width RMuint32 */
#define CPU_fiq_rawstat_hi 0xe11c /* width RMuint32 */
#define CPU_fiq_enableset_hi 0xe120 /* width RMuint32 */
#define CPU_fiq_enableclr_hi 0xe124 /* width RMuint32 */
#define CPU_iiq_status 0xe300 /* width RMuint32 */
#define CPU_iiq_rawstat 0xe304 /* width RMuint32 */
#define CPU_iiq_enableset 0xe308 /* width RMuint32 */
#define CPU_iiq_enableclr 0xe30c /* width RMuint32 */
#define CPU_iiq_softset 0xe310 /* width RMuint32 */
#define CPU_iiq_softclr 0xe314 /* width RMuint32 */
#define CPU_iiq_status_hi 0xe318 /* width RMuint32 */
#define CPU_iiq_rawstat_hi 0xe31c /* width RMuint32 */
#define CPU_iiq_enableset_hi 0xe320 /* width RMuint32 */
#define CPU_iiq_enableclr_hi 0xe324 /* width RMuint32 */
#define CPU_UART_GPIOMODE 0x38 /* width RMuint32 */
#define CPU_UART_GPIODIR 0x30 /* width RMuint32 */
#define CPU_UART_GPIODATA 0x34 /* width RMuint32 */
#define CPU_edge_config_rise_set 0xe210 /* width RMuint32 */
#define CPU_edge_config_rise_clr 0xe214 /* width RMuint32 */
#define CPU_edge_config_fall_set 0xe218 /* width RMuint32 */
#define CPU_edge_config_fall_clr 0xe21c /* width RMuint32 */
#define CPU_edge_config_rise_set_hi 0xe230 /* width RMuint32 */
#define CPU_edge_config_rise_clr_hi 0xe234 /* width RMuint32 */
#define CPU_edge_config_fall_set_hi 0xe238 /* width RMuint32 */
#define CPU_edge_config_fall_clr_hi 0xe23c /* width RMuint32 */
#define intentionaldiff_em 0xeee0 /* width RMuint32 */
#define CPU_pm_select_0 0xc900 /* width RMuint32 */
#define CPU_pm_counter_0 0xc904 /* width RMuint32 */
#define CPU_pm_select_1 0xc908 /* width RMuint32 */
#define CPU_pm_counter_1 0xc90c /* width RMuint32 */
#define CPU_HOST_VBUS_W4_INT_HI 0x00080000 /* width RMuint32 */
#define CPU_remap 0xf000 /* width RMuint32 */
#define CPU_remap1 0xf004 /* width RMuint32 */
#define CPU_remap2 0xf008 /* width RMuint32 */
#define CPU_remap3 0xf00c /* width RMuint32 */
#define CPU_remap4 0xf010 /* width RMuint32 */
#define CPU_remap5 0xf014 /* width RMuint32 */
#define CPU_remap6 0xf018 /* width RMuint32 */
#define CPU_remap7 0xf01c /* width RMuint32 */
#define CPU_remap_address 0x1fc00000 /* width RMuint32 */
#define CPU_remap1_address 0 /* width RMuint32 */
#define CPU_remap2_address 0x04000000 /* width RMuint32 */
#define CPU_remap3_address 0x08000000 /* width RMuint32 */
#define CPU_remap4_address 0x0c000000 /* width RMuint32 */
#define CPU_remap5_address 0x10000000 /* width RMuint32 */
#define CPU_remap6_address 0x14000000 /* width RMuint32 */
#define CPU_remap7_address 0x18000000 /* width RMuint32 */
#define REG_BASE_irq_handler_block 0xf0000 /* width RMuint32 */
#define G2L_BIST_BUSY 0xffe0 /* width RMuint32 */
#define G2L_BIST_PASS 0xffe4 /* width RMuint32 */
#define G2L_BIST_MASK 0xffe8 /* width RMuint32 */
#define G2L_RESET_CONTROL 0xfffc /* width RMuint32 */
#define CPU_UART0_base 0xc100 /* width RMuint32 */
#define CPU_UART1_base 0xc200 /* width RMuint32 */
#define CPU_UART2_base 0xcd00 /* width RMuint32 */
#define CPU_UART_RBR 0x00 /* width RMuint32 */
#define CPU_UART_THR 0x04 /* width RMuint32 */
#define CPU_UART_IER 0x08 /* width RMuint32 */
#define CPU_UART_IIR 0x0c /* width RMuint32 */
#define CPU_UART_FCR 0x10 /* width RMuint32 */
#define CPU_UART_LCR 0x14 /* width RMuint32 */
#define CPU_UART_MCR 0x18 /* width RMuint32 */
#define CPU_UART_LSR 0x1c /* width RMuint32 */
#define CPU_UART_MSR 0x20 /* width RMuint32 */
#define CPU_UART_SCR 0x24 /* width RMuint32 */
#define CPU_UART_CLKDIV 0x28 /* width RMuint32 */
#define CPU_UART_CLKSEL 0x2c /* width RMuint32 */
#define CPU_scard0_gpio_dir 0xc358 /* width RMuint32 */
#define CPU_scard0_gpio_data 0xc35c /* width RMuint32 */
#define CPU_scard0_gpio_mode 0xc360 /* width RMuint32 */
#define CPU_scard1_gpio_dir 0xc3d8 /* width RMuint32 */
#define CPU_scard1_gpio_data 0xc3dc /* width RMuint32 */
#define CPU_scard1_gpio_mode 0xc3e0 /* width RMuint32 */
/* CPUBlock registers done */

/* DemuxCipher registers */
/* DemuxCipher registers done */

/* DemuxEngine registers */
#define REG_BASE_demux_engine_0 0x000A0000 /* width RMuint32 */
#define MEM_BASE_demux_engine_0 0x00140000 /* width RMuint32 */
#define PMEM_BASE_demux_engine_0 0x00140000 /* width RMuint32 */
#define DMEM_BASE_demux_engine_0 0x00150000 /* width RMuint32 */
#define REG_BASE_demux_engine_1 0x000b0000 /* width RMuint32 */
#define MEM_BASE_demux_engine_1 0x00160000 /* width RMuint32 */
#define PMEM_BASE_demux_engine_1 0x00160000 /* width RMuint32 */
#define DMEM_BASE_demux_engine_1 0x00170000 /* width RMuint32 */
#define demux_MISC_dr_mode 0x2f00 /* width RMuint32 */
#define demux_MISC_dr_length 0x2f01 /* width RMuint32 */
#define demux_MISC_dr_address 0x2f02 /* width RMuint32 */
#define demux_MISC_dw_mode 0x2f04 /* width RMuint32 */
#define demux_MISC_dw_length 0x2f05 /* width RMuint32 */
#define demux_MISC_dw_address 0x2f06 /* width RMuint32 */
#define demux_MISC_reset0 0x2f08 /* width RMuint32 */
#define demux_MISC_reset1 0x2f09 /* width RMuint32 */
#define demux_MISC_interrupt 0x2f0a /* width RMuint32 */
#define demux_MISC_timer_div 0x2f0b /* width RMuint32 */
#define demux_MISC_timer_count 0x2f0c /* width RMuint32 */
#define demux_mutex0 0x2f10 /* width RMuint32 */
#define demux_mutex1 0x2f11 /* width RMuint32 */
#define demux_mutex2 0x2f12 /* width RMuint32 */
#define demux_mutex3 0x2f13 /* width RMuint32 */
#define demux_mutex4 0x2f14 /* width RMuint32 */
#define demux_mutex5 0x2f15 /* width RMuint32 */
#define demux_mutex6 0x2f16 /* width RMuint32 */
#define demux_mutex7 0x2f17 /* width RMuint32 */
#define demux_GBUSIF_MAIN_WADD 0x2ea0 /* width RMuint32 */
#define demux_GBUSIF_MAIN_RADD 0x2ea1 /* width RMuint32 */
#define demux_GBUSIF_MAIN_BYTE 0x2ea2 /* width RMuint32 */
#define demux_GBUSIF_MAIN_WORD 0x2ea3 /* width RMuint32 */
#define demux_GBUSIF_MAIN_DWORD 0x2ea4 /* width RMuint32 */
#define demux_GBUSIF_MAIN_STATUS 0x2ea5 /* width RMuint32 */
#define demux_GBUSIF_ISR_WADD 0x2ea8 /* width RMuint32 */
#define demux_GBUSIF_ISR_RADD 0x2ea9 /* width RMuint32 */
#define demux_GBUSIF_ISR_BYTE 0x2eaa /* width RMuint32 */
#define demux_GBUSIF_ISR_WORD 0x2eab /* width RMuint32 */
#define demux_GBUSIF_ISR_DWORD 0x2eac /* width RMuint32 */
#define demux_GBUSIF_ISR_STATUS 0x2ead /* width RMuint32 */
#define demux_MBUSIF_w0_add 0x2ec0 /* width RMuint32 */
#define demux_MBUSIF_w0_cnt 0x2ec1 /* width RMuint32 */
#define demux_MBUSIF_w0_skip 0x2ec2 /* width RMuint32 */
#define demux_MBUSIF_w0_cmd 0x2ec3 /* width RMuint32 */
#define demux_MBUSIF_r0_add 0x2ed0 /* width RMuint32 */
#define demux_MBUSIF_r0_cnt 0x2ed1 /* width RMuint32 */
#define demux_MBUSIF_r0_skip 0x2ed2 /* width RMuint32 */
#define demux_MBUSIF_r0_cmd 0x2ed3 /* width RMuint32 */
#define demux_cipher_c2_secret_key 0x2c00 /* width RMuint32, key x 256bytes */
#define demux_cipher_c2_key_lsb 0x2c70 /* width RMuint32, key x  8bytes */
#define demux_cipher_c2_key_msb 0x2c71 /* width RMuint32 */
#define demux_cipher_c2g_ecb_data_lsb 0x2c72 /* width RMuint32 */
#define demux_cipher_c2g_ecb_data_msb 0x2c73 /* width RMuint32 */
#define demux_cipher_c2_flags 0x2c74 /* width RMuint32 */
#define demux_cipher_multi2_syst_key 0x2c80 /* width RMuint32, key x 32bytes */
#define demux_cipher_multi2_data_key 0x2c88 /* width RMuint32, key x  8bytes */
#define demux_cipher_multi2_iv       0x2c8a /* width RMuint32,  iv x  8bytes */
#define demux_cipher_multi2_flags 0x2c8c /* width RMuint32, ??? 0x2e8c */
#define demux_cipher_clock_disable 0x2e8e /* width RMuint32 */
#define demux_cipher_config 0x2c8f /* width RMuint32 */
#define demux_cipher_rc4_key_0 0x2e40 /* width RMuint32 */
#define demux_cipher_rc4_key_1 0x2e41 /* width RMuint32 */
#define demux_cipher_rc4_key_2 0x2e42 /* width RMuint32 */
#define demux_cipher_rc4_key_3 0x2e43 /* width RMuint32 */
#define demux_cipher_rc4_key_4 0x2e44 /* width RMuint32 */
#define demux_cipher_rc4_key_5 0x2e45 /* width RMuint32 */
#define demux_cipher_rc4_key_6 0x2e46 /* width RMuint32 */
#define demux_cipher_rc4_key_7 0x2e47 /* width RMuint32 */
#define demux_cipher_rc4_flags 0x2e48 /* width RMuint32 */
#define demux_cipher_des_key1_1 0x2e50 /* width RMuint32 */
#define demux_cipher_des_key1_2 0x2e51 /* width RMuint32 */
#define demux_cipher_des_key2_1 0x2e52 /* width RMuint32 */
#define demux_cipher_des_key2_2 0x2e53 /* width RMuint32 */
#define demux_cipher_des_key3_1 0x2e54 /* width RMuint32 */
#define demux_cipher_des_key3_2 0x2e55 /* width RMuint32 */
#define demux_cipher_des_IV_1 0x2e56 /* width RMuint32 */
#define demux_cipher_des_IV_2 0x2e57 /* width RMuint32 */
#define demux_cipher_des_flags 0x2e58 /* width RMuint32 */
#define demux_cipher_dvbcsa_key_lsb 0x2e5c /* width RMuint32 */
#define demux_cipher_dvbcsa_key_msb 0x2e5d /* width RMuint32 */
#define demux_cipher_dvbcsa_flags 0x2e5e /* width RMuint32 */
#define demux_cipher_aes_key_1 0x2e60 /* width RMuint32 */
#define demux_cipher_aes_key_2 0x2e61 /* width RMuint32 */
#define demux_cipher_aes_key_3 0x2e62 /* width RMuint32 */
#define demux_cipher_aes_key_4 0x2e63 /* width RMuint32 */
#define demux_cipher_aes_key_5 0x2e64 /* width RMuint32 */
#define demux_cipher_aes_key_6 0x2e65 /* width RMuint32 */
#define demux_cipher_aes_key_7 0x2e66 /* width RMuint32 */
#define demux_cipher_aes_key_8 0x2e67 /* width RMuint32 */
#define demux_cipher_aes_flags 0x2e68 /* width RMuint32 */
#define demux_cipher_aes_IV_1 0x2e69 /* width RMuint32 */
#define demux_cipher_aes_IV_2 0x2e6a /* width RMuint32 */
#define demux_cipher_aes_IV_3 0x2e6b /* width RMuint32 */
#define demux_cipher_aes_IV_4 0x2e6c /* width RMuint32 */
#define demux_cipher_aes_IV_5 0x2e6d /* width RMuint32 */
#define demux_cipher_aes_IV_6 0x2e6e /* width RMuint32 */
#define demux_cipher_aes_IV_7 0x2e6f /* width RMuint32 */
#define demux_cipher_aes_IV_8 0x2e70 /* width RMuint32 */
#define demux_cipher_dvd_cnt 0x2e78 /* width RMuint32 */
#define demux_cipher_dvd_tklo 0x2e7a /* width RMuint32 */
#define demux_cipher_dvd_tkhi 0x2e7b /* width RMuint32 */
#define demux_cipher_dvd_state0 0x2e7c /* width RMuint32 */
#define demux_cipher_dvd_state1 0x2e7d /* width RMuint32 */
#define demux_cw_ram_multi2_syst_key 0x2a00 /* width RMuint32, 16keys x 32bytes */
#define demux_cw_ram_multi2_data_key 0x2a80 /* width RMuint32, 16keys x  8bytes */
#define demux_cw_ram_multi2_iv 0x2aa0 /* width RMuint32, 16keys x  8bytes */
#define demux_cw_ram_rc4_key 0x2ac0 /* width RMuint32,  8keys x 32bytes */
#define demux_cw_ram_aes_key 0x2b00 /* width RMuint32,  6keys x 32bytes */
#define demux_cw_ram_aes_iv 0x2b08 /* width RMuint32,  6keys x 32bytes */
#define demux_cw_ram_dvbcsa_key 0x2b60 /* width RMuint32, 16keys x  8bytes */
#define demux_cw_ram_des_key1 0x2b80 /* width RMuint32, 16keys x  8bytes */
#define demux_cw_ram_des_key2 0x2ba0 /* width RMuint32, 16keys x  8bytes */
#define demux_cw_ram_des_key3 0x2bc0 /* width RMuint32, 16keys x  8bytes */
#define demux_cw_ram_des_iv 0x2be0 /* width RMuint32, 16keys x  8bytes */
#define demux_section_filter_start 0x3800 /* width RMuint32, 32 entries of 12 RMuint32 */
#define demux_hsf_bytes0 0x3e98 /* width RMuint32 */
#define demux_hsf_bytes1 0x3e99 /* width RMuint32 */
#define demux_hsf_bytes2 0x3e9a /* width RMuint32 */
#define demux_hsf_fiter_index 0x3e9b /* width RMuint32 */
#define demux_hsf_status 0x3e9c /* width RMuint32 */
#define demux_hsf_result 0x3e9d /* width RMuint32 */
#define demux_hsf_pending_index 0x3e9e /* width RMuint32 */
#define demux_hsf_host_channel 0x3e9f /* width RMuint32 */
#define demux_channel_status_control 0x3e08 /* width RMuint32 */
#define demux_channel_config_routing 0x3e09 /* width RMuint32 */
#define demux_ts_frame_size 0x3e0a /* width RMuint32 */
#define demux_dv_error_status 0x3e0b /* width RMuint32 */
#define demux_ats_control 0x3e0c /* width RMuint32 */
#define demux_ats0_counter 0x3e0d /* width RMuint32 */
#define demux_ats1_counter 0x3e0e /* width RMuint32 */
#define demux_ats2_counter 0x3e0f /* width RMuint32 */
#define demux_pat0_pidentry 0x3cc0 /* width RMuint32 */
#define demux_pat0_outputmask 0x3cc1 /* width RMuint32 */
#define demux_cat0_pidentry 0x3cc2 /* width RMuint32 */
#define demux_cat0_outputmask 0x3cc3 /* width RMuint32 */
#define demux_mgt0_pidentry 0x3cc4 /* width RMuint32 */
#define demux_mgt0_outputmask 0x3cc5 /* width RMuint32 */
#define demux_pcr0_pidentry 0x3cc6 /* width RMuint32 */
#define demux_dit0_pidentry 0x3cc7 /* width RMuint32 */
#define demux_pat1_pidentry 0x3cc8 /* width RMuint32 */
#define demux_pat1_outputmask 0x3cc9 /* width RMuint32 */
#define demux_cat1_pidentry 0x3cca /* width RMuint32 */
#define demux_cat1_outputmask 0x3ccb /* width RMuint32 */
#define demux_mgt1_pidentry 0x3ccc /* width RMuint32 */
#define demux_mgt1_outputmask 0x3ccd /* width RMuint32 */
#define demux_pcr1_pidentry 0x3cce /* width RMuint32 */
#define demux_dit1_pidentry 0x3ccf /* width RMuint32 */
#define demux_pat2_pidentry 0x3cd0 /* width RMuint32 */
#define demux_pat2_outputmask 0x3cd1 /* width RMuint32 */
#define demux_cat2_pidentry 0x3cd2 /* width RMuint32 */
#define demux_cat2_outputmask 0x3cd3 /* width RMuint32 */
#define demux_mgt2_pidentry 0x3cd4 /* width RMuint32 */
#define demux_mgt2_outputmask 0x3cd5 /* width RMuint32 */
#define demux_pcr2_pidentry 0x3cd6 /* width RMuint32 */
#define demux_dit2_pidentry 0x3cd7 /* width RMuint32 */
#define demux_splice0_status 0x3ce0 /* width RMuint32 */
#define demux_splice1_status 0x3ce1 /* width RMuint32 */
#define demux_splice2_status 0x3ce2 /* width RMuint32 */
#define demux_pid_bank_control 0x3ce8 /* width RMuint32 */
#define demux_pid_bank 0x3d00 /* width RMuint32, 128 entries of 64 bits */
#define TDMX_gpio_data 0x2e0c /* width RMuint32 */
#define TDMX_gpio_dir 0x2e0d /* width RMuint32 */
#define TDMX_gpio_select 0x2e0e /* width RMuint32 */
#define TSOut0_read_ptr 0x2e3c /* width RMuint32 */
#define TSOut0_config 0x2e3d /* width RMuint32 */
#define TSOut1_read_ptr 0x2e3e /* width RMuint32 */
#define TSOut1_config 0x2e3f /* width RMuint32 */
#define demux_kl_key_31_00 0x2d60 /* width RMuint32 */
#define demux_kl_key_63_32 0x2d61 /* width RMuint32 */
#define demux_kl_key_95_64 0x2d62 /* width RMuint32 */
#define demux_kl_key_127_96 0x2d63 /* width RMuint32 */
#define demux_kl_key_159_128 0x2d64 /* width RMuint32 */
#define demux_kl_key_191_160 0x2d65 /* width RMuint32 */
#define demux_kl_key_control 0x2d66 /* width RMuint32 */
#define demux_kl_aes_iv 0x3b80 /* width RMuint32, 16 iv of 16 bytes */
#define demux_kl_des_iv 0x3bc0 /* width RMuint32, 16 iv of 8 bytes */
#define demux_private_div27_ctl 0x3b29 /* width RMuint32 */
#define demux_spi_write_ptr0 0x1e08 /* width RMuint32 */
#define demux_spi_write_ptr1 0x1e09 /* width RMuint32 */
#define demux_spi_write_ptr2 0x1e0a /* width RMuint32 */
#define demux_spi_write_ptr3 0x1e0b /* width RMuint32 */
#define demux_spi_routing 0x1e0c /* width RMuint32 */
#define demux_spi_clk_phase 0x1e0d /* width RMuint32 */
#define demux_spi_sync_bytes 0x1e0e /* width RMuint32 */
#define demux_idma_write_ptr 0x1e18 /* width RMuint32 */
#define demux_idma_cnt 0x1e19 /* width RMuint32 */
#define demux_odma_read_ptr 0x1e20 /* width RMuint32 */
#define demux_odma_cnt 0x1e21 /* width RMuint32 */
#define demux_odma_sc_stat 0x1e22 /* width RMuint32 */
#define demux_odma_sc_match 0x1e23 /* width RMuint32 */
#define demux_sbox_mode 0x1e28 /* width RMuint32 */
#define demux_MISC_UNRESET_MASK 0xd800 /* width RMuint32 */
#define demux_MISC_RESET_MASK 0xd8d8 /* width RMuint32 */
#define demux_SP_init 0x07fe /* width RMuint32 */
/* DemuxEngine registers done */

/* DemuxOutput registers */
/* DemuxOutput registers done */

/* DemuxTask registers */
/* DemuxTask registers done */

/* DispColorBars registers */
#define VO_color_bars_reset_bit 0x0b /* width RMuint32 */
#define VO_color_bars_ctrl 0x0d00 /* width RMuint32 */
#define VO_color_bars_size 0x0d04 /* width RMuint32 */
/* DispColorBars registers done */

/* DispComponentOut registers */
#define VO_component_out_reset_bit 0x14 /* width RMuint32 */
#define VO_component_out_conv0 0x1000 /* width RMuint32 */
#define VO_component_out_conv1 0x1004 /* width RMuint32 */
#define VO_component_out_conv2 0x1008 /* width RMuint32 */
#define VO_component_out_conv3 0x100c /* width RMuint32 */
#define VO_component_out_conv4 0x1010 /* width RMuint32 */
#define VO_component_out_conv5 0x1014 /* width RMuint32 */
#define VO_component_out_xoffset_field 0x1018 /* width RMuint32 */
#define VO_component_out_yoffset 0x101c /* width RMuint32 */
#define VO_component_out_TV_config 0x1040 /* width RMuint32 */
#define VO_component_out_TV_size 0x1044 /* width RMuint32 */
#define VO_component_out_TV_hsync 0x1048 /* width RMuint32 */
#define VO_component_out_TV_vsync_O_0 0x104c /* width RMuint32 */
#define VO_component_out_TV_vsync_O_1 0x1050 /* width RMuint32 */
#define VO_component_out_TV_vsync_E_0 0x1054 /* width RMuint32 */
#define VO_component_out_TV_vsync_E_1 0x1058 /* width RMuint32 */
#define VO_component_out_TV_HD_hsync_info 0x105c /* width RMuint32 */
#define VO_component_out_TV_HD_vsync 0x1060 /* width RMuint32 */
#define VO_component_out_TV_CGMS 0x1064 /* width RMuint32 */
#define VO_component_out_TV_CC_AGC 0x1068 /* width RMuint32 */
#define VO_component_out_TV_test_config 0x106c /* width RMuint32 */
#define VO_component_out_TV_MV_N_0_22 0x1080 /* width RMuint32 */
#define VO_component_out_TV_MV_N_1_2_3_4 0x1084 /* width RMuint32 */
#define VO_component_out_TV_MV_N_5_6_7_8 0x1088 /* width RMuint32 */
#define VO_component_out_TV_MV_N_9_10_11 0x108c /* width RMuint32 */
#define VO_component_out_TV_MV_N_12_13_14 0x1090 /* width RMuint32 */
#define VO_component_out_TV_MV_N_15_16_17_18 0x1094 /* width RMuint32 */
#define VO_component_out_TV_MV_N_19_20_21 0x1098 /* width RMuint32 */
#define VO_component_out_vbi_EIA805B_ctrl 0x10c0 /* width RMuint32 */
#define VO_component_out_vbi_EIA805B_data0 0x10c0 /* width RMuint32 */
#define VO_component_out_vbi_EIA805B_data1 0x10c4 /* width RMuint32 */
#define VO_component_out_vbi_EIA805B_data2 0x10c8 /* width RMuint32 */
#define VO_component_out_vbi_EIA805B_data3 0x10d0 /* width RMuint32 */
#define VO_component_out_TV_teletext_config 0x1070 /* width RMuint32 */
#define VO_component_out_TV_config2 0x1074 /* width RMuint32 */
#define VO_component_out_TV_cav_minmax 0x1078 /* width RMuint32 */
#define VO_component_out_TV_timing_sync 0x107c /* width RMuint32 */
/* DispComponentOut registers done */

/* DispCompositeOut registers */
#define VO_composite_out_reset_bit 0x15 /* width RMuint32 */
#define VO_composite_out_bcs 0x1100 /* width RMuint32 */
#define VO_composite_out_Xoffset 0x1104 /* width RMuint32 */
#define VO_composite_out_Yoffset 0x1108 /* width RMuint32 */
#define VO_composite_out_TV_config 0x1140 /* width RMuint32 */
#define VO_composite_out_TV_size 0x1144 /* width RMuint32 */
#define VO_composite_out_TV_hsync 0x1148 /* width RMuint32 */
#define VO_composite_out_TV_vsync_O_0 0x114c /* width RMuint32 */
#define VO_composite_out_TV_vsync_O_1 0x1150 /* width RMuint32 */
#define VO_composite_out_TV_vsync_E_0 0x1154 /* width RMuint32 */
#define VO_composite_out_TV_vsync_E_1 0x1158 /* width RMuint32 */
#define VO_composite_out_TV_CGMS 0x1164 /* width RMuint32 */
#define VO_composite_out_TV_CC_AGC 0x1168 /* width RMuint32 */
#define VO_composite_out_TV_test_config 0x116c /* width RMuint32 */
#define VO_composite_out_TV_MV_N_0_22 0x1180 /* width RMuint32 */
#define VO_composite_out_TV_MV_N_1_2_3_4 0x1184 /* width RMuint32 */
#define VO_composite_out_TV_MV_N_5_6_7_8 0x1188 /* width RMuint32 */
#define VO_composite_out_TV_MV_N_9_10_11 0x118c /* width RMuint32 */
#define VO_composite_out_TV_MV_N_12_13_14 0x1190 /* width RMuint32 */
#define VO_composite_out_TV_MV_N_15_16_17_18 0x1194 /* width RMuint32 */
#define VO_composite_out_TV_MV_N_19_20_21 0x1198 /* width RMuint32 */
/* DispCompositeOut registers done */

/* DispConstrainedImage registers */
#define VO_CI_reset_bit 0x18 /* width RMuint32 */
#define VO_CI_read_reset_bit 0x19 /* width RMuint32 */
#define VO_CI_config 0x1800 /* width RMuint32 */
/* DispConstrainedImage registers done */

/* DispCRTMultiScaler registers */
#define VO_CRT_reset_bit 0x06 /* width RMuint32 */
#define VO_CRT_format_hds 0x0600 /* width RMuint32 */
#define VO_CRT_output_size 0x0604 /* width RMuint32 */
#define VO_CRT_scale_factor 0x0608 /* width RMuint32 */
#define VO_CRT_scale_phase 0x060c /* width RMuint32 */
#define VO_CRT_phase 0x060c /* width RMuint32 */
#define VO_CRT_alpha_routing 0x0610 /* width RMuint32 */
#define VO_CRT_key_color 0x0614 /* width RMuint32 */
#define VO_CRT_bcs 0x0618 /* width RMuint32 */
#define VO_CRT_strip_edge 0x061C /* width RMuint32 */
#define VO_CRT_nonlinear_0 0x0620 /* width RMuint32 */
#define VO_CRT_nonlinear_1 0x0624 /* width RMuint32 */
#define VO_CRT_tiling 0x0628 /* width RMuint32 */
#define VO_CRT_bcs2 0x062c /* width RMuint32 */
#define VO_CRT_luma_key 0x0630 /* width RMuint32 */
#define VO_CRT_lut 0xb000 /* width RMuint32 */
#define VO_CRT_lut0 0xb000 /* width RMuint32 */
/* DispCRTMultiScaler registers done */

/* DispDeinterlacer registers */
#define VO_deinterlacing_reset_bit 0x1B /* width RMuint32 */
#define VO_deinterlacing_size_y 0x1D00 /* width RMuint32 */
#define VO_deinterlacing_size_uv 0x1D04 /* width RMuint32 */
#define VO_deinterlacing_param_uv 0x1D08 /* width RMuint32 */
#define VO_deinterlacing_error_0 0x1D0C /* width RMuint32 */
#define VO_deinterlacing_error_1 0x1D10 /* width RMuint32 */
#define VO_deinterlacing_min_win0 0x1D14 /* width RMuint32 */
#define VO_deinterlacing_max_win0 0x1D18 /* width RMuint32 */
#define VO_deinterlacing_min_win1 0x1D1C /* width RMuint32 */
#define VO_deinterlacing_max_win1 0x1D20 /* width RMuint32 */
#define VO_deinterlacing_alpha_0 0x1D24 /* width RMuint32 */
#define VO_deinterlacing_alpha_1 0x1D28 /* width RMuint32 */
#define VO_deinterlacing_control 0x1D2C /* width RMuint32 */
#define VO_deinterlacing_22_pulldown_lsb 0x1D30 /* width RMuint32 */
#define VO_deinterlacing_22_pulldown_msb 0x1D34 /* width RMuint32 */
#define VO_deinterlacing_22_pulldown_win0_lsb 0x1D38 /* width RMuint32 */
#define VO_deinterlacing_22_pulldown_win0_msb 0x1D3C /* width RMuint32 */
#define VO_deinterlacing_22_pulldown_win0_00_lsb 0x1D40 /* width RMuint32 */
#define VO_deinterlacing_22_pulldown_win0_00_msb 0x1D44 /* width RMuint32 */
#define VO_deinterlacing_22_pulldown_win0_01_lsb 0x1D48 /* width RMuint32 */
#define VO_deinterlacing_22_pulldown_win0_01_msb 0x1D4C /* width RMuint32 */
#define VO_deinterlacing_22_pulldown_win0_10_lsb 0x1D50 /* width RMuint32 */
#define VO_deinterlacing_22_pulldown_win0_10_msb 0x1D54 /* width RMuint32 */
#define VO_deinterlacing_22_pulldown_win0_11_lsb 0x1D58 /* width RMuint32 */
#define VO_deinterlacing_22_pulldown_win0_11_msb 0x1D5C /* width RMuint32 */
#define VO_deinterlacing_22_pulldown_win1_lsb 0x1D60 /* width RMuint32 */
#define VO_deinterlacing_22_pulldown_win1_msb 0x1D64 /* width RMuint32 */
#define VO_deinterlacing_22_pulldown_win1_00_lsb 0x1D68 /* width RMuint32 */
#define VO_deinterlacing_22_pulldown_win1_00_msb 0x1D6C /* width RMuint32 */
#define VO_deinterlacing_22_pulldown_win1_01_lsb 0x1D70 /* width RMuint32 */
#define VO_deinterlacing_22_pulldown_win1_01_msb 0x1D74 /* width RMuint32 */
#define VO_deinterlacing_22_pulldown_win1_10_lsb 0x1D78 /* width RMuint32 */
#define VO_deinterlacing_22_pulldown_win1_10_msb 0x1D7C /* width RMuint32 */
#define VO_deinterlacing_22_pulldown_win1_11_lsb 0x1D80 /* width RMuint32 */
#define VO_deinterlacing_22_pulldown_win1_11_msb 0x1D84 /* width RMuint32 */
#define VO_deinterlacing_32_pulldown_lsb 0x1D88 /* width RMuint32 */
#define VO_deinterlacing_32_pulldown_msb 0x1D8C /* width RMuint32 */
#define VO_deinterlacing_32_pulldown_win0_lsb 0x1D90 /* width RMuint32 */
#define VO_deinterlacing_32_pulldown_win0_msb 0x1D94 /* width RMuint32 */
#define VO_deinterlacing_32_pulldown_win0_00_lsb 0x1D98 /* width RMuint32 */
#define VO_deinterlacing_32_pulldown_win0_00_msb 0x1D9C /* width RMuint32 */
#define VO_deinterlacing_32_pulldown_win0_01_lsb 0x1DA0 /* width RMuint32 */
#define VO_deinterlacing_32_pulldown_win0_01_msb 0x1DA4 /* width RMuint32 */
#define VO_deinterlacing_32_pulldown_win0_10_lsb 0x1DA8 /* width RMuint32 */
#define VO_deinterlacing_32_pulldown_win0_10_msb 0x1DAC /* width RMuint32 */
#define VO_deinterlacing_32_pulldown_win0_11_lsb 0x1DB0 /* width RMuint32 */
#define VO_deinterlacing_32_pulldown_win0_11_msb 0x1DB4 /* width RMuint32 */
#define VO_deinterlacing_32_pulldown_win1_lsb 0x1DB8 /* width RMuint32 */
#define VO_deinterlacing_32_pulldown_win1_msb 0x1DBC /* width RMuint32 */
#define VO_deinterlacing_32_pulldown_win1_00_lsb 0x1DC0 /* width RMuint32 */
#define VO_deinterlacing_32_pulldown_win1_00_msb 0x1DC4 /* width RMuint32 */
#define VO_deinterlacing_32_pulldown_win1_01_lsb 0x1DC8 /* width RMuint32 */
#define VO_deinterlacing_32_pulldown_win1_01_msb 0x1DCC /* width RMuint32 */
#define VO_deinterlacing_32_pulldown_win1_10_lsb 0x1DD0 /* width RMuint32 */
#define VO_deinterlacing_32_pulldown_win1_10_msb 0x1DD4 /* width RMuint32 */
#define VO_deinterlacing_32_pulldown_win1_11_lsb 0x1DD8 /* width RMuint32 */
#define VO_deinterlacing_32_pulldown_win1_11_msb 0x1DDC /* width RMuint32 */
/* DispDeinterlacer registers done */

/* DispDigitalOut registers */
#define VO_digit_out_reset_bit 0x12 /* width RMuint32 */
#define VO_digit_out_conv0 0x0e00 /* width RMuint32 */
#define VO_digit_out_conv1 0x0e04 /* width RMuint32 */
#define VO_digit_out_conv2 0x0e08 /* width RMuint32 */
#define VO_digit_out_conv3 0x0e0c /* width RMuint32 */
#define VO_digit_out_conv4 0x0e10 /* width RMuint32 */
#define VO_digit_out_conv5 0x0e14 /* width RMuint32 */
#define VO_digit_out_format 0x0e20 /* width RMuint32 */
#define VO_digit_out_Xoffset 0x0e24 /* width RMuint32 */
#define VO_digit_out_Yoffset 0x0e28 /* width RMuint32 */
#define VO_digit_out_hz_sync 0x0e2c /* width RMuint32 */
#define VO_digit_out_vt_sync 0x0e30 /* width RMuint32 */
#define VO_digit_out_vsync_coord 0x0e34 /* width RMuint32 */
#define VO_digit_out_sync_ext_sync 0x0e38 /* width RMuint32 */
#define VO_digit_out_color_depth 0x0e3c /* width RMuint32 */
#define VO_digit_out_pads_config 0x0020 /* width RMuint32 */
#define VO_pads_config 0x0020 /* width RMuint32 */
#define VO_digit_out_gamma_lut0 0xf000 /* width RMuint32 */
#define VO_digit_out_temp_lut0 0xf400 /* width RMuint32 */
#define VO_digit_out_sync_ext_sync 0x0e38 /* width RMuint32 */
#define VO_pads_delay_limits 0x0024 /* width RMuint32 */
#define VO_pads_ref_delay_limits 0x0028 /* width RMuint32 */
#define VO_pads_ref_delay_init 0x002C /* width RMuint32 */
#define VO_pads_DLL_config 0x0030 /* width RMuint32 */
/* DispDigitalOut registers done */

/* DispGFXMultiScaler registers */
#define VO_GFX_reset_bit 0x07 /* width RMuint32 */
#define VO_GFX_format_hds 0x0700 /* width RMuint32 */
#define VO_GFX_output_size 0x0704 /* width RMuint32 */
#define VO_GFX_scale_factor 0x0708 /* width RMuint32 */
#define VO_GFX_scale_phase 0x070c /* width RMuint32 */
#define VO_GFX_phase 0x070c /* width RMuint32 */
#define VO_GFX_alpha_routing 0x0710 /* width RMuint32 */
#define VO_GFX_key_color 0x0714 /* width RMuint32 */
#define VO_GFX_bcs 0x0718 /* width RMuint32 */
#define VO_GFX_strip_edge 0x071C /* width RMuint32 */
#define VO_GFX_nonlinear_0 0x0720 /* width RMuint32 */
#define VO_GFX_nonlinear_1 0x0724 /* width RMuint32 */
#define VO_GFX_tiling 0x0728 /* width RMuint32 */
#define VO_GFX_lut 0xc000 /* width RMuint32 */
#define VO_GFX_lut0 0xc000 /* width RMuint32 */
#define VO_GFX_bcs2 0x072c /* width RMuint32 */
#define VO_GFX_luma_key 0x0730 /* width RMuint32 */
#define VO_mpscaler_format_hds 0x8800 /* width RMuint32 */
#define VO_mpscaler_alpha 0x8804 /* width RMuint32 */
#define VO_mpscaler_key_color_b 0x8808 /* width RMuint32 */
#define VO_mpscaler_key_color_g 0x880c /* width RMuint32 */
#define VO_mpscaler_key_color_r 0x8810 /* width RMuint32 */
#define VO_mpscaler_strip 0x8814 /* width RMuint32 */
#define VO_mpscaler_scaler0_conf 0x8880 /* width RMuint32 */
#define VO_mpscaler_scaler0_scale_factor 0x8884 /* width RMuint32 */
#define VO_mpscaler_scaler0_panoramic 0x8888 /* width RMuint32 */
#define VO_mpscaler_scaler0_coefficients 0x8890 /* width RMuint32 */
#define VO_mpscaler_scaler1_conf 0x8900 /* width RMuint32 */
#define VO_mpscaler_scaler1_scale_factor 0x8904 /* width RMuint32 */
#define VO_mpscaler_scaler1_panoramic 0x8908 /* width RMuint32 */
#define VO_mpscaler_scaler1_coefficients 0x8910 /* width RMuint32 */
#define VO_mpscaler_scaler2_conf 0x8980 /* width RMuint32 */
#define VO_mpscaler_scaler2_scale_factor 0x8984 /* width RMuint32 */
#define VO_mpscaler_scaler2_panoramic 0x8988 /* width RMuint32 */
#define VO_mpscaler_scaler2_coefficients 0x8990 /* width RMuint32 */
#define VO_mpscaler_scaler3_conf 0x8a00 /* width RMuint32 */
#define VO_mpscaler_scaler3_scale_factor 0x8a04 /* width RMuint32 */
#define VO_mpscaler_scaler3_panoramic 0x8a08 /* width RMuint32 */
#define VO_mpscaler_scaler3_coefficients 0x8a10 /* width RMuint32 */
#define VO_mpscaler_scaler4_conf 0x8a80 /* width RMuint32 */
#define VO_mpscaler_scaler4_scale_factor 0x8a84 /* width RMuint32 */
#define VO_mpscaler_scaler4_panoramic 0x8a88 /* width RMuint32 */
#define VO_mpscaler_scaler4_coefficients 0x8a90 /* width RMuint32 */
#define VO_mpscaler_csc_m00 0x8840 /* width RMuint32 */
#define VO_mpscaler_csc_m01 0x8844 /* width RMuint32 */
#define VO_mpscaler_csc_m02 0x8848 /* width RMuint32 */
#define VO_mpscaler_csc_m10 0x884c /* width RMuint32 */
#define VO_mpscaler_csc_m11 0x8850 /* width RMuint32 */
#define VO_mpscaler_csc_m12 0x8854 /* width RMuint32 */
#define VO_mpscaler_csc_m20 0x8858 /* width RMuint32 */
#define VO_mpscaler_csc_m21 0x885c /* width RMuint32 */
#define VO_mpscaler_csc_m22 0x8860 /* width RMuint32 */
#define VO_mpscaler_csc_r0 0x8864 /* width RMuint32 */
#define VO_mpscaler_csc_r1 0x8868 /* width RMuint32 */
#define VO_mpscaler_csc_r2 0x886c /* width RMuint32 */
#define VO_mpscaler_csc_fe_alpha 0x8870 /* width RMuint32 */
/* DispGFXMultiScaler registers done */

/* DispGraphicInput registers */
#define VO_graph_in_reset_bit 0x11 /* width RMuint32 */
#define VO_graph_in_format 0x0c00 /* width RMuint32 */
#define VO_graph_in_alpha_routing 0x0c04 /* width RMuint32 */
#define VO_graph_in_key_color 0x0c08 /* width RMuint32 */
#define VO_graph_in_data_size 0x0c0c /* width RMuint32 */
#define VO_graph_in_data_Xoffset 0x0c10 /* width RMuint32 */
#define VO_graph_in_data_Yoffset 0x0c14 /* width RMuint32 */
#define VO_graph_in_hz_sync 0x0c18 /* width RMuint32 */
#define VO_graph_in_vt_sync 0x0c1c /* width RMuint32 */
#define VO_graph_in_sync_coord 0x0c20 /* width RMuint32 */
#define VO_graph_in_sync_offset 0x0c24 /* width RMuint32 */
#define VO_graph_in_top_vbi 0x0c28 /* width RMuint32 */
#define VO_graph_in_bot_vbi 0x0c2c /* width RMuint32 */
#define VO_graph_in_counters 0x0c30 /* width RMuint32 */
#define VO_graph_in_format2 0x0c34 /* width RMuint32 */
#define VO_graph_in_counters2 0x0c38 /* width RMuint32 */
#define VO_graph_in_vbi_size 0x0c3c /* width RMuint32 */
#define VO_graph_in_vbi_vsm 0x0c40 /* width RMuint32 */
#define VO_graph_in_vbi_Voffset 0x0c44 /* width RMuint32 */
/* DispGraphicInput registers done */

/* DispHardwareCursor registers */
#define VO_cursor_reset_bit 0x01 /* width RMuint32 */
#define VO_cursor_size_ctrl 0x0100 /* width RMuint32 */
#define VO_cursor_lut 0x0140 /* width RMuint32 */
#define VO_cursor_lut0 0x0140 /* width RMuint32 */
#define VO_cursor_lut1 0x0144 /* width RMuint32 */
#define VO_cursor_lut2 0x0148 /* width RMuint32 */
#define VO_cursor_lut3 0x014c /* width RMuint32 */
#define VO_cursor_lut4 0x0150 /* width RMuint32 */
#define VO_cursor_lut5 0x0154 /* width RMuint32 */
#define VO_cursor_lut6 0x0158 /* width RMuint32 */
#define VO_cursor_lut7 0x015c /* width RMuint32 */
#define VO_cursor_lut8 0x0160 /* width RMuint32 */
#define VO_cursor_lut9 0x0164 /* width RMuint32 */
#define VO_cursor_lut10 0x0168 /* width RMuint32 */
#define VO_cursor_lut11 0x016c /* width RMuint32 */
#define VO_cursor_lut12 0x0170 /* width RMuint32 */
#define VO_cursor_lut13 0x0174 /* width RMuint32 */
#define VO_cursor_lut14 0x0178 /* width RMuint32 */
#define VO_cursor_lut15 0x017c /* width RMuint32 */
#define VO_cursor_pix 0x8000 /* width RMuint32 */
#define VO_cursor_pix0 0x8000 /* width RMuint32 */
/* DispHardwareCursor registers done */

/* DispHDSDConverter registers */
#define VO_HDSD_reset_bit 0x0c /* width RMuint32 */
#define VO_HDSD_read_reset_bit 0x0d /* width RMuint32 */
#define VO_HDSD_config 0x1300 /* width RMuint32 */
#define VO_HDSD_xscale 0x1304 /* width RMuint32 */
#define VO_HDSD_yscale 0x1308 /* width RMuint32 */
#define VO_HDSD_dump 0x130c /* width RMuint32 */
/* DispHDSDConverter registers done */

/* DisplayBlock registers */
#define REG_BASE_display_block 0x00070000 /* width RMuint32 */
#define PMEM_BASE_display_block 0x00300000 /* width RMuint32 */
#define VO_run 0x0000 /* width RMuint32 */
#define VO_reset_datapath 0x0004 /* width RMuint32 */
#define VO_reset_timing 0x0008 /* width RMuint32 */
#define VO_reset_config 0x000c /* width RMuint32 */
#define VO_reset_mode_0 0x0014 /* width RMuint32 */
#define VO_reset_mode_1 0x0018 /* width RMuint32 */
#define VIF_w0 0x4000 /* width RMuint32 */
#define VIF_w1 0x4100 /* width RMuint32 */
#define VIF_w2 0x4200 /* width RMuint32 */
#define VIF_w3 0x4F00 /* width RMuint32 */
#define VIF_r0 0x4300 /* width RMuint32 */
#define VIF_r1 0x4400 /* width RMuint32 */
#define VIF_r2 0x4500 /* width RMuint32 */
#define VIF_r3 0x4600 /* width RMuint32 */
#define VIF_r4 0x4700 /* width RMuint32 */
#define VIF_r5 0x4800 /* width RMuint32 */
#define VIF_r6 0x4900 /* width RMuint32 */
#define VIF_r7 0x4A00 /* width RMuint32 */
#define VIF_r8 0x4B00 /* width RMuint32 */
#define VIF_r9 0x4C00 /* width RMuint32 */
#define VIF_r10 0x4D00 /* width RMuint32 */
#define VIF_r11 0x4E00 /* width RMuint32 */
#define VIF_r12 0x5000 /* width RMuint32 */
#define VIF_r13 0x5100 /* width RMuint32 */
#define VIF_r14 0x5200 /* width RMuint32 */
#define VIF_r15 0x5300 /* width RMuint32 */
#define VIF_w4 0x5400 /* width RMuint32 */
#define VO_dac_mux_config0 0x1940 /* width RMuint32 */
#define VO_dac_mux_config1 0x1944 /* width RMuint32 */
#define VIF_offs 0x0100 /* width RMuint32 */
#define VIF_add 0x0000 /* width RMuint32 */
#define VIF_cnt 0x0004 /* width RMuint32 */
#define VIF_skip 0x0008 /* width RMuint32 */
#define VIF_cmd 0x000c /* width RMuint32 */
#define VIF_addB 0x0010 /* width RMuint32 */
#define VIF_cntB 0x0014 /* width RMuint32 */
#define VIF_skipB 0x0018 /* width RMuint32 */
#define VBUS_IDLE 0x0 /* width RMuint32 */
#define VBUS_LINEAR 0x1 /* width RMuint32 */
#define VBUS_DOUBLE 0x2 /* width RMuint32 */
#define VBUS_RECTANGLE 0x3 /* width RMuint32 */
#define VBUS_DOUBLE_FIELD 0x4 /* width RMuint32 */
#define VBUS_DOUBLE_RECTANGLE 0x5 /* width RMuint32 */
#define VBUS_8BYTE_COLUMN 0x6 /* width RMuint32 */
#define VBUS_VOID 0x8 /* width RMuint32 */
#define VBUS_LINEAR_VOID 0x9 /* width RMuint32 */
#define VBUS_DOUBLE_VOID 0xa /* width RMuint32 */
#define VBUS_RECTANGLE_VOID 0xb /* width RMuint32 */
#define VBUS_DOUBLE_FIELD_VOID 0xc /* width RMuint32 */
#define VBUS_DOUBLE_RECTANGLE_VOID 0xd /* width RMuint32 */
#define VBUS_8BYTE_COLUMN_VOID 0xe /* width RMuint32 */
/* DisplayBlock registers done */

/* DisplayHDMITx registers */
#define VO_hdmi_reset_bit 0x17 /* width RMuint32 */
#define VO_hdmi_regmap 0x3800 /* width RMuint32 */
#define VO_hdmi_config 0x3d00 /* width RMuint32 */
#define VO_hdmi_ctrl 0x3d04 /* width RMuint32 */
#define VO_hdmi_write 0x3d08 /* width RMuint32 */
#define VO_hdmi_read 0x3d0c /* width RMuint32 */
#define VO_hdmi_test0 0x3d10 /* width RMuint32 */
#define VO_hdmi_test1 0x3d14 /* width RMuint32 */
#define VO_hdmi_test2 0x3d18 /* width RMuint32 */
#define VO_hdmi_test3 0x3d1c /* width RMuint32 */
#define VO_hdmi_i2c 0x3dc0 /* width RMuint32 */
#define VO_hdmi_keymem 0x3e00 /* width RMuint32 */
/* DisplayHDMITx registers done */

/* DisplayHDMIRx registers */
#define VO_hdmi_rx_reset_bit 0x1e /* width RMuint32 */
#define VO_hdmi_rx_regmap 0xb000 /* width RMuint32 */
#define VO_hdmi_rx_keymem 0xbc00 /* width RMuint32 */
/* DisplayHDMIRx registers done */

/* DispMainAnalogOut registers */
#define VO_main_analog_reset_bit 0x13 /* width RMuint32 */
#define VO_main_analog_conv0 0x0f00 /* width RMuint32 */
#define VO_main_analog_conv1 0x0f04 /* width RMuint32 */
#define VO_main_analog_conv2 0x0f08 /* width RMuint32 */
#define VO_main_analog_conv3 0x0f0c /* width RMuint32 */
#define VO_main_analog_conv4 0x0f10 /* width RMuint32 */
#define VO_main_analog_conv5 0x0f14 /* width RMuint32 */
#define VO_main_analog_xoffset_field 0x0f18 /* width RMuint32 */
#define VO_main_analog_yoffset 0x0f1c /* width RMuint32 */
#define VO_main_analog_cvbs_conv0 0x0f20 /* width RMuint32 */
#define VO_main_analog_cvbs_conv1 0x0f24 /* width RMuint32 */
#define VO_main_analog_cvbs_conv2 0x0f28 /* width RMuint32 */
#define VO_main_analog_cvbs_conv3 0x0f2c /* width RMuint32 */
#define VO_main_analog_cvbs_conv4 0x0f30 /* width RMuint32 */
#define VO_main_analog_cvbs_conv5 0x0f34 /* width RMuint32 */
#define VO_main_analog_TV_config 0x0f40 /* width RMuint32 */
#define VO_main_analog_TV_size 0x0f44 /* width RMuint32 */
#define VO_main_analog_TV_hsync 0x0f48 /* width RMuint32 */
#define VO_main_analog_TV_vsync_O_0 0x0f4c /* width RMuint32 */
#define VO_main_analog_TV_vsync_O_1 0x0f50 /* width RMuint32 */
#define VO_main_analog_TV_vsync_E_0 0x0f54 /* width RMuint32 */
#define VO_main_analog_TV_vsync_E_1 0x0f58 /* width RMuint32 */
#define VO_main_analog_TV_HD_hsync_info 0x0f5c /* width RMuint32 */
#define VO_main_analog_TV_HD_vsync 0x0f60 /* width RMuint32 */
#define VO_main_analog_TV_CGMS 0x0f64 /* width RMuint32 */
#define VO_main_analog_TV_CC_AGC 0x0f68 /* width RMuint32 */
#define VO_main_analog_TV_test_config 0x0f6c /* width RMuint32 */
#define VO_main_analog_TV_teletext_config 0x0f70 /* width RMuint32 */
#define VO_main_analog_TV_config2 0x0f74 /* width RMuint32 */
#define VO_main_analog_TV_cav_minmax 0x0f78 /* width RMuint32 */
#define VO_main_analog_TV_timing_sync 0x0f7c /* width RMuint32 */
#define VO_main_analog_TV_MV_N_0_22 0x0f80 /* width RMuint32 */
#define VO_main_analog_TV_MV_N_1_2_3_4 0x0f84 /* width RMuint32 */
#define VO_main_analog_TV_MV_N_5_6_7_8 0x0f88 /* width RMuint32 */
#define VO_main_analog_TV_MV_N_9_10_11 0x0f8c /* width RMuint32 */
#define VO_main_analog_TV_MV_N_12_13_14 0x0f90 /* width RMuint32 */
#define VO_main_analog_TV_MV_N_15_16_17_18 0x0f94 /* width RMuint32 */
#define VO_main_analog_TV_MV_N_19_20_21 0x0f98 /* width RMuint32 */
#define VO_main_analog_vbi_EIA805B_ctrl 0x0fc0 /* width RMuint32 */
#define VO_main_analog_vbi_EIA805B_data0 0x0fc0 /* width RMuint32 */
#define VO_main_analog_vbi_EIA805B_data1 0x0fc4 /* width RMuint32 */
#define VO_main_analog_vbi_EIA805B_data2 0x0fc8 /* width RMuint32 */
#define VO_main_analog_vbi_EIA805B_data3 0x0fd0 /* width RMuint32 */
#define VO_main_analog_tlxt0 0xe000 /* width RMuint32 */
#define VO_main_analog_TV_timing_sync 0x0f7c /* width RMuint32 */
/* DispMainAnalogOut registers done */

/* DispMainMixer registers */
#define VO_mix_reset_bit 0x08 /* width RMuint32 */
#define VO_mix_gfx_pos 0x0800 /* width RMuint32 */
#define VO_mix_crt_pos 0x0804 /* width RMuint32 */
#define VO_mix_vcr_pos 0x0808 /* width RMuint32 */
#define VO_mix_sp_pos 0x080C /* width RMuint32 */
#define VO_mix_mv_pos 0x0810 /* width RMuint32 */
#define VO_mix_osd_pos 0x0814 /* width RMuint32 */
#define VO_mix_gin_pos 0x0818 /* width RMuint32 */
#define VO_mix_cur_pos 0x081C /* width RMuint32 */
#define VO_mix_index 0x0820 /* width RMuint32 */
#define VO_mix_frame_size 0x0824 /* width RMuint32 */
#define VO_mix_background 0x0828 /* width RMuint32 */
/* DispMainMixer registers done */

/* DispMainVideoScaler registers */
#define VO_main_reset_bit 0x04 /* width RMuint32 */
#define VO_main_format_hds 0x0400 /* width RMuint32 */
#define VO_main_output_size 0x0404 /* width RMuint32 */
#define VO_main_scale_factor 0x0408 /* width RMuint32 */
#define VO_main_scale_phase 0x040c /* width RMuint32 */
#define VO_main_phase 0x040c /* width RMuint32 */
#define VO_main_alpha_deint_routing 0x0410 /* width RMuint32 */
#define VO_main_deint2 0x0414 /* width RMuint32 */
#define VO_main_bcs 0x0418 /* width RMuint32 */
#define VO_main_pulldown 0x041c /* width RMuint32 */
#define VO_main_strip_filter 0x0420 /* width RMuint32 */
#define VO_main_nonlinear_0 0x0424 /* width RMuint32 */
#define VO_main_nonlinear_1 0x0428 /* width RMuint32 */
#define VO_main_bcs2 0x042c /* width RMuint32 */
/* DispMainVideoScaler registers done */

/* DispOSDScaler registers */
#define VO_osd_reset_bit 0x03 /* width RMuint32 */
#define VO_osd_format_hds 0x0300 /* width RMuint32 */
#define VO_osd_output_size 0x0304 /* width RMuint32 */
#define VO_osd_scale_factor 0x0308 /* width RMuint32 */
#define VO_osd_scale_phase_flicker 0x030c /* width RMuint32 */
#define VO_osd_alpha_routing 0x0310 /* width RMuint32 */
#define VO_osd_key_color 0x0314 /* width RMuint32 */
#define VO_osd_lut 0x9000 /* width RMuint32 */
#define VO_osd_lut0 0x9000 /* width RMuint32 */
/* DispOSDScaler registers done */

/* DispPostProcessing registers */
#define VO_pp_reset_bit 0x1a /* width RMuint32 */
#define VO_pp_size 0x1900 /* width RMuint32 */
#define VO_pp_ctrl 0x1904 /* width RMuint32 */
/* DispPostProcessing registers done */

/* DispRouting registers */
#define VO_routing_reset_bit 0x16 /* width RMuint32 */
#define VO_routing_ctrl 0x1208 /* width RMuint32 */
/* DispRouting registers done */

/* DispSubPictureScaler registers */
#define VO_subp_reset_bit 0x02 /* width RMuint32 */
#define VO_subp_format_hds 0x0200 /* width RMuint32 */
#define VO_subp_output_size 0x0204 /* width RMuint32 */
#define VO_subp_scale_factor 0x0208 /* width RMuint32 */
#define VO_subp_scale_phase_routing 0x020c /* width RMuint32 */
#define VO_sp_lut 0x9400 /* width RMuint32 */
#define VO_sp_lut0 0x9400 /* width RMuint32 */
#define VO_subp_scale_phase_flicker 0x940c /* width RMuint32 */
/* DispSubPictureScaler registers done */

/* DispVCRMixer registers */
#define VO_vcrmix_reset_bit 0x09 /* width RMuint32 */
#define VO_vcrmix_gfx_pos 0x0900 /* width RMuint32 */
#define VO_vcrmix_crt_pos 0x0904 /* width RMuint32 */
#define VO_vcrmix_sp_pos 0x0908 /* width RMuint32 */
#define VO_vcrmix_vcr_pos 0x090C /* width RMuint32 */
#define VO_vcrmix_index 0x0910 /* width RMuint32 */
#define VO_vcrmix_frame_size 0x0914 /* width RMuint32 */
#define VO_vcrmix_background 0x0918 /* width RMuint32 */
/* DispVCRMixer registers done */

/* DispVCRMultiScaler registers */
#define VO_VCR_reset_bit 0x05 /* width RMuint32 */
#define VO_VCR_format_hds 0x0500 /* width RMuint32 */
#define VO_VCR_output_size 0x0504 /* width RMuint32 */
#define VO_VCR_scale_factor 0x0508 /* width RMuint32 */
#define VO_VCR_scale_phase 0x050c /* width RMuint32 */
#define VO_VCR_phase 0x050c /* width RMuint32 */
#define VO_VCR_alpha_routing 0x0510 /* width RMuint32 */
#define VO_VCR_key_color 0x0514 /* width RMuint32 */
#define VO_VCR_bcs 0x0518 /* width RMuint32 */
#define VO_VCR_strip_edge 0x051C /* width RMuint32 */
#define VO_VCR_nonlinear_0 0x0520 /* width RMuint32 */
#define VO_VCR_nonlinear_1 0x0524 /* width RMuint32 */
#define VO_VCR_tiling 0x0528 /* width RMuint32 */
#define VO_VCR_bcs2 0x052c /* width RMuint32 */
#define VO_VCR_luma_key 0x0530 /* width RMuint32 */
#define VO_VCR_lut 0xa000 /* width RMuint32 */
#define VO_VCR_lut0 0xa000 /* width RMuint32 */
/* DispVCRMultiScaler registers done */

/* DispVideoInput registers */
#define VO_vid_in_reset_bit 0x10 /* width RMuint32 */
#define VO_vid_in_format 0x0b00 /* width RMuint32 */
#define VO_vid_in_data_size 0x0b04 /* width RMuint32 */
#define VO_vid_in_data_Xoffset 0x0b08 /* width RMuint32 */
#define VO_vid_in_data_Yoffset 0x0b0c /* width RMuint32 */
#define VO_vid_in_hz_sync 0x0b10 /* width RMuint32 */
#define VO_vid_in_vt_sync 0x0b14 /* width RMuint32 */
#define VO_vid_in_sync_coord 0x0b18 /* width RMuint32 */
#define VO_vid_in_top_vbi 0x0b1c /* width RMuint32 */
#define VO_vid_in_bot_vbi 0x0b20 /* width RMuint32 */
#define VO_vid_in_counters 0x0b24 /* width RMuint32 */
#define VO_vid_in_vbi_size 0x0b28 /* width RMuint32 */
#define VO_vid_in_vbi_vsm 0x0b2c /* width RMuint32 */
#define VO_vid_in_vbi_Voffset 0x0b30 /* width RMuint32 */
#define VO_vid_in_format2 0x0b34 /* width RMuint32 */
#define VO_vid_in_counters2 0x0b38 /* width RMuint32 */
/* DispVideoInput registers done */

/* DispVideoPlane registers */
#define VO_VP_reset_bit 0xF /* width RMuint32 */
#define VO_VP_conf_obsolete 0x1600 /* width RMuint32 */
#define VO_VP_size_obsolete 0x1604 /* width RMuint32 */
#define VO_VP_csc_m00 0x1600 /* width RMuint32 */
#define VO_VP_conf 0x1640 /* width RMuint32 */
#define VO_VP_size 0x1644 /* width RMuint32 */
#define VO_VP_keycolor_lo 0x1648 /* width RMuint32 */
#define VO_VP_keycolor_mi 0x164C /* width RMuint32 */
#define VO_VP_keycolor_hi 0x1650 /* width RMuint32 */
/* DispVideoPlane registers done */

/* GFXEngine registers */
#define VO_graph_acc_reset_bit 0x0a /* width RMuint32 */
#define VO_graph_acc_reset_mask 0x00300000 /* width RMuint32 */
#define VO_graph_acc_reset_run 0x00000000 /* width RMuint32 */
#define VO_graph_acc_reset_path 0x00100000 /* width RMuint32 */
#define VO_graph_acc_reset_time 0x00200000 /* width RMuint32 */
#define VO_graph_acc_reset_conf 0x00300000 /* width RMuint32 */
#define VO_graph_acc_X_format 0x0a00 /* width RMuint32 */
#define VO_graph_acc_X_alpha 0x0a04 /* width RMuint32 */
#define VO_graph_acc_X_keycolor 0x0a08 /* width RMuint32 */
#define VO_graph_acc_Y_format 0x0a0c /* width RMuint32 */
#define VO_graph_acc_Y_keycolor 0x0a10 /* width RMuint32 */
#define VO_graph_acc_control 0x0a14 /* width RMuint32 */
#define VO_graph_acc_font 0x0a18 /* width RMuint32 */
#define VO_graph_acc_fill 0x0a18 /* width RMuint32 */
#define VO_graph_acc_control2 0x0a1c /* width RMuint32 */
#define VO_graph_acc_Z_format 0x0a20 /* width RMuint32 */
#define VO_graph_acc_control3 0x0a24 /* width RMuint32 */
#define VO_graph_acc_lut0 0xd000 /* width RMuint32 */
#define VO_graph_acc_FILL 0 /* width RMuint32 */
#define VO_graph_acc_BLEND 1 /* width RMuint32 */
#define VO_graph_acc_MOVE 2 /* width RMuint32 */
#define VO_graph_acc_REPLACE 3 /* width RMuint32 */
#define VO_graph_acc_RASTER 4 /* width RMuint32 */
#define VO_graph_acc_mode_control 0x0a80 /* width RMuint32 */
#define VO_graph_acc_DRAM_read_address 0x0a84 /* width RMuint32 */
#define VO_graph_acc_DRAM_write_address 0x0a88 /* width RMuint32 */
#define VO_graph_acc_X_bounding_box 0x0a8c /* width RMuint32 */
#define VO_graph_acc_Y_bounding_box 0x0a90 /* width RMuint32 */
#define VO_graph_acc_scaling_and_contours 0x0a94 /* width RMuint32 */
#define VO_graph_acc_matrix_coeffs_scale 0x0a98 /* width RMuint32 */
#define VO_graph_acc_matrix_coeffs_cross_scale 0x0a9c /* width RMuint32 */
#define VO_graph_acc_matrix_coeffs_offset 0x0aa0 /* width RMuint32 */
#define VO_graph_acc_grd_color0 0x0a40 /* width RMuint32 */
#define VO_graph_acc_grd_color1 0x0a44 /* width RMuint32 */
#define VO_graph_acc_grd_scale_factor 0x0a48 /* width RMuint32 */
#define VO_graph_acc_grd_vt_scale_init 0x0a4c /* width RMuint32 */
#define VO_graph_acc_grd_init_square_dist 0x0a50 /* width RMuint32 */
#define VO_graph_acc_grd_ext_radius 0x0a54 /* width RMuint32 */
#define VO_graph_acc_grd_int_radius 0x0a58 /* width RMuint32 */
#define VO_graph_acc_grd_center 0x0a5c /* width RMuint32 */
#define VO_graph_acc_grd_control 0x0a60 /* width RMuint32 */
/* GFXEngine registers done */

/* I2C registers */
#define I2C_MASTER_CONFIG 0x80 /* width RMuint32 */
#define I2C_MASTER_CLK_DIV 0x84 /* width RMuint32 */
#define I2C_MASTER_DEV_ADDR 0x88 /* width RMuint32 */
#define I2C_MASTER_ADDR 0x8c /* width RMuint32 */
#define I2C_MASTER_DATA_OUT 0x90 /* width RMuint32 */
#define I2C_MASTER_DATA_IN 0x94 /* width RMuint32 */
#define I2C_MASTER_STATUS 0x98 /* width RMuint32 */
#define I2C_MASTER_STARTXFER 0x9c /* width RMuint32 */
#define I2C_MASTER_BYTE_CNT 0xa0 /* width RMuint32 */
#define I2C_MASTER_INTEN 0xa4 /* width RMuint32 */
#define I2C_MASTER_INT 0xa8 /* width RMuint32 */
/* I2C registers done */

/* I2CSlave registers */
#define I2C_SLAVE_ADDR_REG 0xC0 /* width RMuint32 */
#define I2C_SLAVE_DATAOUT 0xC4 /* width RMuint32 */
#define I2C_SLAVE_DATAIN 0xC8 /* width RMuint32 */
#define I2C_SLAVE_STATUS 0xCC /* width RMuint32 */
#define I2C_SLAVE_INTEN 0xD0 /* width RMuint32 */
#define I2C_SLAVE_INT 0xD4 /* width RMuint32 */
#define I2C_SLAVE_BUS_HOLD 0xD8 /* width RMuint32 */
/* I2CSlave registers done */

/* IPUBlock registers */
#define REG_BASE_ipu_block 0x000f0000 /* width RMuint32 */
/* IPUBlock registers done */

/* MM registers */
/* MM registers done */

/* MpegEngine registers */
#define REG_BASE_mpeg_engine_0 0x00080000 /* width RMuint32 */
#define MEM_BASE_mpeg_engine_0 0x00100000 /* width RMuint32 */
#define PMEM_BASE_mpeg_engine_0 0x00100000 /* width RMuint32 */
#define DMEM_BASE_mpeg_engine_0 0x00110000 /* width RMuint32 */
#define REG_BASE_mpeg_engine_1 0x00090000 /* width RMuint32 */
#define MEM_BASE_mpeg_engine_1 0x00120000 /* width RMuint32 */
#define PMEM_BASE_mpeg_engine_1 0x00120000 /* width RMuint32 */
#define DMEM_BASE_mpeg_engine_1 0x00130000 /* width RMuint32 */
#define mpeg_mutex0 0x0fe0 /* width RMuint32 */
#define mpeg_mutex1 0x0fe1 /* width RMuint32 */
#define mpeg_mutex2 0x0fe2 /* width RMuint32 */
#define mpeg_mutex3 0x0fe3 /* width RMuint32 */
#define mpeg_mutex4 0x0fe4 /* width RMuint32 */
#define mpeg_mutex5 0x0fe5 /* width RMuint32 */
#define mpeg_mutex6 0x0fe6 /* width RMuint32 */
#define mpeg_mutex7 0x0fe7 /* width RMuint32 */
#define RBUS_offset 0x4000 /* width RMuint32 */
#define mpeg_MBUSIF_w0_addlo 0xE80 /* width RMuint32 */
#define mpeg_MBUSIF_w0_addhi 0xE81 /* width RMuint32 */
#define mpeg_MBUSIF_w0_xcnt 0xE82 /* width RMuint32 */
#define mpeg_MBUSIF_w0_ycnt 0xE83 /* width RMuint32 */
#define mpeg_MBUSIF_w0_skiplo 0xE84 /* width RMuint32 */
#define mpeg_MBUSIF_w0_skiphi 0xE85 /* width RMuint32 */
#define mpeg_MBUSIF_w0_cmd 0xE86 /* width RMuint32 */
#define mpeg_MBUSIF_w0_vbuf_width 0xE87 /* width RMuint32 */
#define mpeg_MBUSIF_r0_addlo 0xE90 /* width RMuint32 */
#define mpeg_MBUSIF_r0_addhi 0xE91 /* width RMuint32 */
#define mpeg_MBUSIF_r0_xcnt 0xE92 /* width RMuint32 */
#define mpeg_MBUSIF_r0_ycnt 0xE93 /* width RMuint32 */
#define mpeg_MBUSIF_r0_skiplo 0xE94 /* width RMuint32 */
#define mpeg_MBUSIF_r0_skiphi 0xE95 /* width RMuint32 */
#define mpeg_MBUSIF_r0_cmd 0xE96 /* width RMuint32 */
#define mpeg_MBUSIF_r0_vbuf_width 0xE97 /* width RMuint32 */
#define mpeg_MBUSIF_r1_addlo 0xEA0 /* width RMuint32 */
#define mpeg_MBUSIF_r1_addhi 0xEA1 /* width RMuint32 */
#define mpeg_MBUSIF_r1_xcnt 0xEA2 /* width RMuint32 */
#define mpeg_MBUSIF_r1_ycnt 0xEA3 /* width RMuint32 */
#define mpeg_MBUSIF_r1_skiplo 0xEA4 /* width RMuint32 */
#define mpeg_MBUSIF_r1_skiphi 0xEA5 /* width RMuint32 */
#define mpeg_MBUSIF_r1_cmd 0xEA6 /* width RMuint32 */
#define mpeg_MBUSIF_r1_vbuf_width 0xEA7 /* width RMuint32 */
#define mpeg_MBUSIF_w1_addlo 0xEB0 /* width RMuint32 */
#define mpeg_MBUSIF_w1_addhi 0xEB1 /* width RMuint32 */
#define mpeg_MBUSIF_w1_xcnt 0xEB2 /* width RMuint32 */
#define mpeg_MBUSIF_w1_ycnt 0xEB3 /* width RMuint32 */
#define mpeg_MBUSIF_w1_skiplo 0xEB4 /* width RMuint32 */
#define mpeg_MBUSIF_w1_skiphi 0xEB5 /* width RMuint32 */
#define mpeg_MBUSIF_w1_cmd 0xEB6 /* width RMuint32 */
#define mpeg_MBUSIF_w1_vbuf_width 0xEB7 /* width RMuint32 */
#define mpeg_MBUSIF_r2_addlo 0xEC0 /* width RMuint32 */
#define mpeg_MBUSIF_r2_addhi 0xEC1 /* width RMuint32 */
#define mpeg_MBUSIF_r2_xcnt 0xEC2 /* width RMuint32 */
#define mpeg_MBUSIF_r2_ycnt 0xEC3 /* width RMuint32 */
#define mpeg_MBUSIF_r2_skiplo 0xEC4 /* width RMuint32 */
#define mpeg_MBUSIF_r2_skiphi 0xEC5 /* width RMuint32 */
#define mpeg_MBUSIF_r2_cmd 0xEC6 /* width RMuint32 */
#define mpeg_MBUSIF_r2_vbuf_width 0xEC7 /* width RMuint32 */
#define mpeg_GBUSIF_MAIN_WADD_LOW 0xFA0 /* width RMuint32 */
#define mpeg_GBUSIF_MAIN_WADD_HIGH 0xFA1 /* width RMuint32 */
#define mpeg_GBUSIF_MAIN_RADD_LOW 0xFA2 /* width RMuint32 */
#define mpeg_GBUSIF_MAIN_RADD_HIGH 0xFA3 /* width RMuint32 */
#define mpeg_GBUSIF_MAIN_BYTE 0xFA4 /* width RMuint32 */
#define mpeg_GBUSIF_MAIN_WORD 0xFA5 /* width RMuint32 */
#define mpeg_GBUSIF_MAIN_DWORD_LOW 0xFA6 /* width RMuint32 */
#define mpeg_GBUSIF_MAIN_DWORD_HIGH 0xFA7 /* width RMuint32 */
#define mpeg_GBUSIF_MAIN_STATUS 0xFA8 /* width RMuint32 */
#define mpeg_GBUSIF_ISR_WADD_LOW 0xFB0 /* width RMuint32 */
#define mpeg_GBUSIF_ISR_WADD_HIGH 0xFB1 /* width RMuint32 */
#define mpeg_GBUSIF_ISR_RADD_LOW 0xFB2 /* width RMuint32 */
#define mpeg_GBUSIF_ISR_RADD_HIGH 0xFB3 /* width RMuint32 */
#define mpeg_GBUSIF_ISR_BYTE 0xFB4 /* width RMuint32 */
#define mpeg_GBUSIF_ISR_WORD 0xFB5 /* width RMuint32 */
#define mpeg_GBUSIF_ISR_DWORD_LOW 0xFB6 /* width RMuint32 */
#define mpeg_GBUSIF_ISR_DWORD_HIGH 0xFB7 /* width RMuint32 */
#define mpeg_GBUSIF_ISR_STATUS 0xFB8 /* width RMuint32 */
#define mpeg_MISC_dr_mode 0xFF0 /* width RMuint32 */
#define mpeg_MISC_dr_length 0xFF1 /* width RMuint32 */
#define mpeg_MISC_dr_address 0xFF2 /* width RMuint32 */
#define mpeg_MISC_sbox_mode 0xFF3 /* width RMuint32 */
#define mpeg_MISC_dw_mode 0xFF4 /* width RMuint32 */
#define mpeg_MISC_dw_length 0xFF5 /* width RMuint32 */
#define mpeg_MISC_dw_address 0xFF6 /* width RMuint32 */
#define mpeg_MISC_codec_type 0xFF7 /* width RMuint32 */
#define mpeg_MISC_reset0 0xFF8 /* width RMuint32 */
#define mpeg_MISC_reset1 0xFF9 /* width RMuint32 */
#define mpeg_MISC_interrupt 0xFFA /* width RMuint32 */
#define mpeg_MISC_timer_div 0xFFB /* width RMuint32 */
#define mpeg_MISC_timer_count 0xFFC /* width RMuint32 */
#define mpeg_MISC_sbox_read_ctrl 0xFFD /* width RMuint32 */
#define mpeg_MISC_sbox_write_ctrl 0xFFE /* width RMuint32 */
#define mpeg_MISC_reserved2 0xFFF /* width RMuint32 */
#define mpeg_MISC_UNRESET_MASK 0x3500 /* width RMuint32 */
#define mpeg_MISC_RESET_MASK 0x3535 /* width RMuint32 */
#define mpeg_SP_init 0x7fe /* width RMuint32 */
/* MpegEngine registers done */

/* PictureTransform registers */
/* PictureTransform registers done */

/* PLL registers */
/* PLL registers done */

/* PngDecoder registers */
/* PngDecoder registers done */

/* PPF registers */
/* PPF registers done */

/* RawDataTransfer registers */
/* RawDataTransfer registers done */

/* SpuDecoder registers */
/* SpuDecoder registers done */

/* STC registers */
/* STC registers done */

/* SystemBlock registers */
#define REG_BASE_system_block 0x00010000 /* width RMuint32 */
#define SYS_clkgen0_pll 0x0000 /* width RMuint32 */
#define SYS_clkgen1_pll 0x0008 /* width RMuint32 */
#define SYS_clkgen1_div 0x000C /* width RMuint32 */
#define SYS_clkgen2_pll 0x0010 /* width RMuint32 */
#define SYS_clkgen2_div 0x0014 /* width RMuint32 */
#define SYS_clkgen3_pll 0x0018 /* width RMuint32 */
#define SYS_clkgen3_div 0x001C /* width RMuint32 */
#define SYS_avclk_mux 0x0038 /* width RMuint32 */
#define SYS_sysclk_mux 0x003C /* width RMuint32 */
#define SYS_clk_cnt 0x0040 /* width RMuint32 */
#define SYS_xtal_in_cnt 0x0048 /* width RMuint32 */
#define DRAM_vbus_w0_cfg 0x0300 /* width RMuint32 */
#define DRAM_vbus_w1_cfg 0x0304 /* width RMuint32 */
#define DRAM_vbus_w2_cfg 0x0308 /* width RMuint32 */
#define DRAM_vbus_w3_cfg 0x030c /* width RMuint32 */
#define DRAM_vbus_r0_cfg 0x0340 /* width RMuint32 */
#define DRAM_vbus_r1_cfg 0x0344 /* width RMuint32 */
#define DRAM_vbus_r2_cfg 0x0348 /* width RMuint32 */
#define DRAM_vbus_r3_cfg 0x034c /* width RMuint32 */
#define DRAM_vbus_r4_cfg 0x0350 /* width RMuint32 */
#define DRAM_vbus_r5_cfg 0x0354 /* width RMuint32 */
#define DRAM_vbus_r6_cfg 0x0358 /* width RMuint32 */
#define DRAM_vbus_r7_cfg 0x035c /* width RMuint32 */
#define DRAM_vbus_r8_cfg 0x0360 /* width RMuint32 */
#define DRAM_vbus_r9_cfg 0x0364 /* width RMuint32 */
#define DRAM_vbus_r10_cfg 0x0368 /* width RMuint32 */
#define DRAM_vbus_r11_cfg 0x036c /* width RMuint32 */
#define DRAM_vbus_r12_cfg 0x0370 /* width RMuint32 */
#define DRAM_vbus_r13_cfg 0x0374 /* width RMuint32 */
#define DRAM_vbus_r14_cfg 0x0378 /* width RMuint32 */
#define DRAM_vbus_r15_cfg 0x037c /* width RMuint32 */
#define DRAM_vbus_w4_cfg 0x0310 /* width RMuint32 */
#define DRAM_mpeg_engine_cfg 0x016c /* width RMuint32 */
#define DRAM_mbus_w0_cfg 0x0200 /* width RMuint32 */
#define DRAM_mbus_w1_cfg 0x0204 /* width RMuint32 */
#define DRAM_mbus_w2_cfg 0x0208 /* width RMuint32 */
#define DRAM_mbus_w3_cfg 0x020c /* width RMuint32 */
#define DRAM_mbus_w4_cfg 0x0210 /* width RMuint32 */
#define DRAM_mbus_w5_cfg 0x0214 /* width RMuint32 */
#define DRAM_mbus_w6_cfg 0x0218 /* width RMuint32 */
#define DRAM_mbus_w7_cfg 0x021c /* width RMuint32 */
#define DRAM_mbus_w8_cfg 0x0220 /* width RMuint32 */
#define DRAM_mbus_w9_cfg 0x0224 /* width RMuint32 */
#define DRAM_mbus_w10_cfg 0x0228 /* width RMuint32 */
#define DRAM_mbus_r0_cfg 0x0240 /* width RMuint32 */
#define DRAM_mbus_r1_cfg 0x0244 /* width RMuint32 */
#define DRAM_mbus_r2_cfg 0x0248 /* width RMuint32 */
#define DRAM_mbus_r3_cfg 0x024c /* width RMuint32 */
#define DRAM_mbus_r4_cfg 0x0250 /* width RMuint32 */
#define DRAM_mbus_r5_cfg 0x0254 /* width RMuint32 */
#define DRAM_mbus_r6_cfg 0x0258 /* width RMuint32 */
#define DRAM_mbus_r7_cfg 0x025c /* width RMuint32 */
#define DRAM_mbus_r8_cfg 0x0260 /* width RMuint32 */
#define DRAM_mbus_r9_cfg 0x0264 /* width RMuint32 */
#define DRAM_mbus_r10_cfg 0x0268 /* width RMuint32 */
#define SYS_clkgen0_div 0x0004 /* width RMuint32 */
#define SYS_hostclk_mux 0x0030 /* width RMuint32 */
#define SYS_sysclk_premux 0x0034 /* width RMuint32 */
#define SYS_rnd_cnt 0x0044 /* width RMuint32 */
#define SYS_cnt_cfg 0x004c /* width RMuint32 */
#define SYS_cfg_cnt0 0x0050 /* width RMuint32 */
#define SYS_cfg_cnt1 0x0054 /* width RMuint32 */
#define SYS_cfg_cnt2 0x0058 /* width RMuint32 */
#define SYS_cfg_cnt3 0x005c /* width RMuint32 */
#define SYS_cfg_cnt4 0x0060 /* width RMuint32 */
#define SYS_cleandiv0_div 0x0080 /* width RMuint32 */
#define SYS_cleandiv1_div 0x0088 /* width RMuint32 */
#define SYS_cleandiv2_div 0x0090 /* width RMuint32 */
#define SYS_cleandiv3_div 0x0098 /* width RMuint32 */
#define SYS_cleandiv4_div 0x00a0 /* width RMuint32 */
#define SYS_cleandiv5_div 0x00a8 /* width RMuint32 */
#define SYS_cleandiv6_div 0x00b0 /* width RMuint32 */
#define SYS_cleandiv7_div 0x00b8 /* width RMuint32 */
#define SYS_cleandiv8_div 0x00c0 /* width RMuint32 */
#define SYS_cleandiv9_div 0x00c8 /* width RMuint32 */
#define SYS_cleandiv10_div 0x00d0 /* width RMuint32 */
#define SYS_cleandiv11_div 0x00d8 /* width RMuint32 */
#define SYS_cleandiv0_ctrl 0x0084 /* width RMuint32 */
#define SYS_cleandiv1_ctrl 0x008c /* width RMuint32 */
#define SYS_cleandiv2_ctrl 0x0094 /* width RMuint32 */
#define SYS_cleandiv3_ctrl 0x009c /* width RMuint32 */
#define SYS_cleandiv4_ctrl 0x00a4 /* width RMuint32 */
#define SYS_cleandiv5_ctrl 0x00ac /* width RMuint32 */
#define SYS_cleandiv6_ctrl 0x00b4 /* width RMuint32 */
#define SYS_cleandiv7_ctrl 0x00bc /* width RMuint32 */
#define SYS_cleandiv8_ctrl 0x00c4 /* width RMuint32 */
#define SYS_cleandiv9_ctrl 0x00cc /* width RMuint32 */
#define SYS_cleandiv10_ctrl 0x00d4 /* width RMuint32 */
#define SYS_cleandiv11_ctrl 0x00dc /* width RMuint32 */
#define SYS_watchdog_counter 0xfd00 /* width RMuint32 */
#define SYS_watchdog_configuration 0xfd04 /* width RMuint32 */
#define MARB_mid01_cfg 0x0200 /* width RMuint32 */
#define MARB_mid21_cfg 0x0204 /* width RMuint32 */
#define MARB_mid02_cfg 0x0208 /* width RMuint32 */
#define MARB_mid22_cfg 0x020c /* width RMuint32 */
#define MARB_mid03_cfg 0x0210 /* width RMuint32 */
#define MARB_mid23_cfg 0x0214 /* width RMuint32 */
#define MARB_mid04_cfg 0x0218 /* width RMuint32 */
#define MARB_mid24_cfg 0x021c /* width RMuint32 */
#define MARB_mid25_cfg 0x0220 /* width RMuint32 */
#define MARB_mid08_cfg 0x0224 /* width RMuint32 */
#define MARB_mid28_cfg 0x0228 /* width RMuint32 */
#define MARB_mid29_cfg 0x022c /* width RMuint32 */
#define MARB_mid0C_cfg 0x0230 /* width RMuint32 */
#define MARB_mid2C_cfg 0x0234 /* width RMuint32 */
#define MARB_mid0E_cfg 0x0238 /* width RMuint32 */
#define MARB_mid2E_cfg 0x023c /* width RMuint32 */
#define MARB_mid10_cfg 0x0240 /* width RMuint32 */
#define MARB_mid30_cfg 0x0244 /* width RMuint32 */
#define MARB_mid14_cfg 0x0248 /* width RMuint32 */
#define MARB_mid34_cfg 0x024c /* width RMuint32 */
#define MARB_mid05_cfg 0x0250 /* width RMuint32 */
#define MARB_mid26_cfg 0x0254 /* width RMuint32 */
#define MARB_mid09_cfg 0x0258 /* width RMuint32 */
#define MARB_mid2A_cfg 0x025c /* width RMuint32 */
#define MARB_mid06_cfg 0x0260 /* width RMuint32 */
#define MARB_mid0A_cfg 0x0264 /* width RMuint32 */
#define MARB_mid1C_cfg 0x0268 /* width RMuint32 */
#define MARB_mid3C_cfg 0x026c /* width RMuint32 */
#define GARB_mid1_cfg 0x0104 /* width RMuint32 */
#define GARB_mid2_cfg 0x0108 /* width RMuint32 */
#define GARB_mid3_cfg 0x010c /* width RMuint32 */
#define GARB_mid4_cfg 0x0110 /* width RMuint32 */
#define GARB_mid5_cfg 0x0114 /* width RMuint32 */
#define GARB_mid6_cfg 0x0118 /* width RMuint32 */
#define GARB_mid7_cfg 0x011c /* width RMuint32 */
#define GARB_mid8_cfg 0x0120 /* width RMuint32 */
#define GARB_mid9_cfg 0x0124 /* width RMuint32 */
#define GARB_midA_cfg 0x0128 /* width RMuint32 */
#define GARB_midB_cfg 0x012c /* width RMuint32 */
#define GARB_midC_cfg 0x0130 /* width RMuint32 */
#define GARB_midD_cfg 0x0134 /* width RMuint32 */
#define GARB_midE_cfg 0x0138 /* width RMuint32 */
#define GARB_spy_addlo 0x0170 /* width RMuint32 */
#define GARB_spy_addhi 0x0174 /* width RMuint32 */
#define GARB_spy_cfg 0x0178 /* width RMuint32 */
#define GARB_spy_cnt 0x017c /* width RMuint32 */
#define VARB_mid01_cfg 0x0300 /* width RMuint32 */
#define VARB_mid02_cfg 0x0304 /* width RMuint32 */
#define VARB_mid21_cfg 0x0308 /* width RMuint32 */
#define VARB_mid22_cfg 0x030c /* width RMuint32 */
#define VARB_mid23_cfg 0x0310 /* width RMuint32 */
#define VARB_mid24_cfg 0x0314 /* width RMuint32 */
#define VARB_mid25_cfg 0x0318 /* width RMuint32 */
#define VARB_mid26_cfg 0x031c /* width RMuint32 */
#define VARB_mid27_cfg 0x0320 /* width RMuint32 */
#define VARB_mid28_cfg 0x0324 /* width RMuint32 */
#define VARB_mid29_cfg 0x0328 /* width RMuint32 */
#define VARB_mid2A_cfg 0x032c /* width RMuint32 */
#define VARB_mid10_cfg 0x0330 /* width RMuint32 */
#define VARB_mid30_cfg 0x0334 /* width RMuint32 */
#define VARB_mid31_cfg 0x0338 /* width RMuint32 */
#define VARB_mid03_cfg 0x033c /* width RMuint32 */
#define VARB_mid2B_cfg 0x0340 /* width RMuint32 */
#define VARB_mid2C_cfg 0x0344 /* width RMuint32 */
#define VARB_mid2D_cfg 0x0348 /* width RMuint32 */
#define VARB_mid2E_cfg 0x034C /* width RMuint32 */
#define VARB_mid11_cfg 0x0350 /* width RMuint32 */
#define IARB_mid01_cfg 0x0400 /* width RMuint32 */
#define IARB_mid02_cfg 0x0404 /* width RMuint32 */
#define SYS_gpio_dir 0x0500 /* width RMuint32 */
#define SYS_gpio_data 0x0504 /* width RMuint32 */
#define SYS_gpio_int 0x0508 /* width RMuint32 */
#define SYS_gpio15_pwm 0x0510 /* width RMuint32 */
#define SYS_gpio14_pwm 0x0514 /* width RMuint32 */
#define REG_BASE_dram_controller_0 0x00030000 /* width RMuint32 */
#define REG_BASE_dram_controller_1 0x00040000 /* width RMuint32 */
#define MEM_BASE_dram_controller_0_alias 0x10000000 /* width RMuint32 */
#define MEM_BASE_dram_controller_0 0x80000000 /* width RMuint32 */
#define MEM_BASE_dram_controller_1_alias 0x20000000 /* width RMuint32 */
#define MEM_BASE_dram_controller_1 0xc0000000 /* width RMuint32 */
#define DRAM_dunit_cfg 0x0000 /* width RMuint32 */
#define DRAM_dunit_delay0_ctrl 0x0004 /* width RMuint32 */
#define DRAM_dunit_delay1_ctrl 0x0008 /* width RMuint32 */
#define DRAM_dunit_auto_delay 0x000c /* width RMuint32 */
#define DRAM_dunit_fall_delay0 0x0010 /* width RMuint32 */
#define DRAM_dunit_fall_delay1 0x0014 /* width RMuint32 */
#define DRAM_dunit_bw_lobound 0x0018 /* width RMuint32 */
#define DRAM_dunit_bw_hibound 0x001c /* width RMuint32 */
#define DRAM_dunit_bw_probe_cfg 0x0020 /* width RMuint32 */
#define DRAM_dunit_bw_probe_cnt 0x0024 /* width RMuint32 */
#define DRAM_dunit_bw_cntall 0x0028 /* width RMuint32 */
#define DRAM_dunit_calibration_delay 0x0030 /* width RMuint32 */
#define DRAM_dunit_calibration_rise_err 0x0034 /* width RMuint32 */
#define DRAM_dunit_calibration_fall_err 0x0038 /* width RMuint32 */
#define DRAM_dunit_calibration_page 0x0088 /* width RMuint32 */
#define DRAM_dunit_flush_buffer 0x0104 /* width RMuint32 */
#define REG_BASE_host_interface 0x00020000 /* width RMuint32 */
#define MEM_BASE_host_interface 0x40000000 /* width RMuint32 */
#define IDE_data 0x0000 /* width RMuint32 */
#define IDE_error 0x0004 /* width RMuint32 */
#define IDE_count 0x0008 /* width RMuint32 */
#define IDE_start_sector 0x000c /* width RMuint32 */
#define IDE_cylinder_lo 0x0010 /* width RMuint32 */
#define IDE_cylinder_hi 0x0014 /* width RMuint32 */
#define IDE_head_device 0x0018 /* width RMuint32 */
#define IDE_cmd_stat 0x001c /* width RMuint32 */
#define IDE_irq_stat 0x0218 /* width RMuint32 */
#define IDE_cmd_stat__ 0x021c /* width RMuint32 */
#define PB_timing0 0x0800 /* width RMuint32 */
#define PB_timing1 0x0804 /* width RMuint32 */
#define PB_timing2 0x0808 /* width RMuint32 */
#define PB_timing3 0x080c /* width RMuint32 */
#define PB_timing4 0x0810 /* width RMuint32 */
#define PB_timing5 0x0814 /* width RMuint32 */
#define PB_default_timing 0x0818 /* width RMuint32 */
#define PB_use_timing0 0x081c /* width RMuint32 */
#define PB_use_timing1 0x0820 /* width RMuint32 */
#define PB_use_timing2 0x0824 /* width RMuint32 */
#define PB_use_timing3 0x0828 /* width RMuint32 */
#define PB_use_timing4 0x082c /* width RMuint32 */
#define PB_use_timing5 0x0830 /* width RMuint32 */
#define PB_CS_config 0x0834 /* width RMuint32 */
#define PB_automode_start_address 0x0840 /* width RMuint32 */
#define PB_automode_control 0x0844 /* width RMuint32 */
#define EMHWLIB_IS_HOST 0xe000 /* width RMuint32 */
#define HOST_REG1 0xfed0 /* width RMuint32 */
#define HOST_REG2 0xfed4 /* width RMuint32 */
#define READ_ADDRESS 0xfec0 /* width RMuint32 */
#define READ_COUNTER 0xfec4 /* width RMuint32 */
#define READ_ENABLE 0xfec8 /* width RMuint32 */
#define READ_REVERSE 0xfecc /* width RMuint32 */
#define WRITE_ADDRESS 0xfed8 /* width RMuint32 */
#define WRITE_COUNTER 0xfedc /* width RMuint32 */
#define WRITE_ENABLE 0xfee0 /* width RMuint32 */
#define BURST 0xfee4 /* width RMuint32 */
#define PCI_TIMEOUT 0x8000 /* width RMuint32 */
#define PCI_TIMEOUT_STATUS 0x8004 /* width RMuint32 */
#define PCI_TIMER 0x8008 /* width RMuint32 */
#define PCI_TIMER_TEST 0x800c /* width RMuint32 */
#define PCI_WAKEUP 0x8010 /* width RMuint32 */
#define PCI_REGION_0_BASE 0x9000 /* width RMuint32 */
#define PCI_REGION_1_BASE 0x9004 /* width RMuint32 */
#define PCI_REGION_2_BASE 0x9008 /* width RMuint32 */
#define PCI_REGION_3_BASE 0x900c /* width RMuint32 */
#define PCI_REGION_4_BASE 0x9010 /* width RMuint32 */
#define PCI_REGION_5_BASE 0x9014 /* width RMuint32 */
#define PCI_REGION_6_BASE 0x9018 /* width RMuint32 */
#define PCI_REGION_7_BASE 0x901c /* width RMuint32 */
#define PCI_irq_status 0x9020 /* width RMuint32 */
#define PCI_irq_set 0x9024 /* width RMuint32 */
#define PCI_irq_clear 0x9028 /* width RMuint32 */
#define SBOX_FIFO_RESET 0x90a0 /* width RMuint32 */
#define SBOX_FIFO_RESET2 0x90a4 /* width RMuint32 */
#define SBOX_ROUTE 0x90a8 /* width RMuint32 */
#define SBOX_ROUTE2 0x90ac /* width RMuint32 */
#define output_SBOX_MBUS_W0 0x9080 /* width RMuint32 */
#define output_SBOX_MBUS_W1 0x9084 /* width RMuint32 */
#define output_SBOX_PCI_MASTER 0x9088 /* width RMuint32 */
#define output_SBOX_PCI_SLAVE 0x908c /* width RMuint32 */
#define output_SBOX_SATA 0x9090 /* width RMuint32 */
#define output_SBOX_IDE_ISA 0x9094 /* width RMuint32 */
#define output_SBOX_IDE_DVD 0x9098 /* width RMuint32 */
#define output_SBOX_SATA2 0x909c /* width RMuint32 */
#define output_SBOX_MBUS_W2 0x90b0 /* width RMuint32 */
#define input_keep_SBOX 0 /* width RMuint32 */
#define input_MBUS_R0_SBOX 1 /* width RMuint32 */
#define input_MBUS_R1_SBOX 2 /* width RMuint32 */
#define input_PCI_MASTER_SBOX 3 /* width RMuint32 */
#define input_PCI_SLAVE_SBOX 4 /* width RMuint32 */
#define input_SATA_SBOX 5 /* width RMuint32 */
#define input_IDE_ISA_SBOX 6 /* width RMuint32 */
#define input_IDE_DVD_SBOX 7 /* width RMuint32 */
#define input_SATA2_SBOX 8 /* width RMuint32 */
#define input_MBUS_R2_SBOX 9 /* width RMuint32 */
#define input_unconnected_SBOX 0xf /* width RMuint32 */
#define host_mutex0 0x9040 /* width RMuint32 */
#define host_mutex1 0x9044 /* width RMuint32 */
#define host_mutex2 0x9048 /* width RMuint32 */
#define host_mutex3 0x904c /* width RMuint32 */
#define host_mutex4 0x9050 /* width RMuint32 */
#define host_mutex5 0x9054 /* width RMuint32 */
#define host_mutex6 0x9058 /* width RMuint32 */
#define host_mutex7 0x905c /* width RMuint32 */
#define host_mutex8 0x9060 /* width RMuint32 */
#define host_mutex9 0x9064 /* width RMuint32 */
#define host_mutex10 0x9068 /* width RMuint32 */
#define host_mutex11 0x906c /* width RMuint32 */
#define host_mutex12 0x9070 /* width RMuint32 */
#define host_mutex13 0x9074 /* width RMuint32 */
#define host_mutex14 0x9078 /* width RMuint32 */
#define host_mutex15 0x907c /* width RMuint32 */
#define PCI_host_reg5 0xfe94 /* width RMuint32 */
#define PCI_chip_is_host 0xfe90 /* width RMuint32 */
#define IDECTRL_idesrc 0x20d0 /* width RMuint32 */
#define IDECTRL_pri_drv1udmatim1 0x20e0 /* width RMuint32 */
#define IDECTRL_pri_drv1udmatim2 0x20f0 /* width RMuint32 */
#define IDECTRL_pri_idectl 0x2100 /* width RMuint32 */
#define IDECTRL_pri_drv0tim 0x2110 /* width RMuint32 */
#define IDECTRL_pri_drv1tim 0x2120 /* width RMuint32 */
#define IDECTRL_idemisc 0x2130 /* width RMuint32 */
#define IDECTRL_idestatus 0x2140 /* width RMuint32 */
#define IDECTRL_udmactl 0x2150 /* width RMuint32 */
#define IDECTRL_pri_drv0udmatim1 0x2160 /* width RMuint32 */
#define IDECTRL_pri_drv0udmatim2 0x2170 /* width RMuint32 */
#define IDECTRL_pref_st 0x2310 /* width RMuint32 */
#define IDECTRL_pri_ctrlblock 0x2398 /* width RMuint32 */
#define IDECTRL_pri_cmdblock 0x23c0 /* width RMuint32 */
#define IDECTRL_bmic 0x2400 /* width RMuint32 */
#define IDECTRL_bmis 0x2410 /* width RMuint32 */
#define IDECTRL_bmidtp 0x2420 /* width RMuint32 */
#define IDECTRL_ide_dmaptr 0x2780 /* width RMuint32 */
#define IDECTRL_ide_dmalen 0x2790 /* width RMuint32 */
#define IDECTRL_pio_prefetch_data 0x27c0 /* width RMuint32 */
#define MEM_BASE_pfla 0x40000000 /* width RMuint32 */
#define PB_CS0_OFFSET 0x00000000 /* width RMuint32 */
#define PB_CS1_OFFSET 0x04000000 /* width RMuint32 */
#define PB_CS2_OFFSET 0x08000000 /* width RMuint32 */
#define PB_CS3_OFFSET 0x0c000000 /* width RMuint32 */
#define ETH_gpio_dir1 0x7100 /* width RMuint32 */
#define ETH_gpio_data1 0x7104 /* width RMuint32 */
#define ETH_gpio_mask1 0x7108 /* width RMuint32 */
#define ETH_gpio_dir2 0x710c /* width RMuint32 */
#define ETH_gpio_data2 0x7110 /* width RMuint32 */
#define ETH0_pad_mode 0x6400 /* width RMuint32 */
#define ETH0_gpio_dir0 0x6404 /* width RMuint32 */
#define ETH0_gpio_data0 0x6408 /* width RMuint32 */
#define ETH0_gpio_dir1 0x640c /* width RMuint32 */
#define ETH0_gpio_data1 0x6410 /* width RMuint32 */
#define ETH0_gpio_irq_sel 0x641c /* width RMuint32 */
#define ETH1_pad_mode 0x6c00 /* width RMuint32 */
#define ETH1_gpio_dir0 0x6c04 /* width RMuint32 */
#define ETH1_gpio_data0 0x6c08 /* width RMuint32 */
#define ETH1_gpio_dir1 0x6c0c /* width RMuint32 */
#define ETH1_gpio_data1 0x6c10 /* width RMuint32 */
#define ETH1_gpio_irq_sel 0x6c1c /* width RMuint32 */
#define PB_automode_control1 0x0848 /* width RMuint32 */
#define PB_CS_config1 0x0838 /* width RMuint32 */
#define PB_CS_ctrl 0x083c /* width RMuint32 */
#define PB_strap_ctrl 0x0880 /* width RMuint32 */
#define PB_strap0 0x0884 /* width RMuint32 */
#define PB_strap1 0x0888 /* width RMuint32 */
#define PB_ECC_code0 0x08c0 /* width RMuint32 */
#define PB_ECC_code1 0x08c4 /* width RMuint32 */
#define PB_ECC_code2 0x08c8 /* width RMuint32 */
#define PB_ECC_code3 0x08cc /* width RMuint32 */
#define PB_ECC_clear 0x08d0 /* width RMuint32 */
#define PB_ECC1_code0 0x08d4 /* width RMuint32 */
#define PB_ECC1_code1 0x08d8 /* width RMuint32 */
#define PB_ECC1_code2 0x08dc /* width RMuint32 */
#define PB_ECC1_code3 0x08e0 /* width RMuint32 */
#define PB_ECC1_clear 0x08e4 /* width RMuint32 */
#define PB_SPI_ctrl 0x08e8 /* width RMuint32 */
#define PB1_timing0 0x0900 /* width RMuint32 */
#define PB1_timing1 0x0904 /* width RMuint32 */
#define PB1_timing2 0x0908 /* width RMuint32 */
#define PB1_timing3 0x090c /* width RMuint32 */
#define PB1_timing4 0x0910 /* width RMuint32 */
#define PB1_timing5 0x0914 /* width RMuint32 */
#define PB1_default_timing 0x0918 /* width RMuint32 */
#define PB1_use_timing0 0x091c /* width RMuint32 */
#define PB1_use_timing1 0x0920 /* width RMuint32 */
#define PB1_use_timing2 0x0924 /* width RMuint32 */
#define PB1_use_timing3 0x0928 /* width RMuint32 */
#define PB1_use_timing4 0x092c /* width RMuint32 */
#define PB1_use_timing5 0x0930 /* width RMuint32 */
#define PB1_CS_config 0x0934 /* width RMuint32 */
#define PB1_CS_config1 0x0938 /* width RMuint32 */
#define PB1_CS_ctrl 0x093c /* width RMuint32 */
#define PB1_automode_start_address 0x0940 /* width RMuint32 */
#define PB1_automode_control 0x0944 /* width RMuint32 */
#define PB1_automode_control1 0x0948 /* width RMuint32 */
#define PB1_strap_ctrl 0x0980 /* width RMuint32 */
#define PB1_strap0 0x0984 /* width RMuint32 */
#define PB1_strap1 0x0988 /* width RMuint32 */
#define PB1_ECC_code0 0x09c0 /* width RMuint32 */
#define PB1_ECC_code1 0x09c4 /* width RMuint32 */
#define PB1_ECC_code2 0x09c8 /* width RMuint32 */
#define PB1_ECC_code3 0x09cc /* width RMuint32 */
#define PB1_ECC_clear 0x09d0 /* width RMuint32 */
#define PB1_ECC1_code0 0x09d4 /* width RMuint32 */
#define PB1_ECC1_code1 0x09d8 /* width RMuint32 */
#define PB1_ECC1_code2 0x09dc /* width RMuint32 */
#define PB1_ECC1_code3 0x09e0 /* width RMuint32 */
#define PB1_ECC1_clear 0x09e4 /* width RMuint32 */
#define PB1_SPI_ctrl 0x09e8 /* width RMuint32 */
#define MIF_W2_ADD 0xb100 /* width RMuint32 */
#define MIF_W2_CNT 0xb104 /* width RMuint32 */
#define MIF_W2_SKIP 0xb108 /* width RMuint32 */
#define MIF_W2_CMD 0xb10c /* width RMuint32 */
#define MIF_R2_ADD 0xb140 /* width RMuint32 */
#define MIF_R2_CNT 0xb144 /* width RMuint32 */
#define MIF_R2_SKIP 0xb148 /* width RMuint32 */
#define MIF_R2_CMD 0xb14c /* width RMuint32 */
#define SYS_cec_config 0x1800 /* width RMuint32 */
#define SYS_cec_status 0x1804 /* width RMuint32 */
#define SYS_cec_clk_div 0x180C /* width RMuint32 */
#define SYS_cec_follower_select 0x1808 /* width RMuint32 */
#define SYS_cec_sft 0x1810 /* width RMuint32 */
#define SYS_cec_start_lo 0x1814 /* width RMuint32 */
#define SYS_cec_start_hi 0x1818 /* width RMuint32 */
#define SYS_cec_zero_lo 0x181C /* width RMuint32 */
#define SYS_cec_zero_hi 0x1820 /* width RMuint32 */
#define SYS_cec_one_lo 0x1824 /* width RMuint32 */
#define SYS_cec_one_hi 0x1828 /* width RMuint32 */
#define SYS_cec_ack_win_lo 0x182C /* width RMuint32 */
#define SYS_cec_ack_win_hi 0x1830 /* width RMuint32 */
#define SYS_cec_sample_delay 0x1834 /* width RMuint32 */
#define SYS_cec_receive_win 0x1838 /* width RMuint32 */
#define SYS_cec_init_xfer_hdr 0x183C /* width RMuint32 */
#define SYS_cec_init_xfer_data 0x1840 /* width RMuint32 */
#define SYS_cec_follower_header 0x1860 /* width RMuint32 */
#define SYS_cec_follower_data 0x1864 /* width RMuint32 */
#define PCI_host_reg1 0xfed0 /* width RMuint32 */
#define PCI_host_reg2 0xfed4 /* width RMuint32 */
#define PCI_host_reg3 0xfe80 /* width RMuint32 */
#define PCI_host_reg4 0xfe84 /* width RMuint32 */
#define PCI_pcictrl_reg1 0xfe88 /* width RMuint32 */
#define PCI_pcictrl_reg2 0xfe8c /* width RMuint32 */
#define PCI_pcictrl_reg3 0xfefc /* width RMuint32 */
#define PCI_REG0 0xfee8 /* width RMuint32 */
#define PCI_REG1 0xfeec /* width RMuint32 */
#define PCI_REG2 0xfef0 /* width RMuint32 */
#define PCI_REG3 0xfef4 /* width RMuint32 */
#define PCI_CONFIG 0xfef8 /* width RMuint32 */
#define MIF_W0_ADD 0xb000 /* width RMuint32 */
#define MIF_W0_CNT 0xb004 /* width RMuint32 */
#define MIF_W0_SKIP 0xb008 /* width RMuint32 */
#define MIF_W0_CMD 0xb00c /* width RMuint32 */
#define MIF_W1_ADD 0xb040 /* width RMuint32 */
#define MIF_W1_CNT 0xb044 /* width RMuint32 */
#define MIF_W1_SKIP 0xb048 /* width RMuint32 */
#define MIF_W1_CMD 0xb04c /* width RMuint32 */
#define MIF_R0_ADD 0xb080 /* width RMuint32 */
#define MIF_R0_CNT 0xb084 /* width RMuint32 */
#define MIF_R0_SKIP 0xb088 /* width RMuint32 */
#define MIF_R0_CMD 0xb08c /* width RMuint32 */
#define MIF_R1_ADD 0xb0c0 /* width RMuint32 */
#define MIF_R1_CNT 0xb0c4 /* width RMuint32 */
#define MIF_R1_SKIP 0xb0c8 /* width RMuint32 */
#define MIF_R1_CMD 0xb0cc /* width RMuint32 */
#define MBUS_IDLE 0 /* width RMuint32 */
#define MBUS_LINEAR 1 /* width RMuint32 */
#define MBUS_DOUBLE 2 /* width RMuint32 */
#define MBUS_RECTANGLE 3 /* width RMuint32 */
#define MBUS_VOID 4 /* width RMuint32 */
#define MBUS_LINEAR_VOID 5 /* width RMuint32 */
#define MBUS_DOUBLE_VOID 6 /* width RMuint32 */
#define MBUS_RECTANGLE_VOID 7 /* width RMuint32 */
#define MBUS_TILED 8 /* width RMuint32 */
#define GBUS_MUTEX_LOCAL 0x10 /* width RMuint32 */
#define GBUS_MUTEX_XPU 0x12 /* width RMuint32 */
#define GBUS_MUTEX_IPU 0x13 /* width RMuint32 */
#define GBUS_MUTEX_CPU 0x14 /* width RMuint32 */
#define GBUS_MUTEX_CPU_1 0x15 /* width RMuint32 */
#define GBUS_MUTEX_MPEG_0 0x16 /* width RMuint32 */
#define GBUS_MUTEX_MPEG_1 0x17 /* width RMuint32 */
#define GBUS_MUTEX_AUDIO_0 0x18 /* width RMuint32 */
#define GBUS_MUTEX_AUDIO_1 0x19 /* width RMuint32 */
#define GBUS_MUTEX_TDMX 0x1a /* width RMuint32 */
#define GBUS_MUTEX_TDMX_1 0x1b /* width RMuint32 */
#define GBUS_MUTEX_AUDIO_2 0x1b /* width RMuint32 */
#define GBUS_MUTEX_HOST 0x1c /* width RMuint32 */
#define GBUS_MUTEX_HOST_1 0x1d /* width RMuint32 */
#define GBUS_MUTEX_HOST_2 0x1e /* width RMuint32 */
#define SYS_chip_features 0xfe0c /* width RMuint32 */
/* SystemBlock registers done */

/* SystemFeatures registers */
/* SystemFeatures registers done */

/* TTXFifo registers */
/* TTXFifo registers done */

/* VCXO registers */
/* VCXO registers done */

/* VideoDecoder registers */
/* VideoDecoder registers done */

/* XPUBlock registers */
#define REG_BASE_xpu_block 0x000e0000 /* width RMuint32 */
/* XPUBlock registers done */

/* XTask registers */
/* XTask registers done */

#endif /* __RMCHIP_REGISTERS_SMP8682_H__ */

/* End of generated file smp8682/rmchip_registers_smp8682.h */
