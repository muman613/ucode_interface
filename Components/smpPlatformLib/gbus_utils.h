#ifndef __GBUS_UTILS_H__
#define __GBUS_UTILS_H__

#define ALLOW_OS_CODE
#include "rmdef/rmdef.h"
#include "remote_client/llad.h"
#include "remote_client/gbus.h"

namespace gbus_utils {
    RMuint32 gbus_time_delta(RMuint32 t1,RMuint32 t2);
    RMuint32 gbus_time_us(GBUS_PTR pgbus);
}

#endif // __GBUS_UTILS_H__

