#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <getopt.h>
#include <unistd.h>
#include <signal.h>
#include "dbgutils.h"
#include "targetEngine.h"
#include "targetStandardInterface.h"
#include "libOptions.h"
#include "utils.h"

////////////////////////////////////////////////////////////////////////////////
//  optionPack stores options used by the test application.
////////////////////////////////////////////////////////////////////////////////

class optionPack {
public:
    optionPack()
    : profile(VideoProfileMPEG2),
      engineNo(0),
      type(targetEngine::UCODE_RELEASE),
      verboseLevel(0)
    {
    }
    std::string                 chipID;
    std::string                 inputStream;
    std::string                 outputYUV;
    std::string                 serverStr;
    RMuint32                    profile;
    RMuint32                    engineNo;
    targetEngine::ucodeType     type;
    RMuint32                    verboseLevel;
};

#ifdef _DEBUG
void debug(const char* sFmt, ...) {
	va_list vargs;
	va_start(vargs, sFmt);

	vfprintf(stderr, sFmt, vargs);

	va_end(vargs);
}
#endif // _DEBUG


/**
 *  Display information about the target.
 */

void display_target_info(TARGET_ENGINE_PTR pEng)
{
    std::string sHostSpec;
    std::string sChipID, sBlockID;
    uint32_t    nEngineID;

    if (pEng->is_valid()) {
        pEng->get_info( sChipID, sBlockID, nEngineID);
        std::cout << "Chip   : " << sChipID << std::endl;
        std::cout << "Block  : " << sBlockID << std::endl;
        std::cout << "Engine : " << nEngineID << std::endl;

        if (pEng->is_connected()) {
            pEng->get_connection_info(sHostSpec);
            std::cout << "Remote : " << sHostSpec << std::endl;
        }
    }
}

/**
 *  Display help to user who requested it.
 */

void display_help(const char* cmd) {
    std::string     sCmd = basename(cmd);
    PROFILE_VECTOR  pVec;

    targetStandardInterface::get_profile_vector(pVec);

    std::cout << sCmd << " --chip [chipID] --stream [stream path] --decoder [decoder id] --yuv [yuv path] --engine [engine no] --mode [d=debug/r=release]" << std::endl;
    std::cout << sCmd << " -c [chipID] -s [stream path] -d [decoder id] -y [yuv path] -e [engine no] -m [d=debug/r=release]" << std::endl;

    std::cout << std::endl;
    std::cout << "Supported decoders:" << std::endl;

    std::for_each(pVec.begin(), pVec.end(), [](std::string codec) { std::cout << "   " << codec << std::endl; } );

    exit(0);
}
/**
 *  Parse commandline parameters.
 */

