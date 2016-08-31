#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <getopt.h>
#include "optionparser.h"

/**
 *  Parse commandline parameters.
 */

bool optionPack::parse(int argc, char* argv[], HELPFUNC pHelpFunc) {
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
                chipID = optarg;
            break;
        case 's':
            if (optarg != nullptr)
                inputStream = optarg;
            break;
        case 'd':
            if (optarg != nullptr) {
                profile = targetStandardInterface::get_profile_id_from_string(optarg);
                if (profile == (RMuint32)-1) {
                    std::cout << "ERROR: Unknown profile " << optarg << " exiting..." << std::endl;
                    return false;
                }
            }
            break;
        case 'y':
            if (optarg != nullptr)
                outputYUV = optarg;
            break;
        case 'e':
            if (optarg != nullptr)
                engineNo = atoi(optarg);
            break;
        case 'm':
            {
                std::string sMode;
                if (optarg != nullptr) {
                    sMode = optarg;

                    if ((sMode == "d") || (sMode == "r")) {
                        type = (sMode == "d")?targetEngine::UCODE_DEBUG:targetEngine::UCODE_RELEASE;
                    }
                }
            }
            break;
        case 'h':
            (*pHelpFunc)(argv[0]);
            break;
        case 'r':
            if (optarg != nullptr) {
                serverStr = optarg;
            }
            break;
        case 'v':
            if (optarg != nullptr) {
                verboseLevel = atoi(optarg);
            } else {
                verboseLevel = 1;
            }
            break;
        default:
            break;
        }
    }

    if ((chipID == "8758") && (profile == VideoProfileH265)) {
        engineNo = 1;
    }


    bRes = (!chipID.empty() &&
            !inputStream.empty() &&
            (profile != (RMuint32)-1));

    return bRes;
}
