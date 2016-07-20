#include "libplatformdb.h"
#include <assert.h>
#include <algorithm>
#if (defined(__WXGTK__) || defined(__WXMSW__))
    #include <wx/filename.h>
	#include <wx/tokenzr.h>
#endif
#include "PlatformDatabase.h"
#include "xml_utils.h"

PlatformDatabase::PlatformDatabase()
:   m_bLoaded(false)
{
    //ctor
    D(debug("PlatformDatabase::PlatformDatabase()\n"));

//    init_hardware();
//    init_loaders();
}

/**
 *
 */

PlatformDatabase::~PlatformDatabase()
{
    //dtor
    D(debug("PlatformDatabase::~PlatformDatabase()\n"));
}

/**
 *
 */

size_t PlatformDatabase::get_chip_count() {
#if (defined(__WXGTK__) || defined(__WXMSW__))
    return m_chips.GetCount();
#else
    return m_chips.size();
#endif // __WXGTK__
}

/**
 *
 */

void PlatformDatabase::AddChip(PlatformChip& newChip)
{
//    D(debug("PlatformDatabase::AddChip()\n"));

#if (defined(__WXGTK__) || defined(__WXMSW__))
    m_chips.Add(newChip);
#else
    m_chips.push_back(newChip);
#endif
}

/**
 *
 */

PlatformChip PlatformDatabase::operator[](size_t index) {
#if (defined(__WXGTK__) || defined(__WXMSW__))
    return m_chips.Item(index);
#else
    return m_chips[index];
#endif
}

/**
 *
 */

PlatformChip PlatformDatabase::operator[](STRING& sChipID) {
    PlatformChip    chip;

#if (defined(__WXGTK__) || defined(__WXMSW__))
    for (size_t i = 0 ; i < m_chips.GetCount() ; i++) {
        chip = m_chips.Item(i);
        if (chip.get_chip_id() == sChipID) {
            return chip;
        }
    }
#else
    for (size_t i = 0 ; i < m_chips.size() ; i++) {
        chip = m_chips[i];
        if (chip.get_chip_id() == sChipID) {
            return chip;
        }
    }
#endif

    return chip;
}

/**
 *
 */

bool PlatformDatabase::FindChip(PlatformChip& which, STRING chip) {
    bool bRes = false;

   // D(debug("PlatformDatabase::FindChip(%s)\n", (const char*)chip.c_str()));

    for (size_t i = 0 ; i < get_chip_count(); i++) {
        PlatformChip    thisChip = m_chips[i];

        if (thisChip.get_chip_id() == chip) {
            which = m_chips[i];
            bRes = true;
            break;
        }
    }

    return bRes;
}

/**
 *
 */

bool PlatformDatabase::FindEngine(PlatformEngine& whichEngine,
                                  PlatformBlock& whichBlock,
                                  STRING chip,
                                  STRING block,
                                  int engine)
{
    bool bRes = false;

    //D(debug("PlatformDatabase::FindEngine(...,...,%s, %s, %d)\n",
    //            (const char*)chip.c_str(), (const char*)block.c_str(), engine));

    for (size_t i = 0 ; i < get_chip_count(); i++) {
        PlatformChip    thisChip = m_chips[i];

        if (thisChip.get_chip_id() == chip) {

//debug("-- found chip! Searching for block...\n");

            for (size_t j = 0 ; (!bRes && (j < thisChip.get_block_count())) ; j++) {
                PlatformBlock thisBlock = thisChip[j];

                if (thisBlock.get_block_name() == block) {
//debug("-- found block! Searching for engine...\n");

                    for (size_t k = 0 ; (!bRes && (k < thisBlock.get_engine_count())) ; k++) {
                        PlatformEngine thisEngine = thisBlock[k];

                        if (thisEngine.get_engine_num() == engine) {
                            whichEngine = thisEngine;
                            whichBlock  = thisBlock;
                            bRes        = true;
                            break;
                        }
                    }

                }
            }
        }
    }


    return bRes;
}

/**
 *
 */
