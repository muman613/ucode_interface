#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <getopt.h>
#include <unistd.h>
#include "dbgutils.h"
#include "targetEngine.h"
#include "targetStandardInterface.h"
#include "utils.h"

////////////////////////////////////////////////////////////////////////////////
//  optionPack stores options used by the test application.
////////////////////////////////////////////////////////////////////////////////

class optionPack {
public:
//    enum ucodeType {
//        UCODE_RELEASE,
//        UCODE_DEBUG,
//    };
    optionPack()
    : engineNo(0),
      type(targetEngine::UCODE_RELEASE)
    {
    }
    std::string                 chipID;
    std::string                 inputStream;
    std::string                 outputYUV;
    std::string                 profile;
    int                         engineNo;
    targetEngine::ucodeType     type;

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
        { "engine", optional_argument, 0, 'e', },
        { "mode",   optional_argument, 0, 'm', },

        { 0, 0, 0, 0, },
    };

    while ((c=getopt_long(argc, argv, "c:s:d:y:e:m:", long_options, &option_index)) != -1) {
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
            if (optarg != nullptr)
                options.profile = optarg;
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
        default:
            break;
        }
    }

    bRes = (!options.chipID.empty() && !options.inputStream.empty());

    return bRes;
}



/**
 *  Main entry point
 */

int main(int argc, char * argv[])
{
    TARGET_ENGINE_PTR   pTarget;
    optionPack          opts;

    D(open_log_files("messages.txt", "errors.txt"));

    set_terminal_mode();

    if (parse_cmdline_arguments( argc, argv, opts )) {

////////////////////////////////////////////////////////////////////////////////
//	Create the target engine, this time a 8758 Video engine.
////////////////////////////////////////////////////////////////////////////////

        pTarget = CREATE_NEW_ENGINE( opts.chipID, "Video",
                                     opts.engineNo, opts.type );
//      pTarget = std::make_shared<targetEngine>("8758", "Video");

        if (pTarget && pTarget->is_valid()) {

            std::cout << "Target was created, attempting to connect!" << std::endl;

            if (pTarget->connect()) {
                std::cout << "Target is connected, loading microcode!" << std::endl;

                display_target_info( pTarget );

                if (pTarget->load_ucode()) {

                    std::cout << "Microcode loaded!" << std::endl;

                    TARGET_STD_IF pStdIF;

////////////////////////////////////////////////////////////////////////////////
//	Create the interface object and pass it the engine to run on.
////////////////////////////////////////////////////////////////////////////////

                    pStdIF = CREATE_NEW_INTERFACE( pTarget );
                    if (pStdIF) {
                        bool bDone = false;

                        std::cout << "Interface was created, playing stream..." << std::endl;
                        pStdIF->play_stream(opts.inputStream,
                                            opts.outputYUV,
                                            opts.profile);

                        std::cout << "waiting for user input!" << std::endl;

                        while (!bDone) {
                            int ch = getkey();

                            if (ch != EOF) {
                                if (ch == 'q' || ch == 'Q') {
                                    std::cout << "User hit quit... Please wait!" << std::endl;
                                    bDone = true;
                                    break;
                                }
                            }

                            usleep(5000);
                        }

                        pStdIF->stop();
                    }
                }
            } else {
                std::cout << "UNABLE TO CONNECT TO TARGET!" << std::endl;
            }

            pTarget.reset();
        }
    }

    D(debug("-- exiting test application!\n"));
    reset_terminal_mode();

    return 0;
}
