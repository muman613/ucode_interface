/*****************************************
 Copyright © 2005, 2006, 2007
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   hwmap2.h
  @brief  

  -long description-

  @author Emmanuel Michon
  @date   2012-03-06
*/

#ifndef __HWMAP2_H__
#define __HWMAP2_H__

#include "top.h"
#include "values.h"
#include "regs.h"

#ifndef __ASSEMBLY__

#ifndef BFLOG
#define BFLOG(x...) do {} while (0)
#define BFPROTO
#define BFCLASS extern inline F32
#endif /* BFLOG */

#define cipher_rc4_det xpu_cipher_rc4
#define cipher_aes_det xpu_cipher_aes
#define cipher_des_det xpu_cipher_des
#define cipher_sha_det xpu_cipher_sha
#define misc_det xpu_misc

#define cpu_uart1_det uart_pc16550
#define cpu_uart2_det uart_pc16550
#define rst_ctrl_det cpu_block_arm

#define dc_dram_unit_det hc_dc_dram_unit
#define dc_cache_unit_det hc_dc_cache_unit
#define dc_cache_unit_common_det hc_dc_cache_unit_common
#define hub_dram_phy01_det phy2
#define hub_dram_phy23_det phy2

#define remap_det lib_mips_remap

#define switchbox_det host_switchbox
#define hc_reset_controller_det hc_reset_controller
#define hc_ghub_int_ctrler_det ghub_int_ctrler
#define hc_ipu_det hc_ipu
#define hc_ocp_remap_1_det lib_mips_remap
#define hc_ghub_allocator_det allocator

#define clock_ctrl_det hcc

#define DIVCNT 9
#define clock_ctrl_int_div_det { struct hcd dd[DIVCNT]; }

#define ha_ipu_det ha_ipu
#define ha_reset_controller_det ha_reset_controller

struct mtst { // mbus thread sub-table
	RMuint8 table[/*isRead*/2][/*id*/64];
};

#include "../horizontal/hookinfo.h"
struct _9347eeee {
	union HOOKINFOReg block[2048];
	struct mtst mtable[/*ring A B or C */3][/*mhid*/64];
};

struct _aaf23780 {
	RMuint32 mid;
	RMuint32 pad[(0x100-4)/4];
	struct {
		RMuint32 mem_base,mem_size,ext_base,ext_size;
	} info[0x40-0x10];
};

#include <stdint.h>

#include "hc_mu_dlc.cfg.h" // that one is verrry speciaaal
struct _06452935 {
	RMuint32 drambw[/*isRead*/2][64];
	RMuint32 fifo[/*isRead*/2][64];
	RMuint32 ringbw[64];
	struct hc_mu_dlc dlc;
};

#define hc_hook_info_det _9347eeee
#define hc_map_mirror_det _aaf23780
#define dc_mbus_unit_det _06452935

#include "../horizontal/otpregmisc.h"
#define otp_det ha_otp_controller

// created at first place for xpu. Other blocks channel ordering can differ
#define mbus_det { struct mbus_regs_32b w0,r0; }
#define mbusm_det { struct mbus_regs_32b w0,r0,w1,r1; }

#include "ghub_int_ctrler.h"
#include "autogen.h"

#define Phc_lbusadddec_lbus_address_decoder_REG_BASE ((struct hc_lbusadddec_lbus_address_decoder_reg *)GBUS_REG_BASE_HUB)

struct hc_lbusadddec_lbus_address_decoder_ext {
	uint8_t sau[4/*banks*/][8/*ways*/][16*1024];
};

#define Phc_lbusadddec_lbus_address_decoder_EXT_BASE ((struct hc_lbusadddec_lbus_address_decoder_ext *)GBUS_EXT_BASE_HUB)

#define Pxpu_lbus_address_decoder_MEM_BASE ((struct xpu_lbus_address_decoder_mem *)GBUS_MEM_BASE_XPU_BLOCK)

#define Pxpu_gbus_bridge_REG_BASE ((struct lib_gbus_bridge *)GBUS_REG_BASE_XPU_BLOCK)

/*
   host  = INTERFACE_2
   host1 = INTERFACE_1
*/
#define Phost_lbus_address_decoder_MEM_BASE ((struct host_lbus_address_decoder_mem *)GBUS_MEM_BASE_HOST_INTERFACE_2)

#define Phost1_gbus_bridge_REG_BASE ((struct lib_gbus_bridge *)GBUS_REG_BASE_HOST_INTERFACE_1)
#define Phost1_lbus_address_decoder_MEM_BASE ((struct host1_lbus_address_decoder_mem *)GBUS_MEM_BASE_HOST_INTERFACE_1)

#define Pcpu_block_arm_MEM_BASE ((struct cpu_block_arm *)GBUS_MEM_BASE_CPU_BLOCK)

#define Pha_lbus_address_decoder_MEM_BASE ((struct ha_lbus_address_decoder_mem *)GBUS_MEM_BASE_HUB)

#endif

/* hack: redundant with prior autogen. files. need to massage with _ASM_ defines. */
#define ha_lbus_address_decoder_mem_local_ram_OFF 0x00020000
#define ha_lbus_address_decoder_mem_local_rom_mem_OFF 0x00030000
#define hc_lbusadddec_lbus_address_decoder_reg_hc_semaphores_OFF 0x00040200
#define xpu_lbus_address_decoder_mem_remap_OFF 0x00010900
#define gbus_bridge_reg_gbus_bridge_mem_prot_OFF 0x00000080
#define cpu_block_arm_rst_ctrl_OFF 0x00120000
#define ha_lbus_address_decoder_mem_ha_ocp_remap_1_OFF 0x00002800
#define hc_lbusadddec_lbus_address_decoder_reg_hc_ocp_remap_0_OFF 0x00040800

#define DRAMCOPY_IROM_VA RM_PA_TO_KVA0(GBUS_MEM_BASE_HUB+ha_lbus_address_decoder_mem_local_rom_mem_OFF+0x10000000)
#define DRAMCOPY_XROM_VA RM_PA_TO_KVA0(GBUS_MEM_BASE_XPU_BLOCK+0x10000000)

// hack misplaced
#define REMAP_SEM (GBUS_REG_BASE_HUB+hc_lbusadddec_lbus_address_decoder_reg_hc_semaphores_OFF+4)

#endif /* __HWMAP2_H__ */
