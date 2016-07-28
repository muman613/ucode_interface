#ifndef __LLAD_H__
#define __LLAD_H__

#include <string>

#define ALLOW_OS_CODE
#include "rmdef/rmdef.h"

#if (__cplusplus >= 201103L)
    #include <memory>
#endif

/** Forward declarations */
class gbus;
namespace rc_sockets {
    struct sock;
}

/**
 *  Class encapsulates the llad structure.
 */

class llad {
public:
	llad();
	llad(const std::string& host);
	virtual ~llad();

    bool            is_valid();

    bool            open();
    bool            open(const std::string& host);

    void            close();

    void            get_config(RMascii* config_name, RMuint32 config_size);
    RMuint32        get_open_count();

    RMuint32        lock();
    void            unlock();

//    RMuint32    wait_interrupt(RMuint32 mast, RMuint32* timeout_microsecond);
//    RMstatus    wait_channels(RMuint32* channel_array, RMuint32 channel_count, RMuint32 timeout);

    bool            get_host_device(std::string& sHost, RMuint32& nDevice);

protected:
    friend class    gbus;

    bool                valid;
    std::string         hostname;
    RMuint32            device;
    rc_sockets::sock*   sd;
};

#if (__cplusplus >= 201103L)
typedef std::shared_ptr<llad>   LLAD_PTR;
#else
typedef llad*                   LLAD_PTR;
#endif

#endif // __LLAD_H__
