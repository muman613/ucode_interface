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

typedef struct _fifo {
    uint32_t        uiFifoCont;             ///< FIFO container address
    uint32_t        uiFifoPtr;              ///< FIFO base address
    uint32_t        uiFifoSize;             ///< FIFO size
    uint32_t        uiFifoRdPtr;            ///< FIFO read pointer
    uint32_t        uiFifoWrPtr;            ///< FIFO write pointer
} FIFO;

typedef struct picBufComponent {
    uint32_t        uiBufAddress;
    uint32_t        uiTotalWidth;
    uint32_t        uiBufWidth;
    uint32_t        uiBufHeight;
    uint32_t        uiPosX;
    uint32_t        uiPosY;
    uint32_t        uiPosWidth;
    uint32_t        uiPosHeight;
    uint32_t        uiSizeTile;
} PICBUF_COMP;

typedef struct picBufSpec {
    uint32_t        uiPicAddress;
    PICBUF_COMP     lumaComp;
    PICBUF_COMP     chromaComp;
} PICBUF_SPEC;

struct inputStats {
    std::string     sInputFile;
    RMuint32        profile;
    size_t          bytesRead;
    RMuint32        pvtdb;
    RMuint32        pvti;
    FIFO            btsFifo;
};

struct outputStats {
    bool            bSavingYUV;
    std::string     sYUVFile;
//    RMuint32        pic_address;
//    RMuint32        pic_luma_buffer;
//    RMuint32        pic_chroma_buffer;
//    RMuint32        pic_width;
//    RMuint32        pic_height;
    RMuint32        frame_count;
    double          save_time;
    FIFO            dispFifo;
    PICBUF_SPEC     picInfo;
};

struct MicrocodeInbandParams {
    RMuint32 ref_cnt;
    RMuint32 params[COMMAND_PARAMS_RMUINT32_SIZE];
};

struct EMhwlibWindow {
        RMuint32 x;
        RMuint32 y;
        RMuint32 width;
        RMuint32 height;
};

struct MicrocodeInbandCommand {
    RMuint32 flags_tag;      // INBAND_COMMAND_GET_TAG() is the macro to find the tag
    RMuint32 byte_counter;   // byte counter - see EMhwlibInbandOffset
    RMuint32 target;         // destination or target id. If 0 = broadcast.
    RMuint32 params_address; // pointer to the "union params_type" that contains the specific parameters
    RMuint32 params_ref_cnt; // 0 if free
};


#define XFER_BUFFERSIZE              65536

/**
 *  Class representing a task in the microcode.
 */

class targetStandardIFTask {
public:
    enum taskState {
        TASK_UNINITIALIZED,
        TASK_INITIALIZED,
        TASK_COMMAND_PENDING,
        TASK_PLAYING,
        TASK_STOPPED,
    };

    enum taskSubstate {
        TASK_SUBSTATE_UNKNOWN,
        TASK_SUBSTATE_SENT_UNINIT,
        TASK_SUBSTATE_UNINIT,
        TASK_SUBSTATE_SENT_INIT,
        TASK_SUBSTATE_STOP,
        TASK_SUBSTATE_SENT_PLAY,
        TASK_SUBSTATE_PLAY,
        TASK_SUBSTATE_SENT_STOP,
    };

    struct targetStdIfParms {
        std::string             sInputStreamName;
        std::string             sOutputYUVName;
        RMuint32                nProfile        = VideoProfileMPEG2;
        bool                    bDumpUntiled    = false;
        std::string             sDumpPath       = "/tmp";
        std::string             sXmlPath        = "../../xml/";
        controlInterface*       pIF             = nullptr;
        TARGET_ALLOC_PTR        pAlloc;
    };

    targetStandardIFTask();
    targetStandardIFTask(targetStdIfParms& parms);
    virtual ~targetStandardIFTask();

