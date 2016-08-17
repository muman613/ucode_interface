#ifndef __STRING_UTILS_H__
#define __STRING_UTILS_H__

#include <string>
#include <vector>

namespace string_utils {

bool split(std::string sMembers,
           const char sDelim,
           std::vector<std::string>& sVec);
bool caseInsensitiveStringCompare(const std::string& str1,
                                  const std::string& str2);
}

#endif // __STRING_UTILS_H__

