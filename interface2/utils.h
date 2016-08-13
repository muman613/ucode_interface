#ifndef	__UTILS_H__
#define __UTILS_H__

#include <time.h>
#include <string>

class CONTEXT;

RMstatus file_exists(const char* szFilename);
RMstatus file_exists(std::string sFilename);

int stricmp(char const *a, char const *b);

#ifndef ENABLE_CURSES
int _kbhit(void);
int getkey();
void set_terminal_mode();
void reset_terminal_mode();
#endif // ENABLE_CURSES

RMint32         get_profile_id_from_string(const char* szCodecID);
const char*     get_profile_string_from_id(RMint32 codec_id);

struct timespec difftimespec(struct timespec start, struct timespec end);
double get_ts_seconds(struct timespec spec);

char* generate_output_yuv(const char* szPath, const char* szInputName);
std::string generate_output_yuv(std::string szPath, std::string szInputName);


void set_tile_dimensions(CONTEXT* ctx, RMuint32 tsw, RMuint32 tsh);
bool set_tile_dimensions(CONTEXT* ctx, std::string sChipId);

bool get_environment_string(const std::string sVarName, std::string& sValue);

#ifdef ENABLE_CURSES
void launch_viewer(CONTEXT* pCtx);
#endif

#endif

