/******************************************************/
/* This file is generated automatically, DO NOT EDIT! */
/******************************************************/
/*
 * smp8758/rmchip_registers_smp8758.h
 *
 * Copyright (c) 2001-2015 Sigma Designs, Inc.
 * All Rights Reserved. Proprietary and Confidential.
 *
 */
 
/**
  @file smp8758/rmchip_registers_smp8758.h
  @brief emhwlib generated file
   
  @author Sigma Designs Software Engineering Team
  @ingroup hwlproperties
*/

#ifndef __RMCHIP_REGISTERS_SMP8758_H__
#define __RMCHIP_REGISTERS_SMP8758_H__

/* Registers definitions for smp8758 */

/* AudioCapture registers */
#define audio_SI_L0_DATA 0x3e50 /* width RMuint32 */
#define audio_SI_R0_DATA 0x3e51 /* width RMuint32 */
#define audio_SI_STATUS 0x3e52 /* width RMuint32 */
#define audio_SI_CONF 0x3e53 /* width RMuint32 */
#define audio_SI_SPDIF_STATUS 0x3e54 /* width RMuint32 */
#define audio_SI_L1_DATA 0x3e55 /* width RMuint32 */
#define audio_SI_R1_DATA 0x3e56 /* width RMuint32 */
#define audio_SI_L2_DATA 0x3e57 /* width RMuint32 */
#define audio_SI_R2_DATA 0x3e58 /* width RMuint32 */
#define audio_SI_L3_DATA 0x3e59 /* width RMuint32 */
#define audio_SI_R3_DATA 0x3e5a /* width RMuint32 */
#define audio_SI_SPDIF_CONF 0x3e5b /* width RMuint32 */
#define audio_SI_SPDIF_STATUS2 0x3e5c /* width RMuint32 */
#define audio_STEREO_IN_LS_DATA 0x3f10 /* width RMuint32 */
#define audio_STEREO_IN_RR_DATA 0x3f11 /* width RMuint32 */
#define audio_STEREO_IN_STATUS 0x3f12 /* width RMuint32 */
#define audio_STEREO_IN_CONF 0x3f13 /* width RMuint32 */
/* AudioCapture registers done */

/* AudioEngine registers */
#define REG_BASE_audio_engine_0 0x00084000 /* width RMuint32 */
#define MEM_BASE_audio_engine_0 0x00180000 /* width RMuint32 */
#define PMEM_BASE_audio_engine_0 0x00180000 /* width RMuint32 */
#define PMEM_SIZE_audio_engine_0 0x8000 /* width RMuint32 */
#define DMEM_BASE_audio_engine_0 0x00190000 /* width RMuint32 */
#define DMEM_SIZE_audio_engine_0 0xf000 /* width RMuint32 */
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
#define audio_STEREO_OUT_LS_DATA 0x3f00 /* width RMuint32 */
#define audio_STEREO_OUT_RS_DATA 0x3f01 /* width RMuint32 */
#define audio_STEREO_OUT_CH_INTR 0x3f02 /* width RMuint32 */
#define audio_STEREO_OUT_CH_CTRL 0x3f03 /* width RMuint32 */
#define audio_STEREO_OUT_AUDIO_CLK_DIV 0x3f04 /* width RMuint32 */
#define audio_STEREO_OUT_AUX_CLK_HI 0x3f05 /* width RMuint32 */
#define audio_STEREO_OUT_AUX_CLK_LO 0x3f06 /* width RMuint32 */
#define audio_STEREO_OUT_AUX_CLK_CFG 0x3f07 /* width RMuint32 */
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
/* AudioEngine registers done */

/* DemuxEngine registers */
#define REG_BASE_demux_engine_0 0x00082000 /* width RMuint32 */
#define MEM_BASE_demux_engine_0 0x00140000 /* width RMuint32 */
#define PMEM_BASE_demux_engine_0 0x00140000 /* width RMuint32 */
#define PMEM_SIZE_demux_engine_0 0x8000 /* width RMuint32 */
#define DMEM_BASE_demux_engine_0 0x00150000 /* width RMuint32 */
#define DMEM_SIZE_demux_engine_0 0x8000 /* width RMuint32 */
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
#define demux_sync_lock_status_config 0x3e02 /* width RMuint32, sync lock status and config */
#define demux_ts_frame_size_3_0 0x3e03 /* width RMuint32, 8 bits for each channel 3,2,1,0 */
#define demux_ts_frame_size_7_4 0x3e04 /* width RMuint32, 8 bits for each channel 7,6,5,4 */
#define demux_tsout0_config 0x2e3d /* width RMuint32 */
#define demux_tsout1_config 0x2e3f /* width RMuint32 */
#define demux_ats_channel_sel 0x3e08 /* width RMuint32 */
#define demux_ats_counter_config 0x3e09 /* width RMuint32 */
#define demux_ats0_load 0x3e0a /* width RMuint32 */
#define demux_ats0_counter 0x3e0b /* width RMuint32 */
#define demux_ats1_load 0x3e0c /* width RMuint32 */
#define demux_ats1_counter 0x3e0d /* width RMuint32 */
#define demux_ats_global_load 0x3e0e /* width RMuint32 */
#define demux_ats_global_counter 0x3e0f /* width RMuint32 */
#define TDMX_gpio_data 0x2e38 /* width RMuint32 */
#define TDMX_gpio_dir 0x2e39 /* width RMuint32 */
#define TDMX_gpio_select 0x2e3a /* width RMuint32 */
#define demux_section_filter_start 0x3800 /* width RMuint32, 32 entries of 12 RMuint32 */
#define demux_pid_bank 0x3000 /* width RMuint32, 256 pid entries */
#define demux_pat0_pidentry 0x3cc0 /* width RMuint32, ? where is it */
#define demux_section_filter_link 0x3400 /* width RMuint32, 128 expanding links for the 128 sections  */
#define demux_section_filter 0x3480 /* width RMuint32, 128 sections, with three entries: value, mode and mask, each one 16 bytes */
#define demux_pcr0_pidentry 0x3cc6 /* width RMuint32 */
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
#define demux_key_31_00 0x2cc0 /* width RMuint32, clear key */
#define demux_key_control 0x2cc8 /* width RMuint32, control clear key */
#define demux_cw_ram_multi2_iv 0x2ac0 /* width RMuint32, 32 ivs */
#define demux_cw_ram_aes_iv 0x2a00 /* width RMuint32, 48 ivs of 128 bits */
#define demux_cw_ram_des_iv 0x2b00 /* width RMuint32, 32 ivs */
#define demux_kl_key_31_00 0x2d60 /* width RMuint32, clear key */
#define demux_kl_key_control 0x2d66 /* width RMuint32, control clear key */
#define demux_kl_aes_iv 0x3b80 /* width RMuint32, 16 iv of 16 bytes */
#define demux_kl_des_iv 0x3bc0 /* width RMuint32, 16 iv of 8 bytes */
#define demux_kl_data_31_00 0x3b40 /* width RMuint32, encrypted key */
#define demux_kl_data_access 0x3b45 /* width RMuint32, control encrypted key */
#define demux_kl_data_ctl 0x3b44 /* width RMuint32, control encrypted key */
/* DemuxEngine registers done */

