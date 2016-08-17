#define ALLOW_OS_CODE 1

#include "include/gbus.h"

#include "sock.h"
#include "include/llad_protocol.h"
#include "struct.h"

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#ifndef __WIN32__
	#include <sys/ioctl.h>
	#include <unistd.h>
#endif


#define LOCALDBG DISABLE

#if defined(_DEBUG) && defined(GBUS_LOGGER)
#define ENABLE_GBUS_LOGGER
#endif // defined

#ifdef ENABLE_GBUS_LOGGER
static FILE* gbusLogFp = 0L;
#endif // ENABLE_GBUS_LOGGER

struct gbus *gbus_open(struct llad *h)
{
	struct gbus *pgbus;
	RMuint16 port;

	RMDBGLOG((LOCALDBG, "%s(%p)\n", __FUNCTION__, h));

#ifdef ENABLE_GBUS_LOGGER
    gbusLogFp = fopen("/tmp/gbuslog_if1.txt", "w");
    fprintf(gbusLogFp, "gbus_open()\n");
#endif // ENABLE_GBUS_LOGGER

	pgbus = (struct gbus *) malloc(sizeof(struct gbus));
	if (pgbus == NULL) return NULL;

	port = SOCK_LLAD_PORT + (RMuint16)h->device;
	pgbus->sd = sock_connect(port, h->hostname);
	if (pgbus->sd == NULL) {
		free(pgbus);
		fprintf(stderr, "network/" __FILE__ ": Unable to open connection to %s:%lu\n", h->hostname, (unsigned long)h->device);
		return NULL;
	}

	pgbus->gbus_lock = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(pgbus->gbus_lock, NULL);

	sock_write_uint32(pgbus->sd, SOCK_GBUS_SERVICE);

	return pgbus;
}

void gbus_close(struct gbus *h)
{
	RMDBGLOG((LOCALDBG, "%s(%p)\n", __FUNCTION__, h));

	if (h != NULL) {
		sock_close(h->sd);
		pthread_mutex_destroy(h->gbus_lock);
		free(h->gbus_lock);
		free(h);
	}

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_close()\n");
    fclose(gbusLogFp);
    gbusLogFp = 0L;
#endif // ENABLE_GBUS_LOGGER
}

RMuint8 gbus_read_uint8(struct gbus *h, RMuint32 byte_address)
{
	RMuint32 val;
	pthread_mutex_lock(h->gbus_lock);

	sock_write_2_uint32(h->sd, SOCK_GBUS_READ_UINT8, byte_address);

	if (sock_read_uint32(h->sd, &val) < 4)
		RMPanic(RM_ERROR);

	RMDBGLOG((LOCALDBG, "%s(%p, 0x%lx) = 0x%x\n", __FUNCTION__, h, byte_address, val));

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_read_uint8(0x%08X) = 0x%02X\n", byte_address, val);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(h->gbus_lock);
	return (RMuint8) val;
}

RMuint16 gbus_read_uint16(struct gbus *h, RMuint32 byte_address)
{
	RMuint32 val;
	pthread_mutex_lock(h->gbus_lock);

	sock_write_2_uint32(h->sd, SOCK_GBUS_READ_UINT16, byte_address);
	if (sock_read_uint32(h->sd, &val) < 4)
		RMPanic(RM_ERROR);

	RMDBGLOG((LOCALDBG, "%s(%p, 0x%lx) = 0x%x\n", __FUNCTION__, h, byte_address, val));

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_read_uint16(0x%08X) = 0x%04X\n", byte_address, val);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(h->gbus_lock);
	return (RMuint16) val;
}

RMuint32 gbus_read_uint32(struct gbus *h, RMuint32 byte_address)
{
	RMuint32 val;
	pthread_mutex_lock(h->gbus_lock);

	sock_write_2_uint32(h->sd, SOCK_GBUS_READ_UINT32, byte_address);
	if (sock_read_uint32(h->sd, &val) < 4)
		RMPanic(RM_ERROR);

	RMDBGLOG((LOCALDBG, "%s(%p, 0x%lx) = 0x%x\n", __FUNCTION__, h, byte_address, val));

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_read_uint32(0x%08X) = 0x%08X\n", byte_address, val);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(h->gbus_lock);
	return (RMuint32) val;
}

void gbus_read_data8(struct gbus *h, RMuint32 byte_address, RMuint8 *data, RMuint32 count)
{

	pthread_mutex_lock(h->gbus_lock);
	RMDBGLOG((LOCALDBG, "%s(%p, 0x%lx)\n", __FUNCTION__, h, byte_address));

	sock_write_3_uint32(h->sd, SOCK_GBUS_READ_DATA8, byte_address, count);
	if (sock_read_buf(h->sd, (RMuint8 *) data, count * sizeof(RMuint8)) < (RMint32) (count * sizeof(RMuint8)))
		RMPanic(RM_ERROR);

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_read_data8(0x%08X, %d)\n", byte_address, count);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(h->gbus_lock);
}

