#ifndef __GBUS_H__
#define __GBUS_H__

#include <string>
#include <vector>

#define ALLOW_OS_CODE
#include "rmdef/rmdef.h"

#if defined(_DEBUG) && defined(GBUS_LOGGER)
    #define ENABLE_GBUS_LOGGER
#endif // defined

/** Forward declarations */
class llad;

namespace rc_sockets {
    struct sock;
}

/**
 *  Gbus class encapsulates the gbus interface.
 */

class gbus {
public:
    gbus();
    gbus(LLAD_PTR pLlad);
    virtual ~gbus();

    bool            is_valid();

    bool            open(LLAD_PTR pLlad);
    void            close();

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

    const LLAD_PTR  get_llad();

#ifdef ENABLE_GBUS_LOGGER
    FILE*           gbus_log_getfp() const;
    void            gbus_log_mark(std::string sMessage);
    void            gbus_log_add_bp(RMuint32 bpAddress);
#endif // ENABLE_GBUS_LOGGER

protected:
    bool                valid;
    LLAD_PTR            pLlad;
    rc_sockets::sock*   sd;
    pthread_mutex_t     gbus_lock;

#ifdef ENABLE_GBUS_LOGGER
    void                    check_bp(RMuint32 address);
    FILE*                   gbusLogFp;
    std::vector<RMuint32>   gbusBPvec;
#endif // ENABLE_GBUS_LOGGER
};

#define GBUS_LOGGER_FILENAME "/tmp/gbuslog_te.txt"

/**
 *
 */

#if (__cplusplus >= 201103L)
typedef std::shared_ptr<gbus>   GBUS_PTR;
#else
typedef gbus*                   GBUS_PTR;
#endif


#endif // __GBUS_H__