/* DispAnalogOutput registers */
/* <register address="0x70400" name="REG_BASE_disp_analog_output_0" type="RMuint32" />
<register address="0x70500" name="REG_BASE_disp_analog_output_1" type="RMuint32" /> */
#define VO_main_analog_reset_bit 0x7 /* width RMuint32 */
#define VO_main_analog_conv0 0x0400 /* width RMuint32 */
#define VO_main_analog_conv1 0x0404 /* width RMuint32 */
#define VO_main_analog_conv2 0x0408 /* width RMuint32 */
#define VO_main_analog_conv3 0x040c /* width RMuint32 */
#define VO_main_analog_conv4 0x0410 /* width RMuint32 */
#define VO_main_analog_conv5 0x0414 /* width RMuint32 */
#define VO_main_analog_xoffset_field 0x0418 /* width RMuint32 */
#define VO_main_analog_yoffset 0x041c /* width RMuint32 */
#define VO_main_analog_cvbs_conv0 0x0420 /* width RMuint32 */
#define VO_main_analog_cvbs_conv1 0x0424 /* width RMuint32 */
#define VO_main_analog_cvbs_conv2 0x0428 /* width RMuint32 */
#define VO_main_analog_cvbs_conv3 0x042c /* width RMuint32 */
#define VO_main_analog_cvbs_conv4 0x0430 /* width RMuint32 */
#define VO_main_analog_cvbs_conv5 0x0434 /* width RMuint32 */
#define VO_main_analog_TV_config 0x0440 /* width RMuint32 */
#define VO_main_analog_TV_size 0x0444 /* width RMuint32 */
#define VO_main_analog_TV_hsync 0x0448 /* width RMuint32 */
#define VO_main_analog_TV_vsync_O_0 0x044c /* width RMuint32 */
#define VO_main_analog_TV_vsync_O_1 0x0450 /* width RMuint32 */
#define VO_main_analog_TV_vsync_E_0 0x0454 /* width RMuint32 */
#define VO_main_analog_TV_vsync_E_1 0x0458 /* width RMuint32 */
#define VO_main_analog_TV_HD_hsync_info 0x045c /* width RMuint32 */
#define VO_main_analog_TV_HD_vsync 0x0460 /* width RMuint32 */
#define VO_main_analog_TV_CGMS 0x0464 /* width RMuint32 */
#define VO_main_analog_TV_CC_AGC 0x0468 /* width RMuint32 */
#define VO_main_analog_TV_test_config 0x046c /* width RMuint32 */
#define VO_main_analog_TV_teletext_config 0x0470 /* width RMuint32 */
#define VO_main_analog_TV_config2 0x0474 /* width RMuint32 */
#define VO_main_analog_TV_cav_minmax 0x0478 /* width RMuint32 */
#define VO_main_analog_TV_timing_sync 0x047c /* width RMuint32 */
#define VO_main_analog_TV_MV_N_0_22 0x0480 /* width RMuint32 */
#define VO_main_analog_TV_MV_N_1_2_3_4 0x0484 /* width RMuint32 */
#define VO_main_analog_TV_MV_N_5_6_7_8 0x0488 /* width RMuint32 */
#define VO_main_analog_TV_MV_N_9_10_11 0x048c /* width RMuint32 */
#define VO_main_analog_TV_MV_N_12_13_14 0x0490 /* width RMuint32 */
#define VO_main_analog_TV_MV_N_15_16_17_18 0x0494 /* width RMuint32 */
#define VO_main_analog_TV_MV_N_19_20_21 0x0498 /* width RMuint32 */
#define VO_main_analog_ext_sync0 0x04A0 /* width RMuint32 */
#define VO_main_analog_ext_sync1 0x04A4 /* width RMuint32 */
#define VO_main_analog_ext_sync2 0x04A8 /* width RMuint32 */
#define VO_main_analog_ext_sync3 0x04AC /* width RMuint32 */
#define VO_main_analog_extra_pixel 0x04B0 /* width RMuint32 */
#define VO_main_analog_starv_config 0x04B4 /* width RMuint32 */
#define VO_main_analog_starv_default1 0x04B8 /* width RMuint32 */
#define VO_main_analog_starv_default2 0x04BC /* width RMuint32 */
#define VO_main_analog_vbi_EIA805B_ctrl 0x04c0 /* width RMuint32 */
#define VO_main_analog_vbi_EIA805B_data0 0x04c0 /* width RMuint32 */
#define VO_main_analog_vbi_EIA805B_data1 0x04c4 /* width RMuint32 */
#define VO_main_analog_vbi_EIA805B_data2 0x04c8 /* width RMuint32 */
#define VO_main_analog_vbi_EIA805B_data3 0x04d0 /* width RMuint32 */
#define VO_main_analog_tlxt0 0x1000 /* width RMuint32 */
#define VO_component_out_reset_bit 0x8 /* width RMuint32 */
#define VO_component_out_conv0 0x0500 /* width RMuint32 */
#define VO_component_out_conv1 0x0504 /* width RMuint32 */
#define VO_component_out_conv2 0x0508 /* width RMuint32 */
#define VO_component_out_conv3 0x050c /* width RMuint32 */
#define VO_component_out_conv4 0x0510 /* width RMuint32 */
#define VO_component_out_conv5 0x0514 /* width RMuint32 */
#define VO_component_out_xoffset_field 0x0518 /* width RMuint32 */
#define VO_component_out_yoffset 0x051c /* width RMuint32 */
#define VO_component_out_cvbs_conv0 0x0520 /* width RMuint32 */
#define VO_component_out_cvbs_conv1 0x0524 /* width RMuint32 */
#define VO_component_out_cvbs_conv2 0x0528 /* width RMuint32 */
#define VO_component_out_cvbs_conv3 0x052c /* width RMuint32 */
#define VO_component_out_cvbs_conv4 0x0530 /* width RMuint32 */
#define VO_component_out_cvbs_conv5 0x0534 /* width RMuint32 */
#define VO_component_out_TV_config 0x0540 /* width RMuint32 */
#define VO_component_out_TV_size 0x0544 /* width RMuint32 */
#define VO_component_out_TV_hsync 0x0548 /* width RMuint32 */
#define VO_component_out_TV_vsync_O_0 0x054c /* width RMuint32 */
#define VO_component_out_TV_vsync_O_1 0x0550 /* width RMuint32 */
#define VO_component_out_TV_vsync_E_0 0x0554 /* width RMuint32 */
#define VO_component_out_TV_vsync_E_1 0x0558 /* width RMuint32 */
#define VO_component_out_TV_HD_hsync_info 0x055c /* width RMuint32 */
#define VO_component_out_TV_HD_vsync 0x0560 /* width RMuint32 */
#define VO_component_out_TV_CGMS 0x0564 /* width RMuint32 */
#define VO_component_out_TV_CC_AGC 0x0568 /* width RMuint32 */
#define VO_component_out_TV_test_config 0x056c /* width RMuint32 */
#define VO_component_out_TV_teletext_config 0x0570 /* width RMuint32 */
#define VO_component_out_TV_config2 0x0574 /* width RMuint32 */
#define VO_component_out_TV_cav_minmax 0x0578 /* width RMuint32 */
#define VO_component_out_TV_timing_sync 0x057c /* width RMuint32 */
#define VO_component_out_TV_MV_N_0_22 0x0580 /* width RMuint32 */
#define VO_component_out_TV_MV_N_1_2_3_4 0x0584 /* width RMuint32 */
#define VO_component_out_TV_MV_N_5_6_7_8 0x0588 /* width RMuint32 */
#define VO_component_out_TV_MV_N_9_10_11 0x058c /* width RMuint32 */
#define VO_component_out_TV_MV_N_12_13_14 0x0590 /* width RMuint32 */
#define VO_component_out_TV_MV_N_15_16_17_18 0x0594 /* width RMuint32 */
#define VO_component_out_TV_MV_N_19_20_21 0x0598 /* width RMuint32 */
#define VO_component_out_ext_sync0 0x05A0 /* width RMuint32 */
#define VO_component_out_ext_sync1 0x05A4 /* width RMuint32 */
#define VO_component_out_ext_sync2 0x05A8 /* width RMuint32 */
#define VO_component_out_ext_sync3 0x05AC /* width RMuint32 */
#define VO_component_out_extra_pixel 0x05B0 /* width RMuint32 */
#define VO_component_out_starv_config 0x05B4 /* width RMuint32 */
#define VO_component_out_starv_default1 0x05B8 /* width RMuint32 */
#define VO_component_out_starv_default2 0x05BC /* width RMuint32 */
#define VO_component_out_vbi_EIA805B_ctrl 0x05c0 /* width RMuint32 */
#define VO_component_out_vbi_EIA805B_data0 0x05c0 /* width RMuint32 */
#define VO_component_out_vbi_EIA805B_data1 0x05c4 /* width RMuint32 */
#define VO_component_out_vbi_EIA805B_data2 0x05c8 /* width RMuint32 */
#define VO_component_out_vbi_EIA805B_data3 0x05d0 /* width RMuint32 */
/* DispAnalogOutput registers done */

/* DispDigitalOutput registers */
/* <register address="0x71400" name="MEM_BASE_disp_digital_output_0" type="RMuint32" />
<register address="0x70200" name="REG_BASE_disp_digital_output_0" type="RMuint32" /> */
#define VO_digit_out_reset_bit 0x0 /* width RMuint32 */
#define VO_digit_out_conv0 0x0200 /* width RMuint32 */
#define VO_digit_out_conv1 0x0204 /* width RMuint32 */
#define VO_digit_out_conv2 0x0208 /* width RMuint32 */
#define VO_digit_out_conv3 0x020c /* width RMuint32 */
#define VO_digit_out_conv4 0x0210 /* width RMuint32 */
#define VO_digit_out_conv5 0x0214 /* width RMuint32 */
#define VO_digit_out_format 0x0220 /* width RMuint32 */
#define VO_digit_out_Xoffset 0x0224 /* width RMuint32 */
#define VO_digit_out_Yoffset 0x0228 /* width RMuint32 */
#define VO_digit_out_hz_sync 0x022c /* width RMuint32 */
#define VO_digit_out_vt_sync 0x0230 /* width RMuint32 */
#define VO_digit_out_vsync_coord 0x0234 /* width RMuint32 */
#define VO_digit_out_sync_ext_sync 0x0238 /* width RMuint32 */
#define VO_digit_out_color_depth 0x023c /* width RMuint32 */
#define VO_digit_out_ext_sync0 0x0240 /* width RMuint32 */
#define VO_digit_out_ext_sync1 0x0244 /* width RMuint32 */
#define VO_digit_out_ext_sync2 0x0248 /* width RMuint32 */
#define VO_digit_out_ext_sync3 0x024C /* width RMuint32 */
#define VO_digit_out_starv_config 0x0250 /* width RMuint32 */
#define VO_digit_out_starv_default1 0x0254 /* width RMuint32 */
#define VO_digit_out_starv_default2 0x0258 /* width RMuint32 */
#define VO_digit_out_field_alternative_mode_ctrl 0x025C /* width RMuint32 */
#define VO_digit_out_gamma_lut0 0x1400 /* width RMuint32 */
#define VO_digit_out_temp_lut0 0x1600 /* width RMuint32 */
#define VO_pads_config 0x0180 /* width RMuint32 */
#define VO_pads_delay_limits 0x0184 /* width RMuint32 */
#define VO_pads_ref_delay_limits 0x0188 /* width RMuint32 */
#define VO_pads_ref_delay_init 0x018C /* width RMuint32 */
#define VO_pads_DLL_config 0x0190 /* width RMuint32 */
/* DispDigitalOutput registers done */

/* DispBlkScaler registers */
#define VO_BlkSclr_reset_bit 0x0c /* width RMuint32 */
#define REG_BASE_blk_sclr 0x381000 /* width RMuint32 */
#define VO_OutPSO_reset_base 0x380000 /* width RMuint32 */
#define VO_BlkSclr_format_hds 0x00 /* width RMuint32 */
#define VO_BlkSclr_alpha 0x04 /* width RMuint32 */
#define VO_BlkSclr_stripe 0x08 /* width RMuint32 */
#define VO_BlkSclr_stripe_color 0x0c /* width RMuint32 */
/* DispBlkScaler registers done */

/* DispHardwareCursor registers */
#define REG_BASE_disp_hardware_cursor_0 0x380180 /* width RMuint32 */
#define MEM_LUT_BASE_disp_hardware_cursor_0 0x380200 /* width RMuint32 */
#define MEM_CUR_BASE_disp_hardware_cursor_0 0x380800 /* width RMuint32 */
/* DispHardwareCursor registers done */

/* DispHDMITx registers */
/* <register address="0x70800" name="REG_BASE_disp_hdmi_0" type="RMuint32" /> */
#define VO_hdmi_reset_bit 0x03 /* width RMuint32 */
#define VO_hdmi_pads_reset_bit 0x04 /* width RMuint32 */
#define VO_hdmi_regmap 0x0800 /* width RMuint32 */
#define VO_hdmi_config 0x0d00 /* width RMuint32 */
#define VO_hdmi_ctrl 0x0d04 /* width RMuint32 */
#define VO_hdmi_write 0x0d08 /* width RMuint32, reserved on T4 */
#define VO_hdmi_read 0x0d0c /* width RMuint32, reserved on T4 */
#define VO_hdmi_test0 0x0d10 /* width RMuint32 */
#define VO_hdmi_test1 0x0d14 /* width RMuint32 */
#define VO_hdmi_test2 0x0d18 /* width RMuint32 */
#define VO_hdmi_test3 0x0d1c /* width RMuint32 */
#define VO_hdmi_i2c 0x0dc0 /* width RMuint32, reserved on T4 */
#define VO_hdmi_keymem 0x0e00 /* width RMuint32 */
/* DispHDMITx registers done */

