#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <inttypes.h>
#include "sock.h"
#include "llad.h"
#include "gbus.h"
#include "rmdef/rmmacros_c.h"
#include "llad_protocol.h"

#if 0
#define LOCALDBG     ENABLE
#else
#define LOCALDBG     DISABLE
#endif // 0

using namespace rc_sockets;

/**
 *
 */

gbus::gbus()
:   valid(false),
    pLlad(0),
    sd(0)
{
    // ctor
#ifdef ENABLE_GBUS_LOGGER
    gbusLogFp = fopen(GBUS_LOGGER_FILENAME, "w");
//  fprintf(gbusLogFp, "gbus_open()\n");
#endif // ENABLE_GBUS_LOGGER
}

/**
 *
 */

gbus::gbus(LLAD_PTR llad)
:   valid(false),
    pLlad(0),
    sd(0)
{
#ifdef ENABLE_GBUS_LOGGER
    gbusLogFp = fopen(GBUS_LOGGER_FILENAME, "w");
//  fprintf(gbusLogFp, "gbus_open()\n");
#endif // ENABLE_GBUS_LOGGER
    valid = open(llad);
}

/**
 *
 */

gbus::~gbus()
{
    // dtor
    close();
#ifdef ENABLE_GBUS_LOGGER
//  fprintf(gbusLogFp, "gbus_close()\n");
    fclose(gbusLogFp);
    gbusLogFp = 0L;
#endif // ENABLE_GBUS_LOGGER
}

/**
 *
 */

bool gbus::is_valid()
{
    return valid;
}

const LLAD_PTR  gbus::get_llad()
{
    return pLlad;
}

/**
 *  Open connection to remote gbus server.
 */

bool gbus::open(LLAD_PTR llad)
{
	RMuint16 port = 0;

    RMDBGLOG((LOCALDBG, "%s(%p)\n", __PRETTY_FUNCTION__, llad.get()));

    pLlad = llad;

    port = SOCK_LLAD_PORT + (RMuint16)pLlad->device;
    sd = sock_connect(port, (RMascii*)pLlad->hostname.c_str());
    if (sd == NULL) {
#ifdef  _VERBOSE
		fprintf(stderr, __FILE__ ": Unable to open connection to %s:%lu\n",
                pLlad->hostname.c_str(), pLlad->device);
#endif // _VERBOSE
        return false;
    }

    pthread_mutex_init(&gbus_lock, NULL);

	sock_write_uint32(sd, SOCK_GBUS_SERVICE);

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_open()\n");
#endif // ENABLE_GBUS_LOGGER

	valid = true;

    return valid;
}

/**
 *  Close the gbus connection.
 */

void gbus::close()
{
    RMDBGLOG((LOCALDBG, "%s()\n", __PRETTY_FUNCTION__));

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_close()\n");
#endif // ENABLE_GBUS_LOGGER

    if (valid == true) {
		sock_close(sd);
		sd = 0L;
		pthread_mutex_destroy(&gbus_lock);
		pLlad.reset();
        valid = false;
    }

    return;
}

/**
 *  Read 8-bit unsigned value from byte_address.
 */

RMuint8 gbus::gbus_read_uint8(RMuint32 byte_address)
{
	RMuint32 val;

	pthread_mutex_lock(&gbus_lock);

	sock_write_2_uint32(sd, SOCK_GBUS_READ_UINT8, byte_address);

	if (sock_read_uint32(sd, &val) < 4)
		RMPanic(RM_ERROR);

	RMDBGLOG((LOCALDBG, "%s(0x%lx) = 0x%x\n", __PRETTY_FUNCTION__, byte_address, val));

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_read_uint8(0x%08X) = 0x%02X\n", byte_address, val);
    check_bp(byte_address);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(&gbus_lock);
	return (RMuint8) val;
}

/**
 *  Read 16-bit unsigned value from byte_address.
 */

RMuint16 gbus::gbus_read_uint16(RMuint32 byte_address)
{
	RMuint32 val;

	pthread_mutex_lock(&gbus_lock);

	sock_write_2_uint32(sd, SOCK_GBUS_READ_UINT16, byte_address);

	if (sock_read_uint32(sd, &val) < 4)
		RMPanic(RM_ERROR);

	RMDBGLOG((LOCALDBG, "%s(0x%lx) = 0x%x\n", __PRETTY_FUNCTION__, byte_address, val));

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_read_uint16(0x%08X) = 0x%04X\n", byte_address, val);
    check_bp(byte_address);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(&gbus_lock);
	return (RMuint16) val;
}

/**
 *  Read 32-bit unsigned value from byte_address.
 */

