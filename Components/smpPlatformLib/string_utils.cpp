#include <iostream>
#include <regex>
#include <sstream>

using namespace std;

namespace string_utils {

    /**
     *  Split a string apart by delimeter returning an array of strings.
     */

    bool split(std::string sMembers,
               const char sDelim,
               std::vector<std::string>& sVec)
    {

        regex re("[\\.]");
        sregex_token_iterator it(sMembers.begin(), sMembers.end(), re, -1);
        sregex_token_iterator reg_end;

        for (; it != reg_end; ++it) {
             sVec.push_back ( *it );
        }

        return (sVec.size() > 0)?true:false;
    }

    bool caseInsensitiveStringCompare(const std::string& str1,
                                      const std::string& str2)
    {
        if (str1.size() != str2.size()) {
            return false;
        }

        for (string::const_iterator c1 = str1.begin(), c2 = str2.begin(); c1 != str1.end(); ++c1, ++c2) {
            if (tolower(*c1) != tolower(*c2)) {
                return false;
            }
        }

        return true;
    }

}