/* DisplayHDMIRx registers */
#define VO_hdmi_rx_reset_bit 0x5 /* width RMuint32, same as ResetBitsBviPso_Hdmi0ResetBit */
#define VO_hdmi_rx_regmap 0x3900 /* width RMuint32, relative to REG_BASE_video_input */
#define VO_hdmi_rx_keymem 0x3c00 /* width RMuint32, relative to REG_BASE_video_input */
/* DisplayHDMIRx registers done */

/* DispConstrainedImage registers */
#define REG_BASE_disp_constrained_image_0 0x380170 /* width RMuint32 */
#define VO_CI_reset_bit 0x00 /* width RMuint32 */
#define VO_CI_read_reset_bit 0x01 /* width RMuint32 */
/* DispConstrainedImage registers done */

/* DispHDSD registers */
#define VO_HDSD_reset_bit 0x02 /* width RMuint32 */
#define VO_HDSD_read_reset_bit 0x03 /* width RMuint32 */
#define VO_HDSD_config 0x381400 /* width RMuint32 */
#define VO_HDSD_xscale 0x381404 /* width RMuint32 */
#define VO_HDSD_yscale 0x381408 /* width RMuint32 */
#define VO_HDSD_dump 0x38140c /* width RMuint32 */
/* DispHDSD registers done */

/* DispInput registers */
#define REG_BASE_video_input 0x50000 /* width RMuint32, same as psoRegBase[VSYNC_PSO_DOMAIN_BVI] */
#define REG_BASE_disp_input_0 0x53900 /* width RMuint32, TODO: check if it is used */
#define VI_digital_in_format 0x0 /* width RMuint32 */
/* DispInput registers done */

/* VideoProcessing registers */
#define REG_BASE_video_processing 0x0008a000 /* width RMuint32, Merge of BVP misc, BVP out and BVP src */
#define REG_RANGE_video_processing 0x00001000 /* width RMuint32 */
#define MEM_BASE_video_processing 0x00300000 /* width RMuint32, Merge of BVP misc, BVP out and BVP src */
#define MEM_RANGE_video_processing 0x00100000 /* width RMuint32 */
#define MEM_BASE_VP_src 0x00360000 /* width RMuint32, BVP src */
#define MEM_BASE_VP_misc 0x00300000 /* width RMuint32, BVP src */
#define PMEM_BASE_display_block 0x00300000 /* width RMuint32 */
/* DFD offsets, relative to MEM_BASE_VP_misc */
#define VO_dfd0_base 0x08000 /* width RMuint32 */
#define VO_dfd1_base 0x08800 /* width RMuint32 */
#define VO_dfd2_base 0x09000 /* width RMuint32 */
#define VO_dfd3_base 0x09800 /* width RMuint32 */
#define VO_dfd4_base 0x0a000 /* width RMuint32 */
#define VO_dfd5_base 0x0a800 /* width RMuint32 */
#define VO_dfd6_base 0x0b000 /* width RMuint32 */
#define VO_dfd7_base 0x0b800 /* width RMuint32 */
#define VO_dfd8_base 0x0c000 /* width RMuint32 */
#define VO_dfd9_base 0x0c800 /* width RMuint32 */
#define VO_dfd10_base 0x0d000 /* width RMuint32 */
#define VO_dfd11_base 0x0d800 /* width RMuint32 */
#define VO_dfd12_base 0x0e000 /* width RMuint32 */
#define VO_dfe0_base 0x12000 /* width RMuint32 */
#define VO_dfe1_base 0x12010 /* width RMuint32 */
#define VO_dfe2_base 0x12020 /* width RMuint32 */
/* DFD reset bits, to be used in the VO_reset_run or VO_reset_datapath regs */
#define VO_dfd0_reset_bit 0 /* width RMuint32 */
#define VO_dfd1_reset_bit 1 /* width RMuint32 */
#define VO_dfd2_reset_bit 2 /* width RMuint32 */
#define VO_dfd3_reset_bit 3 /* width RMuint32 */
#define VO_dfd4_reset_bit 4 /* width RMuint32 */
#define VO_dfd5_reset_bit 5 /* width RMuint32 */
#define VO_dfd6_reset_bit 6 /* width RMuint32 */
#define VO_dfd7_reset_bit 7 /* width RMuint32 */
#define VO_dfd8_reset_bit 8 /* width RMuint32 */
#define VO_dfd9_reset_bit 9 /* width RMuint32 */
#define VO_dfd10_reset_bit 10 /* width RMuint32 */
#define VO_dfd11_reset_bit 11 /* width RMuint32 */
#define VO_dfd12_reset_bit 12 /* width RMuint32 */
#define VO_dfd13_reset_bit 13 /* width RMuint32 */
#define VO_dfd14_reset_bit 14 /* width RMuint32 */
#define VO_dfd15_reset_bit 15 /* width RMuint32 */
#define VO_dfe0_reset_bit 16 /* width RMuint32 */
#define VO_dfe1_reset_bit 17 /* width RMuint32 */
#define VO_dfe2_reset_bit 18 /* width RMuint32 */
#define VO_dfe3_reset_bit 19 /* width RMuint32 */
#define VO_dfe4_reset_bit 20 /* width RMuint32 */
#define VO_dfe5_reset_bit 21 /* width RMuint32 */
#define VO_dfe6_reset_bit 22 /* width RMuint32 */
#define VO_dfe7_reset_bit 23 /* width RMuint32 */
/* VideoProcessing registers done */

/* DisplayBlock registers */
#define REG_BASE_display_block 0x00070000 /* width RMuint32 */
#define PMEM_BASE_display_block 0x00300000 /* width RMuint32 */
#define VO_run 0x0000 /* width RMuint32 */
#define VO_reset_datapath 0x0004 /* width RMuint32 */
#define VO_reset_timing 0x0008 /* width RMuint32 */
#define VO_reset_config 0x000c /* width RMuint32 */
#define VO_reset_mode_0 0x0014 /* width RMuint32 */
#define VO_reset_mode_1 0x0018 /* width RMuint32 */
#define REG_BASE_VIF0_r_0 0x303000 /* width RMuint32 */
#define REG_BASE_VIF0_r_1 0x303040 /* width RMuint32 */
#define REG_BASE_VIF0_r_2 0x303080 /* width RMuint32 */
#define REG_BASE_VIF0_r_3 0x3030c0 /* width RMuint32 */
#define REG_BASE_VIF0_r_4 0x303100 /* width RMuint32 */
#define REG_BASE_VIF0_r_5 0x303140 /* width RMuint32 */
#define REG_BASE_VIF0_r_6 0x303180 /* width RMuint32 */
#define REG_BASE_VIF0_r_7 0x3031c0 /* width RMuint32 */
#define REG_BASE_VIF0_r_8 0x303200 /* width RMuint32 */
#define REG_BASE_VIF0_r_9 0x303240 /* width RMuint32 */
#define REG_BASE_VIF0_r_10 0x303280 /* width RMuint32 */
#define REG_BASE_VIF0_r_11 0x3032c0 /* width RMuint32 */
#define REG_BASE_VIF0_r_12 0x303300 /* width RMuint32 */
#define REG_BASE_VIF0_r_13 0x303340 /* width RMuint32 */
#define REG_BASE_VIF0_r_14 0x303380 /* width RMuint32 */
#define REG_BASE_VIF0_r_15 0x3033c0 /* width RMuint32 */
#define REG_BASE_VIF0_r_16 0x303400 /* width RMuint32 */
#define REG_BASE_VIF1_r_0 0x305000 /* width RMuint32 */
#define REG_BASE_VIF1_r_1 0x305040 /* width RMuint32 */
#define REG_BASE_VIF1_r_2 0x305080 /* width RMuint32 */
#define REG_BASE_VIF1_r_3 0x3050c0 /* width RMuint32 */
#define REG_BASE_VIF0_w_0 0x302000 /* width RMuint32 */
#define REG_BASE_VIF0_w_1 0x302040 /* width RMuint32 */
#define REG_BASE_VIF0_w_2 0x302080 /* width RMuint32 */
#define REG_BASE_VIF0_w_3 0x3020c0 /* width RMuint32 */
#define REG_BASE_VIF0_w_4 0x302100 /* width RMuint32 */
#define REG_BASE_VIF0_w_5 0x302140 /* width RMuint32 */
#define REG_BASE_VIF0_w_6 0x302180 /* width RMuint32 */
#define REG_BASE_VIF0_w_7 0x3021c0 /* width RMuint32 */
#define REG_BASE_VIF1_w_0 0x304000 /* width RMuint32 */
#define VO_dac_mux_config0 0x0100 /* width RMuint32 */
#define VO_dac_mux_config1 0x0104 /* width RMuint32 */
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
/* DisplayBlock registers done */

/* DispVXPDeinterlacer registers */
#define REG_BASE_disp_vxp_deinterlacer_0 0x321f00 /* width RMuint32 */
/* DispVXPDeinterlacer registers done */

/* DispColorBars registers */
#define REG_BASE_disp_color_bars_0 0x380150 /* width RMuint32 */
/* DispColorBars registers done */

/* DispMPScaler registers */
#define REG_BASE_disp_mp_scaler_0 0x321000 /* width RMuint32 */
#define REG_BASE_disp_mp_scaler_1 0x361000 /* width RMuint32 */
#define REG_BASE_disp_mp_scaler_2 0x361400 /* width RMuint32 */
#define REG_BASE_disp_mp_scaler_3 0x381000 /* width RMuint32 */
#define REG_BASE_disp_mp_scaler_4 0x361800 /* width RMuint32 */
#define REG_BASE_disp_mp_scaler_5 0x361c00 /* width RMuint32 */
/* DispMPScaler registers done */

/* DispVXPACE registers */
#define REG_BASE_disp_vxpace_0 0x321800 /* width RMuint32 */
#define REG_BASE_disp_vxpace_1 0x341800 /* width RMuint32 */
/* DispVXPACE registers done */

