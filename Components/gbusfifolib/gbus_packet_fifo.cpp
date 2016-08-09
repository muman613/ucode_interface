/**
 *  @file       gbus_packet_fifo.cpp
 *  @date       August 8, 2016
 *  @author     Michael A. Uman
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define ALLOW_OS_CODE
#include "remote_client/llad.h"
#include "remote_client/gbus.h"
#include "gbus_packet_fifo.h"

//#include "include/gbus_packet_fifo.h"

static void gbus_packet_fifo_get_pointer(GBUS_PTR pgbus, struct gbus_packet_fifo *fifo,
					 RMuint32 *base, RMuint32 *size, RMuint32 *rd_ptr, RMuint32 *wr_ptr)
{
	*base = pgbus->gbus_read_uint32((RMuint32) &(fifo->base));
	*size = pgbus->gbus_read_uint32((RMuint32) &(fifo->size));
	*rd_ptr = pgbus->gbus_read_uint32((RMuint32) &(fifo->rd));
	*wr_ptr = pgbus->gbus_read_uint32((RMuint32) &(fifo->wr));
}

struct gbus_packet_fifo *gbus_packet_fifo_open(GBUS_PTR pgbus, RMuint32 data_address, RMuint32 entry_count, RMuint32 fifo_address)
{
	struct gbus_packet_fifo *fifo = (struct gbus_packet_fifo *) fifo_address;

	pgbus->gbus_write_uint32((RMuint32) &(fifo->base), data_address);
	pgbus->gbus_write_uint32((RMuint32) &(fifo->size), entry_count);
	pgbus->gbus_write_uint32((RMuint32) &(fifo->rd), 0);
	pgbus->gbus_write_uint32((RMuint32) &(fifo->wr), 0);

	return fifo;
}

void gbus_packet_fifo_close(GBUS_PTR pgbus, struct gbus_packet_fifo *fifo)
{
	RMASSERT(gbus_packet_fifo_is_empty(pgbus,fifo));
}


RMbool gbus_packet_fifo_is_empty(GBUS_PTR pgbus, struct gbus_packet_fifo *fifo)
{
	RMuint32 rd, wr;

	rd = pgbus->gbus_read_uint32((RMuint32) &(fifo->rd));
	wr = pgbus->gbus_read_uint32((RMuint32) &(fifo->wr));

	return (rd == wr);
}

RMuint32 gbus_packet_fifo_get_info(GBUS_PTR pgbus, struct gbus_packet_fifo *fifo, RMuint32 *data_start, RMuint32 *writable, RMuint32 *readable)
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

RMuint32 gbus_packet_fifo_get_writable_size(GBUS_PTR pgbus, struct gbus_packet_fifo *fifo, RMuint32 entry_size, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2)
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

RMuint32 gbus_packet_fifo_get_readable_size(GBUS_PTR pgbus, struct gbus_packet_fifo *fifo, RMuint32 entry_size, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2)
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

RMuint32 gbus_packet_fifo_incr_write_ptr(GBUS_PTR pgbus, struct gbus_packet_fifo *fifo, RMuint32 entry_size, RMuint32 incr)
{
	RMuint32 base, size, rd, wr;

	gbus_packet_fifo_get_pointer(pgbus, fifo, &base, &size, &rd, &wr);

	wr += incr;
	if (wr >= size)
		wr -= size;

	pgbus->gbus_write_uint32((RMuint32) &(fifo->wr), wr);

	/* convert relative DMEM word address to relative GBUS byte address */
	return base*4 + wr*entry_size;
}

RMuint32 gbus_packet_fifo_incr_read_ptr(GBUS_PTR pgbus, struct gbus_packet_fifo *fifo, RMuint32 entry_size, RMuint32 incr)
{
	RMuint32 base, size, rd, wr;

	gbus_packet_fifo_get_pointer(pgbus, fifo, &base, &size, &rd, &wr);

	rd += incr;
	if (rd >= size)
		rd -= size;

	pgbus->gbus_write_uint32((RMuint32) &(fifo->rd), rd);

	/* convert relative DMEM word address to relative GBUS byte address */
	return base*4 + rd*entry_size;
}

