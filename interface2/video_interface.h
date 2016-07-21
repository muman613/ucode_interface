#ifndef	__VIDEO_INTERFACE_H__
#define __VIDEO_INTERFACE_H__

//#include "irq_handler_v2/display/include/emhwlib_vsync_displaytypes.h"
#include "gbuslib/include/gbus_fifo.h"
#include "gbuslib/include/gbus_packet_fifo.h"
#include "gbuslib/include/gbus_packet_fifo_eraser.h"
#include "gbuslib/include/gbus_fifo_eraser.h"
#include "gbuslib/include/gbus_time.h"

#define PICTURE_COUNT          32 /* keep in sync with microcode MAX_SLOT_NUMBER */
#define MAX_SLOT_COUNT         32 /* keep in sync with microcode MAX_SLOT_NUMBER from ucode_video/video_t4/src/controller/cntrl.h */
#define MAX_TASK_COUNT         36

//-------------------------
//Command and State Codes
//-------------------------
#define NO_CMD 			0xFF
#define VIDEO_NO_CMD 			0xFF
#define VIDEO_UNINIT 			0
#define VIDEO_INIT  			1
#define VIDEO_STOP  			2
#define VIDEO_PLAYFWD  		    3
#define VIDEO_DECFWDTOEVENT  	4
#define VIDEO_PLAYFWDTOEVENT  	5
#define VIDEO_FASTFWD  		    6
#define VIDEO_PLAYBWD			7
#define VIDEO_FASTBWD			8


#define COMMAND_PARAMS_RMUINT32_SIZE  (20)   /* size in RMuint32 */

// encoding
#define VideoProfileMask            0x00f
#define VideoProfileMPEG2           0x000
#define VideoProfileMPEG4           0x002
#define VideoProfileDIVX3           0x003
#define VideoProfileH264            0x004
#define VideoProfileWMV             0x005
#define VideoProfileVC1             0x006
#define VideoProfileJPEG            0x007 /* JPEG, ISO 10918, OpenDML AVI, QuickTime */
#define VideoProfileAVS             0x008
#define VideoProfileH261            0x009
#define VideoProfileDVDSpu          0x00a
#define VideoProfileBDRLE           0x00b
#define VideoProfileOrientation     0x00c
#define VideoProfilePostProc        0x00d
#define VideoProfileH265            0x00e

#define VideoProfileJPEGType_std    0x000 /* single JPEG, ISO 10918 */
#define VideoProfileJPEGType_mjpeg  0x100 /* motion JPEG, ISO 10918 concatenated or OpenDML AVI File Format Extensions
                                             If the type is set _std instead of _mjpeg the speed of decoding is slower */
#define VideoProfileJPEGType_mjpa   0x200 /* motion JPEG-A, conform to QuickTime File Format Specification */
#define VideoProfileJPEGType_mjpb   0x400 /* motion JPEG-B, conform to QuickTime File Format Specification */

// padding
#define VideoProfileNoPadding       0x000
#define VideoProfilePadding         0x010

// jpeg monochrome
#define VideoProfileJpegMonoChromeWithChroma 0x000
#define VideoProfileJpegMonoChromeNoChroma   0x800

enum VideoCommand {
	VideoCommandNoCmd          = VIDEO_NO_CMD,
	VideoCommandUninit         = VIDEO_UNINIT,
	VideoCommandInit           = VIDEO_INIT,  // results in status "stop"
	VideoCommandStop           = VIDEO_STOP,
	VideoCommandPlayFwd        = VIDEO_PLAYFWD,
	VideoCommandDecFwdToEvent  = VIDEO_DECFWDTOEVENT,
	VideoCommandPlayFwdToEvent = VIDEO_PLAYFWDTOEVENT,
	VideoCommandFastFwd        = VIDEO_FASTFWD,
	VideoCommandPlayBwd        = VIDEO_PLAYBWD,
	VideoCommandFastBwd        = VIDEO_FASTBWD
};

enum VideoStatus {
	VideoStatusPending         = VIDEO_NO_CMD,
	VideoStatusUninit          = VIDEO_UNINIT,
	VideoStatusStop            = VIDEO_STOP,
	VideoStatusPlayFwd         = VIDEO_PLAYFWD,
	VideoStatusDecFwdToEvent   = VIDEO_DECFWDTOEVENT,
	VideoStatusPlayFwdToEvent  = VIDEO_PLAYFWDTOEVENT,
	VideoStatusFastFwd         = VIDEO_FASTFWD,
	VideoStatusPlayBwd         = VIDEO_PLAYBWD,
	VideoStatusFastBwd         = VIDEO_FASTBWD
};