/* DispMixer registers */
#define REG_BASE_disp_mixer_0 0x300240 /* width RMuint32 */
#define REG_BASE_disp_mixer_1 0x300200 /* width RMuint32 */
/* DispMixer registers done */

/* CPUBlock registers */
#define REG_BASE_cpu_block 0x00060000 /* width RMuint32 */
#define MEM_BASE_cpu_block 0x00800000 /* width RMuint32 */
#define CPU_ARM_SCU_BASE 0x20000000 /* width RMuint32 */
#define CPU_ARM_L2CACHE_BASE 0x20100000 /* width RMuint32 */
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
#define CPU_VBUS1_WRITE_CH1_INT 0x00020000 /* width RMuint32 */
#define CPU_DIGITAL0_EOF_INT 0x00040000 /* width RMuint32 */
#define CPU_FRONTPANEL_INT 0x00080000 /* width RMuint32 */
#define CPU_ANALOG0_EOF_INT 0x00100000 /* width RMuin32 */
#define CPU_I2C_INT 0x00400000 /* width RMuint32 */
#define CPU_GFX_ACCEL_INT 0x00800000 /* width RMuint32 */
#define CPU_MISC_PSO_DMA2LBUS_READ_INT 0x01000000 /* width RMuint32 */
#define CPU_ANALOG0_VSYNC_INT 0x02000000 /* width RMuint32 */
#define CPU_ANALOG1_VSYNC_INT 0x04000000 /* width RMuint32 */
#define CPU_DIGITAL0_VSYNC_INT 0x08000000 /* width RMuint32 */
#define CPU_DIGITALIN0_VSYNC_INT 0x10000000 /* width RMuint32 */
#define CPU_DIGITALIN0_VBI_INT 0x20000000 /* width RMuint32 */
#define CPU_VBUS0_WRITE_CH2_INT 0x40000000 /* width RMuint32 */
#define CPU_VBUS0_WRITE_CH4_INT 0x80000000 /* width RMuint32 */
#define CPU_SMARTCARD_HI_INT 0x00000001 /* width RMuint32 */
#define CPU_HDMI_HI_INT 0x00000002 /* width RMuint32 */
#define CPU_ANALOG1_EOF_HI_INT 0x00000004 /* width RMuint32 */
#define CPU_VBUS0_WRITE_CH0_HI_INT 0x00000008 /* width RMuint32 */
#define CPU_VIDSRC0_PSO_DMA2LBUS_READ_HI_INT 0x00000010 /* width RMuint32 */
#define CPU_ETH_PHY_HI_INT 0x00000020 /* width RMuint32 */
#define CPU_ETH_MAC_HI_INT 0x00000040 /* width RMuint32 */
#define CPU_SRC_PSO_DMA2LBUS_READ_HI_INT 0x00000080 /* width RMuint32 */
#define CPU_USB_EHCI_MAC_HI_INT 0x00000100 /* width RMuint32 */
#define CPU_OUT_PSO_DMA2LBUS_READ_HI_INT 0x00080000 /* width RMuint32 */
#define CPU_3D_OFMT_FIELD_HI_INT 0x20000000 /* width RMuint32 */
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
#define LOG2_CPU_VBUS1_WRITE_CH1_INT 17 /* width RMuint32 */
#define LOG2_CPU_DIGITAL0_EOF_INT 18 /* width RMuint32 */
#define LOG2_CPU_FRONTPANEL_INT 19 /* width RMuint32 */
#define LOG2_CPU_ANALOG0_EOF_INT 20 /* width RMuint32 */
#define LOG2_CPU_INFRARED_INT 21 /* width RMuint32 */
#define LOG2_CPU_I2C_INT 22 /* width RMuint32 */
#define LOG2_CPU_GFX_ACCEL_INT 23 /* width RMuint32 */
#define LOG2_CPU_MISC_PSO_DMA2LBUS_READ_INT 24 /* width RMuint32 */
#define LOG2_ANALOG0_VSYNC_INT 25 /* width RMuint32 */
#define LOG2_ANALOG1_VSYNC_INT 26 /* width RMuint32 */
#define LOG2_CPU_DIGITAL0_VSYNC_INT 27 /* width RMuint32 */
#define LOG2_CPU_DIGITALIN0_VSYNC_INT 28 /* width RMuint32 */
#define LOG2_CPU_DIGITALIN0_VBI_INT 29 /* width RMuint32 */
#define LOG2_CPU_VBUS0_WRITE_CH2_INT 30 /* width RMuint32 */
#define LOG2_CPU_VBUS0_WRITE_CH4_INT 31 /* width RMuint32 */
#define LOG2_CPU_SMARTCARD_INT 32 /* width RMuint32 */
#define LOG2_CPU_HDMI_INT 33 /* width RMuint32 */
#define LOG2_CPU_ANALOG1_EOF_HI_INT 34 /* width RMuint32 */
#define LOG2_CPU_VBUS0_WRITE_CH0_HI_INT 35 /* width RMuint32 */
#define LOG2_CPU_VIDSRC0_PSO_DMA2LBUS_READ_HI_INT 36 /* width RMuint32 */
#define LOG2_CPU_ETH_PHY_INT 37 /* width RMuint32 */
#define LOG2_CPU_ETH_MAC_INT 38 /* width RMuint32 */
#define LOG2_CPU_SRC_PSO_DMA2LBUS_READ_HI_INT 39 /* width RMuint32 */
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
#define LOG2_CPU_OUT_PSO_DMA2LBUS_READ_HI_INT 51 /* width RMuint32 */
#define LOG2_CPU_SMARTCARD1_INT 52 /* width RMuint32 */
#define LOG2_CPU_HDMI_CEC_INT 53 /* width RMuint32 */
#define LOG2_CPU_SATA1_INT 54 /* width RMuint32 */
#define LOG2_CPU_DMASATA1_INT 55 /* width RMuint32 */
#define LOG2_CPU_ETH_PHY1_INT 56 /* width RMuint32 */
#define LOG2_CPU_ETH_MAC1_INT 57 /* width RMuint32 */
#define LOG2_CPU_HOST_MBUS_W2_INT 58 /* width RMuint32 */
#define LOG2_CPU_HOST_MBUS_R2_INT 59 /* width RMuint32 */
#define LOG2_CPU_SDIO0_INT 60 /* width RMuint32 */
#define LOG2_CPU_3D_OFMT_FIELD_HI_INT 61 /* width RMuint32 */
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
/* Those are related to the CPU MEM BASE */
#define CPU_arm_debug_unlock 0x110fb0 /* width RMuint32, Called DBGLAR by ARM */
#define CPU_arm_rst_ctrl_off 0x120000 /* width RMuint32 */
#define CPU_event 0x120000 /* width RMuint32 */
#define CPU_standby_status 0x120004 /* width RMuint32 */
#define CPU_rst_config 0x120008 /* width RMuint32 */
#define CPU_glob_var 0x12000c /* width RMuint32 */
#define CPU_watchdog_policy_core0 0x120010 /* width RMuint32 */
#define CPU_watchdog_policy_core1 0x120014 /* width RMuint32 */
#define CPU_watchdog_policy_core2 0x120018 /* width RMuint32 */
#define CPU_watchdog_policy_core3 0x12001c /* width RMuint32 */
#define CPU_apb_en 0x120020 /* width RMuint32 */
#define CPU_debug_en_core0 0x120024 /* width RMuint32 */
#define CPU_debug_en_core1 0x120028 /* width RMuint32 */
#define CPU_debug_en_core2 0x12002c /* width RMuint32 */
#define CPU_debug_en_core3 0x120030 /* width RMuint32 */
#define CPU_TEMP_SENSOR 0x120100 /* width RMuint32 */
/* chip specific stuff over */
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
#define G2L_ANOTHER_RESET_CONTROL 0x0ffc /* width RMuint32 */
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
#define CPU_arm_apb_en 0x120020 /* width RMuint32 */
#define CPU_arm_core0_debug_en 0x120024 /* width RMuint32 */
#define CPU_arm_core1_debug_en 0x120028 /* width RMuint32 */
#define CPU_arm_core2_debug_en 0x12002c /* width RMuint32 */
#define CPU_arm_core3_debug_en 0x120030 /* width RMuint32 */
/* CPUBlock registers done */

/* GFXEngine registers */
/* introduce these once the GACC driver is implemented
<register address="0x380400" name="LUT_BASE_graph_acc_0" type="RMuint32" />
<register address="0x380300" name="REG_BASE_graph_acc_0" type="RMuint32" /> */
#define REG_BASE_graph_acc 0x380300 /* width RMuint32 */
#define VO_graph_acc_reset_bit 0x0d /* width RMuint32 */
#define VO_graph_acc_reset_mask 0x00300000 /* width RMuint32 */
#define VO_graph_acc_reset_run 0x00000000 /* width RMuint32 */
#define VO_graph_acc_reset_path 0x00100000 /* width RMuint32 */
#define VO_graph_acc_reset_time 0x00200000 /* width RMuint32 */
#define VO_graph_acc_reset_conf 0x00300000 /* width RMuint32 */
#define VO_graph_acc_X_format 0x0000 /* width RMuint32 */
#define VO_graph_acc_X_alpha 0x0004 /* width RMuint32 */
#define VO_graph_acc_X_keycolor 0x0008 /* width RMuint32 */
#define VO_graph_acc_Y_format 0x000c /* width RMuint32 */
#define VO_graph_acc_Y_keycolor 0x0010 /* width RMuint32 */
#define VO_graph_acc_control 0x0014 /* width RMuint32 */
#define VO_graph_acc_font 0x0004 /* width RMuint32 */
#define VO_graph_acc_fill 0x0004 /* width RMuint32 */
#define VO_graph_acc_control2 0x001c /* width RMuint32 */
#define VO_graph_acc_Z_format 0x0020 /* width RMuint32 */
#define VO_graph_acc_control3 0x0024 /* width RMuint32 */
#define VO_graph_acc_lut0 0x0100 /* width RMuint32 */
#define VO_graph_acc_FILL 0 /* width RMuint32 */
#define VO_graph_acc_BLEND 1 /* width RMuint32 */
#define VO_graph_acc_MOVE 2 /* width RMuint32 */
#define VO_graph_acc_REPLACE 3 /* width RMuint32 */
#define VO_graph_acc_RASTER 4 /* width RMuint32 */
#define VO_graph_acc_mode_control 0x0080 /* width RMuint32 */
#define VO_graph_acc_DRAM_read_address 0x0084 /* width RMuint32 */
#define VO_graph_acc_DRAM_write_address 0x0088 /* width RMuint32 */
#define VO_graph_acc_X_bounding_box 0x008c /* width RMuint32 */
#define VO_graph_acc_Y_bounding_box 0x0090 /* width RMuint32 */
#define VO_graph_acc_scaling_and_contours 0x0094 /* width RMuint32 */
#define VO_graph_acc_matrix_coeffs_scale 0x0098 /* width RMuint32 */
#define VO_graph_acc_matrix_coeffs_cross_scale 0x009c /* width RMuint32 */
#define VO_graph_acc_matrix_coeffs_offset 0x00a0 /* width RMuint32 */
#define VO_graph_acc_grd_color0 0x0040 /* width RMuint32 */
#define VO_graph_acc_grd_color1 0x0044 /* width RMuint32 */
#define VO_graph_acc_grd_scale_factor 0x0048 /* width RMuint32 */
#define VO_graph_acc_grd_vt_scale_init 0x004c /* width RMuint32 */
#define VO_graph_acc_grd_init_square_dist 0x0050 /* width RMuint32 */
#define VO_graph_acc_grd_ext_radius 0x0054 /* width RMuint32 */
#define VO_graph_acc_grd_int_radius 0x0058 /* width RMuint32 */
#define VO_graph_acc_grd_center 0x005c /* width RMuint32 */
#define VO_graph_acc_grd_control 0x0060 /* width RMuint32 */
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