RMuint32 gbus::gbus_read_uint32(RMuint32 byte_address)
{
	RMuint32 val;

	pthread_mutex_lock(&gbus_lock);

	sock_write_2_uint32(sd, SOCK_GBUS_READ_UINT32, byte_address);
	if (sock_read_uint32(sd, &val) < 4)
		RMPanic(RM_ERROR);

	RMDBGLOG((LOCALDBG, "%s(0x%lx) = 0x%x\n", __PRETTY_FUNCTION__, byte_address, val));

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_read_uint32(0x%08X) = 0x%08X\n", byte_address, val);
    check_bp(byte_address);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(&gbus_lock);
	return (RMuint32) val;
}

/**
 *
 */

void gbus::gbus_write_uint8(RMuint32 byte_address, RMuint8 data)
{
    pthread_mutex_lock(&gbus_lock);
	RMDBGLOG((LOCALDBG, "%s(0x%lx, %u=0x%x)\n", __PRETTY_FUNCTION__, byte_address, data, data));

	sock_write_3_uint32(sd, SOCK_GBUS_WRITE_UINT8, byte_address, data);

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_write_uint8(0x%08X, 0x%02x)\n", byte_address, data);
    check_bp(byte_address);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(&gbus_lock);
}

/**
 *
 */

void gbus::gbus_write_uint16(RMuint32 byte_address, RMuint16 data)
{
    pthread_mutex_lock(&gbus_lock);
	RMDBGLOG((LOCALDBG, "%s(0x%lx, %u=0x%x)\n", __PRETTY_FUNCTION__, byte_address, data, data));

	sock_write_3_uint32(sd, SOCK_GBUS_WRITE_UINT16, byte_address, data);

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_write_uint16(0x%08X, 0x%04x)\n", byte_address, data);
    check_bp(byte_address);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(&gbus_lock);
}

/**
 *
 */

void gbus::gbus_write_uint32(RMuint32 byte_address, RMuint32 data)
{
	pthread_mutex_lock(&gbus_lock);
	RMDBGLOG((LOCALDBG, "%s(0x%lx, %lu=0x%lx)\n", __PRETTY_FUNCTION__, byte_address, data, data));

	sock_write_3_uint32(sd, SOCK_GBUS_WRITE_UINT32, byte_address, data);

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_write_uint32(0x%08X, 0x%08x)\n", byte_address, data);
    check_bp(byte_address);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(&gbus_lock);
}

/**
 *
 */

void gbus::gbus_read_data8(RMuint32 byte_address, RMuint8 *data, RMuint32 count)
{
	pthread_mutex_lock(&gbus_lock);
	RMDBGLOG((LOCALDBG, "%s(0x%lx)\n", __PRETTY_FUNCTION__, byte_address));

	sock_write_3_uint32(sd, SOCK_GBUS_READ_DATA8, byte_address, count);
	if (sock_read_buf(sd, (RMuint8 *) data, count * sizeof(RMuint8)) < (RMint32) (count * sizeof(RMuint8)))
		RMPanic(RM_ERROR);

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_read_data8(0x%08X, %d)\n", byte_address, count);
    check_bp(byte_address);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(&gbus_lock);
}

/**
 *
 */

void gbus::gbus_read_data16(RMuint32 byte_address, RMuint16 *data, RMuint32 count)
{
	RMuint32 i;
	pthread_mutex_lock(&gbus_lock);

	RMDBGLOG((LOCALDBG, "%s(0x%lx, %p, %lu)\n", __PRETTY_FUNCTION__, byte_address, data, count));

	sock_write_3_uint32(sd, SOCK_GBUS_READ_DATA16, byte_address, count);
	if (sock_read_buf(sd, (RMuint8 *)data, count * sizeof(RMuint16)) < (RMint32) (count * sizeof(RMuint16)))
 		RMPanic(RM_ERROR);

	for (i=0 ; i<count ; i++) {
		data[i] = RMbeBufToUint16((RMuint8 *) (data + i));
	}

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_read_data16(0x%08X, %d)\n", byte_address, count);
    check_bp(byte_address);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(&gbus_lock);
}

/**
 *
 */

void gbus::gbus_read_data32(RMuint32 byte_address, RMuint32 *data, RMuint32 count)
{
	RMuint32 i;
	RMint32 Read;
	RMint32 SizeToRead;

	pthread_mutex_lock(&gbus_lock);

	RMDBGLOG((LOCALDBG, "%s(0x%lx, %p, %lu)\n", __PRETTY_FUNCTION__, byte_address, data, count));

	sock_write_3_uint32(sd, SOCK_GBUS_READ_DATA32, byte_address, count);

	SizeToRead = count * sizeof(RMuint32);

	i = 0;
	while (i < 10) {
		Read = sock_read_buf(sd, (RMuint8 *) data, SizeToRead);
		if (Read < 0) {
			RMDBGLOG((ENABLE, "retry\n"));
			RMPanic(RM_ERROR);
		}

		if (Read == SizeToRead)
			break;

		i++;
	}

	for (i=0 ; i<count ; i++) {
		data[i] = RMbeBufToUint32((RMuint8 *) (data + i));
	}

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_read_data32(0x%08X, %d)\n", byte_address, count);
    check_bp(byte_address);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(&gbus_lock);
}