bool parse_cmdline_arguments(int argc, char* argv[], optionPack& options) {
    bool            bRes =  false;
    int             c, option_index = 0;
    static struct option long_options[] = {
        { "chip",   required_argument, 0, 'c', },
        { "stream", required_argument, 0, 's', },
        { "decoder",required_argument, 0, 'd', },
        { "yuv",    required_argument, 0, 'y', },
        { "engine", required_argument, 0, 'e', },
        { "mode",   required_argument, 0, 'm', },
        { "remote", required_argument, 0, 'r', },
        { "help",   no_argument,       0, 'h', },
        { "verbose",optional_argument, 0, 'v', },

        { 0, 0, 0, 0, },
    };

    while ((c=getopt_long(argc, argv, "c:s:d:y:e:m:r:v:h", long_options, &option_index)) != -1) {
        switch (c) {
        case 'c':
            if (optarg != nullptr)
                options.chipID = optarg;
            break;
        case 's':
            if (optarg != nullptr)
                options.inputStream = optarg;
            break;
        case 'd':
            if (optarg != nullptr) {
                options.profile = targetStandardInterface::get_profile_id_from_string(optarg);
                if (options.profile == (RMuint32)-1) {
                    std::cout << "ERROR: Unknown profile " << optarg << " exiting..." << std::endl;
                    return false;
                }
            }
            break;
        case 'y':
            if (optarg != nullptr)
                options.outputYUV = optarg;
            break;
        case 'e':
            if (optarg != nullptr)
                options.engineNo = atoi(optarg);
            break;
        case 'm':
            {
                std::string sMode;
                if (optarg != nullptr) {
                    sMode = optarg;

                    if ((sMode == "d") || (sMode == "r")) {
                        options.type = (sMode == "d")?targetEngine::UCODE_DEBUG:targetEngine::UCODE_RELEASE;
                    }
                }
            }
            break;
        case 'h':
            display_help(argv[0]);
            break;
        case 'r':
            if (optarg != nullptr) {
                options.serverStr = optarg;
            }
            break;
        case 'v':
            if (optarg != nullptr) {
                options.verboseLevel = atoi(optarg);
            } else {
                options.verboseLevel = 1;
            }
            break;
        default:
            break;
        }
    }

    if ((options.chipID == "8758") && (options.profile == VideoProfileH265)) {
        options.engineNo = 1;
    }


    bRes = (!options.chipID.empty() &&
            !options.inputStream.empty() &&
            (options.profile != (RMuint32)-1));

    return bRes;
}

/**
 *  Display frame count...
 */

void display_stats(const outputStats& stats)
{
    char buffer[128];
    static size_t lastSize = 0;

    if (stats.frame_count > 0) {
        snprintf(buffer, 128, "Frame # : %d @ 0x%08X save %d X %d frame to %s (%2.3f sec/frame)",
                 stats.frame_count,
                 stats.pic_address,
                 stats.pic_width,
                 stats.pic_height,
                 stats.sYUVFile.c_str(),
                 stats.save_time);
        if (lastSize != 0) {
            for (size_t i = 0 ; i < lastSize ; i++)
                fputc('\b', stdout);
        }

        fputs(buffer, stdout);
        fflush(stdout);
        lastSize = strlen(buffer);
    }
}

void _control_c_handler(int n) {
    reset_terminal_mode();
    exit(-10);
}

bool wait_for_playback_to_start(TARGET_STD_IF pIF)
{
    bool    bDone = false,
            bRes = false;
    targetStandardIFTask::taskState tskState = targetStandardIFTask::TASK_UNINITIALIZED;
    targetStandardIFTask::taskSubstate tskSubstate = targetStandardIFTask::TASK_SUBSTATE_UNKNOWN;
    targetStandardInterface::if_state ifState;
    char    sMsgBuffer[128];
    static size_t lastSize = 0;
    std::string sCmdString;

    while (!bDone) {
        ifState = pIF->get_interface_state();

        pIF->get_task_state(0, &tskState, &tskSubstate);

        switch (tskState) {
            case targetStandardIFTask::TASK_COMMAND_PENDING:
                switch (tskSubstate) {
                    case targetStandardIFTask::TASK_SUBSTATE_SENT_UNINIT:
                        sCmdString = "Sent UNINIT command";
                        break;
                    case targetStandardIFTask::TASK_SUBSTATE_SENT_INIT:
                        sCmdString = "Sent INIT command";
                        break;
                    case targetStandardIFTask::TASK_SUBSTATE_SENT_STOP:
                        sCmdString = "Sent STOP command";
                        break;
                    case targetStandardIFTask::TASK_SUBSTATE_SENT_PLAY:
                        sCmdString = "Sent PLAY command";
                        break;
                    default:
                        break;
                }
                break;
            case targetStandardIFTask::TASK_PLAYING:
                sCmdString = "Playing";
                break;
            default:
                break;
        }
//        std::cout <<  "ifState :" << (int)ifState << " Task State : " << (int)tskState << " Task Substate : " << (int)tskSubstate << std::endl;

        snprintf(sMsgBuffer, 128, "%d %s...", (int)ifState, sCmdString.c_str());

        if (lastSize != 0) {
            for (size_t i = 0 ; i < lastSize ; i++)
                fputc('\b', stdout);
        }

        fputs(sMsgBuffer, stdout);
        fflush(stdout);
        lastSize = strlen(sMsgBuffer);

        if (ifState == targetStandardInterface::IF_PLAYING)
            bDone = true;

        usleep(100);
    }

    fputs("\033[K\n", stdout);

    return bRes;
}