/* SystemBlock registers */
#define REG_BASE_system_block 0x00010000 /* width RMuint32 */
/* SystemBlock registers - offsets relative to REG_BASE_system_block */
#define SYS_clkgen0_pll 0x0000 /* width RMuint32 */
#define SYS_clkgen0_div 0x0004 /* width RMuint32 */
#define SYS_clkgen1_pll 0x0008 /* width RMuint32 */
#define SYS_clkgen1_div 0x000C /* width RMuint32 */
#define SYS_clkgen2_pll 0x0010 /* width RMuint32 */
#define SYS_clkgen2_div 0x0014 /* width RMuint32 */
#define SYS_clkgen3_pll 0x0018 /* width RMuint32 */
#define SYS_clkgen3_div 0x001C /* width RMuint32 */
#define SYS_sysclk_div_ctrl 0x0020 /* width RMuint32 */
#define SYS_cpuclk_div_ctrl 0x0024 /* width RMuint32 */
#define SYS_gpuclk_div_ctrl 0x0028 /* width RMuint32 */
#define SYS_gpuhostclk_mux 0x0030 /* width RMuint32 */
#define SYS_hostclk_mux 0x0030 /* width RMuint32, legacy name */
#define SYS_sysclk_premux 0x0034 /* width RMuint32 */
#define SYS_avclk_mux 0x0038 /* width RMuint32 */
#define SYS_sysclk_mux 0x003C /* width RMuint32 */
#define SYS_clk_cnt 0x0040 /* width RMuint32 */
#define SYS_rnd_cnt 0x0044 /* width RMuint32 */
#define SYS_xtal_in_cnt 0x0048 /* width RMuint32 */
#define SYS_cnt_cfg 0x004c /* width RMuint32 */
#define SYS_cfg_cnt0 0x0050 /* width RMuint32 */
#define SYS_cfg_cnt1 0x0054 /* width RMuint32 */
#define SYS_cfg_cnt2 0x0058 /* width RMuint32 */
#define SYS_cfg_cnt3 0x005c /* width RMuint32 */
#define SYS_cfg_cnt4 0x0060 /* width RMuint32 */
#define SYS_cleandiv0_div 0x0080 /* width RMuint32 */
#define SYS_cleandiv0_ctrl 0x0084 /* width RMuint32 */
#define SYS_cleandiv1_div 0x0088 /* width RMuint32 */
#define SYS_cleandiv1_ctrl 0x008c /* width RMuint32 */
#define SYS_cleandiv2_div 0x0090 /* width RMuint32 */
#define SYS_cleandiv2_ctrl 0x0094 /* width RMuint32 */
#define SYS_cleandiv3_div 0x0098 /* width RMuint32 */
#define SYS_cleandiv3_ctrl 0x009c /* width RMuint32 */
#define SYS_cleandiv4_div 0x00a0 /* width RMuint32 */
#define SYS_cleandiv4_ctrl 0x00a4 /* width RMuint32 */
#define SYS_cleandiv5_div 0x00a8 /* width RMuint32 */
#define SYS_cleandiv5_ctrl 0x00ac /* width RMuint32 */
#define SYS_cleandiv6_div 0x00b0 /* width RMuint32 */
#define SYS_cleandiv6_ctrl 0x00b4 /* width RMuint32 */
#define SYS_cleandiv7_div 0x00b8 /* width RMuint32 */
#define SYS_cleandiv7_ctrl 0x00bc /* width RMuint32 */
#define SYS_cleandiv8_div 0x00c0 /* width RMuint32 */
#define SYS_cleandiv8_ctrl 0x00c4 /* width RMuint32 */
#define SYS_cleandiv9_div 0x00c8 /* width RMuint32 */
#define SYS_cleandiv9_ctrl 0x00cc /* width RMuint32 */
#define SYS_cleandiv10_div 0x00d0 /* width RMuint32 */
#define SYS_cleandiv10_ctrl 0x00d4 /* width RMuint32 */
#define SYS_cleandiv11_div 0x00d8 /* width RMuint32 */
#define SYS_cleandiv11_ctrl 0x00dc /* width RMuint32 */
/* DRAM VBUS Unit - offsets relative to REG_BASE_dram_controller */
#define DRAM_vbus_w0_cfg 0x0300 /* width RMuint32, w0 MainVideo Write */
#define DRAM_vbus_w1_cfg 0x0304 /* width RMuint32, w1 VXPNRDI IfmdWrite */
#define DRAM_vbus_w2_cfg 0x0308 /* width RMuint32, w2 HDSD/CI Write */
#define DRAM_vbus_w3_cfg 0x030c /* width RMuint32, w3 VXPNRDI Write Y */
#define DRAM_vbus_w4_cfg 0x0310 /* width RMuint32, w4 VXPNRDI Write C */
#define DRAM_vbus_w5_cfg 0x0314 /* width RMuint32, w5 Reserved */
#define DRAM_vbus_w6_cfg 0x036c /* width RMuint32, w6 DigitalInput Y Write */
#define DRAM_vbus_w7_cfg 0x0370 /* width RMuint32, w7 DigitalInput C Write */
#define DRAM_vbus_r0_cfg 0x0380 /* width RMuint32, r0 VXPNRDI IFMD */
#define DRAM_vbus_r1_cfg 0x0384 /* width RMuint32, r1 MainVideo Y */
#define DRAM_vbus_r2_cfg 0x0388 /* width RMuint32, r2 MainVideo C */
#define DRAM_vbus_r3_cfg 0x038c /* width RMuint32, r3 VXPNRDI Current Y */
#define DRAM_vbus_r4_cfg 0x0390 /* width RMuint32, r4 VXPNRDI Current C */
#define DRAM_vbus_r5_cfg 0x0394 /* width RMuint32, r5 VXPNRDI Past Y */
#define DRAM_vbus_r6_cfg 0x0398 /* width RMuint32, r6 VXPNRDI Past C */
#define DRAM_vbus_r7_cfg 0x039c /* width RMuint32, r7 Graphics0 */
#define DRAM_vbus_r8_cfg 0x03a0 /* width RMuint32, r8 Secondary Y */
#define DRAM_vbus_r9_cfg 0x03a4 /* width RMuint32, r9 Graphics2 Y */
#define DRAM_vbus_r10_cfg 0x03a8 /* width RMuint32, r10 Graphics2 C */
#define DRAM_vbus_r11_cfg 0x03ac /* width RMuint32, r11 Graphics1 Y */
#define DRAM_vbus_r12_cfg 0x03b0 /* width RMuint32, r12 Memory_1 Y */
#define DRAM_vbus_r13_cfg 0x03b4 /* width RMuint32, r13  */
#define DRAM_vbus_r14_cfg 0x03b8 /* width RMuint32, r14 HDSD/CI Read */
#define DRAM_vbus_r15_cfg 0x03bc /* width RMuint32, r15 VXPNRDI IfmdRead */
#define DRAM_vbus_r16_cfg 0x03c0 /* width RMuint32, r16 Secondary C */
#define DRAM_vbus_r17_cfg 0x03c4 /* width RMuint32, r17 Reserved */
#define DRAM_vbus_r18_cfg 0x03c8 /* width RMuint32, r18 Reserved */
#define DRAM_vbus_r19_cfg 0x03cc /* width RMuint32, r19 Reserved */
#define DRAM_vbus_r20_cfg 0x03d0 /* width RMuint32, r20 Reserved */
/* DRAM MBUS Unit - offsets relative to REG_BASE_dram_controller */
#define DRAM_mbus_w0_cfg 0x0200 /* width RMuint32, HostInterface W0 */
#define DRAM_mbus_w1_cfg 0x0204 /* width RMuint32, HostInterface W1 */
#define DRAM_mbus_w2_cfg 0x0208 /* width RMuint32, HostInterface W2 */
#define DRAM_mbus_w3_cfg 0x020c /* width RMuint32, VideoDecoder0 W0(Misc) */
#define DRAM_mbus_w4_cfg 0x0210 /* width RMuint32, VideoDecoder1 W0(Misc) */
#define DRAM_mbus_w5_cfg 0x0214 /* width RMuint32, TransportDemux0 W0 */
#define DRAM_mbus_w6_cfg 0x0218 /* width RMuint32, TransportDemux0 W1 */
#define DRAM_mbus_w7_cfg 0x021c /* width RMuint32, Audio0 W0 */
#define DRAM_mbus_w8_cfg 0x0220 /* width RMuint32, Unused - it was Audio1 W0 */
#define DRAM_mbus_w9_cfg 0x0224 /* width RMuint32, VideoDecoder0 W1(Dblk) */
#define DRAM_mbus_w10_cfg 0x0228 /* width RMuint32, VideoDecoder1 W1(Dblk) */
#define DRAM_mbus_w11_cfg 0x022c /* width RMuint32, VideoDecoder0 W2(Store) */
#define DRAM_mbus_w12_cfg 0x0230 /* width RMuint32, VideoDecoder1 W2(Store) */
#define DRAM_mbus_w13_cfg 0x0234 /* width RMuint32, XPUBlock W0 */
#define DRAM_mbus_w14_cfg 0x0238 /* width RMuint32, VideoDecoder0 W3() */
#define DRAM_mbus_w15_cfg 0x023c /* width RMuint32, VideoDecoder1 W3() */
#define DRAM_mbus_w16_cfg 0x0240 /* width RMuint32, VideoIn W0 */
#define DRAM_mbus_w17_cfg 0x0244 /* width RMuint32, VideoIn W1 */
#define DRAM_mbus_w18_cfg 0x0248 /* width RMuint32, GACC NX W0 */
#define DRAM_mbus_w19_cfg 0x024c /* width RMuint32, HostInterface W5(PCIe W0) - it was Audio2 W0 */
#define DRAM_mbus_w20_cfg 0x0250 /* width RMuint32, HostInterface W3(Eth0 W0) */
#define DRAM_mbus_w21_cfg 0x0254 /* width RMuint32, HostInterface W4(Eth1 W0) */
#define DRAM_mbus_r0_cfg 0x0280 /* width RMuint32, HostInterface R0 */
#define DRAM_mbus_r1_cfg 0x0284 /* width RMuint32, HostInterface R1 */
#define DRAM_mbus_r2_cfg 0x0288 /* width RMuint32, HostInterface R2 */
#define DRAM_mbus_r3_cfg 0x028c /* width RMuint32, VideoDecoder0 R0(Misc) */
#define DRAM_mbus_r4_cfg 0x0290 /* width RMuint32, VideoDecoder0 R1(Huffman) */
#define DRAM_mbus_r5_cfg 0x0294 /* width RMuint32, VideoDecoder1 R0(Misc) */
#define DRAM_mbus_r6_cfg 0x0298 /* width RMuint32, VideoDecoder1 R1(Huffman) */
#define DRAM_mbus_r7_cfg 0x029c /* width RMuint32, TransportDemux0 R0 */
#define DRAM_mbus_r8_cfg 0x02a0 /* width RMuint32, TransportDemux0 R1 */
#define DRAM_mbus_r9_cfg 0x02a4 /* width RMuint32, Audio0 R0 */
#define DRAM_mbus_r10_cfg 0x02a8 /* width RMuint32, Unused - it was Audio1 R0 */
#define DRAM_mbus_r11_cfg 0x02ac /* width RMuint32, VideoDecoder0 R2(Dblk) */
#define DRAM_mbus_r12_cfg 0x02b0 /* width RMuint32, VideoDecoder1 R2(Dblk) */
#define DRAM_mbus_r13_cfg 0x02b4 /* width RMuint32, XPUBlock R0 */
#define DRAM_mbus_r14_cfg 0x02b8 /* width RMuint32, GACC X/Y R0 */
#define DRAM_mbus_r15_cfg 0x02bc /* width RMuint32, GACC Z/Y R1 */
#define DRAM_mbus_r16_cfg 0x02c0 /* width RMuint32, GACC Z R2 */
#define DRAM_mbus_r17_cfg 0x02c4 /* width RMuint32, VideoDecoder1 R3 - it was Audio2 R0 */
#define DRAM_mbus_r18_cfg 0x02c8 /* width RMuint32, HostInterface R3(Eth0 R0) */
#define DRAM_mbus_r19_cfg 0x02cc /* width RMuint32, HostInterface R4(Eth1 R0) */
#define DRAM_mbus_r20_cfg 0x02d0 /* width RMuint32, dma2lbus */
#define DRAM_mbus_r21_cfg 0x02d4 /* width RMuint32, HostInterface R5(PCIe R0) */
#define DRAM_mbus_r22_cfg 0x02d8 /* width RMuint32, HostInterface R6(PCIe R1) */
#define DRAM_mpeg_engine_cfg 0x016c /* width RMuint32 */
#define SYS_watchdog_counter 0xfd00 /* width RMuint32 */
#define SYS_watchdog_configuration 0xfd04 /* width RMuint32 */
#define MARB_mid01_cfg 0x0200 /* width RMuint32, host_w0 */
#define MARB_mid21_cfg 0x0204 /* width RMuint32, host_r0 */
#define MARB_mid02_cfg 0x0208 /* width RMuint32, host_w1 */
#define MARB_mid22_cfg 0x020c /* width RMuint32, host_r1 */
#define MARB_mid03_cfg 0x0210 /* width RMuint32, host_w2 */
#define MARB_mid23_cfg 0x0214 /* width RMuint32, host_r2 */
#define MARB_mid0D_cfg 0x0218 /* width RMuint32, host_w3(ETH0) */
#define MARB_mid2D_cfg 0x021c /* width RMuint32, host_r3(ETH0) */
#define MARB_mid0F_cfg 0x0220 /* width RMuint32, host_w4(ETH1) */
#define MARB_mid2F_cfg 0x0224 /* width RMuint32, host_r4(ETH1) */
#define MARB_mid04_cfg 0x0228 /* width RMuint32, vdec0_w0 */
#define MARB_mid24_cfg 0x022c /* width RMuint32, vdec0_r0 */
#define MARB_mid25_cfg 0x0230 /* width RMuint32, vdec0_r1 */
#define MARB_mid08_cfg 0x0234 /* width RMuint32, vdec1_w0 */
#define MARB_mid28_cfg 0x0238 /* width RMuint32, vdec1_r0 */
#define MARB_mid29_cfg 0x023c /* width RMuint32, vdec1_r1 */
#define MARB_mid0C_cfg 0x0240 /* width RMuint32, tdmx0_w0 */
#define MARB_mid2C_cfg 0x0244 /* width RMuint32, tdmx0_r0 */
#define MARB_mid0E_cfg 0x0248 /* width RMuint32, tdmx1_w0 */
#define MARB_mid2E_cfg 0x024c /* width RMuint32, tdmx1_r0 */
#define MARB_mid10_cfg 0x0250 /* width RMuint32, audio0_w0 */
#define MARB_mid30_cfg 0x0254 /* width RMuint32, audio0_r0 */
#define MARB_mid11_cfg 0x0258 /* width RMuint32, unused - it was audio1_w0 */
#define MARB_mid31_cfg 0x025c /* width RMuint32, unused - it was audio1_r0 */
#define MARB_mid12_cfg 0x0260 /* width RMuint32, host_w5(pcie_w0) - it was audio2_w0 */
#define MARB_mid32_cfg 0x0264 /* width RMuint32, vdec1_r3 - it was audio2_r0 */
#define MARB_mid05_cfg 0x0268 /* width RMuint32, vdec0_w1 */
#define MARB_mid26_cfg 0x026c /* width RMuint32, vdec0_r2 */
#define MARB_mid09_cfg 0x0270 /* width RMuint32, vdec1_w1 */
#define MARB_mid2A_cfg 0x0274 /* width RMuint32, vdec1_r2 */
#define MARB_mid06_cfg 0x0278 /* width RMuint32, vdec0_w2 */
#define MARB_mid0A_cfg 0x027c /* width RMuint32, vdec1_w2 */
#define MARB_mid1C_cfg 0x0280 /* width RMuint32, xpu_w0 */
#define MARB_mid3C_cfg 0x0284 /* width RMuint32, xpu_r0 */
#define MARB_mid07_cfg 0x0288 /* width RMuint32, vdec0_w3 */
#define MARB_mid0B_cfg 0x028c /* width RMuint32, vdec1_w3 */
#define MARB_mid18_cfg 0x0290 /* width RMuint32, vin_w0 */
#define MARB_mid19_cfg 0x0294 /* width RMuint32, vin_w1 */
#define MARB_mid1B_cfg 0x0298 /* width RMuint32, gacc_nx_w0 */
#define MARB_mid3D_cfg 0x029c /* width RMuint32, gacc_x_r0 */
#define MARB_mid3E_cfg 0x02a0 /* width RMuint32, gacc_y_r1 */
#define MARB_mid3F_cfg 0x02a4 /* width RMuint32, gacc_z_r2 */
#define MARB_mid3A_cfg 0x02a8 /* width RMuint32, dma2lbus */
#define MARB_mid2B_cfg 0x02ac /* width RMuint32, host_r6(pcie_r1) */
#define MARB_mid27_cfg 0x02b0 /* width RMuint32, host_r5(pcie_r0) */
#define GARB_mid1_cfg 0x0104 /* width RMuint32, simulation */
#define GARB_mid2_cfg 0x0108 /* width RMuint32, XPU */
#define GARB_mid3_cfg 0x010c /* width RMuint32, IPU */
#define GARB_mid4_cfg 0x0110 /* width RMuint32, CPU */
#define GARB_mid5_cfg 0x0114 /* width RMuint32, CPU */
#define GARB_mid6_cfg 0x0118 /* width RMuint32, VDEC0 */
#define GARB_mid7_cfg 0x011c /* width RMuint32, VDEC1 */
#define GARB_mid8_cfg 0x0120 /* width RMuint32, AUDIO0 */
#define GARB_mid9_cfg 0x0124 /* width RMuint32, AUDIO1 */
#define GARB_midA_cfg 0x0128 /* width RMuint32, TDMX0 */
#define GARB_midB_cfg 0x012c /* width RMuint32, TDMX1 */
#define GARB_midC_cfg 0x0130 /* width RMuint32, HOST-Eth0 */
#define GARB_midD_cfg 0x0134 /* width RMuint32, HOST-Eth1 */
#define GARB_midE_cfg 0x0138 /* width RMuint32, HOST-PCI-USB */
#define GARB_spy_addlo 0x0170 /* width RMuint32 */
#define GARB_spy_addhi 0x0174 /* width RMuint32 */
#define GARB_spy_cfg 0x0178 /* width RMuint32 */
#define GARB_spy_cnt 0x017c /* width RMuint32 */
#define VARB_mid01_cfg 0x0300 /* width RMuint32, w0 MainVideo Write */
#define VARB_mid02_cfg 0x0304 /* width RMuint32, w1 VXPNRDI IfmdWrite */
#define VARB_mid03_cfg 0x0308 /* width RMuint32, w2 HDSD/CI Write */
#define VARB_mid04_cfg 0x030c /* width RMuint32, w3 VXPNRDI Write Y */
#define VARB_mid05_cfg 0x0310 /* width RMuint32, w4 VXPNRDI Write C */
#define VARB_mid06_cfg 0x0314 /* width RMuint32, w5 Reserved */
#define VARB_mid07_cfg 0x036c /* width RMuint32, w6 DigitalInput Y Write */
#define VARB_mid08_cfg 0x0370 /* width RMuint32, w7 DigitalInput C Write */
#define VARB_mid21_cfg 0x0318 /* width RMuint32, r0 VXPNRDI IFMD */
#define VARB_mid22_cfg 0x031c /* width RMuint32, r1 MainVideo Y */
#define VARB_mid23_cfg 0x0320 /* width RMuint32, r2 MainVideo C */
#define VARB_mid24_cfg 0x0324 /* width RMuint32, r3 VXPNRDI Current Y */
#define VARB_mid25_cfg 0x0328 /* width RMuint32, r4 VXPNRDI Current C */
#define VARB_mid26_cfg 0x032c /* width RMuint32, r5 VXPNRDI Past Y */
#define VARB_mid27_cfg 0x0330 /* width RMuint32, r6 VXPNRDI Past C */
#define VARB_mid28_cfg 0x0334 /* width RMuint32, r7 Graphics0 */
#define VARB_mid29_cfg 0x0338 /* width RMuint32, r8 Secondary Y */
#define VARB_mid2A_cfg 0x033c /* width RMuint32, r9 Graphics2 Y */
#define VARB_mid2B_cfg 0x0340 /* width RMuint32, r10 Graphics2 C */
#define VARB_mid2C_cfg 0x0344 /* width RMuint32, r11 Graphics1 Y */
#define VARB_mid2D_cfg 0x0348 /* width RMuint32, r12 Memory_1 Y */
#define VARB_mid2E_cfg 0x034c /* width RMuint32, r13  */
#define VARB_mid2F_cfg 0x0350 /* width RMuint32, r14 HDSD/CI Read */
#define VARB_mid30_cfg 0x0354 /* width RMuint32, r15 VXPNRDI IfmdRead */
#define VARB_mid31_cfg 0x0358 /* width RMuint32, r16 Secondary C */
#define VARB_mid32_cfg 0x035c /* width RMuint32, r17 Reserved */
#define VARB_mid33_cfg 0x0360 /* width RMuint32, r18 Reserved */
#define VARB_mid34_cfg 0x0364 /* width RMuint32, r19 Reserved */
#define VARB_mid35_cfg 0x0368 /* width RMuint32, r20 Reserved */
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
#define HOST_TEMP_SENSOR 0xe0f0 /* width RMuint32 */
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
#define PB_padmode_pbusb 0x08f0 /* width RMuint32 */
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
/* MIF registers have been reordered - offsets relative to REG_BASE_host_interface */
#define MIF_W0_ADD 0xb000 /* width RMuint32 */
#define MIF_W0_CNT 0xb004 /* width RMuint32 */
#define MIF_W0_SKIP 0xb008 /* width RMuint32 */
#define MIF_W0_CMD 0xb00c /* width RMuint32 */
#define MIF_W1_ADD 0xb040 /* width RMuint32 */
#define MIF_W1_CNT 0xb044 /* width RMuint32 */
#define MIF_W1_SKIP 0xb048 /* width RMuint32 */
#define MIF_W1_CMD 0xb04c /* width RMuint32 */
#define MIF_W2_ADD 0xb080 /* width RMuint32 */
#define MIF_W2_CNT 0xb084 /* width RMuint32 */
#define MIF_W2_SKIP 0xb088 /* width RMuint32 */
#define MIF_W2_CMD 0xb08c /* width RMuint32 */
/* <register name="MIF_HOLE_ADD"  type="RMuint32" address="0xb0c0" />
<register name="MIF_HOLE_CNT"  type="RMuint32" address="0xb0c4" />
<register name="MIF_HOLE_SKIP" type="RMuint32" address="0xb0c8" />
<register name="MIF_HOLE_CMD"  type="RMuint32" address="0xb0cc" /> */
#define MIF_R0_ADD 0xb100 /* width RMuint32 */
#define MIF_R0_CNT 0xb104 /* width RMuint32 */
#define MIF_R0_SKIP 0xb108 /* width RMuint32 */
#define MIF_R0_CMD 0xb10c /* width RMuint32 */
#define MIF_R1_ADD 0xb140 /* width RMuint32 */
#define MIF_R1_CNT 0xb144 /* width RMuint32 */
#define MIF_R1_SKIP 0xb148 /* width RMuint32 */
#define MIF_R1_CMD 0xb14c /* width RMuint32 */
#define MIF_R2_ADD 0xb180 /* width RMuint32 */
#define MIF_R2_CNT 0xb184 /* width RMuint32 */
#define MIF_R2_SKIP 0xb188 /* width RMuint32 */
#define MIF_R2_CMD 0xb18c /* width RMuint32 */
/* <register name="MIF_R3_ADD"  type="RMuint32" address="0xb1c0" />
<register name="MIF_R3_CNT"  type="RMuint32" address="0xb1c4" />
<register name="MIF_R3_SKIP" type="RMuint32" address="0xb1c8" />
<register name="MIF_R3_CMD"  type="RMuint32" address="0xb1cc" /><register name="MIF_R4_ADD"  type="RMuint32" address="0xb200" />
<register name="MIF_R4_CNT"  type="RMuint32" address="0xb204" />
<register name="MIF_R4_SKIP" type="RMuint32" address="0xb208" />
<register name="MIF_R4_CMD"  type="RMuint32" address="0xb20c" /> */
#define MBUS_IDLE 0x0 /* width RMuint32 */
#define MBUS_VOID 0x1 /* width RMuint32 */
#define MBUS_LINEAR 0x2 /* width RMuint32 */
#define MBUS_LINEAR_VOID 0x3 /* width RMuint32 */
#define MBUS_DOUBLE 0x4 /* width RMuint32 */
#define MBUS_DOUBLE_VOID 0x5 /* width RMuint32 */
#define MBUS_RECTANGLE 0x6 /* width RMuint32 */
#define MBUS_RECTANGLE_VOID 0x7 /* width RMuint32 */
#define MBUS_INTERLACED_RECTANGLE 0x8 /* width RMuint32 */
#define MBUS_INTERLACED_RECTANGLE_VOID 0x9 /* width RMuint32 */
#define MBUS_DOUBLE_RECTANGLE 0xa /* width RMuint32 */
#define MBUS_DOUBLE_RECTANGLE_VOID 0xb /* width RMuint32 */
#define MBUS_VERTICAL 0xc /* width RMuint32 */
#define MBUS_VERTICAL_VOID 0xd /* width RMuint32 */
#define MBUS_DOUBLE_VERTICAL 0xe /* width RMuint32 */
#define MBUS_DOUBLE_VERTICAL_VOID 0xf /* width RMuint32 */
#define MBUS_TILED 0x2000 /* width RMuint32 */
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
#define SYS_UART0_base 0x0700 /* width RMuint32 */
#define SYS_chip_device_id 0xfe00 /* width RMuint32 */
#define SYS_chip_revision_id 0xfe04 /* width RMuint32 */
#define SYS_chip_features 0xfe0c /* width RMuint32 */
/* SystemBlock registers done */

