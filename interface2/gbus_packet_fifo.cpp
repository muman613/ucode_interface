#include "include/gbus_packet_fifo.h"

static void gbus_packet_fifo_get_pointer(struct gbus *pgbus, struct gbus_packet_fifo *fifo,
					 RMuint32 *base, RMuint32 *size, RMuint32 *rd_ptr, RMuint32 *wr_ptr)
{
	*base = gbus_read_uint32(pgbus, (RMuint32) &(fifo->base));
	*size = gbus_read_uint32(pgbus, (RMuint32) &(fifo->size));
	*rd_ptr = gbus_read_uint32(pgbus, (RMuint32) &(fifo->rd));
	*wr_ptr = gbus_read_uint32(pgbus, (RMuint32) &(fifo->wr));
}

struct gbus_packet_fifo *gbus_packet_fifo_open(struct gbus *pgbus, RMuint32 data_address, RMuint32 entry_count, RMuint32 fifo_address)
{
	struct gbus_packet_fifo *fifo = (struct gbus_packet_fifo *) fifo_address;

	gbus_write_uint32(pgbus, (RMuint32) &(fifo->base), data_address);
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->size), entry_count);
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->rd), 0);
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->wr), 0);

	return fifo;
}

void gbus_packet_fifo_close(struct gbus *pgbus, struct gbus_packet_fifo *fifo)
{
	RMASSERT(gbus_packet_fifo_is_empty(pgbus,fifo));
}


RMbool gbus_packet_fifo_is_empty(struct gbus *pgbus, struct gbus_packet_fifo *fifo)
{
	RMuint32 rd, wr;

	rd = gbus_read_uint32(pgbus, (RMuint32) &(fifo->rd));
	wr = gbus_read_uint32(pgbus, (RMuint32) &(fifo->wr));

	return (rd == wr);
}

RMuint32 gbus_packet_fifo_get_info(struct gbus *pgbus, struct gbus_packet_fifo *fifo, RMuint32 *data_start, RMuint32 *writable, RMuint32 *readable)
{
	RMuint32 start, size, rd, wr;

	gbus_packet_fifo_get_pointer(pgbus, fifo, &start, &size, &rd, &wr);

	/* convert relative DMEM word address to relative GBUS byte address */
	*data_start = 4*start;

	*writable = rd - wr + size - 1;
	if ((*writable) >= size)
		(*writable) -= size;

	*readable = size - 1 - (*writable);

	return size;
}

RMuint32 gbus_packet_fifo_get_writable_size(struct gbus *pgbus, struct gbus_packet_fifo *fifo, RMuint32 entry_size, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2)
{
	RMuint32 base, size, rd, wr;

	gbus_packet_fifo_get_pointer(pgbus, fifo, &base, &size, &rd, &wr);

	/* convert relative DMEM word address to relative GBUS byte address */
	*wr_ptr1 = base*4 + wr*entry_size;

	if (wr >= rd) {
		if (rd > 0) {
			*wr_size1 = size - wr;
			*wr_ptr2 = base*4;
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

RMuint32 gbus_packet_fifo_get_readable_size(struct gbus *pgbus, struct gbus_packet_fifo *fifo, RMuint32 entry_size, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2)
{
	RMuint32 base, size, rd, wr;

	gbus_packet_fifo_get_pointer(pgbus, fifo, &base, &size, &rd, &wr);

	/* convert relative DMEM word address to relative GBUS byte address */
	*rd_ptr1 = base*4 + rd*entry_size;

	if (wr >= rd) {
		*rd_size1 = wr - rd;
		*rd_ptr2 = 0;
		return (*rd_size1);
	}
	else {
		*rd_size1 = size - rd;
		*rd_ptr2 = base*4;
		return (*rd_size1 + wr);
	}
}

RMuint32 gbus_packet_fifo_incr_write_ptr(struct gbus *pgbus, struct gbus_packet_fifo *fifo, RMuint32 entry_size, RMuint32 incr)
{
	RMuint32 base, size, rd, wr;

	gbus_packet_fifo_get_pointer(pgbus, fifo, &base, &size, &rd, &wr);

	wr += incr;
	if (wr >= size)
		wr -= size;

	gbus_write_uint32(pgbus, (RMuint32) &(fifo->wr), wr);

	/* convert relative DMEM word address to relative GBUS byte address */
	return base*4 + wr*entry_size;
}

RMuint32 gbus_packet_fifo_incr_read_ptr(struct gbus *pgbus, struct gbus_packet_fifo *fifo, RMuint32 entry_size, RMuint32 incr)
{
	RMuint32 base, size, rd, wr;

	gbus_packet_fifo_get_pointer(pgbus, fifo, &base, &size, &rd, &wr);

	rd += incr;
	if (rd >= size)
		rd -= size;

	gbus_write_uint32(pgbus, (RMuint32) &(fifo->rd), rd);

	/* convert relative DMEM word address to relative GBUS byte address */
	return base*4 + rd*entry_size;
}

/**********************************************************************************************************************************/

static void gbus_entry_fifo_get_pointer(struct gbus *pgbus, struct gbus_entry_fifo *fifo,
					 RMuint32 *base, RMuint32 *size, RMuint32 *rd_ptr, RMuint32 *wr_ptr)
{
	*base = gbus_read_uint32(pgbus, (RMuint32) &(fifo->base));
	*size = gbus_read_uint32(pgbus, (RMuint32) &(fifo->size));
	*rd_ptr = gbus_read_uint32(pgbus, (RMuint32) &(fifo->rd));
	*wr_ptr = gbus_read_uint32(pgbus, (RMuint32) &(fifo->wr));
}

struct gbus_entry_fifo *gbus_entry_fifo_open(struct gbus *pgbus, RMuint32 data_address, RMuint32 entry_count, RMuint32 fifo_address)
{
	struct gbus_entry_fifo *fifo = (struct gbus_entry_fifo *) fifo_address;

	gbus_write_uint32(pgbus, (RMuint32) &(fifo->base), data_address);
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->size), entry_count);
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->rd), 0);
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->wr), 0);

	return fifo;
}