#if 0
Target* PlatformDatabase::MakeNewTarget(STRING name, STRING chip, STRING block, int engine) {
    Target*         pTarget = 0L;
    wxUint32        pm_map, dm_map, pmdm_map, dram_map;
    wxUint32        pm_size, dm_size;
    PlatformEngine  whichEngine;
    PlatformBlock   whichBlock;


   // D(debug("PlatformDatabase::MakeNewTarget(%s)", (const char*)name.c_str()));

    pmdm_map = dram_map = 0L;

    if (FindEngine(whichEngine, whichBlock, chip, block, engine)) {
        pTarget = new PlatformTarget(name);
//      wxASSERT(pTarget != 0L);

        ((PlatformTarget*)pTarget)->SetBlock(whichBlock);
        ((PlatformTarget*)pTarget)->SetEngine(whichEngine);
//        ((PlatformTarget*)pTarget)->SetBlockName(block);
//        ((PlatformTarget*)pTarget)->SetDMWidth(whichEngine.get_dmWidth());

        pm_map   = whichEngine.get_pmBase();
        pm_size  = whichEngine.get_pmSize();
        pmdm_map = pm_map;
        dm_map   = whichEngine.get_dmBase();
        dm_size  = whichEngine.get_dmSize();
        dram_map = whichEngine.get_dramBase();

        pTarget->SetValue(string_t("PMDM_map"),    pmdm_map);
        pTarget->SetValue(string_t("PM_map"),      pm_map);
        pTarget->SetValue(string_t("PM_size"),     pm_size);

        pTarget->SetValue(string_t("DM_map"),      dm_map);
        pTarget->SetValue(string_t("DM_size"),     dm_size);

        pTarget->SetValue(string_t("DRAM_map"),    dram_map);
    }

    return pTarget;
}
#endif

/**
 *
 */

void PlatformDatabase::Dump(FILE* fOut) {
#if (defined(__WXGTK__) || defined(__WXMSW__))
    wxFprintf(fOut, "Dump of Platform Database:\n");

    if (m_chips.GetCount() > 0) {
        for (size_t i = 0 ; i < m_chips.GetCount() ; i++) {
            PlatformChip    chip;

            chip = m_chips.Item(i);
            //wxLogDebug("-- Chip [%s] --", chip.get_chip_id());

            wxFprintf(fOut, "-----------------------------------------\n");
            chip.Dump(fOut);
            wxFprintf(fOut, "-----------------------------------------\n");
        }
    } else {
        wxFprintf(fOut, "-- no chips defined!\n");
    }
#else
    fprintf(fOut,"Dump of Platform Database:\n");

    if (m_chips.size() > 0) {
        for (size_t i = 0 ; i < m_chips.size() ; i++) {
            PlatformChip chip = m_chips[i];

            fprintf(fOut, "-----------------------------------------\n");
            chip.Dump(fOut);
            fprintf(fOut, "-----------------------------------------\n");
        }
    } else {
        fprintf(fOut, "-- no chips defined!\n");
    }
#endif // __WXGTK__
}


#if (defined(__WXGTK__) || defined(__WXMSW__))
/**
 *  Load platform database from XML file.
 */

