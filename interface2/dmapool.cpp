/*****************************************
 Copyright © 2001-2003
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

#define ALLOW_OS_CODE 1

#include "../llad/include/dmapool.h"

struct dmapool *dmapool_open(struct llad *h, void *area, RMuint32 buffercount, RMuint32 log2_buffersize)
{
	RMPanic(RM_NOTIMPLEMENTED);
	RMNOTIFY((NULL, RM_NOTIMPLEMENTED, "%s\n", __FUNCTION__));
	return (struct dmapool*)NULL;
}

void dmapool_close(struct dmapool *h)
{
	RMPanic(RM_NOTIMPLEMENTED);
	RMNOTIFY((NULL, RM_NOTIMPLEMENTED, "%s\n", __FUNCTION__));
	return;
}

RMuint32 dmapool_reset(struct dmapool *h)
{
	RMPanic(RM_NOTIMPLEMENTED);
	RMNOTIFY((NULL, RM_NOTIMPLEMENTED, "%s\n", __FUNCTION__));
	return 0xffffffff;
}

RMuint32 dmapool_get_id(struct dmapool *h)
{
	RMPanic(RM_NOTIMPLEMENTED);
	RMNOTIFY((NULL, RM_NOTIMPLEMENTED, "%s\n", __FUNCTION__));
	return 0xffffffff;
}

void dmapool_get_info(struct dmapool *h, RMuint32 *size)
{
	RMPanic(RM_NOTIMPLEMENTED);
	RMNOTIFY((NULL, RM_NOTIMPLEMENTED, "%s\n", __FUNCTION__));
	*size = 0;
	return;
}

RMuint8 *dmapool_get_buffer(struct dmapool *h, RMuint32 *timeout_microsecond)
{
	RMPanic(RM_NOTIMPLEMENTED);
	RMNOTIFY((NULL, RM_NOTIMPLEMENTED, "%s\n", __FUNCTION__));
	return (RMuint8 *) NULL;
}

RMuint32 dmapool_get_available_buffer_count(struct dmapool *h)
{
	RMPanic(RM_NOTIMPLEMENTED);
	RMNOTIFY((NULL, RM_NOTIMPLEMENTED, "%s\n", __FUNCTION__));
	return (RMuint32) -1;
}

RMuint32 dmapool_get_physical_address(struct dmapool *h, RMuint8 *ptr, RMuint32 size)
{
	RMPanic(RM_NOTIMPLEMENTED);
	RMNOTIFY((NULL, RM_NOTIMPLEMENTED, "%s\n", __FUNCTION__));
	return 0;
}

RMuint8 *dmapool_get_virtual_address(struct dmapool *h, RMuint32 physical_addr, RMuint32 size)
{
	RMPanic(RM_NOTIMPLEMENTED);
	RMNOTIFY((NULL, RM_NOTIMPLEMENTED, "%s\n", __FUNCTION__));
	return (RMuint8*)NULL;
}

RMstatus dmapool_acquire(struct dmapool *h, RMuint32 physical_address)
{
	RMPanic(RM_NOTIMPLEMENTED);
	RMNOTIFY((NULL, RM_NOTIMPLEMENTED, "%s\n", __FUNCTION__));
	return RM_NOTIMPLEMENTED;
}

RMstatus dmapool_release(struct dmapool *h, RMuint32 physical_address)
{
	RMPanic(RM_NOTIMPLEMENTED);
	RMNOTIFY((NULL, RM_NOTIMPLEMENTED, "%s\n", __FUNCTION__));
	return RM_NOTIMPLEMENTED;
}

void dmapool_writeback_cache(struct dmapool *h, RMuint32 physical_address, RMuint32 size)
{
	RMPanic(RM_NOTIMPLEMENTED);
	RMNOTIFY((NULL, RM_NOTIMPLEMENTED, "%s\n", __FUNCTION__));
	return;
}

void dmapool_invalidate_cache(struct dmapool *h, RMuint32 physical_address, RMuint32 size)
{
	RMPanic(RM_NOTIMPLEMENTED);
	RMNOTIFY((NULL, RM_NOTIMPLEMENTED, "%s\n", __FUNCTION__));
	return;

}
