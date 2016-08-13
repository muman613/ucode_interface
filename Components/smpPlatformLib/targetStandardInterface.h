#ifndef __TARGET_STD_INTERFACE_H__
#define __TARGET_STD_INTERFACE_H__

#include <memory>

#ifdef USE_PTHREADS
    #include <pthread.h>
#else
#if (__cplusplus >= 201103L)
    #include <thread>
    #include <atomic>
#else
    #pragma GCC error "Must compile with C++11 standard"
#endif
#endif // USE_PTHREADS

#include "targetEngine.h"
#include "targetInterfaceBase.h"

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

typedef enum _SOC_ARCH {
  SOC_TANGO,
  SOC_CALYPSO,
  SOC_PMAN,
} SOC_ARCH;

#define XFER_BUFFERSIZE              65536

/**
 *
 */

class targetStandardInterface : public targetInterfaceBase
{
public:
    targetStandardInterface(TARGET_ENGINE_PTR pEngine);
    virtual ~targetStandardInterface();

    bool                    play_stream(const std::string& sInputStreamName,
                                        const std::string& sOutputYUVName);
protected:
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

    RMstatus                init_video_engine();
    RMstatus                open_video_decoder();

    void                    init_parameters();
    bool                    set_tile_dimensions(std::string sChip);
    void                    set_tile_dimensions(RMuint32 tsw, RMuint32 tsh);

    bool                    bValid;

    SOC_ARCH                soc_arch;
    RMuint32	            DecoderDataSize;
	RMuint32	            DecoderContextSize;
	RMuint32	            BitstreamFIFOSize;
	RMuint32	            PtsFIFOCount;
	RMuint32	            InbandFIFOCount;
	RMuint32	            NumOfPictures;
	RMuint32	            UserDataSize;
	RMuint32	            ExtraPictureBufferCount;
	RMuint32	            user_inband_cmd_fifo;
	RMuint32	            inband_params_address;
	RMuint32	            event_table_pointer;

	RMuint32	            pvtdb;                      ///< Address of video task database.
	RMuint32	            pvti;                       ///< Address of video task interface.

    /* FIFO addresses */
	RMuint32	            data_fifo;
	RMuint32	            bts_fifo;
	RMuint32	            display_fifo;
	RMuint32	            user_data_fifo;

    RMuint32                pvc_tw;                     ///< Tile Width
    RMuint32                pvc_th;                     ///< Tile Height
    RMuint32                pvc_ts;                     ///< Tile Size

    RMuint32                decoderProfile;             ///< Decoder profile (default mpeg2)

    RMuint8*                pChroma;
    RMuint8*                pLuma;


	RMuint32                tile_width_l2;              ///< Tile width used by detile algo
	RMuint32                tile_height_l2;             ///< Tile height used by detile algo
	RMuint32                storage_format;
    RMuint32                luma_nb_comp_per_sample;    ///< Number of components per sample of luma
    RMuint32                chroma_nb_comp_per_sample;  ///< Number of components per sample of chroma

    RMuint32                picture_w;
    RMuint32                picture_h;
    RMuint32                picture_count;

    std::string             inputStreamName;
    std::string             outputYUVName;
	FILE*                   yuvfp;                      ///< Output yuv file handle.
    RMuint32                total_frames;

private:
    bool                    launch_threads();
    void                    stop_threads();

    void*                   fifoFillThreadFunc();
    void*                   fifoEmptyThreadFunc();

    RMuint32                write_data_in_circular_bts_fifo(RMuint8 *pBuf,
                                                            RMuint32 sizeToSend);
#ifdef  USE_PTHREADS
    pthread_t                   fifoFillThread;         ///< Thread used to send stream data to input fifo...
    pthread_t                   fifoEmptyThread;        ///< Thread used to extract pictures from display fifo...
    volatile sig_atomic_t       fifoFillRunning;        ///< Thread used to extract pictures from display fifo...
    volatile sig_atomic_t       fifoEmptyRunning;
    volatile sig_atomic_t       terminateThreads;
    /* Thread mutex objects */
    pthread_mutex_t             contextMutex;
    pthread_mutex_t             displayMutex;

    /** Callback stubs */
    static void*                _fifoFillThreadFunc(targetStandardInterface* pThis);
    static void*                _fifoEmptyThreadFunc(targetStandardInterface* pThis);
#else
#if (__cplusplus >= 201103L)
    std::thread                 fifoFillThread;         ///< Thread used to send stream data to input fifo...
    std::thread                 fifoEmptyThread;
    mutable std::atomic_bool    fifoFillRunning;
    mutable std::atomic_bool    fifoEmptyRunning;
    mutable std::atomic_bool    terminateThreads;
    mutable std::mutex          contextMutex;
//  std::mutex              displayMutex;
#else  // (__cplusplus >= 201103L)
#pragma GCC error "std::thread not available"
#endif // (__cplusplus >= 201103L)
#endif // USE_PTHREADS
};

#define VPTS_FIFO_ENTRY_SIZE	8 /* 8 bytes = PTS on 32 bits and byte counter on 32 bits */
#define DECODE_ERROR_ENTRIES 	128
#define DECODER_DATA_SIZE       (29638656 * 12)
#define DECODER_CTX_SIZE        6242304



typedef std::shared_ptr<targetStandardInterface>    TARGET_STD_IF;

#endif // __TARGET_STD_INTERFACE_H__