bool PlatformDatabase::LoadDatabase(STRING sDbFilename, STRING sInstallPath) {
    bool            bResult = false;
    wxXmlDocument   doc;
    XML_NODE*      pNode;
    wxFileName      sFName;
    STRING        sDbFullpath;

    D(debug("PlatformDatabase::LoadDatabase(%s)\n", (const char*)sDbFilename.c_str()));

    sFName = sDbFilename;

    if (sFName.FileExists()) {
        sDbFullpath = sDbFilename;
    } else {
        //STRING    sInstallPath = wxGetApp().get_exe_path();
        sDbFullpath = sInstallPath + sDbFilename;

        sFName = sDbFullpath;

        if (!sFName.FileExists()) {
            //wxLogDebug("ERROR: Unable to locate platform database!");
            return false;
        }
    }

    //wxLogDebug("OK - found platform database @ %s", sDbFullpath);

    if (doc.Load(sDbFullpath)) {
        ArrayOfNodes    targetNodeArray;

//debug("-- xml file opened!\n");
        pNode = doc.GetRoot();

        if (pNode->GetName() == "em86xxTargetConfig") {
            m_dbVersion = pNode->GetAttribute("version");

            //wxLogDebug("Database version # = %s", m_dbVersion);

            if (FindTags(wxT("target"), pNode, targetNodeArray)) {

//debug("found %d target nodes!\n", targetNodeArray.GetCount());

                for (size_t i = 0 ; i < targetNodeArray.GetCount() ; i++) {
                    ArrayOfNodes    blockNodeArray;
                    XML_NODE       tNode;
                    STRING          sChip;
                    STRING          sHWtype;
                    STRING          sName;
                    PlatformChip*   pNewChip;

                    tNode = targetNodeArray.Item(i);
#if wxCHECK_VERSION(2,9,5)
                    sChip   = tNode.GetAttribute( "id" );
                    sHWtype = tNode.GetAttribute( "type" );
                    sName   = tNode.GetAttribute( "name" );
#else
                    sChip   = tNode.GetPropVal(wxT("id"), wxT(""));
                    sHWtype = tNode.GetPropVal(wxT("type"), wxT(""));
                    sName   = tNode.GetPropVal(wxT("name", wxT("")));
#endif

                    pNewChip = new PlatformChip(sChip, sHWtype);

                    if (FindTags(wxT("block"), &tNode, blockNodeArray)) {
                        for (size_t j =0 ; j < blockNodeArray.GetCount() ; j++) {
                            ArrayOfNodes    engineArray;
                            XML_NODE       bNode;
                            XML_NODE       *pControlNode = 0;
                            STRING        sBlockName, sTmp;
                            PlatformBlock*  pNewBlock;
                            wxUint32        resetReg = 0;
                            REG_PAIR_VECTOR hostIntVec;

                            bNode = blockNodeArray.Item(j);
#if wxCHECK_VERSION(2,9,5)
                            sBlockName = bNode.GetAttribute( "name" );
#else
                            sBlockName = bNode.GetPropVal(wxT("name"), wxT(""));
#endif
//                            printf("blockname = %s\n", sBlockName.c_str());

                            /* Get the control registers */
                            pControlNode = FindTag("control", &bNode);
                            if (pControlNode) {
                                sTmp = pControlNode->GetAttribute("hostint");
                                parse_hostint_string(sTmp, hostIntVec);

                                sTmp = pControlNode->GetAttribute("reset");
                                sscanf((const char*)sTmp.c_str(), "0x%08x", &resetReg);
//                              wxFprintf(stderr, "HostInt @ 0x%08X resetReg @ 0x%08X\n",
//                                        hostintReg, resetReg);
                            }

                            //pNewBlock = new PlatformBlock(sBlockName, resetReg, hostintReg);
                            pNewBlock = new PlatformBlock(sBlockName, resetReg, hostIntVec);
                            wxASSERT(pNewBlock != 0);

                            if(FindTags(wxT("engine"), &bNode, engineArray)) {

                                for (size_t k=0 ; k < engineArray.GetCount() ; k++) {
                                    HandleEngineNode(pNewBlock, engineArray.Item(k));
                                }
                            }

                            pNewChip->AddBlock(*pNewBlock);
                            delete pNewBlock;
                        }
                    }

                    AddChip(*pNewChip);
                    delete pNewChip;
                }

                //wxLogDebug("There are %ld chips in database!", m_chips.GetCount());
                bResult = true;
            } else {
                //wxLogDebug("ERROR: Could not find any targets!");
            }
        } else {
            //wxLogDebug("ERROR: Not a platform database XML file!");
        }
    }

    m_bLoaded = bResult;

    return bResult;
}


/**
 *
 */

