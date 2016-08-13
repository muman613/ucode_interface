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
}
