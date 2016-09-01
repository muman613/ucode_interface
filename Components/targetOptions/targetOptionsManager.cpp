#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <cstdlib>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include "dbgutils.h"

#include "targetOptionsManager.h"

typedef xmlNode *                               XML_NODE_PTR;
typedef std::string                             STRING;
typedef std::vector<XML_NODE_PTR>	    		XMLNODE_VECTOR;
typedef std::vector<XML_NODE_PTR>::iterator     XMLNODE_VECTOR_ITER;
typedef xmlDoc *                                XML_DOC_PTR;

extern void            print_element_names(XML_NODE_PTR a_node);
extern XML_NODE_PTR    find_child_node(XML_NODE_PTR, const STRING&, XMLNODE_VECTOR*);
extern bool            get_node_contents_string(XML_NODE_PTR, STRING&);
extern bool            get_node_attribute_string(XML_NODE_PTR pNode, STRING sAttr, STRING& sString);

targetOptionsManager::targetOptionsManager()
:   m_bValid(false)
{
    //ctor
    memset(&defaults, 0, sizeof(TARGET_OPTIONS));
}

targetOptionsManager::targetOptionsManager(const std::string& sConfigXmlPath)
:   m_bValid(false)
{
    //ctor
    memset(&defaults, 0, sizeof(TARGET_OPTIONS));
    SetConfigXmlPath(sConfigXmlPath);
}

targetOptionsManager::~targetOptionsManager()
{
    //dtor
}

bool targetOptionsManager::is_valid() const {
    return m_bValid;
}

void targetOptionsManager::SetConfigXmlPath(const std::string& sConfigXmlPath)
{
    m_sConfigXmlPath = sConfigXmlPath;
    m_bValid = get_defaults();
}

/**
 *
 */

bool targetOptionsManager::get_defaults()
{
    XML_NODE_PTR    pRootNode = nullptr;
    XML_NODE_PTR    pTmpNode  = nullptr;
    XML_DOC_PTR     pDocument = nullptr;
    bool            bRes      = false;

    D(debug("%s\n", __PRETTY_FUNCTION__));

    pDocument = xmlParseFile(m_sConfigXmlPath.c_str());
    if (pDocument != nullptr) {
        pRootNode = xmlDocGetRootElement( pDocument );

        if ((pRootNode != nullptr) &&
            (xmlStrcasecmp(pRootNode->name, BAD_CAST "targetOptions") == 0))
        {
            XML_NODE_PTR    pDefaults = nullptr;

            pDefaults = find_child_node(pRootNode, "defaults", nullptr);
            if (pDefaults != nullptr) {
                std::string sTmp;

                pTmpNode = find_child_node(pDefaults, "ifVersion", nullptr);
                if (pTmpNode != nullptr) {
                    get_node_contents_string(pTmpNode, sTmp);
                    defaults.ifVersion = std::stoi(sTmp);
                }

                pTmpNode = find_child_node(pDefaults, "decoderDataSize", nullptr);
                if (pTmpNode != nullptr) {
                    get_node_contents_string(pTmpNode, sTmp);
                    defaults.decoderDataSize = std::stoi(sTmp);
                }

                pTmpNode = find_child_node(pDefaults, "decoderContextSize", nullptr);
                if (pTmpNode != nullptr) {
                    get_node_contents_string(pTmpNode, sTmp);
                    defaults.decoderContextSize = std::stoi(sTmp);
                }

                pTmpNode = find_child_node(pDefaults, "decodeErrorEntries", nullptr);
                if (pTmpNode != nullptr) {
                    get_node_contents_string(pTmpNode, sTmp);
                    defaults.decodeErrorEntries = std::stoi(sTmp);
                }

                pTmpNode = find_child_node(pDefaults, "bitstreamFIFOSize", nullptr);
                if (pTmpNode != nullptr) {
                    get_node_contents_string(pTmpNode, sTmp);
                    defaults.bitstreamFIFOSize = std::stoi(sTmp);
                }

                pTmpNode = find_child_node(pDefaults, "numPictures", nullptr);
                if (pTmpNode != nullptr) {
                    get_node_contents_string(pTmpNode, sTmp);
                    defaults.numPictures = std::stoi(sTmp);
                }
            }
            bRes = true;
        }
        xmlFreeDoc(pDocument);
    }

    return bRes;
}