    void                    enable_dump(const std::string& sPath = "/tmp/");
    void                    disable_dump();
    bool                    get_dump_info(std::string& sPath);

    friend std::ostream& operator<<(std::ostream& os,const targetStandardIFTask& task);

    bool                    start();
    bool                    stop();

    //taskState               get_state() const;
    void                    get_state(taskState* pState, taskSubstate* pSubState = nullptr);

    bool                    get_output_stats(outputStats& stats) const;
    bool                    get_input_stats(inputStats& stats) const;

protected:
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
    RMuint32                picbuf_address;
    RMuint32                luma_address;
    RMuint32                chroma_address;

    double                  save_time;                  ///< seconds per frame

    std::string             inputStreamName;
    std::string             outputYUVName;
	FILE*                   yuvfp;                      ///< Output yuv file handle.
    RMuint32                total_frames;               ///< Frame Count.
    bool                    dump_y_uv;                  ///< If true dump each tiled buffer to Y & UV file.
    std::string             dumpPath;

    RMuint32                ifVersion;

    size_t                  total_bytes_read;

    typedef std::chrono::time_point<std::chrono::high_resolution_clock> time_point;
    typedef std::chrono::duration<double>                               time_diff;

    volatile std::atomic<taskState>      task_state;
    volatile std::atomic<taskSubstate>   task_substate;

    std::string             sXmlPath;

    PICBUF_SPEC             picbufSpec;

private:
    controlInterface*       pIF;
    TARGET_ALLOC_PTR        pAlloc;

    void                    init_parameters();
    RMstatus                init_video_engine();

    RMstatus                open_video_decoder();

    /*! Launch the threads */
    bool                    launch_threads();
    /*! Stop the threads. */
    void                    stop_threads();
    /*! The FIFO Fill Thread function. */
    void*                   fifoFillThreadFunc();
    /*! The FIFO Empty Thread function. */
    void*                   fifoEmptyThreadFunc();

    RMuint32                write_data_in_circular_bts_fifo(RMuint8 *pBuf,
                                                            RMuint32 sizeToSend);

    RMstatus                process_picture(RMuint32 picture_address);

    /*! Save untiled frame to output file */
    void                    save_frame(RMuint32 frame_count,
                                       EMhwlibWindow* luma_position_in_buffer,
                                       RMuint32 luma_ttl_wd,
                                       EMhwlibWindow* chroma_position_in_buffer,
                                       RMuint32 chroma_ttl_wd);

    void                    READ_PICTURE_BUFFER_RECT(RMuint32 address,
                                                     std::string sField,
                                                     struct EMhwlibWindow* pDest);
    RMuint32                READ_PICTURE_BUFFER_MEMBER(RMuint32 address,
                                                       const std::string& member);

    bool                    set_tile_dimensions(std::string sChip);
    void                    set_tile_dimensions(RMuint32 tsw, RMuint32 tsh);

    RMstatus                set_video_codec();
    RMstatus                send_video_command(enum VideoCommand cmd,
                                               enum VideoStatus stat);

    void                    get_dump_filenames(RMuint32 frame_no,
                                               std::string& sYFilename,
                                               std::string& sUVFilename);

    void                    update_task_state(VideoCommand command, VideoStatus status);

    void                    set_state(taskState pState, taskSubstate pSubState);

    std::thread                         fifoFillThread;    ///< Thread used to send stream data to input fifo...
    std::thread                         fifoEmptyThread;   ///< Thread used to extract pictures to output file.
    volatile mutable std::atomic_bool   fifoFillRunning;   ///< Flag set when the fill thread is running.
    volatile mutable std::atomic_bool   fifoEmptyRunning;  ///< Flag set when the empty thread is running.
    volatile mutable std::atomic_bool   terminateThreads;  ///< Flag used to signal threads shut-down.
//  mutable std::mutex                  contextMutex;      ///< Mutex for access to class context variables.
    mutable std::mutex                  stateMutex;
    mutable std::mutex                  inputStatMutex;
    mutable std::mutex                  outputStatMutex;

