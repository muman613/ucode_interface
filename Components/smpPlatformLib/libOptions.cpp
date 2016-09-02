#include "libOptions.h"

/*! Global options */
libOptions      globalOptions;

libOptions::libOptions()
{
    //ctor
}

libOptions::~libOptions()
{
    //dtor
}

void libOptions::set_ucode_path(const std::string& sPath) {
    m_sUcodePath = sPath;
}

void libOptions::set_xml_path(const std::string& sPath) {
    m_sXmlPath = sPath;
}

std::string libOptions::get_ucode_path() const {
    return m_sUcodePath;
}

std::string libOptions::get_xml_path() const {
    return m_sXmlPath;
}