struct task_entry {
	RMuint32 DataBasePtr;
	RMuint32 PrevNextEntry;
	RMuint32 TaskStatus;
};

struct scheduler_data {
	RMuint32 NumberOfTasks;
	struct task_entry task_list[MAX_TASK_COUNT];
};

struct overlay_handle {
	RMuint32 source_addr; /* gbus address in DRAM */
	RMuint32 source_size; /* size */
	RMuint32 start_addr;  /* DBUS address in PMEM or DMEM */
};

/* MEMORY SLOT  */
struct slot {
	RMuint32 upper_buffer_end_addr;
	RMuint32 lower_buffer_start_addr; // hack: swap positions for these two fields to solve
	RMuint16 upper_buffer_first_slot; // the RMuint16 misalignment issue
	RMuint16 lower_buffer_last_slot;
	RMuint32 start_addr;
};

/* CONTROLLER DATA */
struct task_context {
	/* PICTURE SIZE FROM THE DECODER */
	RMuint16 new_luma_width;
	RMuint16 new_luma_height;
	RMuint16 new_chroma_width;
	RMuint16 new_chroma_height;
	RMuint32 picture_type;
	/* INITIALIZED PARAMETERES */
	RMuint32 total_size;
	RMuint32 luma0_buffer_start_addr;
	RMuint16 slot_size;		/* luma, in KBytes */
	RMuint16 num_slots;
	RMuint16 tiled_buffer;
	/* CURRENT PICTURE BUFFER PARAMETERS */
	RMuint16 clear_on_screen_at_stop;
	RMuint16 curr_luma_width;
	RMuint16 curr_luma_height;
	RMuint16 curr_chroma_width;
	RMuint16 curr_chroma_height;
	RMuint32 curr_luma_buffer_size;
	RMuint32 curr_chroma_buffer_size;
	RMuint32 curr_combined_buffer_size;	/* in KBytes */
#if (RMFEATURE_VIDEO_INTERFACE_VERSION==2)
	RMuint16 memory_alloc_scheme;
#else
	RMuint16 reserved;
#endif
	RMuint16 max_num_buff;
	RMuint32 number_of_references;
	RMuint32 skip_flag;
#if (RMFEATURE_VIDEO_INTERFACE_VERSION==2)
	RMuint32 luma1_buffer_start_addr;
	RMuint16 luma_buff0_addr_alignment;
	RMuint16 luma_buff1_addr_alignment;
	RMuint32 buffer_alloc_DRAM_bank;
	struct slot memory_slot_list[2*MAX_SLOT_COUNT];
#else
	struct slot memory_slot_list[MAX_SLOT_COUNT];
#endif
};

struct data_seg {
	RMuint32 StartAddress;
	RMuint32 Size;
};

struct video_task_memory_descriptor {
#if (RMFEATURE_VIDEO_INTERFACE_VERSION==2)
	struct data_seg LumaFrameBuffer0;
	struct data_seg LumaFrameBuffer1;
	struct data_seg ContextBuffer;
#else
	struct data_seg DataAddress;
	RMuint32 ContextTotalSize;  // to be removed  !!!!!!
#endif
	RMuint32 DisplayPictureBufferCount;
	RMuint32 ExtraPictureBufferCount;
};

struct video_task_interface {

