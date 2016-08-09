#ifndef __TARGET_STD_INTERFACE_H__
#define __TARGET_STD_INTERFACE_H__

#include <memory>
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

typedef enum _SOC_ARCH {
  SOC_TANGO,
  SOC_CALYPSO,
  SOC_PMAN,
} SOC_ARCH;

class targetStandardInterface : public targetInterfaceBase
{
public:
    targetStandardInterface(TARGET_ENGINE_PTR pEngine);
    virtual ~targetStandardInterface();

    void                test_function();

    RMstatus            init_video_engine();
    RMstatus            open_video_decoder();

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

    void                init_parameters();
    bool                set_tile_dimensions(std::string sChip);
    void                set_tile_dimensions(RMuint32 tsw, RMuint32 tsh);

    bool                bValid;

    SOC_ARCH            soc_arch;
    RMuint32	        DecoderDataSize;
	RMuint32	        DecoderContextSize;
	RMuint32	        BitstreamFIFOSize;
	RMuint32	        PtsFIFOCount;
	RMuint32	        InbandFIFOCount;
	RMuint32	        NumOfPictures;
	RMuint32	        UserDataSize;
	RMuint32	        ExtraPictureBufferCount;
	RMuint32	        user_inband_cmd_fifo;
	RMuint32	        inband_params_address;
	RMuint32	        event_table_pointer;

	RMuint32	        pvtdb;                      ///< Address of video task database.
	RMuint32	        pvti;                       ///< Address of video task interface.

    /* FIFO addresses */
	RMuint32	        data_fifo;
	RMuint32	        bts_fifo;
	RMuint32	        display_fifo;
	RMuint32	        user_data_fifo;

    RMuint32            pvc_tw;                     ///< Tile Width
    RMuint32            pvc_th;                     ///< Tile Height
    RMuint32            pvc_ts;                     ///< Tile Size

    RMuint8*            pChroma;
    RMuint8*            pLuma;

	FILE*               yuvfp;                      ///< Output yuv file handle.

	RMuint32            tile_width_l2;              ///< Tile width used by detile algo
	RMuint32            tile_height_l2;             ///< Tile height used by detile algo
	RMuint32            storage_format;
    RMuint32            luma_nb_comp_per_sample;    ///< Number of components per sample of luma
    RMuint32            chroma_nb_comp_per_sample;  ///< Number of components per sample of chroma

    RMuint32            picture_w;
    RMuint32            picture_h;
    RMuint32            picture_count;
};

#define VPTS_FIFO_ENTRY_SIZE	8 /* 8 bytes = PTS on 32 bits and byte counter on 32 bits */
#define DECODE_ERROR_ENTRIES 	128
#define DECODER_DATA_SIZE       (29638656 * 12)
#define DECODER_CTX_SIZE        6242304



typedef std::shared_ptr<targetStandardInterface>    TARGET_STD_IF;

#endif // __TARGET_STD_INTERFACE_H__