bool PlatformDatabase::HandleEngineNode(PlatformBlock* pBlock, XML_NODE& eNode) {
    XML_NODE       *mNode      = 0L;
    STRING        sTmp;
    long            engineNum;
    wxUint32        ioBase = 0xdeadbeef,
                    pmBase = 0xdeadbeef , pmSize = 0xdeadbeef, pmWidth = 0xdeadbeef,
                    dmBase = 0xdeadbeef, dmSize = 0xdeadbeef, dmWidth = 0xdeadbeef,
                    dramBase = 0xdeadbeef, dramSize = 0xdeadbeef, dramWidth = 0xdeadbeef;

#if wxCHECK_VERSION(2,9,5)
    sTmp = eNode.GetAttribute( "id" );
#else
    sTmp = eNode.GetPropVal(wxT("id"), wxT(""));
#endif
    sTmp.ToLong(&engineNum);

    mNode = eNode.GetChildren();

    while (mNode != 0L) {
        if (mNode->GetType() == wxXML_ELEMENT_NODE) {
            STRING mapName = mNode->GetName();

            mapName.MakeLower();

            if (mapName == "io_map") {
                sTmp = mNode->GetAttribute("base");
                sscanf(sTmp.c_str(), "0x%08x", &ioBase);
            } else if (mapName == "pm_map") {
                sTmp = mNode->GetAttribute("base");
                sscanf(sTmp.c_str(), "0x%08x", &pmBase);
                sTmp = mNode->GetAttribute("size");
                sscanf(sTmp.c_str(), "0x%08x", &pmSize);
				sTmp = mNode->GetAttribute("width");
				if (!sTmp.IsEmpty())
					sscanf(sTmp.c_str(), "0x%08x", &pmWidth);
				else
					pmWidth = 4;
            } else if (mapName == "dm_map") {
                sTmp = mNode->GetAttribute("base");
                sscanf(sTmp.c_str(), "0x%08x", &dmBase);
                sTmp = mNode->GetAttribute("size");
                sscanf(sTmp.c_str(), "0x%08x", &dmSize);
                sTmp = mNode->GetAttribute("width");
				if (!sTmp.IsEmpty())
					sscanf(sTmp.c_str(), "%d", &dmWidth);
				else
					dmWidth = 4;
            } else if (mapName == "dram_map") {
                sTmp = mNode->GetAttribute("base");
                sscanf(sTmp.c_str(), "0x%08x", &dramBase);
                sTmp = mNode->GetAttribute("size");
                sscanf(sTmp.c_str(), "0x%08x", &dramSize);
                sTmp = mNode->GetAttribute("width");
				if (!sTmp.IsEmpty())
					sscanf(sTmp.c_str(), "%d", &dramWidth);
				else
					dramWidth = 4;
            } else {
                wxFprintf(stderr, "ERROR: Unknown tag [%s]...\n", mapName);
            }

        }

        mNode = mNode->GetNext();
    }

//   wxFprintf(stderr, "Block %-10s Engine %ld : iobase = 0x%08X | pmBase = 0x%08X Size = 0x%08X | dmBase = 0x%08X Size = 0x%08X dmWidth = %d| dramBase = 0x%08X Size = 0x%08X\n",
//             pBlock->get_block_name(), engineNum, ioBase, pmBase, pmSize, dmBase, dmSize, dmWidth, dramBase, dramSize);

    PlatformEngine      newEngine(engineNum, ioBase,
								  pmBase, pmSize, pmWidth,
								  dmBase, dmSize, dmWidth,
								  dramBase, dramSize, dramWidth);
    pBlock->AddEngine(newEngine);

    return true;
}

#else   // __WXGTK__

bool PlatformDatabase::LoadDatabase(STRING sDbFilename, STRING sInstallPath) {
    bool            bResult = false;
    XML_DOC_PTR     pXmlDoc = 0L;
    XML_NODE_PTR    pRoot = 0L;
    XMLNODE_VECTOR  targetNodeArray;

    pXmlDoc = xmlParseFile( sDbFilename.c_str() );

    if (pXmlDoc != 0L) {
        pRoot = xmlDocGetRootElement( pXmlDoc );
        if ((pRoot != 0) && (xmlStrcasecmp(pRoot->name, BAD_CAST "em86xxTargetConfig") == 0)) {
            if (get_node_attribute_string( pRoot, "version", m_dbVersion)) {
                D(debug("Found XML file version %s\n", m_dbVersion.c_str()));
			}
            if (find_child_node(pRoot, "target", &targetNodeArray) != 0) {
                D(debug("Found %ld nodes...\n", targetNodeArray.size()));

                for (size_t i = 0 ; i < targetNodeArray.size() ; i++) {
                    PlatformChip*   pNewChip = 0L;
                    XMLNODE_VECTOR  blockNodeArray;
                    XML_NODE_PTR    tNode = targetNodeArray[i];
                    XML_NODE_PTR    pControlNode = 0L;
                    STRING          sChip, sType, sBlockName, sName, sTmp;

                    if (get_node_attribute_string(tNode, "id", sChip) &&
                        get_node_attribute_string(tNode, "type", sType))
                    {
                        get_node_attribute_string(tNode, "name", sName);

                        D(debug("Chip %s %s %s\n", sChip.c_str(), sType.c_str(), sName.c_str()));

                        pNewChip = new PlatformChip( sChip, sType, sName );
                        assert(pNewChip != 0L);

                        if (find_child_node( tNode, "block", &blockNodeArray) != 0) {
                            REG_PAIR_VECTOR hostIntVec;
                            wxUint32        resetReg = 0L;
                            PlatformBlock*  pNewBlock = 0L;

//                          D(debug("Found %ld block nodes!\n", blockNodeArray.size()));

                            for (size_t j = 0 ; j < blockNodeArray.size() ; j++) {
                                XMLNODE_VECTOR  engineNodeArray;
                                XML_NODE_PTR    bNode = blockNodeArray[j];

                                if (get_node_attribute_string( bNode, "name", sBlockName )) {
//                                  D(debug("Block %s\n", sBlockName.c_str()));

                                    pControlNode = find_child_node( bNode, "control", 0L);
                                    if (pControlNode != 0) {
                                        get_node_attribute_string(pControlNode, "hostint", sTmp);
//                                      D(debug("Host Int @ %s...\n", sTmp.c_str()));
                                        parse_hostint_string(sTmp, hostIntVec);
                                        get_node_attribute_string(pControlNode, "reset", sTmp);
//                                      D(debug("Reset @ %s...\n", sTmp.c_str()));
                                        sscanf(sTmp.c_str(), "0x%08x", &resetReg);
                                    }
                                }

                                pNewBlock = new PlatformBlock( sBlockName, resetReg, hostIntVec );
                                assert(pNewBlock != 0L);

                                if (find_child_node( bNode, "engine",
                                                     &engineNodeArray) != 0)
                                {
//                                  D(debug("-- found %ld engines!\n", engineNodeArray.size()));
                                    for (size_t k = 0 ; k < engineNodeArray.size() ; k++) {
                                        HandleEngineNode( pNewBlock, engineNodeArray[k]);
                                    }
                                }

                                pNewChip->AddBlock(*pNewBlock);
                                delete pNewBlock;
                            }
                        }
                        AddChip(*pNewChip);
                        delete pNewChip;
                    }
                }
                bResult = true;
            }
        }
        xmlFreeDoc( pXmlDoc );
        bResult = true;
    }

    return bResult;
}

