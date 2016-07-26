#ifndef __LLAD_H__
#define __LLAD_H__

#include <string>
#include "rmdef/rmdef.h"
#include "sock.h"

class gbus;

class llad {
public:
	llad();
	llad(const std::string& host);
	virtual ~llad();

    bool        open();
    bool        open(const std::string& host);

    void        close();

    void        get_config(RMascii* config_name, RMuint32 config_size);
    RMuint32    get_open_count();

    RMuint32    lock();
    void        unlock();

//    RMuint32    wait_interrupt(RMuint32 mast, RMuint32* timeout_microsecond);
//    RMstatus    wait_channels(RMuint32* channel_array, RMuint32 channel_count, RMuint32 timeout);

protected:
    friend class gbus;

    std::string     hostname;
    struct sock*    sd;
    RMuint32        device;
};


#endif // __LLAD_H__