    void                        update_input_stats();
    void                        update_output_stats();

    inputStats                  iStats;
    outputStats                 oStats;
};

typedef std::shared_ptr<targetStandardIFTask>   TASK_PTR;
typedef std::array<TASK_PTR, MAX_TASK_COUNT>    IFTASKARRAY;

/**
 *  Some specific types...
 */

typedef std::vector<std::string>            PROFILE_VECTOR;
typedef std::vector<std::string>::iterator  PROFILE_VECTOR_ITERATOR;

/**
 *
 */
class targetStandardInterface : public targetInterfaceBase
{
public:

    enum if_state {
        IF_UNINITIALIZED,           ///< Initial state
        IF_INITIALIZED,             ///< Interface initialized.
        IF_COMMAND_PENDING,         ///< Set to initializing while
        IF_PLAYING,
    };

    targetStandardInterface(TARGET_ENGINE_PTR pEngine);
    virtual ~targetStandardInterface();

    void                    enable_dump(const std::string& sPath = "/tmp/");
    void                    disable_dump();
    bool                    get_dump_info(std::string& sPath);

    bool                    play_stream(const std::string& sInputStreamName,
                                        const std::string& sOutputYUVName,
                                        RMuint32 profile = VideoProfileMPEG2,
                                        RMuint32 taskID = 0);
    bool                    play_stream(const std::string& sInputStreamName,
                                        const std::string& sOutputYUVName,
                                        const std::string& sProfile,
                                        RMuint32 taskID = 0);
    bool                    stop();

    static RMint32          get_profile_id_from_string(const std::string& sCodecID);
    static std::string      get_profile_string_from_id(RMint32 codec_id);
    static void             get_profile_vector(PROFILE_VECTOR& pVec);

#ifdef _DEBUG
    void                    debug_state(std::ostream& os = std::cout);
#endif // _DEBUG

    if_state                get_interface_state(uint32_t* taskCount = nullptr) const;
    bool                    get_task_state(uint32_t taskID,
                                           targetStandardIFTask::taskState* pTaskState,
                                           targetStandardIFTask::taskSubstate* pTaskSubstate);
    bool                    get_output_stats(RMuint32 taskID, outputStats& stats) const;
    bool                    get_input_stats(RMuint32 taskID, inputStats& stats) const;

protected:

    static struct profileEntry {
        std::string     sIdent;
        int             nProfile;
    } profileTable[];

    void                        init_parameters();
    void                        stop_tasks();

    bool                        bValid;

    volatile std::atomic<if_state>       ifState;
   // RMuint32                    ifVersion;          ///< (1 = version 1 2 = version 2)
    IFTASKARRAY                 tasks;

    bool                        dump_y_uv;
    std::string                 dumpPath;

    void                        clear_scheduler_data();

    bool                        _play_stream(const std::string& sInputStreamName,
                                             const std::string& sOutputYUVName,
                                             RMuint32 sProfile,
                                             RMuint32 taskID);

private:
    mutable std::mutex      contextMutex;      ///< Mutex for access to class context variables.
};

#define VPTS_FIFO_ENTRY_SIZE	8 /* 8 bytes = PTS on 32 bits and byte counter on 32 bits */
#define DECODE_ERROR_ENTRIES 	128
#define DECODER_DATA_SIZE       (29638656 * 6)
//#define DECODER_DATA_SIZE       (29638656 * 12)
#define DECODER_CTX_SIZE        6242304



typedef std::shared_ptr<targetStandardInterface>    TARGET_STD_IF;

#define CREATE_NEW_INTERFACE(engine)											\
	std::make_shared<targetStandardInterface>( engine )

#define PLATFORM_OPTION_FILE            "targetOptions.xml"

#endif // __TARGET_STD_INTERFACE_H__