bool PlatformDatabase::HandleEngineNode(PlatformBlock* pBlock, XML_NODE_PTR pNode)
{
    XML_NODE        *mNode      = 0L;
    STRING          sTmp;
    long            engineNum;
    wxUint32        ioBase = 0xdeadbeef,
                    pmBase = 0xdeadbeef , pmSize = 0xdeadbeef, pmWidth = 0xdeadbeef,
                    dmBase = 0xdeadbeef, dmSize = 0xdeadbeef, dmWidth = 0xdeadbeef,
                    dramBase = 0xdeadbeef, dramSize = 0xdeadbeef, dramWidth = 0xdeadbeef;

    get_node_attribute_string(pNode, "id", sTmp);
    sscanf( sTmp.c_str(), "%ld", &engineNum);

    mNode = pNode->children;

    while (mNode != 0L) {
        if (mNode->type == XML_ELEMENT_NODE) {
            STRING mapName = (const char*)mNode->name;

            std::transform(mapName.begin(), mapName.end(), mapName.begin(), ::tolower);

            if (mapName == "io_map") {
                if (get_node_attribute_string(mNode, "base", sTmp)) {
                    sscanf(sTmp.c_str(), "0x%08x", &ioBase);
                }
            } else if (mapName == "pm_map") {
                if (get_node_attribute_string(mNode, "base", sTmp)) {
                    sscanf(sTmp.c_str(), "0x%08x", &pmBase);
                }
                if (get_node_attribute_string(mNode, "size", sTmp)) {
                    sscanf(sTmp.c_str(), "0x%08x", &pmSize);
                }
                if (get_node_attribute_string(mNode, "width", sTmp)) {
                    sscanf(sTmp.c_str(), "%d", &pmWidth);
                } else {
                    pmWidth = 4;
                }
            } else if (mapName == "dm_map") {
                if (get_node_attribute_string(mNode, "base", sTmp)) {
                    sscanf(sTmp.c_str(), "0x%08x", &dmBase);
                }
                if (get_node_attribute_string(mNode, "size", sTmp)) {
                    sscanf(sTmp.c_str(), "0x%08x", &dmSize);
                }
                if (get_node_attribute_string(mNode, "width", sTmp)) {
                    sscanf(sTmp.c_str(), "%d", &dmWidth);
                } else {
                    dmWidth = 4;
                }
            } else if (mapName == "dram_map") {
                if (get_node_attribute_string(mNode, "base", sTmp)) {
                    sscanf(sTmp.c_str(), "0x%08x", &dramBase);
                }
                if (get_node_attribute_string(mNode, "size", sTmp)) {
                    sscanf(sTmp.c_str(), "0x%08x", &dramSize);
                }
                if (get_node_attribute_string(mNode, "width", sTmp)) {
                    sscanf(sTmp.c_str(), "%d", &dramWidth);
                } else {
                    dramWidth = 4;
                }
            } else {
#ifdef	_DEBUG
				fprintf(stderr, "ERROR: Unknown tag [%s]...\n", mapName.c_str());
#endif
            }
        }

        mNode = mNode->next;
    }

    PlatformEngine      newEngine(engineNum, ioBase,
								  pmBase, pmSize, pmWidth,
								  dmBase, dmSize, dmWidth,
								  dramBase, dramSize, dramWidth);
    pBlock->AddEngine(newEngine);

    return true;
}

