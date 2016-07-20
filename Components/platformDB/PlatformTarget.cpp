//#include "StdAfx.h"
#if (defined(__WXGTK__) || defined(__WXMSW__))
#include <wx/wx.h>
#include <wx/debug.h>
#endif // __WXGTK__

#include "PlatformTypes.h"
#include "PlatformDebug.h"
#include "PlatformTarget.h"

#define DEFAULT_DRAMMAP 0x10000000

/**
 *  PlatformTarget constructor
 */

PlatformTarget::PlatformTarget(STRING name)
{
    // ctor
    D(debug("PlatformTarget::PlatformTarget(%s)\n", (const char*)name.c_str()));
    m_targetName = name;
}

/**
 *
 */

PlatformTarget::~PlatformTarget()
{
    // dtor
    D(debug("PlatformTarget::~PlatformTarget()\n"));
}

/**
 *
 */

RMuint32 PlatformTarget::GetValue(const STRING& parameter) {
    D(debug("PlatformTarget::GetValue(%s)\n", (const char*)parameter.c_str()));
    return m_parameterMap[parameter];
}

/**
 *
 */

bool PlatformTarget::SetValue(const STRING& parameter, RMuint32 value) {
    D(debug("PlatformTarget::SetValue(%s, 0x%08X)\n", (const char*)parameter.c_str(), value));
    m_parameterMap[parameter] = value;
    return true;
}

/**
 *
 */

std::list<STRING> PlatformTarget::GetParameters() {
    std::list<STRING>     resList;

//debug("PlatformTarget::GetParameters()\n");

    std::map<STRING, RMuint32>::iterator mIter;

    for (mIter = m_parameterMap.begin() ; mIter != m_parameterMap.end() ; mIter++) {
        resList.push_back((*mIter).first);
    }

    return resList;
}

/**
 *  Return segment type as an enumerated value.
 */

PlatformTarget::eSegType PlatformTarget::GetSegmentType(RMuint32 address) {
	eSegType	type = SEGMENT_UNKNOWN;

    D(debug("PlatformTarget::GetSegmentType(0x%08x)\n", address));

#ifdef DEBUG_SEGTYPE
    //wxLogDebug("PM map   %08X-%08X PM_size   %08X", get_pmBase(), get_pmBase() + get_pmSize(), get_pmSize());
    //wxLogDebug("DM map   %08X-%08X DM size   %08X", get_dmBase(), get_dmBase() + get_dmSize(), get_dmSize());
    //wxLogDebug("DRAM map %08X-%08X DRAM size %08X", get_dramBase(), get_dramBase() + get_dramSize(), get_dramSize());
#endif

	if ((address >= m_engine.get_dramBase()) && (address < (m_engine.get_dramBase() + m_engine.get_dramSize()))) {
		type = SEGMENT_DRAM;
        D(debug("-- SEGMENT_DRAM\n"));
	} else if ((address >= m_engine.get_dmBase()) && (address < (m_engine.get_dmBase() + m_engine.get_dmSize()))) {
		type = SEGMENT_DM;
        D(debug("-- SEGMENT_DM\n"));
	} else if ((address >= m_engine.get_pmBase()) && (address < (m_engine.get_pmBase() + m_engine.get_pmSize()))) {
        type = SEGMENT_PM;
        D(debug("-- SEGMENT_PM\n"));
    } else {
        D(debug("-- SEGMENT_UNKNOWN\n"));
    }

	return type;
}

/**
 *  Return the segment type as a string (PM/DM/DRAM/UNDEFINED)
 */

STRING PlatformTarget::GetSegmentName(RMuint32 address) {
    STRING sRes;

    switch (GetSegmentType(address)) {
    case SEGMENT_DRAM:
        sRes = "DRAM";
        break;
    case SEGMENT_DM:
        sRes = "DM";
        break;
    case SEGMENT_PM:
        sRes = "PM";
        break;
    case SEGMENT_UNKNOWN:
        sRes = "UNDEFINED";
        break;
    }

    return sRes;
}

/**
	Parse an aliased memory address into an absolute gbus address.
 */

