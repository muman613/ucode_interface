#ifndef __PLATFORM_TARGET_H__
#define __PLATFORM_TARGET_H__

#include "PlatformTypes.h"
#include "PlatformTargetBase.h"

class PlatformChip;

#define TARGET_LITTLEENDIAN 0x0001
#define TARGET_BIGENDIAN    0x0002

/**
 *
 */

class PlatformTarget  : public Target  {
public:
    PlatformTarget(STRING name);
    virtual ~PlatformTarget();

    RMuint32            GetValue(const STRING& parameter);
    bool                SetValue(const STRING& parameter, RMuint32 value);
    std::list<STRING>   GetParameters();

	eSegType            GetSegmentType(RMuint32 address);
	STRING              GetSegmentName(RMuint32 address);
    STRING              GetAddressStr(unsigned int address,
                                      bool bNewAlias = false);
    RMuint32            GetAddressFromStr(STRING& addr,
                                          bool bNewAlias = false);

    int                 GetEndianess();
    int                 GetPtrSize();
    virtual void        Dump(FILE* ofp);

protected:
    STRING              m_targetName;
	ParameterMap        m_parameterMap;
};

#endif  // __PLATFORM_TARGET_H__
