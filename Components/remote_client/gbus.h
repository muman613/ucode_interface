#ifndef __GBUS_H__
#define __GBUS_H__

#include <string>
#include "rmdef/rmdef.h"
#include "rmdef/rmmacros_c.h"
#include "sock.h"
#include "llad.h"

class gbus {
public:
    gbus();
    gbus(llad* pLlad);
    virtual ~gbus();

    bool open(llad* pLlad);
    void close();

    RMuint8         gbus_read_uint8(RMuint32 byte_address);
    RMuint16        gbus_read_uint16(RMuint32 byte_address);
    RMuint32        gbus_read_uint32(RMuint32 byte_address);

    void            gbus_write_uint8(RMuint32 byte_address, RMuint8 data);
    void            gbus_write_uint16(RMuint32 byte_address, RMuint16 data);
    void            gbus_write_uint32(RMuint32 byte_address, RMuint32 data);

    void            gbus_read_data8(RMuint32 byte_address, RMuint8 *data, RMuint32 count);
    void            gbus_read_data16(RMuint32 byte_address, RMuint16 *data, RMuint32 count);
    void            gbus_read_data32(RMuint32 byte_address, RMuint32 *data, RMuint32 count);

    void            gbus_write_data8(RMuint32 byte_address, RMuint8 *data, RMuint32 count);
    void            gbus_write_data16(RMuint32 byte_address, RMuint16 *data, RMuint32 count);
    void            gbus_write_data32(RMuint32 byte_address, RMuint32 *data, RMuint32 count);
protected:
    bool            valid;
    llad*           pLlad;
    struct sock*    sd;
    pthread_mutex_t gbus_lock;
};

#endif // __GBUS_H__

