#ifndef __TARGETOPTIONSMANAGER_H__
#define __TARGETOPTIONSMANAGER_H__

#include <string>
#include <stdint.h>

typedef struct targetIFOptions {
    uint32_t        ifVersion;
    uint32_t        decoderDataSize;
    uint32_t        decoderContextSize;
    uint32_t        decodeErrorEntries;
    uint32_t        bitstreamFIFOSize;
    uint32_t        numPictures;
} TARGET_OPTIONS;

typedef struct targetIFOptionsReq {
    uint32_t*       ifVersion               = nullptr;
    uint32_t*       decoderDataSize         = nullptr;
    uint32_t*       decoderContextSize      = nullptr;
    uint32_t*       decodeErrorEntries      = nullptr;
    uint32_t*       bitstreamFIFOSize       = nullptr;
    uint32_t*       numPictures             = nullptr;
} TARGET_OPTIONS_REQ;


class targetOptionsManager
{
    public:
        targetOptionsManager();
        targetOptionsManager(const std::string& sConfigXmlPath);
        virtual ~targetOptionsManager();

        void                SetConfigXmlPath(const std::string& sConfigXmlPath);
        const std::string&  GetConfigXmlPath() const;

        bool                is_valid() const;

        bool                get_options(std::string sChip,
                                        TARGET_OPTIONS_REQ& req);
    protected:
        bool                m_bValid;
        std::string         m_sConfigXmlPath;

        bool                get_defaults();
        bool                get_chip_node(void* pNode, TARGET_OPTIONS& options);

    private:
        TARGET_OPTIONS      defaults;
};

#endif // __TARGETOPTIONSMANAGER_H__