/* XPUBlock registers */
#define REG_BASE_xpu_block 0x000e0000 /* width RMuint32 */
/* Montgomery accelerator */
#define XPU_montgomery_reg_base_idx0 0xd800 /* width RMuint32 */
#define XPU_montgomery_reg_base_idx1 0xd910 /* width RMuint32 */
#define XPU_montgomery_reg_base_idx2 0xda20 /* width RMuint32 */
#define XPU_montgomery_reg_base_idx3 0xdb30 /* width RMuint32 */
#define XPU_montgomery_reg_base_modulus 0xdd00 /* width RMuint32 */
#define XPU_montgomery_control 0xdf00 /* width RMuint32 */
#define XPU_montgomery_operand_sel 0xdf04 /* width RMuint32 */
#define XPU_montgomery_debug_status 0xdf08 /* width RMuint32 */
#define XPU_montgomery_int_clr_enable 0xdfd8 /* width RMuint32 */
#define XPU_montgomery_int_set_enable 0xdfdc /* width RMuint32 */
#define XPU_montgomery_int_status 0xdfe0 /* width RMuint32 */
#define XPU_montgomery_int_enable 0xdfe4 /* width RMuint32 */
#define XPU_montgomery_clr_status 0xdfe8 /* width RMuint32 */
#define XPU_montgomery_set_status 0xdfec /* width RMuint32 */
#define XPU_montgomery_soft_reset 0xdff0 /* width RMuint32 */
#define XPU_montgomery_mod_id 0xdffc /* width RMuint32 */
/* XPUBlock registers done */

