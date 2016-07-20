/*****************************************
 Copyright © 2004-2005
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmem86xxid.h
  @brief  

  long description

  @author Emmanuel Michon
  @date   2004-09-22
*/

#ifndef __RMEM86XXID_H__
#define __RMEM86XXID_H__

/*
  must be ok for C and for gas. Be careful.
  Answer is 1 or -1, RMsignImmediate(0)=1.

  ?, < cannot be used
  0xffffffff because gas computes on 64bit

  ...CHECK ANY CHANGE...
 */
#define RMsignImmediate(x) ((1|((x)>>31))&0xffffffff)

#define RMHEXDIGIT(x,n) ('0'+ ( ((x)>>((n)*4))&0xf ) + ((RMsignImmediate( ( ((x)>>((n)*4))&0xf ) -10)+1)&0xffffffff)/2*('a'-'9'-1))

/* video tokens */
#define LOG2_IPATOKEN_VIDEO_MPEG12  15
#define LOG2_IPATOKEN_VIDEO_MPEG4   14
#define LOG2_IPATOKEN_VIDEO_H264    13
#define LOG2_IPATOKEN_VIDEO_VC1     12
#define LOG2_IPATOKEN_VIDEO_WMV9    11
#define LOG2_IPATOKEN_VIDEO_JPEG    10
#define LOG2_IPATOKEN_VIDEO_MSMPEG4 9
#define LOG2_IPATOKEN_VIDEO_AVS     8
#define LOG2_IPATOKEN_VIDEO_H261    7
#define LOG2_IPATOKEN_VIDEO_RV      0

/* audio tokens */
#define LOG2_IPATOKEN_AUDIO_MPEGL12   31
#define LOG2_IPATOKEN_AUDIO_MPEGL3    30
#define LOG2_IPATOKEN_AUDIO_MPEG4AAC  29
#define LOG2_IPATOKEN_AUDIO_MPEG4BSAC 28
#define LOG2_IPATOKEN_AUDIO_MPEG4HE   27
#define LOG2_IPATOKEN_AUDIO_DD        26
#define LOG2_IPATOKEN_AUDIO_DDP       25
#define LOG2_IPATOKEN_AUDIO_TRUEHD    24
#define LOG2_IPATOKEN_AUDIO_DTS       23
#define LOG2_IPATOKEN_AUDIO_DTSNEO6	  22
#define LOG2_IPATOKEN_AUDIO_DTSHD     21
#define LOG2_IPATOKEN_AUDIO_DTSES	  20
#define LOG2_IPATOKEN_AUDIO_DTSHDMA   19
#define LOG2_IPATOKEN_AUDIO_DTSHDLBR  18
#define LOG2_IPATOKEN_AUDIO_WMA9      17
#define LOG2_IPATOKEN_AUDIO_WMA9PRO   16
#define LOG2_IPATOKEN_AUDIO_ATRAC3    15
#define LOG2_IPATOKEN_AUDIO_DTSRE     14
#define LOG2_IPATOKEN_AUDIO_DDRE      13
#define LOG2_IPATOKEN_AUDIO_DDPL2X    12
#define LOG2_IPATOKEN_AUDIO_DRA    	  11
#define LOG2_IPATOKEN_AUDIO_DDPL2	  10
#define LOG2_IPATOKEN_AUDIO_WOWHD	  9
#define LOG2_IPATOKEN_AUDIO_TRUSUR	  8
#define LOG2_IPATOKEN_AUDIO_TRUVOL	  7
#define LOG2_IPATOKEN_AUDIO_DTSBR	  6

/* demux tokens */
#define LOG2_IPATOKEN_DEMUX_C2        31
#define LOG2_IPATOKEN_DEMUX_DVBCSA    30
#define LOG2_IPATOKEN_DEMUX_MULTI2    29
#define LOG2_IPATOKEN_DEMUX_CSS       28
#define LOG2_IPATOKEN_DEMUX_RC4       27
#define LOG2_IPATOKEN_DEMUX_AES       26
#define LOG2_IPATOKEN_DEMUX_DES       25

#define EM86XX_MODEID_WITHHOST   1000
#define EM86XX_MODEID_STANDALONE 2000

/*
  EM86XX_DEBUG_VIDEO should be one of... 
  (resp)
*/
#define EM86XX_DEBUG_CHIP      1000
#define EM86XX_DEBUG_SIMU      2000

/*
  macros below 
  are independent of chip.
*/

#define XTAL_MHZ 27 // 27 MHz Crystal at XTAL_IN pad
#define XTAL_KHZ (XTAL_MHZ * 1000)
#define XTAL_HZ (XTAL_KHZ * 1000)

#define DEMUX_DSP_TIMER_HZ 5000  /* Frequency of the DSP timer interrupt, in Hz */
#define HB_PERIOD_MS 1000
#define UART_LCR_8N1 0x03    /* None, 8 bit, 1 bit */

#endif /* __RMEM86XXID_H__ */
