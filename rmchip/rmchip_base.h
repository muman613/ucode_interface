/*****************************************
 Copyright (c) 2004-2010
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmchip_base.h
  @brief

  long description

  @author Sebastian Frias
  @date   2010-08-19
*/

#ifndef __RMCHIP_BASE_H__
#define __RMCHIP_BASE_H__


/*******************************************************************
************************************** processor architecture
*******************************************************************/

#define RMCHIP_CPU_ARCH RMCHIP_ARCH_MIPS_24Kf_TOKEN
#define RMCHIP_IPU_ARCH RMCHIP_ARCH_MIPS_4Ke_TOKEN
#define RMCHIP_XPU_ARCH RMCHIP_ARCH_MIPS_4Ke_TOKEN

#define RMCHIP_GPU_ARCH RMCHIP_GPU_ARCH_NONE_TOKEN

/******************************************************************/


/* new necessary defines */
#define MAX_OUTPORTS_COUNT 6


/*******************************************************************
************************************** decoding capabilities
*******************************************************************/


#define RMFEATURE_HAS_WMV9 1

#define RMFEATURE_HAS_H264 1


/* hack: maybe audio wmapro here? */

/*******************************************************************
************************************** sizes of the DSP PMEM and DMEM
*******************************************************************/




#define ZBOOTXENV_MAXSIZE 0x4000


/*******************************************************************
************************************* sizes of scaler's linebuffers
*******************************************************************/

#define SCALER_MAX_INPUT_HEIGHT    2048



#define MULTISCALER_MAX_VBUS_UNIT    0x3f

/* for tango2 ES8 and greater. Runtime switch */
#define ES8_SCALER_VBUS_DRAM_PRIORITY 8
#define ES8_GFX_ENGINE_VBUS_DRAM_PRIORITY 9
#define ES8_MBUS_DRAM_PRIORITY 6

/* for all other chips */
#define SCALER_VBUS_DRAM_PRIORITY 3
#define GFX_ENGINE_VBUS_DRAM_PRIORITY 1
#define MBUS_DRAM_PRIORITY 2

/* Tango2Shuttle, Tango2 and up */

#define SPUSCALER_LINEBUFFER_SIZE 12288
#define SPUSCALER_MAX_LINE_WIDTH   2048 /* in 32BPP mode */
#define SPUSCALER_MAX_VBUS_UNIT    0x3f

#define OSDSCALER_LINEBUFFER_SIZE 24576
#define OSDSCALER_MAX_LINE_WIDTH   2048 /* in 32BPP mode */
#define OSDSCALER_MAX_VBUS_UNIT    0x7f


#define MAINVIDEOSCALER_LINEBUFFER_SIZE 24576 /* total memory: Y + UV */
/* video scaler does not support 32BPP but fake it */
#define MAINVIDEOSCALER_MAX_LINE_WIDTH 1024

#define MAINVIDEOSCALER_MAX_VBUS_UNIT_LUMA  0x3f

#define MAINVIDEOSCALER_MAX_VBUS_UNIT_CHROMA  0x3f

#define MAINVIDEOSCALER_HAS_WIDE_BW_FILTER 1

/*******************************************************************
************************************** features of PLLs
*******************************************************************/

/* No specifc PLL features in this configuration */


/*******************************************************************
************************************** within audio block
*******************************************************************/

/* Tango2Shuttle, Tango2 and up */
#define RMFEATURE_HAS_SPDIF_INPUT 1  /* separate pin for SPDIF capture, not shared with I2S */




#define RMFEATURE_HAS_AUDIOOUTPADSCTRL 1 /* control for I2S out and SPDIF out pads in bits [25:22] of SO_CH_CTRL1 */


/*******************************************************************
************************************** within display block
*******************************************************************/


/* Specific display features */
#define RMFEATURE_HAS_VIDEO_IN 1
#define RMFEATURE_HAS_DIGITAL_OUT 1
#define RMFEATURE_HAS_MAIN_ANALOG_OUT 1
#define RMFEATURE_HAS_HARD_GFX_SCALER 1
#define RMFEATURE_HAS_MAIN_MIXER 1
#define RMFEATURE_HAS_BLACKSTRIP_BITS_COUNT 9