void gbus_entry_fifo_close(struct gbus *pgbus, struct gbus_entry_fifo *fifo)
{
	RMASSERT(gbus_entry_fifo_is_empty(pgbus,fifo));
}


RMbool gbus_entry_fifo_is_empty(struct gbus *pgbus, struct gbus_entry_fifo *fifo)
{
	RMuint32 rd, wr;

	rd = gbus_read_uint32(pgbus, (RMuint32) &(fifo->rd));
	wr = gbus_read_uint32(pgbus, (RMuint32) &(fifo->wr));

	return (rd == wr);
}

void gbus_entry_fifo_flush(struct gbus *pgbus, struct gbus_entry_fifo *fifo)
{
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->rd), 0);
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->wr), 0);
}

RMuint32 gbus_entry_fifo_get_info(struct gbus *pgbus, struct gbus_entry_fifo *fifo, RMuint32 *data_start, RMuint32 *writable, RMuint32 *readable)
{
	RMuint32 start, size, rd, wr;

	gbus_entry_fifo_get_pointer(pgbus, fifo, &start, &size, &rd, &wr);

	*data_start = start;

	*writable = rd - wr + size - 1;
	if ((*writable) >= size)
		(*writable) -= size;

	*readable = size - 1 - (*writable);

	return size;
}


RMuint32 gbus_entry_fifo_get_writable_size(struct gbus *pgbus, struct gbus_entry_fifo *fifo, RMuint32 entry_size, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2)
{
	RMuint32 base, size, rd, wr;

	gbus_entry_fifo_get_pointer(pgbus, fifo, &base, &size, &rd, &wr);

	*wr_ptr1 = base + wr*entry_size;

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

RMuint32 gbus_entry_fifo_get_readable_size(struct gbus *pgbus, struct gbus_entry_fifo *fifo, RMuint32 entry_size, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2)
{
	RMuint32 base, size, rd, wr;

	gbus_entry_fifo_get_pointer(pgbus, fifo, &base, &size, &rd, &wr);

	*rd_ptr1 = base + rd*entry_size;

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

RMuint32 gbus_entry_fifo_incr_write_ptr(struct gbus *pgbus, struct gbus_entry_fifo *fifo, RMuint32 entry_size, RMuint32 incr)
{
	RMuint32 base, size, rd, wr;

	gbus_entry_fifo_get_pointer(pgbus, fifo, &base, &size, &rd, &wr);

	wr += incr;
	if (wr >= size)
		wr -= size;

	gbus_write_uint32(pgbus, (RMuint32) &(fifo->wr), wr);

	return base + wr*entry_size;
}

RMuint32 gbus_entry_fifo_incr_read_ptr(struct gbus *pgbus, struct gbus_entry_fifo *fifo, RMuint32 entry_size, RMuint32 incr)
{
	RMuint32 base, size, rd, wr;

	gbus_entry_fifo_get_pointer(pgbus, fifo, &base, &size, &rd, &wr);

	rd += incr;
	if (rd >= size)
		rd -= size;

	gbus_write_uint32(pgbus, (RMuint32) &(fifo->rd), rd);

	return base + rd*entry_size;
}