/**
 *  Main entry point
 */

int main(int argc, char * argv[])
{
    TARGET_ENGINE_PTR   pTarget;
    optionPack          opts;

//  globalOptions.set_xml_path("../../../xml/");
//  globalOptions.set_ucode_path("../../../ucode/");

    D(open_log_files("messages.txt", "errors.txt"));

    if (parse_cmdline_arguments( argc, argv, opts )) {
        set_terminal_mode();
        signal(SIGINT, _control_c_handler);

////////////////////////////////////////////////////////////////////////////////
//	Create the target engine, this time a 8758 Video engine.
////////////////////////////////////////////////////////////////////////////////

        pTarget = CREATE_NEW_ENGINE( opts.chipID, "Video",
                                     opts.engineNo, opts.type );

        if (pTarget && pTarget->is_valid()) {
            std::cout << *pTarget;

            std::cout << "Target was created, attempting to connect!" << std::endl;

            if (pTarget->connect(opts.serverStr)) {
                std::cout << "Target is connected to " << pTarget->get_targetid() << ", loading microcode!" << std::endl;

                if (opts.verboseLevel > 0)
                    display_target_info( pTarget );

                if (pTarget->load_ucode()) {
                    std::cout << *pTarget;

                    std::cout << "Microcode loaded!" << std::endl;

                    TARGET_STD_IF pStdIF;

////////////////////////////////////////////////////////////////////////////////
//	Create the interface object and pass it the engine to run on.
////////////////////////////////////////////////////////////////////////////////

                    pStdIF = CREATE_NEW_INTERFACE( pTarget );
                    if (pStdIF) {
                        bool bDone = false;
                        outputStats stats;

#if defined(_DEBUG) && defined(DUMP_TILED)
                        std::cout << "Dumping untiled buffers to /tmp/..." << std::endl;
                        pStdIF->enable_dump();
#endif // defined(_DEBUG) && defined(DUMP_TILED)

                        std::cout << "Interface was created, playing " <<
                            targetStandardInterface::get_profile_string_from_id(opts.profile) <<
                            " stream..." << std::endl;

////////////////////////////////////////////////////////////////////////////////
//	Play the media file on the interface...
////////////////////////////////////////////////////////////////////////////////

                        pStdIF->play_stream(opts.inputStream,
                                            opts.outputYUV,
                                            opts.profile);


                        wait_for_playback_to_start(pStdIF);

                        std::cout << "waiting for user input!" << std::endl;

#ifdef  _DEBUG
                        pStdIF->debug_state();
#endif // _DEBUG

                        while (!bDone) {
                            int ch = getkey();

                            if (ch != EOF) {
                                if (ch == 'q' || ch == 'Q') {
                                    putc('\n', stdout);
                                    std::cout << "User hit quit... Please wait!" << std::endl;
                                    bDone = true;
                                    break;
                                }
                            }

                            if (pStdIF->get_output_stats(0, stats)) {
                                display_stats(stats);
                            }
                            usleep(5000);
                        }

                        pStdIF->stop();

                        pStdIF.reset();
                    }
                } else {
                    std::cout << "Unable to load microcode!" << std::endl;
                }
            } else {
                std::cout << "UNABLE TO CONNECT TO TARGET!" << std::endl;
            }

            pTarget.reset();
        } else {
            std::cout << "Unable to open engine..." << std::endl;
        }

        reset_terminal_mode();
    }

    D(debug("-- exiting test application!\n"));

    return 0;
}
