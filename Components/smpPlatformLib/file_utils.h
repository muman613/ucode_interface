#ifndef __FILE_UTILS_H__
#define __FILE_UTILS_H__

namespace file_utils {
    RMstatus file_exists(std::string sFilename);
    RMstatus file_exists(const char* szFilename);

    bool can_write_file(std::string sFilename);
    bool can_write_file(const char* szFilename);
}

#endif // __FILE_UTILS_H__

