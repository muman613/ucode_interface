#ifndef TARGET_HH
#define TARGET_HH

#include <stdio.h>
#include <list>
#include <string>

#include "PlatformTypes.h"
#include "PlatformBlock.h"
#include "PlatformEngine.h"
#include "PlatformDebug.h"

#define TARGET_LITTLEENDIAN 0x0001
#define TARGET_BIGENDIAN    0x0002

typedef std::map<string_t, RMuint32>            ParameterMap;
typedef std::map<string_t, RMuint32>::iterator  ParameterMapIter;


class Target
{
public:
    virtual ~Target() {}

    /**
     * Return the name of the target.
     */
    string_t GetName() {
        return m_targetName;
    }
    string_t GetBlock() {
        return m_block.get_block_name();
    }

	int dsp_engine() {
		return m_engine.get_engine_num();
	}

	enum eSegType {
		SEGMENT_PM,
		SEGMENT_DM,
		SEGMENT_DRAM,
		SEGMENT_UNKNOWN = -1,
	};

	virtual eSegType GetSegmentType(unsigned int address) = 0;
    virtual STRING   GetSegmentName(RMuint32 address) = 0;
    /**
     * Return the endianess of the target.
     */
    virtual int GetEndianess() = 0;
    /**
     * Return the size of a pointer on this target.
     */
    virtual int GetPtrSize() = 0;

    /**
     * Return a string which represents the specified address.
     */
    virtual string_t GetAddressStr(unsigned int address)
    {
        char buffer[16];
        sprintf(buffer, "0x%X", address);
        return buffer;
    }
	virtual unsigned int GetAddressFromStr(string_t& addr, bool bNewAlias = false) = 0;

    /**
     * Return a list of target properties.
     */
    virtual std::list<string_t> GetParameters() = 0;
    /**
     * Return the value of a parameter specific to 1 target.
     */
    virtual unsigned int GetValue(const string_t& parameter) = 0;
    /**
     * Return the default value of the given parameter.
     */
//    virtual unsigned int GetDefaultValue(const string_t& parameter) = 0;
    /**
     * Set a new value for the given parameter.
     * @return true  if the parameter has been successfully modified.
     */
    virtual bool SetValue(const string_t& parameter, unsigned int value) = 0;

	virtual int PM_WIDTH() {
		return 1;
	}
	virtual int DM_WIDTH() {
		return m_engine.get_dmWidth();
	}
	virtual int DRAM_WIDTH() {
		return 1;
	}

#ifdef __WXDEBUG__
    virtual void Dump(FILE* ofp) { }
#endif


    void SetEngine(const PlatformEngine& engine) {
        D(debug("PlatformTarget::SetEngine(...)\n"));
        m_engine = engine;
    }

    void SetBlock(const PlatformBlock& block) {
        D(debug("PlatformTarget::SetBlock(...)"));
        m_block = block;
    }

    wxUint32 get_ioBase() {
        return m_engine.get_ioBase();
    }

    wxUint32 get_pmBase() {
        return m_engine.get_pmBase();
    }
    wxUint32 get_pmSize() {
        return m_engine.get_pmSize();
    }
	wxUint32 get_pmWidth() {
		return m_engine.get_pmWidth();
	}
    wxUint32 get_dmBase() {
        return m_engine.get_dmBase();
    }
    wxUint32 get_dmSize() {
        return m_engine.get_dmSize();
    }
    wxUint32 get_dmWidth() {
        return m_engine.get_dmWidth();
    }

    wxUint32 get_dramBase() {
        return m_engine.get_dramBase();
    }

    wxUint32 get_dramSize() {
        return m_engine.get_dramSize();
    }
	wxUint32 get_dramWidth() {
		return m_engine.get_dramWidth();
	}

    wxUint32 get_resetReg() {
        return m_block.get_resetReg();
    }
//    wxUint32 get_hostintReg() {
//        return m_block.get_hostintReg();
//    }
    REG_PAIR_VECTOR& get_hostint_vector() {
        return m_block.get_hostint_vector();
    }
protected:
    STRING          m_targetName;
    //string_t        m_blockName;

    PlatformBlock   m_block;
	PlatformEngine  m_engine;
    //int             m_dspno;
};

#endif

/* End of target.hh */
