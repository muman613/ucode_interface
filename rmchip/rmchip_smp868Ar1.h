/* You can edit. 
   But this file will be translated to .mk,
   and the .mk in turn can be translated back to an equivalent file, without comments, reordered, to untangle the #ifdef structure.
 */

#ifndef __SMP868AR1_H__
#define __SMP868AR1_H__ 1

#include "rmchip_common.h"

#define AUDIO_DM_SIZE 0xc000
#define AUDIO_PM_SIZE 0x3000
#define DEMUX_DM_SIZE 0x4000
#define DEMUX_PM_SIZE 0x6000
#define FG_SIZE 0x5000
#define IOSVA_TEXT 0xddd00000
#define LOG2_IOS 0x14
#define MPEG_DM_SIZE 0x1000
#define MPEG_PM_SIZE 0x3000
#define RMCHIP_AUDIO_ENGINE_COUNT 1
#define RMCHIP_CPU_ARCH 0x7d1
#define RMCHIP_DEMUX_ENGINE_COUNT 1
#define RMCHIP_DISPLAY_BLOCK_VERSION 1
#define RMCHIP_DRAM_CONTROLLER_COUNT 1
#define RMCHIP_GPU_ARCH 0x3e8
#define RMCHIP_REVISION 1
#define RMCHIP_VIDEO_ENGINE_COUNT 1
#define RMCHIP_VIDEO_ENGINE_REVISION 2
#define RMCHIP_VIDEO_ENGINE_VERSION 6
#define RMFEATURE_DemuxEngine_TSOUT_SPI_COUNT 0
#define RMFEATURE_DemuxEngine_TSOUT_SSI_COUNT 0
#define RMFEATURE_DemuxEngine_TS_IN_SPI_COUNT 1
#define RMFEATURE_DemuxEngine_TS_IN_SSI_COUNT 2
#define RMFEATURE_EZBOOT_SUPPORT_CPUSPI 1
#define RMFEATURE_EZBOOT_SUPPORT_HOSTSPI 1
#define RMFEATURE_HAS_4FIELD_MOTION_ADAPTIVE_DEINTERLACING 1
#define RMFEATURE_HAS_CLEAN_DIVIDER_BUG 1
#define RMFEATURE_HAS_CONSTANT_BLEND_DEINTERLACING 1
#define RMFEATURE_HAS_DDR3 1
#define RMFEATURE_HAS_DEDICATED_DEINTERLACING 1
#define RMFEATURE_HAS_DEMUX_ENGINE_1 1
#define RMFEATURE_USE_POST_65NM_PLL 1
#define RMFEATURE_VideoDecoder_HAS_DRAM_MUX_FOR_MOTION_COMP 1
#define RMFEATURE_uCode_audio__kernel_audio_transfer_asm_MBUS_VERSION 1

#endif /* __SMP868AR1_H__ */
