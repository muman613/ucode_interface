/* You can edit. 
   But this file will be translated to .mk,
   and the .mk in turn can be translated back to an equivalent file, without comments, reordered, to untangle the #ifdef structure.
 */

#ifndef __SMP8674R3_H__
#define __SMP8674R3_H__ 1

#include "rmchip_common.h"

#define AD_BORDER 0x800e71f4
#define AD_CRC32_TAB 0x800e44e0
#define AD_HEAP_MALLOC 0x800e6ff0
#define AUDIO_DM_SIZE 0xc000
#define AUDIO_PM_SIZE 0x3000
#define DEMUX_DM_SIZE 0x8000
#define DEMUX_PM_SIZE 0x6000
#define FG_SIZE 0x5000
#define IOSVA_TEXT 0xddd00000
#define LOG2_IOS 0x14
#define MPEG_DM_SIZE 0x3000
#define MPEG_PM_SIZE 0x4000
#define RMCHIP_AUDIO_ENGINE_COUNT 2
#define RMCHIP_CPU_ARCH 0x7d1
#define RMCHIP_DEMUX_ENGINE_COUNT 1
#define RMCHIP_DISPLAY_BLOCK_VERSION 1
#define RMCHIP_DRAM_CONTROLLER_COUNT 1
#define RMCHIP_GPU_ARCH 0x3e8
#define RMCHIP_L2_CACHE_PRESENT 1
#define RMCHIP_OTP_PRESENT 1
#define RMCHIP_REVISION 3
#define RMCHIP_VIDEO_ENGINE_COUNT 1
#define RMCHIP_VIDEO_ENGINE_VERSION 0xb
#define RMFEATURE_CPUSPI_S_BIT_IS_BUSY 1
#define RMFEATURE_DemuxEngine_HAS_KEY_LADDER_CIPHER_BLOCK 1
#define RMFEATURE_DemuxEngine_HAS_KEY_LADDER_FW_RECIPHER 1
#define RMFEATURE_DemuxEngine_HAS_PrivateEmmEcmFilter 1
#define RMFEATURE_DemuxEngine_HAS_TS_OUT 1
#define RMFEATURE_DemuxEngine_TSOUT_SPI_COUNT 0
#define RMFEATURE_DemuxEngine_TSOUT_SSI_COUNT 0
#define RMFEATURE_DemuxEngine_TS_IN_SPI_COUNT 1
#define RMFEATURE_DemuxEngine_TS_IN_SSI_COUNT 2
#define RMFEATURE_EZBOOT_SUPPORT_CPUSPI 1
#define RMFEATURE_EZBOOT_SUPPORT_MLCNAND 1
#define RMFEATURE_EZBOOT_SUPPORT_PFLASH 1
#define RMFEATURE_HAS_4FIELD_MOTION_ADAPTIVE_DEINTERLACING 1
#define RMFEATURE_HAS_AUDIO_ENGINE_1 1
#define RMFEATURE_HAS_CLEAN_DIVIDER_BUG 1
#define RMFEATURE_HAS_CONSTANT_BLEND_DEINTERLACING 1
#define RMFEATURE_HAS_DDR3 1
#define RMFEATURE_HAS_DEDICATED_DEINTERLACING 1
#define RMFEATURE_HAS_HWSHA256 1
#define RMFEATURE_HAS_TANGO4_GBUS_MAP 1
#define RMFEATURE_NEEDS_OCP_RESYNC 1
#define RMFEATURE_UART0_IS_IN_SYSTEM_BLOCK 1
#define RMFEATURE_USE_POST_65NM_PLL 1
#define RMFEATURE_VideoDecoder_HAS_DRAM_MUX_FOR_MOTION_COMP 1
#define RMFEATURE_VideoDecoder_HAS_SCALE_PIC 1
#define RMFEATURE_keyloadingtools2_loader_loader_XTASK_VERSION 1
#define RMFEATURE_uCode_audio__kernel_audio_transfer_asm_MBUS_VERSION 2
#define XBOOT3_VERSION 0xc8
#define RMFEATURE_ROM_BDL_DISABLE_UART 1
#define RMFEATURE_XBOOT3_NAGRA_CUSTOM 1
#define RMCHIP_ROM_SPI_SUPPORT 1
#define RMCHIP_ROM_EMMC_SUPPORT 1
#define RMCHIP_ROM_EMMC_DRIVER_VERSION 2
#define RMCHIP_ROM_HASBUG38862 1
#define RMCHIP_ROM_HASBUG39413 1
#define RMCHIP_ROM_HASBUG40123 1
#define RMCHIP_ROM_HASBUG40541 1

#endif /* __SMP8674R3_H__ */
