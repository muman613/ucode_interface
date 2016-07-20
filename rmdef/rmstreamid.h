/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmstreamid.h
  @brief  

  The enumerations absolutely needed to write anything related to MPEG software

  @author Emmanuel Michon
  @date   2003-02-13
*/

#ifndef __RMSTREAMID_H__
#define __RMSTREAMID_H__

RM_EXTERN_C_BLOCKSTART

typedef enum {
	RMVDEMUX_FIRST__=3974,
	RMVDEMUX_VIDEO,
	RMVDEMUX_AUDIO,
	RMVDEMUX_SUBPICTURE,
	RMVDEMUX_NAVIGATION,
	RMVDEMUX_LAST__,
} RMvdemuxDataType;

typedef enum {
	RM_SYSTEM_UNKNOWN=4753,
	RM_SYSTEM_MPEG1,                   // can be detected.
	RM_SYSTEM_MPEG2_TRANSPORT,         // can be detected.
	RM_SYSTEM_MPEG2_PROGRAM,           // can be detected.
	RM_SYSTEM_MPEG2_DVD,               // can be detected.
	RM_SYSTEM_MPEG2_DVD_AUDIO,
	RM_SYSTEM_MPEG4,
	RM_SYSTEM_AVI,
	RM_SYSTEM_ID3,
	RM_SYSTEM_RIFFCDXA,  // this is RIFF/CDXA type or VCD, we do not support it but we detect it
	RM_SYSTEM_DIVX_MP3,         /* deprecated, use RM_SYSTEM_AVI instead */
	RM_SYSTEM_DIVX_AC3,         /* deprecated, use RM_SYSTEM_AVI instead */
	RM_SYSTEM_DIVX_MPEG1,       /* deprecated, use RM_SYSTEM_AVI instead */
	RM_SYSTEM_DIVX_PCM,         /* deprecated, use RM_SYSTEM_AVI instead */
	RM_SYSTEM_DIVX_WMA,         /* deprecated, use RM_SYSTEM_AVI instead */
	RM_SYSTEM_DIVX_WMV9_MP3,    /* deprecated, use RM_SYSTEM_AVI instead */
	RM_SYSTEM_DIVX_WMV9_AC3,    /* deprecated, use RM_SYSTEM_AVI instead */
	RM_SYSTEM_DIVX_WMV9_MPEG1,  /* deprecated, use RM_SYSTEM_AVI instead */
	RM_SYSTEM_DIVX_WMV9_PCM,    /* deprecated, use RM_SYSTEM_AVI instead */
	RM_SYSTEM_DIVX3_MP3,        /* deprecated, use RM_SYSTEM_AVI instead */
	RM_SYSTEM_DIVX3_AC3,        /* deprecated, use RM_SYSTEM_AVI instead */
	RM_SYSTEM_DIVX3_MPEG1,      /* deprecated, use RM_SYSTEM_AVI instead */
	RM_SYSTEM_DIVX3_PCM,        /* deprecated, use RM_SYSTEM_AVI instead */
	RM_SYSTEM_ASF,
	RM_SYSTEM_MPEG2_TRANSPORT_192,
	RM_SYSTEM_ELEMENTARY_AUDIO,
	RM_SYSTEM_ELEMENTARY_VIDEO,
} RMsystemType;



typedef enum {
	RM_VIDEO_UNKNOWN,
	RM_VIDEO_MPEG12,
	RM_VIDEO_MPEG4,
	RM_VIDEO_H263,
	RM_VIDEO_H264,
	RM_VIDEO_WMV,
	RM_VIDEO_VC1,
	RM_VIDEO_DIVX3,
	RM_VIDEO_DIVX4,
	RM_VIDEO_XVID, /*mpeg4 with padding bug*/
	RM_VIDEO_MJPEG,
	RM_VIDEO_JPEG,
	RM_VIDEO_BMP,
	RM_VIDEO_TIFF,
	RM_VIDEO_GIF,
	RM_VIDEO_PNG,
} RMvideoType;