bool targetOptionsManager::get_options(std::string sChip,
                                     TARGET_OPTIONS_REQ& req)
{
    bool                bRes      = false;
    TARGET_OPTIONS      resOpts   = defaults;

    D(debug("%s(%s, refToOptions)\n", __PRETTY_FUNCTION__, sChip.c_str()));

    if (m_bValid == true) {
        XML_NODE_PTR        pRootNode = nullptr;
        XML_DOC_PTR         pDocument = nullptr;
        XMLNODE_VECTOR      nodeVec;

        pDocument = xmlParseFile(m_sConfigXmlPath.c_str());

        if (pDocument != nullptr) {
            pRootNode = xmlDocGetRootElement( pDocument );

            if ((pRootNode != nullptr) &&
                (xmlStrcasecmp(pRootNode->name, BAD_CAST "targetOptions") == 0))
            {
                find_child_node(pRootNode, "chip", &nodeVec);

                for (auto node : nodeVec) {
                    std::string sNodeChip;

                    if (get_node_attribute_string(node, "id", sNodeChip)) {
                        if (sChip == sNodeChip) {
                            get_chip_node(node, resOpts);
                            break;
                        }
                    }
                }

                if (req.ifVersion != nullptr)
                    *(req.ifVersion) = resOpts.ifVersion;

                if (req.decoderDataSize != nullptr)
                    *(req.decoderDataSize) = resOpts.decoderDataSize;

                if (req.decoderContextSize != nullptr)
                    *(req.decoderContextSize) = resOpts.decoderContextSize;

                if (req.decodeErrorEntries != nullptr)
                    *(req.decodeErrorEntries) = resOpts.decodeErrorEntries;

                if (req.bitstreamFIFOSize != nullptr)
                    *(req.bitstreamFIFOSize) = resOpts.bitstreamFIFOSize;

                if (req.numPictures != nullptr)
                    *(req.numPictures) = resOpts.numPictures;

                bRes = true;
            }
        }

        xmlFreeDoc(pDocument);
    }
    return bRes;
}

bool targetOptionsManager::get_chip_node(void* pNode, TARGET_OPTIONS& options) {
    XML_NODE_PTR    pChipNode = (XML_NODE_PTR)pNode;
    XML_NODE_PTR    pTmpNode;

    if (pChipNode != nullptr) {
        std::string sTmp;

        pTmpNode = find_child_node(pChipNode, "ifVersion", nullptr);
        if (pTmpNode != nullptr) {
            get_node_contents_string(pTmpNode, sTmp);
            options.ifVersion = std::stoi(sTmp);
        }

        pTmpNode = find_child_node(pChipNode, "decoderDataSize", nullptr);
        if (pTmpNode != nullptr) {
            get_node_contents_string(pTmpNode, sTmp);
            options.decoderDataSize = std::stoi(sTmp);
        }

        pTmpNode = find_child_node(pChipNode, "decoderContextSize", nullptr);
        if (pTmpNode != nullptr) {
            get_node_contents_string(pTmpNode, sTmp);
            options.decoderContextSize = std::stoi(sTmp);
        }

        pTmpNode = find_child_node(pChipNode, "decodeErrorEntries", nullptr);
        if (pTmpNode != nullptr) {
            get_node_contents_string(pTmpNode, sTmp);
            options.decodeErrorEntries = std::stoi(sTmp);
        }

        pTmpNode = find_child_node(pChipNode, "bitstreamFIFOSize", nullptr);
        if (pTmpNode != nullptr) {
            get_node_contents_string(pTmpNode, sTmp);
            options.bitstreamFIFOSize = std::stoi(sTmp);
        }

        pTmpNode = find_child_node(pChipNode, "numPictures", nullptr);
        if (pTmpNode != nullptr) {
            get_node_contents_string(pTmpNode, sTmp);
            options.numPictures = std::stoi(sTmp);
        }
    }

    return true;
}
