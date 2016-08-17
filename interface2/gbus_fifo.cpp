#include "include/gbus_fifo.h"

struct gbus_fifo *gbus_fifo_open(struct gbus *pgbus, RMuint32 data_address, RMuint32 data_size, RMuint32 fifo_address)
{
	return gbus_fifo_open_rdwr(pgbus, data_address, data_size, fifo_address, 0, 0);
}

struct gbus_fifo *gbus_fifo_open_rdwr(struct gbus *pgbus, RMuint32 data_address, RMuint32 data_size, RMuint32 fifo_address, RMuint32 rd_ptr, RMuint32 wr_ptr)
{
	struct gbus_fifo *fifo = (struct gbus_fifo *) fifo_address;

	gbus_write_uint32(pgbus, (RMuint32) &(fifo->base), data_address);
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->size), data_size);
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->rd), rd_ptr);
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->wr), wr_ptr);

	return fifo;
}

void gbus_fifo_close(struct gbus *pgbus, struct gbus_fifo *fifo)
{
	RMASSERT(gbus_fifo_is_empty(pgbus,fifo));
}

void gbus_fifo_get_pointer(struct gbus *pgbus, struct gbus_fifo *fifo,
	RMuint32 *base, RMuint32 *size, RMuint32 *rd_ptr, RMuint32 *wr_ptr)
{
	*base = gbus_read_uint32(pgbus, (RMuint32) &(fifo->base));
	*size = gbus_read_uint32(pgbus, (RMuint32) &(fifo->size));
	*rd_ptr = gbus_read_uint32(pgbus, (RMuint32) &(fifo->rd));
	*wr_ptr = gbus_read_uint32(pgbus, (RMuint32) &(fifo->wr));
}

RMbool gbus_fifo_is_empty(struct gbus *pgbus, struct gbus_fifo *fifo)
{
	RMuint32 base, size, rd, wr;

	gbus_fifo_get_pointer(pgbus, fifo, &base, &size, &rd, &wr);

	return (rd == wr);
}

RMuint32 gbus_fifo_get_info(struct gbus *pgbus, struct gbus_fifo *fifo, RMuint32 *data_start, RMuint32 *writable, RMuint32 *readable)
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

RMuint32 gbus_fifo_get_writable_size(struct gbus *pgbus, struct gbus_fifo *fifo, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2)
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

RMuint32 gbus_fifo_get_readable_size(struct gbus *pgbus, struct gbus_fifo *fifo, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2)
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

RMuint32 gbus_fifo_get_readable_sizeWHATISTHIS(struct gbus *pgbus, struct gbus_fifo *fifo, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2, RMuint32 entry_size)
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

RMuint32 gbus_fifo_incr_write_ptr(struct gbus *pgbus, struct gbus_fifo *fifo, RMuint32 incr)
{
	RMuint32 base, size, rd, wr;

	gbus_fifo_get_pointer(pgbus, fifo, &base, &size, &rd, &wr);

	wr += incr;
	if (wr >= size)
		wr -= size;

	gbus_write_uint32(pgbus, (RMuint32) &(fifo->wr), wr);

	return wr + base;
}

RMuint32 gbus_fifo_incr_read_ptr(struct gbus *pgbus, struct gbus_fifo *fifo, RMuint32 incr)
{
	RMuint32 base, size, rd, wr;

	gbus_fifo_get_pointer(pgbus, fifo, &base, &size, &rd, &wr);

	rd += incr;
	if (rd >= size)
		rd -= size;

	gbus_write_uint32(pgbus, (RMuint32) &(fifo->rd), rd);

	return rd + base;
}


void gbus_fifo_flush_ptr(struct gbus *pgbus, struct gbus_fifo *fifo)
{
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->rd), 0);
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->wr), 0);
}

