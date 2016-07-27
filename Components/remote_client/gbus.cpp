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
}

/**
 *
 */

gbus::gbus(LLAD_PTR llad)
:   valid(false),
    pLlad(0),
    sd(0)
{
    valid = open(llad);
}

/**
 *
 */

gbus::~gbus()
{
    // dtor
}

/**
 *
 */

bool gbus::is_valid()
{
    return valid;
}

/**
 *
 */

bool gbus::open(LLAD_PTR llad)
{
	RMuint16 port = 0;

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

	valid = true;

    return valid;
}

/**
 *
 */

void gbus::close()
{
    if (valid == true) {
		sock_close(sd);
		sd = 0L;
		pthread_mutex_destroy(&gbus_lock);
        valid = false;
    }

    return;
}

/**
 *
 */

RMuint8 gbus::gbus_read_uint8(RMuint32 byte_address)
{
	RMuint32 val;

	pthread_mutex_lock(&gbus_lock);

	sock_write_2_uint32(sd, SOCK_GBUS_READ_UINT8, byte_address);

	if (sock_read_uint32(sd, &val) < 4)
		RMPanic(RM_ERROR);

	RMDBGLOG((LOCALDBG, "%s(0x%lx) = 0x%x\n", __FUNCTION__, byte_address, val));

	pthread_mutex_unlock(&gbus_lock);
	return (RMuint8) val;
}

/**
 *
 */

RMuint16 gbus::gbus_read_uint16(RMuint32 byte_address)
{
	RMuint32 val;

	pthread_mutex_lock(&gbus_lock);

	sock_write_2_uint32(sd, SOCK_GBUS_READ_UINT16, byte_address);

	if (sock_read_uint32(sd, &val) < 4)
		RMPanic(RM_ERROR);

	RMDBGLOG((LOCALDBG, "%s(0x%lx) = 0x%x\n", __FUNCTION__, byte_address, val));

	pthread_mutex_unlock(&gbus_lock);
	return (RMuint16) val;
}

/**
 *
 */

RMuint32 gbus::gbus_read_uint32(RMuint32 byte_address)
{
	RMuint32 val;

	pthread_mutex_lock(&gbus_lock);

	sock_write_2_uint32(sd, SOCK_GBUS_READ_UINT32, byte_address);
	if (sock_read_uint32(sd, &val) < 4)
		RMPanic(RM_ERROR);

	RMDBGLOG((LOCALDBG, "%s(0x%lx) = 0x%x\n", __FUNCTION__, byte_address, val));

	pthread_mutex_unlock(&gbus_lock);
	return (RMuint32) val;
}

/**
 *
 */

void gbus::gbus_write_uint8(RMuint32 byte_address, RMuint8 data)
{
    pthread_mutex_lock(&gbus_lock);
	RMDBGLOG((LOCALDBG, "%s(0x%lx, %u=0x%x)\n", __FUNCTION__, byte_address, data, data));

	sock_write_3_uint32(sd, SOCK_GBUS_WRITE_UINT8, byte_address, data);

	pthread_mutex_unlock(&gbus_lock);
}

/**
 *
 */

void gbus::gbus_write_uint16(RMuint32 byte_address, RMuint16 data)
{
    pthread_mutex_lock(&gbus_lock);
	RMDBGLOG((LOCALDBG, "%s(0x%lx, %u=0x%x)\n", __FUNCTION__, byte_address, data, data));

	sock_write_3_uint32(sd, SOCK_GBUS_WRITE_UINT16, byte_address, data);

	pthread_mutex_unlock(&gbus_lock);
}

/**
 *
 */

void gbus::gbus_write_uint32(RMuint32 byte_address, RMuint32 data)
{
	pthread_mutex_lock(&gbus_lock);
	RMDBGLOG((LOCALDBG, "%s(0x%lx, %lu=0x%lx)\n", __FUNCTION__, byte_address, data, data));

	sock_write_3_uint32(sd, SOCK_GBUS_WRITE_UINT32, byte_address, data);

	pthread_mutex_unlock(&gbus_lock);
}

