#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__

#include <string>
#include <vector>

namespace string_utils {

bool split(std::string sMembers,
           const char sDelim,
           std::vector<std::string>& sVec);

}

#endif // __STRING_UTILS_H__