/**********************************************************************************************************************************/

static void gbus_entry_fifo_get_pointer(GBUS_PTR pgbus, struct gbus_entry_fifo *fifo,
					 RMuint32 *base, RMuint32 *size, RMuint32 *rd_ptr, RMuint32 *wr_ptr)
{
	*base = pgbus->gbus_read_uint32((RMuint32) &(fifo->base));
	*size = pgbus->gbus_read_uint32((RMuint32) &(fifo->size));
	*rd_ptr = pgbus->gbus_read_uint32((RMuint32) &(fifo->rd));
	*wr_ptr = pgbus->gbus_read_uint32((RMuint32) &(fifo->wr));
}

struct gbus_entry_fifo *gbus_entry_fifo_open(GBUS_PTR pgbus, RMuint32 data_address, RMuint32 entry_count, RMuint32 fifo_address)
{
	struct gbus_entry_fifo *fifo = (struct gbus_entry_fifo *) fifo_address;

	pgbus->gbus_write_uint32((RMuint32) &(fifo->base), data_address);
	pgbus->gbus_write_uint32((RMuint32) &(fifo->size), entry_count);
	pgbus->gbus_write_uint32((RMuint32) &(fifo->rd), 0);
	pgbus->gbus_write_uint32((RMuint32) &(fifo->wr), 0);

	return fifo;
}

void gbus_entry_fifo_close(GBUS_PTR pgbus, struct gbus_entry_fifo *fifo)
{
	RMASSERT(gbus_entry_fifo_is_empty(pgbus,fifo));
}


RMbool gbus_entry_fifo_is_empty(GBUS_PTR pgbus, struct gbus_entry_fifo *fifo)
{
	RMuint32 rd, wr;

	rd = pgbus->gbus_read_uint32((RMuint32) &(fifo->rd));
	wr = pgbus->gbus_read_uint32((RMuint32) &(fifo->wr));

	return (rd == wr);
}

void gbus_entry_fifo_flush(GBUS_PTR pgbus, struct gbus_entry_fifo *fifo)
{
	pgbus->gbus_write_uint32((RMuint32) &(fifo->rd), 0);
	pgbus->gbus_write_uint32((RMuint32) &(fifo->wr), 0);
}

RMuint32 gbus_entry_fifo_get_info(GBUS_PTR pgbus, struct gbus_entry_fifo *fifo, RMuint32 *data_start, RMuint32 *writable, RMuint32 *readable)
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


RMuint32 gbus_entry_fifo_get_writable_size(GBUS_PTR pgbus, struct gbus_entry_fifo *fifo, RMuint32 entry_size, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2)
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

RMuint32 gbus_entry_fifo_get_readable_size(GBUS_PTR pgbus, struct gbus_entry_fifo *fifo, RMuint32 entry_size, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2)
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

RMuint32 gbus_entry_fifo_incr_write_ptr(GBUS_PTR pgbus, struct gbus_entry_fifo *fifo, RMuint32 entry_size, RMuint32 incr)
{
	RMuint32 base, size, rd, wr;

	gbus_entry_fifo_get_pointer(pgbus, fifo, &base, &size, &rd, &wr);

	wr += incr;
	if (wr >= size)
		wr -= size;

	pgbus->gbus_write_uint32((RMuint32) &(fifo->wr), wr);

	return base + wr*entry_size;
}

RMuint32 gbus_entry_fifo_incr_read_ptr(GBUS_PTR pgbus, struct gbus_entry_fifo *fifo, RMuint32 entry_size, RMuint32 incr)
{
	RMuint32 base, size, rd, wr;

	gbus_entry_fifo_get_pointer(pgbus, fifo, &base, &size, &rd, &wr);

	rd += incr;
	if (rd >= size)
		rd -= size;

	pgbus->gbus_write_uint32((RMuint32) &(fifo->rd), rd);

	return base + rd*entry_size;
}