void gbus_read_data16(struct gbus *h, RMuint32 byte_address, RMuint16 *data, RMuint32 count)
{
	RMuint32 i;
	pthread_mutex_lock(h->gbus_lock);

	RMDBGLOG((LOCALDBG, "%s(%p, 0x%lx, %p, %lu)\n", __FUNCTION__, h, byte_address, data, count));

	sock_write_3_uint32(h->sd, SOCK_GBUS_READ_DATA16, byte_address, count);
	if (sock_read_buf(h->sd, (RMuint8 *)data, count * sizeof(RMuint16)) < (RMint32) (count * sizeof(RMuint16)))
 		RMPanic(RM_ERROR);

	for (i=0 ; i<count ; i++) {
		data[i] = RMbeBufToUint16((RMuint8 *) (data + i));
	}

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_read_data16(0x%08X, %d)\n", byte_address, count);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(h->gbus_lock);
}

void gbus_read_data32(struct gbus *h, RMuint32 byte_address, RMuint32 *data, RMuint32 count)
{
	RMuint32 i;
	RMint32 Read;
	RMint32 SizeToRead;
	pthread_mutex_lock(h->gbus_lock);

	RMDBGLOG((LOCALDBG, "%s(%p, 0x%lx, %p, %lu)\n", __FUNCTION__, h, byte_address, data, count));

	sock_write_3_uint32(h->sd, SOCK_GBUS_READ_DATA32, byte_address, count);

	SizeToRead = count * sizeof(RMuint32);

	i = 0;
	while (i < 10) {
		Read = sock_read_buf(h->sd, (RMuint8 *) data, SizeToRead);
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
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(h->gbus_lock);
}

void gbus_write_uint8(struct gbus *h, RMuint32 byte_address, RMuint8  data)
{

	pthread_mutex_lock(h->gbus_lock);
	RMDBGLOG((LOCALDBG, "%s(%p, 0x%lx, %u=0x%x)\n", __FUNCTION__, h, byte_address, data, data));

	sock_write_3_uint32(h->sd, SOCK_GBUS_WRITE_UINT8, byte_address, data);

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_write_uint8(0x%08X, 0x%02x)\n", byte_address, data);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(h->gbus_lock);
}

void gbus_write_uint16(struct gbus *h, RMuint32 byte_address, RMuint16 data)
{

	pthread_mutex_lock(h->gbus_lock);
	RMDBGLOG((LOCALDBG, "%s(%p, 0x%lx, %u=0x%x)\n", __FUNCTION__, h, byte_address, data, data));

	sock_write_3_uint32(h->sd, SOCK_GBUS_WRITE_UINT16, byte_address, data);

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_write_uint16(0x%08X, 0x%04x)\n", byte_address, data);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(h->gbus_lock);
}

void gbus_write_uint32(struct gbus *h, RMuint32 byte_address, RMuint32 data)
{

	pthread_mutex_lock(h->gbus_lock);
	RMDBGLOG((LOCALDBG, "%s(%p, 0x%lx, %lu=0x%lx)\n", __FUNCTION__, h, byte_address, data, data));

	sock_write_3_uint32(h->sd, SOCK_GBUS_WRITE_UINT32, byte_address, data);

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_write_uint32(0x%08X, 0x%08x)\n", byte_address, data);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(h->gbus_lock);
}

void gbus_write_data8(struct gbus *h, RMuint32 byte_address, const RMuint8 *data, RMuint32 count)
{

	pthread_mutex_lock(h->gbus_lock);
	RMDBGLOG((LOCALDBG, "%s(%p, 0x%lx, %p, %lu)\n", __FUNCTION__, h, byte_address, data, count));

	sock_write_3_uint32(h->sd, SOCK_GBUS_WRITE_DATA8, byte_address, count);
	if (sock_write_buf(h->sd, (RMuint8 *)data, count * sizeof(RMuint8)) < (RMint32) (count * sizeof(RMuint8)))
		RMPanic(RM_ERROR);

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_write_data8(0x%08X, %d)\n", byte_address, count);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(h->gbus_lock);
}

void gbus_write_data16(struct gbus *h, RMuint32 byte_address, const RMuint16 *data, RMuint32 count)
{
	RMuint32 i;
	RMuint16 *non_const_data = (RMuint16 *) data;
	pthread_mutex_lock(h->gbus_lock);


	RMDBGLOG((LOCALDBG, "%s(%p, 0x%lx, %p, %lu)\n", __FUNCTION__, h, byte_address, data, count));

	sock_write_3_uint32(h->sd, SOCK_GBUS_WRITE_DATA16, byte_address, count);

	for (i=0 ; i<count ; i++) /* the risks taken by this approach can't be underlined enough:
				     the supposedly (and, in the end, from the caller's point of
				     view, effectively) const data is temporary changed for byte
				     reordering. This breaks reentrancy of the function. The safe
				     alternative is to use an intermediate buffer to reorder the
				     data into. */
		RMuint16ToBeBuf(non_const_data[i], (RMuint8 *) (non_const_data + i));

	if (sock_write_buf(h->sd, (RMuint8 *)non_const_data, count * sizeof(RMuint16)) < (RMint32) (count * sizeof(RMuint16)))
		RMPanic(RM_ERROR);

	for (i=0 ; i<count ; i++)
		non_const_data[i] = RMbeBufToUint16((RMuint8 *) (non_const_data + i));

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_write_data16(0x%08X, %d)\n", byte_address, count);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(h->gbus_lock);
}

void gbus_write_data32(struct gbus *h, RMuint32 byte_address, const RMuint32 *data, RMuint32 count)
{
	RMuint32 i;
	RMuint32 *non_const_data = (RMuint32 *) data;
	pthread_mutex_lock(h->gbus_lock);

	RMDBGLOG((LOCALDBG, "%s(%p, 0x%lx, %p, %lu)\n", __FUNCTION__, h, byte_address, data, count));

	sock_write_3_uint32(h->sd, SOCK_GBUS_WRITE_DATA32, byte_address, count);

	for (i=0 ; i<count ; i++) /* the risks taken by this approach can't be underlined enough:
				     the supposedly (and, in the end, from the caller's point of
				     view, effectively) const data is temporary changed for byte
				     reordering. This breaks reentrancy of the function. The safe
				     alternative is to use an intermediate buffer to reorder the
				     data into. */
		RMuint32ToBeBuf(non_const_data[i], (RMuint8 *) (non_const_data + i));

	if (sock_write_buf(h->sd, (RMuint8 *) non_const_data, count * sizeof(RMuint32)) < (RMint32) (count * sizeof(RMuint32)))
		RMPanic(RM_ERROR);

	for (i=0 ; i<count ; i++)
		non_const_data[i] = RMbeBufToUint32((RMuint8 *) (non_const_data + i));

#ifdef ENABLE_GBUS_LOGGER
    fprintf(gbusLogFp, "gbus_write_data32(0x%08X, %d)\n", byte_address, count);
#endif // ENABLE_GBUS_LOGGER

	pthread_mutex_unlock(h->gbus_lock);
}

RMstatus gbus_lock_area(struct gbus *h, RMuint32 *region_index, RMuint32 byte_address, RMuint32 size, RMuint32 *region_count, RMuint32 *offset)
{
	RMPanic(RM_NOTIMPLEMENTED);
	RMNOTIFY((NULL, RM_NOTIMPLEMENTED, "%s\n", __FUNCTION__));
	return RM_NOTIMPLEMENTED;
}

RMstatus gbus_get_locked_area(struct gbus *h, RMuint32 byte_address, RMuint32 size, RMuint32 *region_index, RMuint32 *region_count, RMuint32 *offset)
{
	RMPanic(RM_NOTIMPLEMENTED);
	RMNOTIFY((NULL, RM_NOTIMPLEMENTED, "%s\n", __FUNCTION__));
	return RM_NOTIMPLEMENTED;
}

RMstatus gbus_unlock_region(struct gbus *h, RMuint32 region_index)
{
	RMPanic(RM_NOTIMPLEMENTED);
	RMNOTIFY((NULL, RM_NOTIMPLEMENTED, "%s\n", __FUNCTION__));
	return RM_NOTIMPLEMENTED;
}

RMuint8 *gbus_map_region_cached(struct gbus *h, RMuint32 region_index, RMuint32 region_count)
{
	RMPanic(RM_NOTIMPLEMENTED);
	RMNOTIFY((NULL, RM_NOTIMPLEMENTED, "%s\n", __FUNCTION__));
	return NULL;
}

RMuint8 *gbus_map_region(struct gbus *h, RMuint32 region_index, RMuint32 region_count)
{
	RMPanic(RM_NOTIMPLEMENTED);
	RMNOTIFY((NULL, RM_NOTIMPLEMENTED, "%s\n", __FUNCTION__));
	return NULL;
}

void gbus_unmap_region(struct gbus *h, RMuint8 *address, RMuint32 size)
{
	RMPanic(RM_NOTIMPLEMENTED);
	RMNOTIFY((NULL, RM_NOTIMPLEMENTED, "%s\n", __FUNCTION__));
	return;
}

void gbus_writeback_cache_region(struct gbus *h, RMuint32 virtual_address, RMuint32 size)
{
	RMPanic(RM_NOTIMPLEMENTED);
	RMNOTIFY((NULL, RM_NOTIMPLEMENTED, "%s\n", __FUNCTION__));
	return;
}

void gbus_invalidate_cache_region(struct gbus *h, RMuint32 virtual_address, RMuint32 size)
{
	RMPanic(RM_NOTIMPLEMENTED);
	RMNOTIFY((NULL, RM_NOTIMPLEMENTED, "%s\n", __FUNCTION__));
	return;
}