#endif


bool PlatformDatabase::parse_hostint_string(STRING hostIntStr, REG_PAIR_VECTOR& regVec) {
    bool                bRes = false;
#if (defined(__WXGTK__) || defined(__WXMSW__))
    wxStringTokenizer   tokenizer;

#ifdef  VERBOS_UTILS
    wxLogDebug("parse_hostint_string(%s, ...)", hostIntStr);
#endif

    regVec.clear();

    tokenizer.SetString( hostIntStr, ";" );

#ifdef  VERBOSE_UTILS
    wxLogDebug("-- found %ld tokens!", tokenizer.CountTokens());
#endif

    while (tokenizer.HasMoreTokens()) {
        wxArrayString   sItem;
        wxString        sToken = tokenizer.GetNextToken();

#ifdef  VERBOSE_UTILS
        wxLogDebug("token = %s", sToken);
#endif

        sItem = ::wxStringTokenize( sToken, "=" );

        if (sItem.Count() == 2) {
            long        address, value;
            REG_PAIR    regPair;

            sItem[0].ToLong(&address, 16);
            sItem[1].ToLong(&value, 16);

#ifdef  VERBOSE_UTILS
            wxLogDebug("Address 0x%08lX Value 0x%08lX", address, value);
#endif

            regPair.first  = (wxUint32)address;
            regPair.second = (wxUint32)value;

            regVec.push_back(regPair);
        } else {
            wxLogDebug("ERROR: Invalid format for host interrupt definition!");
        }
    }

    bRes = !regVec.empty();
#else
    char *str = (char *)hostIntStr.c_str();
    char *saveptr1 = 0L, *saveptr2 = 0;
    char *token = 0L;

#ifdef  VERBOS_UTILS
    D(debug("parse_hostint_string(%s, ...)", hostIntStr.c_str()));
#endif // VERBOS_UTILS

    regVec.clear();

#ifdef _WIN32
    while ((token = strtok_s(str, ";", &saveptr1)) != 0) {
#else
    while ((token = strtok_r(str, ";", &saveptr1)) != 0) {
#endif
        char *      token2  = 0L;
        char *      str2    = token;
        int         j       = 0;
        wxUint32    address = 0,
                    value   = 0;

#ifdef  VERBOS_UTILS
        D(debug("token = %s\n", token));
#endif // VERBOS_UTILS

#ifdef  _WIN32
        while ((token2 = strtok_s(str2, "=", &saveptr2)) != 0) {
#else
        while ((token2 = strtok_r(str2, "=", &saveptr2)) != 0) {
#endif  // _WIN32

            //D(debug("Component %s\n", token2));

            switch (j) {
            case 0:
                sscanf(token2, "0x%08x", &address);
                break;
            case 1:
                sscanf(token2, "0x%08x", &value);
                break;
            default:
#ifdef	_DEBUG
				fprintf(stderr, "ERROR: Invalid host interrupt string!\n");
#endif
				//                D(debug("ERROR: Invalid host interrupt string!\n"));
                break;
            }
            str2 = 0L;
            j++;
        }
        if (j == 2) {
            REG_PAIR    regPair;

            regPair.first = address;
            regPair.second = value;

#ifdef  VERBOSE_UTILS
            D(debug("Address 0x%08lX Value 0x%08lX", address, value));
#endif

            regVec.push_back( regPair );
        }
        str = 0L;
    }

    bRes = !regVec.empty();
#endif // __WXGTK__

    return bRes;
}


bool PlatformDatabase::GetChipNames(STRING_VECTOR& sVec)
{
//	bool bRes = false;

	for (size_t i = 0 ; i < m_chips.size() ; i++) {
		STRING sChipName = m_chips[i].get_chip_id();
		sVec.push_back( sChipName );
	}

	return ((sVec.size() > 0)?true:false);
}