#define RMFEATURE_HAS_GRAPHIC_IN 1

/* Tango2 and up */

#define RMFEATURE_HAS_GRAPHIC_IN 1
#define RMFEATURE_HAS_VCR_SCALER 1
#define RMFEATURE_HAS_VCR_CHANNEL 1
#define RMFEATURE_HAS_VIDEO_PLANE 1
#define RMFEATURE_HAS_COMPONENT_OUT 1
#define RMFEATURE_HAS_BCS2 1
#undef RMFEATURE_HAS_BLACKSTRIP_BITS_COUNT
#define RMFEATURE_HAS_BLACKSTRIP_BITS_COUNT 11
#define RMFEATURE_HAS_HDMI 1
#define RMFEATURE_HAS_GRAPHACC_CSCONV 1 /* colorspace and sampling mode conversion */
#define RMFEATURE_HAS_GRAPHACC_FULLBLEND 1
#define RMFEATURE_HAS_GRAPHACC_GRADIENTS 1
#define RMFEATURE_HAS_COMPONENT_COMPOSITE_MODE 1 /* composite mode bits in component out config register (for 625i modes) */
#define RMFEATURE_HAS_HDSD_CONVERTER 1



/* Tango2 and up */
#define RMFEATURE_HAS_CAPTURE_COUNTER 1  /* chip provides line and pixel counters for input */
#define RMFEATURE_HAS_VBI_CAPTURE 1  /* chip has raw VBI capture capability */
#define RMFEATURE_HAS_GRAPHIC_IN 1
#define RMFEATURE_HAS_HWI2C 1  /* chip has hardware i2c interface (master and slave) */


/* Tango2Shuttle, Tango2 and up */

#define RMFEATURE_HAS_ANC_CAPTURE 1  /* chip can capture ANC-formatted (sliced) VBI data */
#define RMFEATURE_HAS_SPU_SCALER 1  /* chip has working SPU scaler */
#define RMFEATURE_HAS_CAPTURE_COUNTER2 1  /* chip provides active line count for 656 input */


/* Tango2Shuttle, Tango2 and up */

#define RMFEATURE_HAS_GENERIC_SPU_SCALER 1 /* chip has a 8bit graphic scaler for SPU */
#define RMFEATURE_HAS_DOUBLE_RATE 1


#ifdef RMFEATURE_HAS_HWI2C  /* backwards compatibility, used to be defined for Tango2 before ES8 only. Err on safe side */
#define RMFEATURE_HAS_FAULTY_I2C_BURST_WRITE 1 /* OBSOLETE: (Hardware I2C burst write is sending MSBit of previous data byte when starvation occurs) Use I2C:BurstPatch property instead! */
#endif

#define RMFEATURE_XOFFSET_DIG_COMPENSATE 3        /* sync-to-video delay in the digital output block */
#define RMFEATURE_XOFFSET_HDMI_COMPENSATE 2       /* sync-to-video delay for internal SiI9030 HDMI chip */
#define RMFEATURE_XOFFSET_VESA_COMPENSATE 7       /* sync-to-video delay for analog VESA modes */
#define RMFEATURE_XOFFSET_HDTV_COMPENSATE 13      /* video-to-sync delay for analog HDTV modes */
#define RMFEATURE_XOFFSET_SDTV525_COMPENSATE 8    /* video-to-sync delay for analog 525 line modes */
#define RMFEATURE_XOFFSET_SDTV625_COMPENSATE 20   /* video-to-sync delay for analog 625 line modes */


#define RMFEATURE_WITH_BWSAMPLING 1


/* hack tbd by Christian W. */
/* sizes of some buffers (IN BYTES) */
/* etc. */
/* use format RMFEATURE_HAS_XXX */





/* RMFEATURE_OUTPORT_COUNT */

#define RMFEATURE_OUTPORT_COUNT 3



/* RMFEATURE_HAS_OUTPORT_RESET_DELAY  */

#define RMFEATURE_HAS_OUTPORT_RESET_DELAY 1



#define RMFEATURE_HAS_MULTISCALER_LUMA_KEYING 1


#define RMCHIP_DISPLAY_BLOCK_VERSION 1

#define SOC_ARCH SOC_TANGO


#endif /* __RMCHIP_BASE_H__ */