/* MpegEngine registers */
#define REG_BASE_mpeg_engine_0 0x00080000 /* width RMuint32 */
#define MEM_BASE_mpeg_engine_0 0x00100000 /* width RMuint32 */
#define PMEM_BASE_mpeg_engine_0 0x00100000 /* width RMuint32 */
#define PMEM_SIZE_mpeg_engine_0 0x4000 /* width RMuint32 */
#define DMEM_BASE_mpeg_engine_0 0x00110000 /* width RMuint32 */
#define DMEM_SIZE_mpeg_engine_0 0x3000 /* width RMuint32 */
#define REG_BASE_mpeg_engine_1 0x00081000 /* width RMuint32 */
#define MEM_BASE_mpeg_engine_1 0x00120000 /* width RMuint32 */
#define PMEM_BASE_mpeg_engine_1 0x00120000 /* width RMuint32 */
#define PMEM_SIZE_mpeg_engine_1 0x8000 /* width RMuint32 */
#define DMEM_BASE_mpeg_engine_1 0x00130000 /* width RMuint32 */
#define DMEM_SIZE_mpeg_engine_1 0x3000 /* width RMuint32 */
#define mpeg_MBUSIF_w0_addlo 0x3E80 /* width RMuint32 */
#define mpeg_MBUSIF_w0_addhi 0x3E81 /* width RMuint32 */
#define mpeg_MBUSIF_w0_xcnt 0x3E82 /* width RMuint32 */
#define mpeg_MBUSIF_w0_ycnt 0x3E83 /* width RMuint32 */
#define mpeg_MBUSIF_w0_skiplo 0x3E84 /* width RMuint32 */
#define mpeg_MBUSIF_w0_skiphi 0x3E85 /* width RMuint32 */
#define mpeg_MBUSIF_w0_cmd 0x3E86 /* width RMuint32 */
#define mpeg_MBUSIF_w0_vbuf_width 0x3E87 /* width RMuint32 */
#define mpeg_MBUSIF_w1_addlo 0x3E90 /* width RMuint32 */
#define mpeg_MBUSIF_w1_addhi 0x3E91 /* width RMuint32 */
#define mpeg_MBUSIF_w1_xcnt 0x3E92 /* width RMuint32 */
#define mpeg_MBUSIF_w1_ycnt 0x3E93 /* width RMuint32 */
#define mpeg_MBUSIF_w1_skiplo 0x3E94 /* width RMuint32 */
#define mpeg_MBUSIF_w1_skiphi 0x3E95 /* width RMuint32 */
#define mpeg_MBUSIF_w1_cmd 0x3E96 /* width RMuint32 */
#define mpeg_MBUSIF_w1_vbuf_width 0x3E97 /* width RMuint32 */
#define mpeg_MBUSIF_w2_addlo 0x3EA0 /* width RMuint32 */
#define mpeg_MBUSIF_w2_addhi 0x3EA1 /* width RMuint32 */
#define mpeg_MBUSIF_w2_xcnt 0x3EA2 /* width RMuint32 */
#define mpeg_MBUSIF_w2_ycnt 0x3EA3 /* width RMuint32 */
#define mpeg_MBUSIF_w2_skiplo 0x3EA4 /* width RMuint32 */
#define mpeg_MBUSIF_w2_skiphi 0x3EA5 /* width RMuint32 */
#define mpeg_MBUSIF_w2_cmd 0x3EA6 /* width RMuint32 */
#define mpeg_MBUSIF_w2_vbuf_width 0x3EA7 /* width RMuint32 */
#define mpeg_MBUSIF_w3_addlo 0x3EB0 /* width RMuint32 */
#define mpeg_MBUSIF_w3_addhi 0x3EB1 /* width RMuint32 */
#define mpeg_MBUSIF_w3_xcnt 0x3EB2 /* width RMuint32 */
#define mpeg_MBUSIF_w3_ycnt 0x3EB3 /* width RMuint32 */
#define mpeg_MBUSIF_w3_skiplo 0x3EB4 /* width RMuint32 */
#define mpeg_MBUSIF_w3_skiphi 0x3EB5 /* width RMuint32 */
#define mpeg_MBUSIF_w3_cmd 0x3EB6 /* width RMuint32 */
#define mpeg_MBUSIF_w3_vbuf_width 0x3EB7 /* width RMuint32 */
#define mpeg_MBUSIF_r0_addlo 0x3EC0 /* width RMuint32 */
#define mpeg_MBUSIF_r0_addhi 0x3EC1 /* width RMuint32 */
#define mpeg_MBUSIF_r0_xcnt 0x3EC2 /* width RMuint32 */
#define mpeg_MBUSIF_r0_ycnt 0x3EC3 /* width RMuint32 */
#define mpeg_MBUSIF_r0_skiplo 0x3EC4 /* width RMuint32 */
#define mpeg_MBUSIF_r0_skiphi 0x3EC5 /* width RMuint32 */
#define mpeg_MBUSIF_r0_cmd 0x3EC6 /* width RMuint32 */
#define mpeg_MBUSIF_r0_vbuf_width 0x3EC7 /* width RMuint32 */
#define mpeg_MBUSIF_r1_addlo 0x3ED0 /* width RMuint32 */
#define mpeg_MBUSIF_r1_addhi 0x3ED1 /* width RMuint32 */
#define mpeg_MBUSIF_r1_xcnt 0x3ED2 /* width RMuint32 */
#define mpeg_MBUSIF_r1_ycnt 0x3ED3 /* width RMuint32 */
#define mpeg_MBUSIF_r1_skiplo 0x3ED4 /* width RMuint32 */
#define mpeg_MBUSIF_r1_skiphi 0x3ED5 /* width RMuint32 */
#define mpeg_MBUSIF_r1_cmd 0x3ED6 /* width RMuint32 */
#define mpeg_MBUSIF_r1_vbuf_width 0x3ED7 /* width RMuint32 */
#define mpeg_MBUSIF_r2_addlo 0x3EE0 /* width RMuint32 */
#define mpeg_MBUSIF_r2_addhi 0x3EE1 /* width RMuint32 */
#define mpeg_MBUSIF_r2_xcnt 0x3EE2 /* width RMuint32 */
#define mpeg_MBUSIF_r2_ycnt 0x3EE3 /* width RMuint32 */
#define mpeg_MBUSIF_r2_skiplo 0x3EE4 /* width RMuint32 */
#define mpeg_MBUSIF_r2_skiphi 0x3EE5 /* width RMuint32 */
#define mpeg_MBUSIF_r2_cmd 0x3EE6 /* width RMuint32 */
#define mpeg_MBUSIF_r2_vbuf_width 0x3EE7 /* width RMuint32 */
#define mpeg_GBUSIF_MAIN_WADD_LOW 0x39C0 /* width RMuint32 */
#define mpeg_GBUSIF_MAIN_WADD_HIGH 0x39C1 /* width RMuint32 */
#define mpeg_GBUSIF_MAIN_RADD_LOW 0x39C2 /* width RMuint32 */
#define mpeg_GBUSIF_MAIN_RADD_HIGH 0x39C3 /* width RMuint32 */
#define mpeg_GBUSIF_MAIN_BYTE 0x39C4 /* width RMuint32 */
#define mpeg_GBUSIF_MAIN_WORD 0x39C6 /* width RMuint32 */
#define mpeg_GBUSIF_MAIN_DWORD_LOW 0x39C8 /* width RMuint32 */
#define mpeg_GBUSIF_MAIN_DWORD_HIGH 0x39C9 /* width RMuint32 */
#define mpeg_GBUSIF_MAIN_STATUS 0x39CA /* width RMuint32 */
#define mpeg_GBUSIF_ISR_WADD_LOW 0x39D0 /* width RMuint32 */
#define mpeg_GBUSIF_ISR_WADD_HIGH 0x39D1 /* width RMuint32 */
#define mpeg_GBUSIF_ISR_RADD_LOW 0x39D2 /* width RMuint32 */
#define mpeg_GBUSIF_ISR_RADD_HIGH 0x39D3 /* width RMuint32 */
#define mpeg_GBUSIF_ISR_BYTE 0x39D4 /* width RMuint32 */
#define mpeg_GBUSIF_ISR_WORD 0x39D6 /* width RMuint32 */
#define mpeg_GBUSIF_ISR_DWORD_LOW 0x39D8 /* width RMuint32 */
#define mpeg_GBUSIF_ISR_DWORD_HIGH 0x39D9 /* width RMuint32 */
#define mpeg_GBUSIF_ISR_STATUS 0x39DA /* width RMuint32 */
#define mpeg_MISC_mutex0 0x3fc0 /* width RMuint32 */
#define mpeg_MISC_mutex1 0x3fc1 /* width RMuint32 */
#define mpeg_mutex0 0x3FE0 /* width RMuint32 */
#define mpeg_mutex1 0x3FE1 /* width RMuint32 */
#define mpeg_mutex2 0x3FE2 /* width RMuint32 */
#define mpeg_mutex3 0x3FE3 /* width RMuint32 */
#define mpeg_mutex4 0x3FE4 /* width RMuint32 */
#define mpeg_mutex5 0x3FE5 /* width RMuint32 */
#define mpeg_mutex6 0x3FE6 /* width RMuint32 */
#define mpeg_mutex7 0x3FE7 /* width RMuint32 */
#define mpeg_MISC_w1_cfg 0x3FE9 /* width RMuint32 */
#define mpeg_MISC_dsp_irq_extend 0x3FEA /* width RMuint32 */
#define mpeg_MISC_dsp_irq_extend_mask 0x3FEB /* width RMuint32 */
#define mpeg_MISC_ssbox_mode 0x3FEC /* width RMuint32 */
#define mpeg_MISC_reset2 0x3FED /* width RMuint32 */
#define mpeg_MISC_mvp_hd_read_ctrl 0x3FEE /* width RMuint32 */
#define mpeg_MISC_mvp_hd_write_ctrl 0x3FEF /* width RMuint32 */
#define mpeg_MISC_dr_mode 0x3FF0 /* width RMuint32 */
#define mpeg_MISC_dr_length 0x3FF1 /* width RMuint32 */
#define mpeg_MISC_dr_address 0x3FF2 /* width RMuint32 */
#define mpeg_MISC_sbox_mode 0x3FF3 /* width RMuint32 */
#define mpeg_MISC_dw_mode 0x3FF4 /* width RMuint32 */
#define mpeg_MISC_dw_length 0x3FF5 /* width RMuint32 */
#define mpeg_MISC_dw_address 0x3FF6 /* width RMuint32 */
#define mpeg_MISC_codec_type 0x3FF7 /* width RMuint32 */
#define mpeg_MISC_reset0 0x3FF8 /* width RMuint32 */
#define mpeg_MISC_reset1 0x3FF9 /* width RMuint32 */
#define mpeg_MISC_interrupt 0x3FFA /* width RMuint32 */
#define mpeg_MISC_timer_div 0x3FFB /* width RMuint32 */
#define mpeg_MISC_timer_count 0x3FFC /* width RMuint32 */
#define mpeg_MISC_sbox_read_ctrl 0x3FFD /* width RMuint32 */
#define mpeg_MISC_sbox_write_ctrl 0x3FFE /* width RMuint32 */
#define mpeg_MISC_version_revision 0x3FFF /* width RMuint32 */
#define mpeg_MISC_UNRESET_MASK 0x3500 /* width RMuint32 */
#define mpeg_MISC_RESET_MASK 0x3535 /* width RMuint32 */
#define MPEG_TEMP_SENSOR 0xfe80 /* width RMuint32 */
/* MpegEngine registers done */

#endif /* __RMCHIP_REGISTERS_SMP8758_H__ */

/* End of generated file smp8758/rmchip_registers_smp8758.h */
