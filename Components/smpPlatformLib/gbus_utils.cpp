#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <assert.h>

#include "gbus_utils.h"

#ifdef _DEBUG
#define LOCALDBG ENABLE
#else
#define LOCALDBG DISABLE
#endif // _DEBUG

namespace gbus_utils {

    static const RMuint32 REG_BASE_system_block = 0x00010000;
    static const RMuint32 SYS_xtal_in_cnt       = 0x0048;

    RMuint32 gbus_time_delta(RMuint32 t1,RMuint32 t2) {
#ifdef WITH_QUICKTURN
        // not very accurate (maybe wrong)
        return (t1<=t2)?(t2-t1):(0xffffffff-(t1-t2));
#else
        return (t1<=t2)?(t2-t1):(0xffffffff/XTAL_MHZ-(t1-t2));
#endif
    }

    /**
     *
     */

    RMuint32 gbus_time_us(GBUS_PTR pgbus) {
        RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));
#ifdef WITH_QUICKTURN
        return gbus_read_uint32(pgbus,REG_BASE_system_block+SYS_clk_cnt)*4;
#else
        return pgbus->gbus_read_uint32(REG_BASE_system_block+SYS_xtal_in_cnt)/XTAL_MHZ;
#endif
    }
}
