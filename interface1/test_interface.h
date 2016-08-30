/******************************************************************************
 *                                                                            *
 ******************************************************************************/

#ifndef	__TEST_INTERFACE_H__
#define __TEST_INTERFACE_H__

#ifdef ENABLE_THREADS
    #include <pthread.h>
#endif // ENABLE_THREADS

//#define DRAM_BASE       0xa8000000 // hardcoded value in a free Dram zone
#define DRAM_BASE       0xb0000000 // hardcoded value in a free Dram zone

#undef  G2L_RESET_CONTROL
#define G2L_RESET_CONTROL		0xffc

//#ifndef REG_BASE_mpeg_engine_0
//// hardware addresses for mpeg engine
//#define REG_BASE_mpeg_engine_0		0x80000  // Registers
//#define MEM_BASE_mpeg_engine_0		0x100000 // PMEM = Program memory
//#define DMEM_BASE_mpeg_engine_0		0x110000 // DMEM = Data memory
//#endif

#define VPTS_FIFO_ENTRY_SIZE	8 /* 8 bytes = PTS on 32 bits and byte counter on 32 bits */
#define DECODE_ERROR_ENTRIES 	128
#if (RMCHIP_ID == RMCHIP_ID_SMP8756)
#define DECODER_DATA_SIZE       29638656
#else // (RMCHIP_ID == RMCHIP_ID_SMP8756)
#define DECODER_DATA_SIZE       (29638656 * 12)
#endif // (RMCHIP_ID == RMCHIP_ID_SMP8756)
#define DECODER_CTX_SIZE        6242304

#define BUFFERSIZE              65536

struct _uiContext;

/**
 *  DSP register values.
 */

#define DSP_RUN                 0x00
#define DSP_STOP                0x01
#define DSP_RESET               0x03

#define PICTURE_DISPLAY_DATA_PIXEL_FORMAT_YUV    0x0000
#define PICTURE_DISPLAY_DATA_PIXEL_FORMAT_Y      0x0040
#define PICTURE_DISPLAY_DATA_PIXEL_FORMAT_YUYV   0x0080
#define PICTURE_DISPLAY_DATA_PIXEL_FORMAT_RGBA   0x00C0

typedef enum _SOC_ARCH {
  SOC_TANGO,
  SOC_CALYPSO,
  SOC_PMAN,
} SOC_ARCH;


typedef enum _appState {
    APP_STATE_UNKNOWN,
    APP_INITIALIZING,
    APP_LOADING_MICROCODE_0,
    APP_LOADING_MICROCODE_1,
    APP_SENDING_UNINIT,
    APP_SENDING_INIT,
    APP_SENDING_PLAY,
    APP_SENDING_STOP,
    APP_PLAYING,
} APP_STATE;

/**
 *  Context structure used to pass to all top level functions.
 */

typedef struct _ifcontext {
    /* User supplied options */
	const char*	szBinFilename[2];           ///< Name of microcode image file.
	const char*	szStrFilename;              ///< Name of input video stream.
    const char* szYUVFilename;              ///< Name of output YUV file.
    const char* szYUVPath;
    RMuint32    decoderProfile;             ///< Decoder profile (default mpeg2)

    RMuint32    memBaseAddress;
    RMuint32    pmBaseAddress;
    RMuint32    dmBaseAddress;
    RMuint32    regBaseAddress;
    RMuint32    dramBaseAddress;

	RMuint32	uiDRAMPtr;
	RMuint32	DecoderDataSize;
	RMuint32	DecoderContextSize;
	RMuint32	BitstreamFIFOSize;
	RMuint32	PtsFIFOCount;
	RMuint32	InbandFIFOCount;
	RMuint32	NumOfPictures;
	RMuint32	UserDataSize;
	RMuint32	ExtraPictureBufferCount;
	RMuint32	user_inband_cmd_fifo;
	RMuint32	inband_params_address;
	RMuint32	event_table_pointer;

	RMuint32	pvtdb;                      ///< Address of video task database.
	RMuint32	pvti;                       ///< Address of video task interface.

    /* FIFO addresses */
	RMuint32	data_fifo;
	RMuint32	bts_fifo;
	RMuint32	display_fifo;
	RMuint32	user_data_fifo;

    RMuint32    pvc_tw;                     ///< Tile Width
    RMuint32    pvc_th;                     ///< Tile Height
    RMuint32    pvc_ts;                     ///< Tile Size

    RMuint32    binSize;
    RMuint32    dram_lo;
    RMuint32    dram_hi;

	struct llad*	pllad;
	struct gbus*	pgbus;

    RMuint8*    pChroma;
    RMuint8*    pLuma;

	FILE*       yuvfp;                      ///< Output yuv file handle.

	SOC_ARCH    soc_arch;                   ///< System architecture used in detile algo
	RMuint32    tile_width_l2;              ///< Tile width used by detile algo
	RMuint32    tile_height_l2;             ///< Tile height used by detile algo
	RMuint32    storage_format;
    RMuint32    luma_nb_comp_per_sample;    ///< Number of components per sample of luma
    RMuint32    chroma_nb_comp_per_sample;  ///< Number of components per sample of chroma

//  APP_STATE   application_state;

#ifdef  ENABLE_THREADS
    pthread_t               fifoFillThread;             ///< Thread used to send stream data to input fifo...
    pthread_t               fifoEmptyThread;            ///< Thread used to extract pictures from display fifo...
    volatile sig_atomic_t   fifoFillRunning;
    volatile sig_atomic_t   fifoEmptyRunning;
    volatile sig_atomic_t   terminateThreads;
    /* Thread mutex objects */
    pthread_mutex_t         contextMutex;
    pthread_mutex_t         displayMutex;
#endif // ENABLE_THREADS

#ifdef  ENABLE_CURSES
//    void*                   pUIContext;
    struct _uiContext*      pUIContext;
#endif // ENABLE_CURSES

    int                     dump_y_uv;
} CONTEXT;


#define COMMAND_TIMEOUT         0xffffffff

#define READ_PICTURE_BUFFER(pgbus, address, member)                                 \
    gbus_read_uint32(pgbus, (RMuint32) &(((struct VideoMicrocodePicture *)address)->member))

#define READ_PICTURE_BUFFER_STRUCT(pgbus, address, member, dest, type)              \
    gbus_read_data8(pgbus, (RMuint32) &(((struct VideoMicrocodePicture *)address)->member), (RMuint8 *)&dest, sizeof(type))

/* Context display macros */

#define DISPLAY_CTX_PTR(VAR)  \
    printf("%-40s : 0x%08lX\n", #VAR , ctx->VAR);

#define DISPLAY_CTX_VAR(VAR)  \
    printf("%-40s : %ld (0x%08lX)\n", #VAR , ctx->VAR, ctx->VAR);

#define DISPLAY_CTX_STR(VAR, STR)  \
    printf("%-40s : %s\n", STR , ctx->VAR);

#define DISPLAY_CTX_STR2(VAR, STR)  \
    printf("%-40s : %s\n", #VAR , STR);

#define SET_DISPLAY_CONTEXT(ctx, member, value)                                \
    ((UI_CONTEXT*)ctx->pUIContext)->member = value

#ifdef ENABLE_ENV_VARS

#define UCODE_0     "MICROCODE_0"
#define UCODE_1     "MICROCODE_1"
#define CODEC_ID    "CODEC_ID"

#endif // ENABLE_ENV_VARS

#endif // __TEST_INTERFACE_H__
