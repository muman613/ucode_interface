#include <stdio.h>
#include <stdlib.h>

#define ALLOW_OS_CODE
#include "remote_client/llad.h"
#include "remote_client/gbus.h"
#include "gbus_fifo.h"

/*****************************************
 Copyright © 2001-2016
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

struct gbus_fifo *gbus_fifo_open(GBUS_PTR pgbus, RMuint32 data_address, RMuint32 data_size, RMuint32 fifo_address)
{
	return gbus_fifo_open_rdwr(pgbus, data_address, data_size, fifo_address, 0, 0);
}

struct gbus_fifo *gbus_fifo_open_rdwr(GBUS_PTR pgbus, RMuint32 data_address, RMuint32 data_size, RMuint32 fifo_address, RMuint32 rd_ptr, RMuint32 wr_ptr)
{
	struct gbus_fifo *fifo = (struct gbus_fifo *) fifo_address;

	pgbus->gbus_write_uint32((RMuint32) &(fifo->base), data_address);
	pgbus->gbus_write_uint32((RMuint32) &(fifo->size), data_size);
	pgbus->gbus_write_uint32((RMuint32) &(fifo->rd), rd_ptr);
	pgbus->gbus_write_uint32((RMuint32) &(fifo->wr), wr_ptr);

	return fifo;
}

void gbus_fifo_close(GBUS_PTR pgbus, struct gbus_fifo *fifo)
{
	RMASSERT(gbus_fifo_is_empty(pgbus,fifo));
}

void gbus_fifo_get_pointer(GBUS_PTR pgbus, struct gbus_fifo *fifo,
	RMuint32 *base, RMuint32 *size, RMuint32 *rd_ptr, RMuint32 *wr_ptr)
{
	*base   = pgbus->gbus_read_uint32((RMuint32) &(fifo->base));
	*size   = pgbus->gbus_read_uint32((RMuint32) &(fifo->size));
	*rd_ptr = pgbus->gbus_read_uint32((RMuint32) &(fifo->rd));
	*wr_ptr = pgbus->gbus_read_uint32((RMuint32) &(fifo->wr));
}

RMbool gbus_fifo_is_empty(GBUS_PTR pgbus, struct gbus_fifo *fifo)
{
	RMuint32 base, size, rd, wr;

	gbus_fifo_get_pointer(pgbus, fifo, &base, &size, &rd, &wr);

	return (rd == wr);
}

RMuint32 gbus_fifo_get_info(GBUS_PTR pgbus, struct gbus_fifo *fifo, RMuint32 *data_start, RMuint32 *writable, RMuint32 *readable)
{
	RMuint32 start, size, rd, wr;

	gbus_fifo_get_pointer(pgbus, fifo, &start, &size, &rd, &wr);

	*data_start = start;

	*writable = rd - wr + size - 1;
	if ((*writable) >= size)
		(*writable) -= size;

	*readable = size - 1 - (*writable);

	return size;
}

RMuint32 gbus_fifo_get_writable_size(GBUS_PTR pgbus, struct gbus_fifo *fifo, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2)
{
	RMuint32 base, size, rd, wr;

	gbus_fifo_get_pointer(pgbus, fifo, &base, &size, &rd, &wr);

	*wr_ptr1 = base + wr;

	if (wr >= rd) {
		if (rd > 0) {
			*wr_size1 = size - wr;
			*wr_ptr2 = base;
			return (*wr_size1 + rd - 1);
		}
		else {
			*wr_size1 = size - 1 - wr;
			*wr_ptr2 = 0;
			return (*wr_size1);
		}
	}
	else {
		*wr_size1 = rd - 1 - wr;
		*wr_ptr2 = 0;
		return (*wr_size1);
	}
}

RMuint32 gbus_fifo_get_readable_size(GBUS_PTR pgbus, struct gbus_fifo *fifo, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2)
{
	RMuint32 base, size, rd, wr;

	gbus_fifo_get_pointer(pgbus, fifo, &base, &size, &rd, &wr);

	*rd_ptr1 = base + rd;

	if (wr >= rd) {
		*rd_size1 = wr - rd;
		*rd_ptr2 = 0;
		return (*rd_size1);
	}
	else {
		*rd_size1 = size - rd;
		*rd_ptr2 = base;
		return (*rd_size1 + wr);
	}
}


RMuint32 gbus_fifo_get_readable_sizeWHATISTHIS(GBUS_PTR pgbus, struct gbus_fifo *fifo, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2, RMuint32 entry_size)
{
	RMuint32 base, size, rd, wr;

	gbus_fifo_get_pointer(pgbus, fifo, &base, &size, &rd, &wr);

	*rd_ptr1 = base + (rd * entry_size);

	if (wr >= rd) {
		*rd_size1 = wr - rd;
		*rd_ptr2 = 0;
		return (*rd_size1);
	}
	else {
		*rd_size1 = size - rd;
		*rd_ptr2 = base;
		return (*rd_size1 + wr);
	}
}


RMuint32 gbus_fifo_incr_write_ptr(GBUS_PTR pgbus, struct gbus_fifo *fifo, RMuint32 incr)
{
	RMuint32 base, size, rd, wr;

	gbus_fifo_get_pointer(pgbus, fifo, &base, &size, &rd, &wr);

	wr += incr;
	if (wr >= size)
		wr -= size;

	pgbus->gbus_write_uint32((RMuint32) &(fifo->wr), wr);

	return wr + base;
}

RMuint32 gbus_fifo_incr_read_ptr(GBUS_PTR pgbus, struct gbus_fifo *fifo, RMuint32 incr)
{
	RMuint32 base, size, rd, wr;

	gbus_fifo_get_pointer(pgbus, fifo, &base, &size, &rd, &wr);

	rd += incr;
	if (rd >= size)
		rd -= size;

	pgbus->gbus_write_uint32((RMuint32) &(fifo->rd), rd);

	return rd + base;
}

void gbus_fifo_flush_ptr(GBUS_PTR pgbus, struct gbus_fifo *fifo)
{
	pgbus->gbus_write_uint32((RMuint32) &(fifo->rd), 0);
	pgbus->gbus_write_uint32((RMuint32) &(fifo->wr), 0);
}

