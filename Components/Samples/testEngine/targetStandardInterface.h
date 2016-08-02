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

protected:
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

typedef std::shared_ptr<targetStandardInterface>    TARGET_STD_IF;

#endif // __TARGET_STD_INTERFACE_H__