	/* DECODER STATE */
	RMuint32 Command;		/* set by EMhwlib Video,Spu */
	RMuint32 Status;		/* updated by the ucode Flow Controller */
	RMuint32 EventTablePointer;	/* updated by the EMhwlib */
	RMuint32 Error_Code;		/* updated by the ucode Flow Controller */
	RMuint32 StarvationCnt;		/* updated by the ucode Flow Controller */
	RMuint32 CommandParam;		/* "EndSequence_Init", set by EMhwlib PictureTransform set_OrientationMode or
					   for Video set_SequenceEndCodeResetFlags (EndSequence) */
	/*INIT COMMAND PARAMETERS */
	RMuint32 Profile;		/* set by EMhwlib Video,Spu set_Codec -> video_set_profile */
	RMuint32 MiscFlags;		/* set by EMhwlib Video,Spu at set_Open:
                                                bit 0 = 1 full task init
                                                bit 0 = 0 no task_context init */
	RMuint32 LowDelay;		/* set by EMhwlib Video set_LowDelay -> video_set_low_delay */
	RMuint32 SrcTypeDerivationMode;	/* set by EMhwlib Video set_InterlacedProgressiveAlgorithm -> video_set_interlaced_progressive_algorithm */
#if (RMFEATURE_VIDEO_INTERFACE_VERSION==2)
	/* expand struct video_task_memory_descriptor TaskMemParams; due to debug probe */
	struct data_seg LumaFrameBuffer0;
	struct data_seg LumaFrameBuffer1;
	struct data_seg ContextBuffer;
#else
	/* start struct video_task_memory_descriptor TaskMemParams; */
	RMuint32 DataAddress;
	RMuint32 DataSize;
	RMuint32 ContextTotalSize;
#endif
	RMuint32 DisplayPictureBufferCount;
	RMuint32 ExtraPictureBufferCount;
	/* end struct video_task_memory_descriptor TaskMemParams; */
	/* PLAYBACK CONTROL */
	RMuint32 PTSValueLo;		/* set by EMhwlib Video set_InitialHwPts -> video_set_initial_pts */
	RMuint32 PTSValueHi;		/* set by EMhwlib Video set_InitialHwPts -> video_set_initial_pts */
	RMuint32 FrameCnt;              /* updated by the ucode */
	RMuint32 DisplayFrameCnt;       /* updated by the ucode */
	RMuint32 FrameSkipCnt;          /* updated by the ucode */
	RMuint32 DisplayErrorThreshold; /* pictures with an error count above this value are not sent to display */
	RMuint32 AnchorErrPropagationThreshold;
	RMuint32 AnchorErrPropagationLength;
	/* PLAYBACK CONTROL SPECIFIC PARAMETERS */
	RMuint32 ForceFixedVOPRate;	/* set by EMhwlib Video set_VopInfo, set_VideoTimeScale -> video_set_vop */
	RMuint32 FixedVopTimeIncrVal;	/* set by EMhwlib Video set_VopInfo, set_VideoTimeScale -> video_set_vop */
	RMuint32 FixedTimeIncrResVal;	/* set by EMhwlib Video set_VopInfo, set_VideoTimeScale -> video_set_vop */
	/* PLAYBACK INIT SPECIFIC PARAMETERS */
	RMuint32 Image_Width;		/* set by EMhwlib Video set_WMV9VSProp -> video_set_WMV9VSProp,
	                                                        set_DIVX3VSProp -> video_set_DIVX3VSProp */
	RMuint32 Image_Height;		/* set by EMhwlib Video set_WMV9VSProp -> video_set_WMV9VSProp,
	                                                        set_DIVX3VSProp -> video_set_DIVX3VSProp */
	RMuint32 SequenceInfo;		/* set by EMhwlib Video set_WMV9VSProp -> video_set_WMV9VSProp,
							        set_H264Flags -> video_set_SequenceInfo,
								set_JPEGFlags -> video_set_SequenceInfo,
						          PictureTransform set_Open with inplace transform */
	RMuint32 ValidSeq;		/* set by EMhwlib Video set_StorePreviousVideoHeader -> video_store_previous_header */
	RMuint32 SeqParam;		/* set by EMhwlib Video set_CommonFlags -> video_set_SeqParam */
	RMuint32 STCPtr;		/* "VsyncPeriodPtr" set by the Hardware Library only for SpuDecoder, else NULL */
	RMuint32 VsyncPeriodPtr;	/* "STCPtr" set by the Hardware Library only for SpuDecoder, else NULL */
};



