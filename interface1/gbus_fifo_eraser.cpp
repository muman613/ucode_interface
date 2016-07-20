/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

#include "llad/include/llad.h"
#include "include/gbus_fifo_eraser.h"

struct gbus_fifo_eraser *gbus_fifo_eraser_open(struct gbus *h, RMuint32 data_address, RMuint32 data_size, RMuint32 fifo_address)
{
	struct gbus_fifo_eraser *fifo = (struct gbus_fifo_eraser *) fifo_address;

	gbus_write_uint32(h, (RMuint32) &(fifo->base), data_address);
	gbus_write_uint32(h, (RMuint32) &(fifo->size), data_size);
	gbus_write_uint32(h, (RMuint32) &(fifo->rd), 0);
	gbus_write_uint32(h, (RMuint32) &(fifo->wr), 0);
	gbus_write_uint32(h, (RMuint32) &(fifo->er), 0);

	return fifo;
}

void gbus_fifo_eraser_close(struct gbus *h, struct gbus_fifo_eraser *fifo)
{
	// warn about pending erasable entries 
	RMASSERT(gbus_fifo_eraser_is_empty(h,fifo));
}

RMbool gbus_fifo_eraser_is_empty(struct gbus *h, struct gbus_fifo_eraser *fifo)
{
	RMuint32 er, rd, wr;
	
	er   = gbus_read_uint32(h, (RMuint32) &(fifo->er));
	rd   = gbus_read_uint32(h, (RMuint32) &(fifo->rd));
	wr   = gbus_read_uint32(h, (RMuint32) &(fifo->wr));
	
	return ((er==rd)&&(rd==wr));
}

void gbus_fifo_eraser_flush(struct gbus *h, struct gbus_fifo_eraser *fifo)
{
	gbus_write_uint32(h, (RMuint32) &(fifo->rd), 0);
	gbus_write_uint32(h, (RMuint32) &(fifo->wr), 0);
	gbus_write_uint32(h, (RMuint32) &(fifo->er), 0);
}

RMuint32 gbus_fifo_eraser_get_info(struct gbus *h, struct gbus_fifo_eraser *fifo, RMuint32 *start_address, 	RMuint32 *writable, RMuint32 *readable, RMuint32 *erasable)
{
	RMuint32 start, size, rd, wr, er;

	start = gbus_read_uint32(h, (RMuint32) &(fifo->base));
	size  = gbus_read_uint32(h, (RMuint32) &(fifo->size));
	er   = gbus_read_uint32(h, (RMuint32) &(fifo->er));
	wr   = gbus_read_uint32(h, (RMuint32) &(fifo->wr));
	rd   = gbus_read_uint32(h, (RMuint32) &(fifo->rd));
	
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

RMuint32 gbus_fifo_eraser_get_writable_size(struct gbus *h, struct gbus_fifo_eraser *fifo, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2)
{
	RMuint32 wr, er, base, size;

	base = gbus_read_uint32(h, (RMuint32) &(fifo->base));
	size = gbus_read_uint32(h, (RMuint32) &(fifo->size));
	er   = gbus_read_uint32(h, (RMuint32) &(fifo->er));
	wr   = gbus_read_uint32(h, (RMuint32) &(fifo->wr));
	
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

RMuint32 gbus_fifo_eraser_get_readable_size(struct gbus *h, struct gbus_fifo_eraser *fifo, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2)
{
	RMuint32 wr, rd, base, size;

	base = gbus_read_uint32(h, (RMuint32) &(fifo->base));
	size = gbus_read_uint32(h, (RMuint32) &(fifo->size));
	rd   = gbus_read_uint32(h, (RMuint32) &(fifo->rd));
	wr   = gbus_read_uint32(h, (RMuint32) &(fifo->wr));

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


RMuint32 gbus_fifo_eraser_get_erasable_size(struct gbus *h, struct gbus_fifo_eraser *fifo, RMuint32 *er_ptr1, RMuint32 *er_size1, RMuint32 *er_ptr2)
{
	RMuint32 er, rd, base, size;

	base = gbus_read_uint32(h, (RMuint32) &(fifo->base));
	size = gbus_read_uint32(h, (RMuint32) &(fifo->size));
	rd   = gbus_read_uint32(h, (RMuint32) &(fifo->rd));
	er   = gbus_read_uint32(h, (RMuint32) &(fifo->er));

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

RMuint32 gbus_fifo_eraser_incr_write_ptr(struct gbus *h, struct gbus_fifo_eraser *fifo, RMuint32 incr)
{
	RMuint32 wr, base, size;

	base = gbus_read_uint32(h, (RMuint32) &(fifo->base));
	size = gbus_read_uint32(h, (RMuint32) &(fifo->size));
	wr   = gbus_read_uint32(h, (RMuint32) &(fifo->wr));

	wr += incr;
	if (wr >= size)
		wr = (wr - size);

	gbus_write_uint32(h, (RMuint32) &(fifo->wr), wr);
		
	return base + wr;
}

RMuint32 gbus_fifo_eraser_incr_read_ptr(struct gbus *h, struct gbus_fifo_eraser *fifo, RMuint32 incr)
{
	RMuint32 rd, base, size;

	base = gbus_read_uint32(h, (RMuint32) &(fifo->base));
	size = gbus_read_uint32(h, (RMuint32) &(fifo->size));
	rd   = gbus_read_uint32(h, (RMuint32) &(fifo->rd));

	rd += incr;
	if (rd >= size)
		rd = (rd - size);
		
	gbus_write_uint32(h, (RMuint32) &(fifo->rd), rd);

	return base + rd;
}

RMuint32 gbus_fifo_eraser_incr_erase_ptr(struct gbus *h, struct gbus_fifo_eraser *fifo, RMuint32 incr)
{
	RMuint32 er, base, size;

	base = gbus_read_uint32(h, (RMuint32) &(fifo->base));
	size = gbus_read_uint32(h, (RMuint32) &(fifo->size));
	er   = gbus_read_uint32(h, (RMuint32) &(fifo->er));

	er += incr;
	if (er >= size)
		er = (er - size);
		
	gbus_write_uint32(h, (RMuint32) &(fifo->er), er);

	return base + er;
}
