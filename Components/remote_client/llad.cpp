#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <inttypes.h>

#define ALLOW_OS_CODE

#include "sock.h"
#include "llad.h"
#include "llad_protocol.h"

/**
 *
 */

llad::llad()
:   valid(false),
    sd(0)
{
    // ctor
}

/**
 *
 */

llad::llad(const std::string& host)
:   valid(false),
    hostname(host),
    sd(0)
{
    valid = open();
}

/**
 *
 */

llad::~llad()
{
    // dtor
    if (valid == true)
        close();
}

/**
 *  Return whether the object was opened successfully.
 */

bool llad::is_valid()
{
    return valid;
}

/**
 *
 */

bool llad::open()
{
    bool bRes = false;

    if (!hostname.empty())
        bRes = open(hostname);

    return bRes;
}

bool llad::open(const std::string& host)
{
    bool        bRes = false;
    RMuint32    port = 0;
	RMuint32    uid = 0;

#ifdef  _DEBUG
    fprintf(stderr, "%s(%s)\n", __FUNCTION__, host.c_str());
#endif // _DEBUG

    if (!host.empty()) {
        std::size_t  pos;

        hostname = host;

        pos = hostname.find_first_of(':');

        if (pos != std::string::npos) {
            std::string sTarget;
            std::string sDevice;

            sTarget = hostname.substr(0, pos);
            sDevice = hostname.substr(pos + 1);

            device = strtol( sDevice.c_str(), NULL, 10);
#ifdef  _DEBUG
            fprintf(stderr, "sTarget = %s\n", sTarget.c_str());
            fprintf(stderr, "sDevice = %s\n", sDevice.c_str());
            fprintf(stderr, "device  = %ld\n", (long int)device);
#endif // _DEBUG

            port = SOCK_LLAD_PORT + device;

            sd = sock_connect( port, (RMascii*)sTarget.c_str() );
            if (sd == NULL) {
#ifdef _VERBOSE
                fprintf(stderr, __FILE__ ": Unable to open connection to %s\n", hostname.c_str());
#endif // _VERBOSE
                return false;
            }

            sock_write_uint32(sd, SOCK_LLAD_SERVICE);
            sock_write_uint32(sd, (RMuint32) getuid());
            if ((sock_read_uint32(sd, &uid) < 4) || (uid != (RMuint32) getuid())) {
                sock_close(sd);
#ifdef _VERBOSE
                fprintf(stderr, __FILE__ ": Connection refused, locked by user %" PRIu32 "\n", (unsigned int)uid);
#endif // _VERBOSE
                return false;
            }

            hostname = sTarget;
            bRes     = true;
        } else {

        }
    }

    return bRes;
}

/**
 *
 */

void llad::close()
{
#ifdef  _DEBUG
    fprintf(stderr, "%s()\n", __FUNCTION__);
#endif // _DEBUG

    if (sd != NULL) {
        sock_close( sd );
        sd = 0L;
    }
}

/**
 *
 */

void llad::get_config(RMascii* config_name, RMuint32 config_size)
{
	sock_write_uint32(sd, SOCK_LLAD_GET_CONFIG);
	sock_write_uint32(sd, config_size);
	sock_read_buf(sd, (RMuint8*)config_name, config_size);
}

/**
 *
 */

RMuint32 llad::get_open_count()
{
	RMuint32 count = 0;

	sock_write_uint32(sd, SOCK_LLAD_GET_OPEN_COUNT);
	sock_read_uint32(sd, &count);

	return count;
}


RMuint32 llad::lock()
{
	RMuint32 count = 0;

	sock_write_uint32(sd, SOCK_LLAD_LOCK);
	sock_read_uint32(sd, &count);

	return count;
}

void llad::unlock()
{
	sock_write_uint32(sd, SOCK_LLAD_UNLOCK);
}