union VideoMicrocodePictureDisplayData {
	struct {
/*
	   0-1      fields.
*/
	RMuint32 fields:2;

/*
	   2 top field first
*/
	RMuint32 tff:1;

/*
	   3 repeat first field
*/
	RMuint32 rff:1;

/*
	    4-5 repeat frame
*/
	RMuint32 repeat_frame:2;

/*
	   6-7 pixel format
*/
	RMuint32 pixel_format:2;
/*
	   8-10 bits per pixel
*/
	RMuint32 bits_per_pixel:3;
/*
	   11-13 bit mapping
*/
	RMuint32 bit_mapping:3;
/*
	   14  progressive sequence
*/
	RMuint32 prog_seq:1;
/*
	   15 linear_buffer
*/
	RMuint32 linear_buffer:1;
/*
	   16-19 uv_luma_top_field_ver_phase_offset
*/
	RMuint32 uv_luma_top_field_ver_phase_offset:4;

/*
	   20-23 uv_luma_top_field_hor_phase_offset
*/
	RMuint32 uv_luma_top_field_hor_phase_offset:4;

/*
	   24-27 uv_luma_bot_field_ver_phase_offset
*/
	RMuint32 uv_luma_bot_field_ver_phase_offset:4;

/*
	   28-31 uv_luma_bot_field_hor_phase_offset
*/
	RMuint32 uv_luma_bot_field_hor_phase_offset:4;

	} bits;
	RMuint32 value;
};

enum VsyncPictureVersion {
	VsyncPictureVersionVideoMicrocode = 1,
	VsyncPictureVersionEMhwlib, // 2
	VsyncPictureVersionSubpictureVideoMicrocode, // 3
};

/* Window: absolute, front reference point */

struct EMhwlibWindowSize {
	RMuint32 width;
	RMuint32 height;
};

struct EMhwlibWindowPosition {
	RMuint32 x;
	RMuint32 y;
};

struct EMhwlibWindow {
	RMuint32 x;
	RMuint32 y;
	RMuint32 width;
	RMuint32 height;
};


union EMhwlibPictureStereoscopicData {
	struct {
		/*
		Stereoscopic 3D format, see also 'EMhwlibStereoscopic...' types for element definitions
		[7:0]   Format (0=2D,etc.), as in "enum EMhwlibStereoscopicFormat":
			 0 = 2D
			 1 = Anaglyphic
			 2 = Page Flip (Frame Sequential)
			 3 = Line Interleave
			 4 = Column Interleave
			 5 = Checkerboard Interleave
			 6 = Side by Side, Half
			 7 = Over / Under, Half (Top and Bottom)
			 8 = Line Alternative
			 9 = Column Alternative
			10 = Checkerboard Alternative
			11 = Side by Side, Full
			12 = Over / Under, Full
			13 = Frame Packing
			14 = Field Alternative (Field Sequential)
			15 = L + Depth
			16 = L + Depth + Graphics + Graphics Depth
			17..255 = reserved
		*/
		RMuint32 format:8;

		/*
		[9:8]   SubSampling Method, as in "enum EMhwlibStereoscopicSubSamplingMethod"
			0 = Horizontal
			1 = Quincunx
			2 = Vertical
			3 = reserved
		*/
		RMuint32 subSamplingMethod:2;

		/*
		[11:10] SubSampling Position, as in "enum EMhwlibStereoscopicSubSamplingPosition"
			0 = Odd  Left, Odd  Right
			1 = Odd  Left, Even Right
			2 = Even Left, Odd  Right
			3 = Even Left, Even Right
		*/
		RMuint32 subSamplingPosition:2;

		/*
		[12]    View Arrangement/Order
			If Format [7:0] is other than 2 (Page Flip):
			  0 = Left view is leftmost/topmost
			  1 = Right view is leftmost/topmost
			If Format [7:0] is 2 (Page flip):
			  1 = This is the first view
			  0 = This is a subsequent view
		*/
		RMuint32 viewOrder:1;

		/*
		[14:13] Flip (This only applies to SbS or TnB formats)
			0 = No view is spatially flipped
			1 = reserved
			2 = Left  view is spatially flipped, vertically for TnB, horizontally for SbS
			3 = Right view is spatially flipped, vertically for TnB, horizontally for SbS
		*/
		RMuint32 flip:2;

		/*
		[15]    Force flag (Implementation specific, no general use)
			0 = Not forced / overridden / valid
			1 = Forced /overridden / valid
		*/
		RMuint32 forceFlag:1;

		/*
		[23:16] View ID
			Index of the view stored in the current picture buffer.
			As a convention, when number of views is two, View ID = 0 is
			used for the left view and View ID = 1 is for the right view.
			When the number of views is greater than two, the application
			should provide separately to the display handler an association
			table mapping the View ID to a specific viewpoint.
			The View ID has to be less than the Number of Views, or zero.
		*/
		RMuint32 viewID:8;