/* 
   The following is a compromise to avoid the
   pain of having different types for audio probing.

   Keep code in sync with rm84cmn.h
*/
#ifdef _EAUDIOFORMAT_TYPE_DEFINED_
// accept existing.
#else
#define _EAUDIOFORMAT_TYPE_DEFINED_ 1
#define AUDIO_FORMAT_MPEG1       1
#define AUDIO_FORMAT_MPEG2       2
#define AUDIO_FORMAT_AC3         3
#define AUDIO_FORMAT_PCM         4
#define AUDIO_FORMAT_DTS         5
#define AUDIO_FORMAT_DVD_AUDIO   6
#define AUDIO_FORMAT_REVERSE_PCM 7
#define AUDIO_FORMAT_AAC         8
typedef enum {
	eAudioFormat_MPEG1       = AUDIO_FORMAT_MPEG1, // mpeg1 layer 1.
	eAudioFormat_MPEG2       = AUDIO_FORMAT_MPEG2, // mpeg1 layer 2.
	eAudioFormat_AC3         = AUDIO_FORMAT_AC3,
	eAudioFormat_PCM         = AUDIO_FORMAT_PCM,
	eAudioFormat_DTS         = AUDIO_FORMAT_DTS,
	eAudioFormat_DVD_AUDIO   = AUDIO_FORMAT_DVD_AUDIO,
	eAudioFormat_REVERSE_PCM = AUDIO_FORMAT_REVERSE_PCM,
	eAudioFormat_AAC         = AUDIO_FORMAT_AAC,
	eAudioFormat_MPEG1_LAYER3,  // mpeg1 layer 3.
	eAudioFormat_MPEG2_LAYER1,  // mpeg2 layer 1.
	eAudioFormat_MPEG2_LAYER2,  // mpeg2 layer 2.
	eAudioFormat_MPEG2_LAYER3,  // mpeg2 layer 3.
	eAudioFormat_WMA,
	eAudioFormat_WMAPRO,
	eAudioFormat_UNKNOWN,
	eAudioFormat_AAC_DSI,
	eAudioFormat_AAC_ADIF,
	eAudioFormat_AAC_ADTS,
	eAudioFormat_WMATS,
	eAudioFormat_AAC_LATM,
} eAudioFormat_type;


typedef enum    // used for PropId = eaDvdAudioConf_type in PropSet=AUDIO_SET
{
    // first digit after eaDvdAudio specifies chanels/GR1, second digit specifies chanels/GR2
    eaDvdAudio10_C = 0,        // 0x00 Hw?? LR
    
    eaDvdAudio20_LR,           // 0x01
    eaDvdAudio21_LfRfS,        // 0x02
    eaDvdAudio22_LfRfLsRs,     // 0x03
    eaDvdAudio21_LfRfLfe,      // 0x04
    eaDvdAudio22_LfRfLfeS,     // 0x05
    eaDvdAudio23_LfRfLfeLsRs,  // 0x06 Hw?? LfRfLfe
    eaDvdAudio21_LfRfC,        // 0x07 Hw?? LfRfC
    eaDvdAudio22_LfRfCS,       // 0x08
    eaDvdAudio23_LfRfCLsRs,    // 0x09
    eaDvdAudio22_LfRfCLfe,     // 0x0a
    eaDvdAudio23_LfRfCLfeS,    // 0x0b Hw?? LfLfCLfe
    eaDvdAudio24_LfRfCLfeLsRs, // 0x0c Hw?? LfRfCLfe

    eaDvdAudio31_LfRfCS,       // 0x0d
    eaDvdAudio32_LfRfCLsRs,    // 0x0e
    eaDvdAudio31_LfRfCLfe,     // 0x0f
    eaDvdAudio32_LfRfCLfeS,    // 0x10
    eaDvdAudio33_LfRfCLfeLsRs, // 0x11

    eaDvdAudio41_LfRfLsRsLfe,  // 0x12
    eaDvdAudio41_LfRfLsRsC,    // 0x13
    eaDvdAudio42_LfRfLsRsCLfe, // 0x14

}eaDvdAudioChannelAssign_type;

#endif // _EAUDIOFORMAT_TYPE_DEFINED_

// additions of new enumerated types in this file must be discussed
// with the whole development team.

RM_EXTERN_C_BLOCKEND

#endif // __RMSTREAMID_H__