/**
 *
 */

void gbus::gbus_write_data8(RMuint32 byte_address, RMuint8 *data, RMuint32 count)
{
	pthread_mutex_lock(&gbus_lock);
	RMDBGLOG((LOCALDBG, "%s(0x%lx, %p, %lu)\n", __PRETTY_FUNCTION__, byte_address, data, count));

	sock_write_3_uint32(sd, SOCK_GBUS_WRITE_DATA8, byte_address, count);
	if (sock_write_buf(sd, (RMuint8 *)data, count * sizeof(RMuint8)) < (RMint32) (count * sizeof(RMuint8)))
		RMPanic(RM_ERROR);

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_write_data8(0x%08X, %d)\n", byte_address, count);
    check_bp(byte_address);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(&gbus_lock);
}

/**
 *
 */

void gbus::gbus_write_data16(RMuint32 byte_address, RMuint16 *data, RMuint32 count)
{
	RMuint32 i;
	RMuint16 *non_const_data = (RMuint16 *) data;

	pthread_mutex_lock(&gbus_lock);

	RMDBGLOG((LOCALDBG, "%s(0x%lx, %p, %lu)\n", __PRETTY_FUNCTION__, byte_address, data, count));

	sock_write_3_uint32(sd, SOCK_GBUS_WRITE_DATA16, byte_address, count);

	for (i=0 ; i<count ; i++)
		RMuint16ToBeBuf(non_const_data[i], (RMuint8 *) (non_const_data + i));

	if (sock_write_buf(sd, (RMuint8 *)non_const_data, count * sizeof(RMuint16)) < (RMint32) (count * sizeof(RMuint16)))
		RMPanic(RM_ERROR);

	for (i=0 ; i<count ; i++)
		non_const_data[i] = RMbeBufToUint16((RMuint8 *) (non_const_data + i));

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_write_data16(0x%08X, %d)\n", byte_address, count);
    check_bp(byte_address);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(&gbus_lock);
}

/**
 *
 */

void gbus::gbus_write_data32(RMuint32 byte_address, RMuint32 *data, RMuint32 count)
{
	RMuint32 i;
	RMuint32 *non_const_data = (RMuint32 *) data;

	pthread_mutex_lock(&gbus_lock);

	RMDBGLOG((LOCALDBG, "%s(%0x%lx, %p, %lu)\n", __PRETTY_FUNCTION__, byte_address, data, count));

	sock_write_3_uint32(sd, SOCK_GBUS_WRITE_DATA32, byte_address, count);

	for (i=0 ; i<count ; i++)
		RMuint32ToBeBuf(non_const_data[i], (RMuint8 *) (non_const_data + i));

	if (sock_write_buf(sd, (RMuint8 *) non_const_data, count * sizeof(RMuint32)) < (RMint32) (count * sizeof(RMuint32)))
		RMPanic(RM_ERROR);

	for (i=0 ; i<count ; i++)
		non_const_data[i] = RMbeBufToUint32((RMuint8 *) (non_const_data + i));

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_write_data32(0x%08X, %d)\n", byte_address, count);
    check_bp(byte_address);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(&gbus_lock);
}

#ifdef ENABLE_GBUS_LOGGER

FILE* gbus::gbus_log_getfp() const {
    return gbusLogFp;
}

/**
 *  Display a marker in the gbus log...
 */

void  gbus::gbus_log_mark(std::string sMessage) {
	pthread_mutex_lock(&gbus_lock);
    fprintf(gbusLogFp, "%s", "----");
    fprintf(gbusLogFp, "%s", sMessage.c_str());
    std::string sLines( 80 - 4 - sMessage.length(), '-');
    fprintf(gbusLogFp, "%s\n", sLines.c_str());
	pthread_mutex_unlock(&gbus_lock);

    return;
}

void  gbus::gbus_log_add_bp(RMuint32 bpAddress) {
    RMDBGLOG((LOCALDBG, "%s(0x%08X)", __PRETTY_FUNCTION__, bpAddress));
    gbusBPvec.push_back(bpAddress);
}

#define BREAKPOINT	__asm__("int $3")

void gbus::check_bp(RMuint32 address) {
    for (size_t i = 0 ; i < gbusBPvec.size() ; i++) {
        if (gbusBPvec[i] == address) {
            BREAKPOINT;
        }
    }

    return;
}
#endif // ENABLE_GBUS_LOGGER
