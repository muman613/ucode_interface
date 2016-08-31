#ifndef __OPTIONPARSER_H__
#define __OPTIONPARSER_H__

#include <string>
#define ALLOW_OS_CODE
#include "rmdef/rmdef.h"
#include "targetEngine.h"
#include "targetStandardInterface.h"

typedef void (*HELPFUNC)(const char* cmd);

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

    bool parse(int argc, char* argv[], HELPFUNC pHelpFunc = nullptr);
};
//void display_help(const char* cmd)



#endif // __OPTIONPARSER_H__

