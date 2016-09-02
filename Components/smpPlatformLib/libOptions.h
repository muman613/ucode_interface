#ifndef __LIBOPTIONS_H__
#define __LIBOPTIONS_H__

#include <string>
#include <stdint.h>

#define         DEFAULT_UCODE_PATH      "../../../"
#define         DEFAULT_XML_PATH        "../../../xml/"

class libOptions
{
    public:
        libOptions();
        virtual ~libOptions();

        void            set_ucode_path(const std::string& sPath);
        void            set_xml_path(const std::string& sPath);

        std::string     get_ucode_path() const;
        std::string     get_xml_path() const;

    protected:
        std::string     m_sUcodePath        = DEFAULT_UCODE_PATH;
        std::string     m_sXmlPath          = DEFAULT_XML_PATH;

    private:
};

extern libOptions globalOptions;

#define     OPTION_UCODE_PATH       globalOptions.get_ucode_path()
#define     OPTION_XML_PATH         globalOptions.get_xml_path()


#endif // __LIBOPTIONS_H__
