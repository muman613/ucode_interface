#include <stdio.h>
#include <stdlib.h>

#define ALLOW_OS_CODE
#include "remote_client/llad.h"
#include "remote_client/gbus.h"
#include "gbus_fifo_eraser.h"

/*****************************************
 Copyright © 2001-2016
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

//#include "llad/include/llad.h"
//#include "include/gbus_fifo_eraser.h"

struct gbus_fifo_eraser *gbus_fifo_eraser_open(GBUS_PTR h, RMuint32 data_address, RMuint32 data_size, RMuint32 fifo_address)
{
	struct gbus_fifo_eraser *fifo = (struct gbus_fifo_eraser *) fifo_address;

	h->gbus_write_uint32((RMuint32) &(fifo->base), data_address);
	h->gbus_write_uint32((RMuint32) &(fifo->size), data_size);
	h->gbus_write_uint32((RMuint32) &(fifo->rd), 0);
	h->gbus_write_uint32((RMuint32) &(fifo->wr), 0);
	h->gbus_write_uint32((RMuint32) &(fifo->er), 0);

	return fifo;
}

void gbus_fifo_eraser_close(GBUS_PTR h, struct gbus_fifo_eraser *fifo)
{
	// warn about pending erasable entries
	RMASSERT(gbus_fifo_eraser_is_empty(h,fifo));
}

RMbool gbus_fifo_eraser_is_empty(GBUS_PTR h, struct gbus_fifo_eraser *fifo)
{
	RMuint32 er, rd, wr;

	er   = h->gbus_read_uint32((RMuint32) &(fifo->er));
	rd   = h->gbus_read_uint32((RMuint32) &(fifo->rd));
	wr   = h->gbus_read_uint32((RMuint32) &(fifo->wr));

	return ((er==rd)&&(rd==wr));
}

void gbus_fifo_eraser_flush(GBUS_PTR h, struct gbus_fifo_eraser *fifo)
{
	h->gbus_write_uint32((RMuint32) &(fifo->rd), 0);
	h->gbus_write_uint32((RMuint32) &(fifo->wr), 0);
	h->gbus_write_uint32((RMuint32) &(fifo->er), 0);
}

RMuint32 gbus_fifo_eraser_get_info(GBUS_PTR h, struct gbus_fifo_eraser *fifo, RMuint32 *start_address, 	RMuint32 *writable, RMuint32 *readable, RMuint32 *erasable)
{
	RMuint32 start, size, rd, wr, er;

	start = h->gbus_read_uint32((RMuint32) &(fifo->base));
	size  = h->gbus_read_uint32((RMuint32) &(fifo->size));
	er   = h->gbus_read_uint32((RMuint32) &(fifo->er));
	wr   = h->gbus_read_uint32((RMuint32) &(fifo->wr));
	rd   = h->gbus_read_uint32((RMuint32) &(fifo->rd));

	*start_address = start;

	*writable = er - wr + size - 1;
	if ((*writable) >= size)
		(*writable) -= size;

	*readable = wr - rd + size;
	if ((*readable) >= size)
		(*readable) -= size;

	(*erasable) = size - 1 - (*readable) - (*writable);

	return size;
}

RMuint32 gbus_fifo_eraser_get_writable_size(GBUS_PTR h, struct gbus_fifo_eraser *fifo, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2)
{
	RMuint32 wr, er, base, size;

	base = h->gbus_read_uint32((RMuint32) &(fifo->base));
	size = h->gbus_read_uint32((RMuint32) &(fifo->size));
	er   = h->gbus_read_uint32((RMuint32) &(fifo->er));
	wr   = h->gbus_read_uint32((RMuint32) &(fifo->wr));

	*wr_ptr1 = base + wr;

	if (wr >= er) {
		if (er > 0) {
			*wr_size1 = size - wr;
			*wr_ptr2 = base;
			return (*wr_size1 + er - 1);
		}
		else {
			*wr_size1 = size - 1 - wr;
			*wr_ptr2 = 0;
			return (*wr_size1);
		}
	}
	else {
		*wr_size1 = er - 1 - wr;
		*wr_ptr2 = 0;
		return (*wr_size1);
	}
}

RMuint32 gbus_fifo_eraser_get_readable_size(GBUS_PTR h, struct gbus_fifo_eraser *fifo, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2)
{
	RMuint32 wr, rd, base, size;

	base = h->gbus_read_uint32((RMuint32) &(fifo->base));
	size = h->gbus_read_uint32((RMuint32) &(fifo->size));
	rd   = h->gbus_read_uint32((RMuint32) &(fifo->rd));
	wr   = h->gbus_read_uint32((RMuint32) &(fifo->wr));

	*rd_ptr1 = base + rd;

	if (wr >= rd) {
		*rd_size1 = wr - rd;
		*rd_ptr2 = 0;
		return (*rd_size1);
	}
	else {
		*rd_size1 = size - rd;
		*rd_ptr2 = base;
		return (*rd_size1 +  wr);
	}
}

RMuint32 gbus_fifo_eraser_get_erasable_size(GBUS_PTR h, struct gbus_fifo_eraser *fifo, RMuint32 *er_ptr1, RMuint32 *er_size1, RMuint32 *er_ptr2)
{
	RMuint32 er, rd, base, size;

	base = h->gbus_read_uint32((RMuint32) &(fifo->base));
	size = h->gbus_read_uint32((RMuint32) &(fifo->size));
	rd   = h->gbus_read_uint32((RMuint32) &(fifo->rd));
	er   = h->gbus_read_uint32((RMuint32) &(fifo->er));

	*er_ptr1 = base + er;

	if (rd >= er) {
		*er_size1 = rd - er;
		*er_ptr2 = 0;
		return (*er_size1);
	}
	else {
		*er_size1 = size - er;
		*er_ptr2 = base;
		return (*er_size1 +  rd);
	}
}

RMuint32 gbus_fifo_eraser_incr_write_ptr(GBUS_PTR h, struct gbus_fifo_eraser *fifo, RMuint32 incr)
{
	RMuint32 wr, base, size;

	base = h->gbus_read_uint32((RMuint32) &(fifo->base));
	size = h->gbus_read_uint32((RMuint32) &(fifo->size));
	wr   = h->gbus_read_uint32((RMuint32) &(fifo->wr));

	wr += incr;
	if (wr >= size)
		wr = (wr - size);

	h->gbus_write_uint32((RMuint32) &(fifo->wr), wr);

	return base + wr;
}

RMuint32 gbus_fifo_eraser_incr_read_ptr(GBUS_PTR h, struct gbus_fifo_eraser *fifo, RMuint32 incr)
{
	RMuint32 rd, base, size;

	base = h->gbus_read_uint32((RMuint32) &(fifo->base));
	size = h->gbus_read_uint32((RMuint32) &(fifo->size));
	rd   = h->gbus_read_uint32((RMuint32) &(fifo->rd));

	rd += incr;
	if (rd >= size)
		rd = (rd - size);

	h->gbus_write_uint32((RMuint32) &(fifo->rd), rd);

	return base + rd;
}

RMuint32 gbus_fifo_eraser_incr_erase_ptr(GBUS_PTR h, struct gbus_fifo_eraser *fifo, RMuint32 incr)
{
	RMuint32 er, base, size;

	base = h->gbus_read_uint32((RMuint32) &(fifo->base));
	size = h->gbus_read_uint32((RMuint32) &(fifo->size));
	er   = h->gbus_read_uint32((RMuint32) &(fifo->er));

	er += incr;
	if (er >= size)
		er = (er - size);

	h->gbus_write_uint32((RMuint32) &(fifo->er), er);

	return base + er;
}