		/*
		[31:24] Number of Views
			The total number of views per access unit. If number of views is two or more,
			the Format [7:0] shall be 2, "Page Flip". The view parity shall be determined
			by the View ID in [23:16]. The view pairing shall be determined by the View
			Arrangement in bit [12], or by equal PTS values among pairs.
		*/
		RMuint32 numViews:8;
	} bits;
	RMuint32 value;
};

struct EMhwlibPostProcessing {
	RMuint32 quantizer_addr;
	/* The address of the memory rectangle in which quantizer
	   scale parameters are stored, two bytes per macro block
	   (the post processing module needs 12-bit values but they
	   are sent through r12 vbus channel on 16-bit values).
	   When the frame is coded as two field pictures, the macro
	   block quantizer scale data lines are interleaved: the first
	   line corresponds to the first macro block row of the top
	   field, the second line corresponds to the first macro block
	   row of the bottom field, and so on.
	*/
	RMuint32 quantizer_total_width;
	/* The total width of the buffer in tile units when
	   quantizer_addr is not 0 (should equate to
	   luma_total_width ).
	*/
};

/*  WARNING: This structure must be kept in sync with the definition of
 *  "decoder_picture_buffer_t dma struct" in emhwlib_v2/video/ucode/global.h
 */

struct VideoMicrocodePicture {
	enum VsyncPictureVersion picture_version;       /* 0x00 */
	RMuint32 luma_address;                          /* 0x04 */
	RMuint32 luma_total_width;                      /* 0x08 */
	RMuint32 chroma_address;                        /* 0x0c */
	RMuint32 chroma_total_width;                    /* 0x10 */
	struct EMhwlibWindow luma_position_in_buffer;   /* 0x14 */
	struct EMhwlibWindow chroma_position_in_buffer; /* 0x24 */
	RMuint32 scaled_width;                          /* 0x34 */
	RMuint32 scaled_height;                         /* 0x38 */
	struct EMhwlibWindow panscan_1;                 /* 0x3c */
	struct EMhwlibWindow panscan_2;                 /* 0x4c */
	struct EMhwlibWindow panscan_3;                 /* 0x5c */
	struct EMhwlibWindow panscan_4;                 /* 0x6c */
	RMuint32 ar_x;                                  /* 0x7c */
	RMuint32 ar_y;                                  /* 0x80 */
	RMuint32 color_description;                     /* 0x84 */
	RMuint32 first_pts_lo;                          /* 0x88 */
	RMuint32 first_pts_hi;                          /* 0x8c */
	RMuint32 delta_pts;                             /* 0x90 */
	RMuint32 system_pts;                            /* 0x94 */
	RMuint32 timecode;                              /* 0x98 */
	RMuint32 time_increment_resolution;             /* 0x9c */
	union VideoMicrocodePictureDisplayData picture_display_data; /* 0xa0 */
	RMuint32 picture_data_extension;                /* 0xa4 */
	RMuint32 luma_scale;                            /* 0xa8 */
	RMuint32 chroma_scale;                          /* 0xac */
	RMuint32 picture_bytecount;                     /* 0xb0 */
	union EMhwlibPictureStereoscopicData picture_multiview_data; /* 0xb4 */
	RMuint32 user_data_entry_status;	        /* 0xb8 */
	RMuint32 user_data_entry_size;                  /* 0xbc */
	RMuint32 picture_decode_status;                 /* 0xc0 */
	RMuint32 picture_display_status;                /* 0xc4 */
	RMuint32 error_status;                          /* 0xc8 */
	struct EMhwlibPostProcessing post_processing;   /* 0xcc */
	RMuint32 palette_address;                       /* 0xd4 */
	RMuint32 palette_size;                          /* 0xd8 */
	RMuint32 palette_buffer_size;                   /* 0xdc */
	RMuint32 active_format;                         /* 0xe0 */
	RMuint32 horizontal_bar;                        /* 0xe4 */
	RMuint32 vertical_bar;                          /* 0xe8 */
	RMuint32 frame_count;                           /* 0xec */
	RMuint32 native_time_increment_resolution;      /* 0xf0 */
};

struct video_task_data_base {                     /* videotask_database dma struct*/