/**
 *
 */

void gbus::gbus_read_data8(RMuint32 byte_address, RMuint8 *data, RMuint32 count)
{
	pthread_mutex_lock(&gbus_lock);
	RMDBGLOG((LOCALDBG, "%s(0x%lx)\n", __FUNCTION__, byte_address));

	sock_write_3_uint32(sd, SOCK_GBUS_READ_DATA8, byte_address, count);
	if (sock_read_buf(sd, (RMuint8 *) data, count * sizeof(RMuint8)) < (RMint32) (count * sizeof(RMuint8)))
		RMPanic(RM_ERROR);

	pthread_mutex_unlock(&gbus_lock);
}

/**
 *
 */

void gbus::gbus_read_data16(RMuint32 byte_address, RMuint16 *data, RMuint32 count)
{
	RMuint32 i;
	pthread_mutex_lock(&gbus_lock);

	RMDBGLOG((LOCALDBG, "%s(0x%lx, %p, %lu)\n", __FUNCTION__, byte_address, data, count));

	sock_write_3_uint32(sd, SOCK_GBUS_READ_DATA16, byte_address, count);
	if (sock_read_buf(sd, (RMuint8 *)data, count * sizeof(RMuint16)) < (RMint32) (count * sizeof(RMuint16)))
 		RMPanic(RM_ERROR);

	for (i=0 ; i<count ; i++) {
		data[i] = RMbeBufToUint16((RMuint8 *) (data + i));
	}
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

	RMDBGLOG((LOCALDBG, "%s(0x%lx, %p, %lu)\n", __FUNCTION__, byte_address, data, count));

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
	pthread_mutex_unlock(&gbus_lock);
}

/**
 *
 */

void gbus::gbus_write_data8(RMuint32 byte_address, RMuint8 *data, RMuint32 count)
{
	pthread_mutex_lock(&gbus_lock);
	RMDBGLOG((LOCALDBG, "%s(0x%lx, %p, %lu)\n", __FUNCTION__, byte_address, data, count));

	sock_write_3_uint32(sd, SOCK_GBUS_WRITE_DATA8, byte_address, count);
	if (sock_write_buf(sd, (RMuint8 *)data, count * sizeof(RMuint8)) < (RMint32) (count * sizeof(RMuint8)))
		RMPanic(RM_ERROR);

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

	RMDBGLOG((LOCALDBG, "%s(0x%lx, %p, %lu)\n", __FUNCTION__, byte_address, data, count));

	sock_write_3_uint32(sd, SOCK_GBUS_WRITE_DATA16, byte_address, count);

	for (i=0 ; i<count ; i++)
		RMuint16ToBeBuf(non_const_data[i], (RMuint8 *) (non_const_data + i));

	if (sock_write_buf(sd, (RMuint8 *)non_const_data, count * sizeof(RMuint16)) < (RMint32) (count * sizeof(RMuint16)))
		RMPanic(RM_ERROR);

	for (i=0 ; i<count ; i++)
		non_const_data[i] = RMbeBufToUint16((RMuint8 *) (non_const_data + i));

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

	RMDBGLOG((LOCALDBG, "%s(%0x%lx, %p, %lu)\n", __FUNCTION__, byte_address, data, count));

	sock_write_3_uint32(sd, SOCK_GBUS_WRITE_DATA32, byte_address, count);

	for (i=0 ; i<count ; i++)
		RMuint32ToBeBuf(non_const_data[i], (RMuint8 *) (non_const_data + i));

	if (sock_write_buf(sd, (RMuint8 *) non_const_data, count * sizeof(RMuint32)) < (RMint32) (count * sizeof(RMuint32)))
		RMPanic(RM_ERROR);

	for (i=0 ; i<count ; i++)
		non_const_data[i] = RMbeBufToUint32((RMuint8 *) (non_const_data + i));

	pthread_mutex_unlock(&gbus_lock);
}