unsigned int PlatformTarget::GetAddressFromStr(STRING& addr, bool bNewAlias) {
	unsigned int	result = (unsigned int)-1;
	unsigned long	tmp = 0, mod = 0;

    D(debug("PlatformTarget::GetAddressFromStr(%s)\n", (const char*)addr.c_str()));

	if (bNewAlias == true) {
		D(debug("-- using new alias system!\n"));

		if (addr.substr(0, 4) == "DRAM") {
	//        result = m_parameterMap["DRAM_map"];
			result = m_engine.get_dramBase(); // 0x800000;
			if (addr[4] == ':') {
				sscanf(addr.substr(5).c_str(), "0x%08lx", &tmp);
				result += tmp;
			}
		} else if (addr.substr(0,2) == "DM") {
			result = m_engine.get_dmBase();
			if (addr[2] == ':') {
				sscanf(addr.substr(3).c_str(), "0x%04lx", &tmp);
				result += tmp;
			}
		} else if (addr.substr(0,2) == "PM") {
			result =m_engine.get_pmBase();
			if (addr[2] == ':') {
				sscanf(addr.substr(3).c_str(), "0x%04lx", &tmp);
				result += tmp;
			}
		} else if (addr.substr(0,2) == "0x") {
			sscanf(addr.c_str(), "0x%08lx", &tmp);
			result = tmp;
		}
	} else {
		//wxLogDebug("-- using old alias system!");

		if (addr.substr(0, 4) == "DRAM") {
			if (addr[4] == ':') {
	//			result = dram_map;
				result = m_parameterMap["DRAM_map"];
				sscanf(addr.substr(5).c_str(), "0x%08lx", &tmp);
				result += tmp;
			}
		} else if (addr.substr(0,2) == "DM") {
			if (addr[2] == ':') {
				result = m_parameterMap["DM_map"];
				sscanf(addr.substr(3).c_str(), "0x%04lx:%ld", &tmp, &mod);
				result += (tmp * 4) + mod;
			}
		} else if (addr.substr(0,2) == "PM") {
			if (addr[2] == ':') {
				result = m_parameterMap["PM_map"];
				sscanf(addr.substr(3).c_str(), "0x%04lx:%ld", &tmp, &mod);
				result += (tmp * 2) + mod;
			}
		} else if (addr.substr(0,2) == "0x") {
			sscanf(addr.c_str(), "0x%08lx", &tmp);
			result = tmp;
		}
	}

	//wxLogDebug("Address %s resolved as %d", addr, result);

	return result;
}

/**
 * Return the endianess of the target.
 */

int PlatformTarget::GetEndianess() {
    return TARGET_BIGENDIAN;
}

/**
 * Return the size of a pointer on this target.
 */

int PlatformTarget::GetPtrSize() {
    return 4;
}

/**
 *
 */

STRING PlatformTarget::GetAddressStr(unsigned int address, bool bNewAlias) {
	char buffer[32];
//	bool bNewAlias = false;

//  wxLogDebug("PlatformTarget::GetAddressStr(%08x)", address);

	if (bNewAlias == true) {
		switch (GetSegmentType(address)) {
		case SEGMENT_DRAM:
			sprintf(buffer, "DRAM : 0x%08X",  address); //address - m_parameterMap["DRAM_map"]);
			break;
		case SEGMENT_DM:
			sprintf(buffer, "DM   : 0x%08X", address); // (address - m_parameterMap["DM_map"]) / 4, (address - m_parameterMap["DM_map"]) % 4);
			break;
		case SEGMENT_PM:
			sprintf(buffer, "PM   : 0x%08X", address); // (address - m_parameterMap["PM_map"]) / 2, (address - m_parameterMap["PM_map"]) % 2);
			break;
		case SEGMENT_UNKNOWN:
			sprintf(buffer, "???? : 0x%08X", (unsigned short)address);
			break;
		}
	} else {
		unsigned int dm_map, pm_map;
		dm_map = m_parameterMap["DM_map"];
		pm_map = m_parameterMap["PM_map"];

		switch (GetSegmentType(address)) {
		case SEGMENT_DRAM:
			//		sprintf(buffer, "DRAM:0x%08X", address - dram_map);
			sprintf(buffer, "DRAM:0x%08X", address);
			break;
		case SEGMENT_DM:
			sprintf(buffer, "DM:0x%06X:%d", (address - dm_map) / 4, (address - dm_map) % 4);
			break;
		case SEGMENT_PM:
			sprintf(buffer, "PM:0x%06X:%d", (address - pm_map) / 2, (address - pm_map) % 2);
			break;
		case SEGMENT_UNKNOWN:
			sprintf(buffer, "????:0x%06X", (unsigned short)address);
			break;
		}
	}

	return buffer;
}

///**
//	Return true if new memory aliases should be used.
// */
//bool PlatformTarget::use_new_alias() {
////	GUIPrefs*		pPrefs			= wxGetApp().get_ptr();
////	wxASSERT(pPrefs != 0L);
////	return pPrefs->m_bUseNewAlias;
//    return false;
//}

/**
 *  Dump target info.
 */

void PlatformTarget::Dump(FILE* ofp) {
    ParameterMapIter pIter;

#if (defined(__WXGTK__) || defined(__WXMSW__))
    wxFprintf(ofp, "Dump of PlatformTarget %s\n", m_targetName);

    for (pIter = m_parameterMap.begin() ; pIter != m_parameterMap.end() ; pIter++) {
        wxFprintf(ofp, "%s = %08x\n", (*pIter).first, (*pIter).second);
    }

    m_engine.Dump(ofp);
#else
    fprintf(ofp, "Dump of PlatformTarget %s\n", m_targetName.c_str());

    for (pIter = m_parameterMap.begin() ; pIter != m_parameterMap.end() ; pIter++) {
        fprintf(ofp, "%s = %08x\n", (*pIter).first.c_str(), (*pIter).second);
    }

    m_engine.Dump(ofp);
#endif // __WXGTK__

}