	/* TASK OVERLAYS */
	struct overlay_handle context;            /* struct ovl_handle */
	struct overlay_handle task_priority_calc; /* struct ovl_handle */
	struct overlay_handle init_decoder;       /* struct ovl_handle */
	struct overlay_handle decode_picture;     /* struct ovl_handle */
	struct overlay_handle header_layer;       /* struct ovl_handle - process header , no decoding */
	struct overlay_handle timer_hw_reset;     /* struct ovl_handle - flush anchors */
	/* TASK POINTERS */
	RMuint32 Task_InterfacePtr;               /* Task_InterfacePtr pointer to video_task_interface */
	struct gbus_fifo_eraser* InputFifoPtr;    /* input bitstream fifo */
	RMuint32 CurrDecodeBufferPtr;             /* video ucode internal */
	RMuint32 DecodeBufRequest;                /* video ucode internal */
	RMuint32 LBF_statusCntr;                  /* video ucode internal */
	/* TASK CONTAINERS */
	struct gbus_entry_fifo pts_fifo;          /* struct gbus_fifo */
	struct gbus_entry_fifo_eraser inband_cmd_fifo; /* struct gbus_fifo_eraser */
	RMuint32 Inband_Params_Address;
	struct gbus_entry_fifo display_fifo;      /* struct gbus_fifo */
	struct gbus_fifo_eraser user_data_fifo;   /* struct gbus_fifo_eraser - highlight_fifo for spu */
	struct gbus_entry_fifo error_code_fifo;   /* struct gbus_fifo */
	/* TASK PRIVATE AREA */
	struct gbus_fifo_eraser user_data_in_fifo; /* struct gbus_fifo_eraser */
	struct gbus_entry_fifo_eraser user_data_info_fifo; /* struct gbus_fifo_eraser */
	RMuint32 curr_user_data_entry_status;
	RMuint32 curr_user_data_entry_size;
	RMuint32 bytecount_checked;
	RMuint32 latest_bytecount;
	struct task_context task_private_data;	/* video ucode private_data TBD */
	/* DECODE BUFFERS CONTAINERS */
	RMuint32 PicBufNum;			/* video ucode internal */
	// assume VideoMicrocodePicture has a size greater or equal than VideoMicrocodeSubpicture. These structures should be union
#if (RMFEATURE_VIDEO_INTERFACE_VERSION==2)
	struct VideoMicrocodePicture PicBuf[2*MAX_SLOT_COUNT]; /* video ucode FirstPicBuf */
#else
	struct VideoMicrocodePicture PicBuf[MAX_SLOT_COUNT]; /* video ucode FirstPicBuf */
#endif
};

struct MicrocodeInbandParams {
	RMuint32 ref_cnt;
	RMuint32 params[COMMAND_PARAMS_RMUINT32_SIZE];
};

struct MicrocodeInbandCommand {
	RMuint32 flags_tag;      // INBAND_COMMAND_GET_TAG() is the macro to find the tag
	RMuint32 byte_counter;   // byte counter - see EMhwlibInbandOffset
	RMuint32 target;         // destination or target id. If 0 = broadcast.
	RMuint32 params_address; // pointer to the "union params_type" that contains the specific parameters
	RMuint32 params_ref_cnt; // 0 if free
};

enum EMhwlibVideoMicrocodeFrameType {
	EMhwlibVideoMicrocodeFrameType_I = 0,
	EMhwlibVideoMicrocodeFrameType_P,
	EMhwlibVideoMicrocodeFrameType_B = 4,
	EMhwlibVideoMicrocodeFrameType_BI, // VC1 specific
	EMhwlibVideoMicrocodeFrameType_Skipped, // VC1 specific
	EMhwlibVideoMicrocodeFrameType_ReferenceB = 8, // H264 specific
};

struct EMhwlibVideoDecoder_DecodeError {
	RMuint32 FrameCount; /* decode order frame count */
	RMuint32 FrameByteCount; /* offset or bytecounter of the decoded frame relative to input stream */
	RMuint32 CorruptedMacroblocksCount; /* number of corrupted macroblocks */
	RMuint32 OverflowCount; /* number of error entries skipped due to error fifo full */
	enum EMhwlibVideoMicrocodeFrameType FrameType; /*  */
	RMuint32 ErrorCount; /* it could be greater than 16, but the next array contains only 16 */
	RMuint16 ErrorCodes[16]; /* array of up to 16 errors */
};

