#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "targetEngine.h"
#include "targetStandardInterface.h"

#ifdef _DEBUG
void debug(const char* sFmt, ...) {
	va_list vargs;
	va_start(vargs, sFmt);

	vfprintf(stderr, sFmt, vargs);

	va_end(vargs);
}
#endif // _DEBUG


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
 *  Main entry point
 */

int main(int argc, char * argv[])
{
    TARGET_ENGINE_PTR   pTarget;

#ifdef _DEBUG
    open_log_files("messages.txt", "errors.txt");
#endif // _DEBUG

    pTarget = std::make_shared<targetEngine>("8758", "Video");

    if (pTarget && pTarget->is_valid()) {

        std::cout << "Target is opened!" << std::endl;

        if (pTarget->connect()) {
            std::cout << "Target is connected!" << std::endl;

            display_target_info( pTarget );

            if (pTarget->load_ucode()) {

                std::cout << "Microcode loaded!" << std::endl;

                TARGET_STD_IF pStdIF;

                pStdIF = std::make_shared<targetStandardInterface>(pTarget);
                if (pStdIF) {
                    pStdIF->play_stream("/media/elementary/mpeg2/test100.m2v",
                                        "/tmp/capture.yuv");
                }
//                pStdIF->init_video_engine();
//                pStdIF->open_video_decoder();
            }

//            pTarget->test_function();
        }

        pTarget.reset();
    }

    return 0;
}