#ifdef __cplusplus
namespace video_interface {
#endif // __cplusplus

RMstatus video_set_ucode_dram_offset(
	struct gbus *pGBus,
	RMuint32 MemBase,
	RMuint32 start_address);
RMstatus video_set_scheduler_memory(
	struct gbus *pGBus,
	RMuint32 MemBase,
	RMuint32 start_address,
	RMuint32 size);
RMstatus video_get_scheduler_memory(
	struct gbus *pGBus,
	RMuint32 MemBase,
	RMuint32 *pstart_address,
	RMuint32 *psize);
RMstatus video_set_display_error_threshold(
	struct gbus *pGBus,
	struct video_task_interface *pvti,
	RMuint32 threshold);
RMstatus video_set_anchor_propagation_parms(
	struct gbus *pGBus,
	struct video_task_interface *pvti,
	RMuint32 threshold, RMuint32 length);
RMstatus video_set_vti_pointer(
	struct gbus *pGBus,
	struct video_task_data_base *pvtdb,
	RMuint32 pvti_in);
RMstatus video_set_vtdb_pointer(
	struct gbus *pGBus,
	RMuint32 MemBase,
	RMuint32 index,
	RMuint32 pvtdb);
RMstatus video_set_data_context_buffer(
	struct gbus *pGBus,
	struct video_task_interface *pvti, /* struct video_task_data_base *pvtdb, */
	RMuint32 start_address,
	RMuint32 total_size,
	RMuint32 context_size);
RMstatus video_set_bts_fifo_pointer(
	struct gbus *pGBus,
	struct video_task_data_base *pvtdb,
	RMuint32 bts_fifo);
RMstatus video_get_pts_fifo(
	struct gbus *pGBus,
	struct video_task_data_base *pvtdb,
	RMuint32 *pts_fifo);
RMstatus video_open_pts_fifo(
	struct gbus *pGBus,
	struct video_task_data_base *pvtdb,
	RMuint32 start,
	RMuint32 size);
RMstatus video_open_inband_fifo(
	struct gbus *pGBus,
	struct video_task_data_base *pvtdb,
	RMuint32 start,
	RMuint32 size);
RMstatus video_get_display_fifo(
	struct gbus *pGBus,
	struct video_task_data_base *pvtdb,
	RMuint32 *display_fifo);
RMstatus video_get_irq_info(
	struct gbus *pGBus,
	struct video_task_interface *pvti,
	RMuint32 *pevent_table_pointer);
RMstatus video_get_user_data_fifo(
	struct gbus *pGBus,
	struct video_task_data_base *pvtdb,
	RMuint32 *fifo);
RMstatus video_open_user_data_fifo(
	struct gbus *pGBus,
	struct video_task_data_base *pvtdb,
	RMuint32 start,
	RMuint32 size);
RMstatus video_get_user_data_fifo(
	struct gbus *pGBus,
	struct video_task_data_base *pvtdb,
	RMuint32 *fifo);
RMstatus video_open_error_code_fifo(
	struct gbus *pGBus,
	struct video_task_data_base *pvtdb,
	RMuint32 start,
	RMuint32 size);
RMstatus video_set_extra_pictures(
	struct gbus *pGBus,
	struct video_task_interface *pvti,
	RMint32 extra_buffer_count);
RMstatus video_set_command(
	struct gbus *pGBus,
	struct video_task_interface *pvti,
	enum VideoCommand command);
RMstatus video_get_status(
	struct gbus *pGBus,
	struct video_task_interface *pvti,
	enum VideoStatus *status);
RMstatus video_set_profile(
	struct gbus *pGBus,
	struct video_task_interface *pvti,
	RMuint32 profile);
RMstatus video_get_profile(
	struct gbus *pGBus,
	struct video_task_interface *pvti,
	RMuint32 *profile);

#if (RMFEATURE_VIDEO_INTERFACE_VERSION==2)
#define PICTURE_BUFFER_BANK_0 0
#define PICTURE_BUFFER_BANK_1 1
RMstatus video_set_picture_buffer(
	struct gbus *pGBus,
	struct video_task_interface *pvti,
	RMuint32 id,
	RMuint32 address,
	RMuint32 size);

RMstatus video_set_context_buffer(
	struct gbus *pGBus,
	struct video_task_interface *pvti,
	RMuint32 address,
	RMuint32 size);
#endif

//class UcodeSymbolMgr;

void set_symbol_resolver(void* pMgr);
void* get_symbol_resolver();

#ifdef __cplusplus
}
#endif


#endif // __VIDEO_INTERFACE_H__

