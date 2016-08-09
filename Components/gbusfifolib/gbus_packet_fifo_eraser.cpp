/**
 *  @file       gbus_packet_fifo_eraser.cpp
 *  @date       August 8, 2016
 *  @author     Michael A. Uman
 */

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define ALLOW_OS_CODE
#include "remote_client/llad.h"
#include "remote_client/gbus.h"
#include "gbus_packet_fifo_eraser.h"

static void gbus_packet_fifo_eraser_get_pointer(GBUS_PTR pgbus, struct gbus_packet_fifo_eraser *fifo,
					 RMuint32 *base, RMuint32 *size, RMuint32 *rd_ptr, RMuint32 *wr_ptr, RMuint32 *er_ptr)
{
	*base   = pgbus->gbus_read_uint32((RMuint32) &(fifo->base));
	*size   = pgbus->gbus_read_uint32((RMuint32) &(fifo->size));
	*rd_ptr = pgbus->gbus_read_uint32((RMuint32) &(fifo->rd));
	*wr_ptr = pgbus->gbus_read_uint32((RMuint32) &(fifo->wr));
	*er_ptr = pgbus->gbus_read_uint32((RMuint32) &(fifo->er));
}

struct gbus_packet_fifo_eraser *gbus_packet_fifo_eraser_open(GBUS_PTR pgbus, RMuint32 data_address, RMuint32 size, RMuint32 fifo_address)
{
	struct gbus_packet_fifo_eraser *fifo = (struct gbus_packet_fifo_eraser *) fifo_address;

	pgbus->gbus_write_uint32((RMuint32) &(fifo->base), data_address);
	pgbus->gbus_write_uint32((RMuint32) &(fifo->size), size);
	pgbus->gbus_write_uint32((RMuint32) &(fifo->rd), 0);
	pgbus->gbus_write_uint32((RMuint32) &(fifo->wr), 0);
	pgbus->gbus_write_uint32((RMuint32) &(fifo->er), 0);

	return fifo;
}

void gbus_packet_fifo_eraser_close(GBUS_PTR pgbus, struct gbus_packet_fifo_eraser *fifo)
{
	// warn about pending erasable entries
	RMASSERT(gbus_packet_fifo_eraser_is_empty(pgbus,fifo));
}

RMbool gbus_packet_fifo_eraser_is_empty(GBUS_PTR pgbus, struct gbus_packet_fifo_eraser *fifo)
{
	RMuint32 er, rd, wr;

	er   = pgbus->gbus_read_uint32((RMuint32) &(fifo->er));
	rd   = pgbus->gbus_read_uint32((RMuint32) &(fifo->rd));
	wr   = pgbus->gbus_read_uint32((RMuint32) &(fifo->wr));

	return ((er==rd)&&(rd==wr));
}

RMuint32 gbus_packet_fifo_eraser_get_info(GBUS_PTR pgbus, struct gbus_packet_fifo_eraser *fifo, RMuint32 offset, RMuint32 *data_start, RMuint32 *writable, RMuint32 *readable, RMuint32 *erasable)
{
	RMuint32 start, size, rd, wr, er;

	gbus_packet_fifo_eraser_get_pointer(pgbus, fifo, &start, &size, &rd, &wr, &er);

	/* convert relative DMEM word address to relative GBUS byte address */
	*data_start = offset + 4*start;

	*writable = er - wr + size - 1;
	if ((*writable) >= size)
		(*writable) -= size;

	*readable = wr - rd + size;
	if ((*readable) >= size)
		(*readable) -= size;

	(*erasable) = size - 1 - (*readable) - (*writable);

	return size;
}

RMuint32 gbus_packet_fifo_eraser_get_writable_size(GBUS_PTR pgbus, struct gbus_packet_fifo_eraser *fifo,
						RMuint32 offset, RMuint32 entry_size, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2)
{
	RMuint32 base, size, rd, wr, er;
	gbus_packet_fifo_eraser_get_pointer(pgbus, fifo, &base, &size, &rd, &wr, &er);

	/* convert relative DMEM word address to relative GBUS byte address */
	*wr_ptr1 = offset + base*4 + wr*entry_size;

	if (wr >= er) {
		if (er > 0) {
			*wr_size1 = size - wr;
			*wr_ptr2 = offset + base*4;
			return (*wr_size1 + er - 1);
		}
		else {
			*wr_size1 = size - 1 - wr;
			*wr_ptr2 = offset;
			return (*wr_size1);
		}
	}
	else {
		*wr_size1 = er - 1 - wr;
		*wr_ptr2 = 0;
		return (*wr_size1);
	}
}

RMuint32 gbus_packet_fifo_eraser_get_readable_size(GBUS_PTR pgbus, struct gbus_packet_fifo_eraser *fifo,
						RMuint32 offset, RMuint32 entry_size, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2)
{
	RMuint32 base, size, rd, wr, er;
	gbus_packet_fifo_eraser_get_pointer(pgbus, fifo, &base, &size, &rd, &wr, &er);

	/* convert relative DMEM word address to relative GBUS byte address */
	*rd_ptr1 = offset + base*4 + rd*entry_size;

	if (wr >= rd) {
		*rd_size1 = wr - rd;
		*rd_ptr2 = offset;
		return (*rd_size1);
	}
	else {
		*rd_size1 = size - rd;
		*rd_ptr2 = offset + base*4;
		return (*rd_size1 + wr);
	}
}

RMuint32 gbus_packet_fifo_eraser_get_erasable_size(GBUS_PTR pgbus, struct gbus_packet_fifo_eraser *fifo,
						 RMuint32 offset, RMuint32 entry_size, RMuint32 *er_ptr1, RMuint32 *er_size1, RMuint32 *er_ptr2)
{
	RMuint32 base, size, rd, wr, er;
	gbus_packet_fifo_eraser_get_pointer(pgbus, fifo, &base, &size, &rd, &wr, &er);

	/* convert relative DMEM word address to relative GBUS byte address */
	*er_ptr1 = offset + base*4 + er*entry_size;

	if (rd >= er) {
		*er_size1 = rd - er;
		*er_ptr2 = offset;
		return (*er_size1);
	}
	else {
		*er_size1 = size - er;
		*er_ptr2 = offset + base*4;
		return (*er_size1 + rd);
	}
}

RMuint32 gbus_packet_fifo_eraser_incr_write_ptr(GBUS_PTR pgbus, struct gbus_packet_fifo_eraser *fifo,
						RMuint32 offset, RMuint32 entry_size, RMuint32 incr)
{
	RMuint32 base, size, rd, wr, er;
	gbus_packet_fifo_eraser_get_pointer(pgbus, fifo, &base, &size, &rd, &wr, &er);

	wr += incr;
	if (wr >= size)
		wr -= size;

    pgbus->gbus_write_uint32((RMuint32) &(fifo->wr), wr);

	/* convert relative DMEM word address to relative GBUS byte address */
	return offset + base*4 + wr*entry_size;
}

RMuint32 gbus_packet_fifo_eraser_incr_read_ptr(GBUS_PTR pgbus, struct gbus_packet_fifo_eraser *fifo,
						RMuint32 offset, RMuint32 entry_size, RMuint32 incr)
{
	RMuint32 base, size, rd, wr, er;
	gbus_packet_fifo_eraser_get_pointer(pgbus, fifo, &base, &size, &rd, &wr, &er);

	rd += incr;
	if (rd >= size)
		rd -= size;

	pgbus->gbus_write_uint32((RMuint32) &(fifo->rd), rd);

	/* convert relative DMEM word address to relative GBUS byte address */
	return offset + base*4 + rd*entry_size;
}

RMuint32 gbus_packet_fifo_eraser_incr_erase_ptr(GBUS_PTR pgbus, struct gbus_packet_fifo_eraser *fifo,
						RMuint32 offset, RMuint32 entry_size, RMuint32 incr)
{
	RMuint32 base, size, rd, wr, er;
	gbus_packet_fifo_eraser_get_pointer(pgbus, fifo, &base, &size, &rd, &wr, &er);

	er += incr;
	if (er >= size)
		er -= size;

	pgbus->gbus_write_uint32((RMuint32) &(fifo->er), er);

	/* convert relative DMEM word address to relative GBUS byte address */
	return offset + base*4 + er*entry_size;
}

/**********************************************************************************************************************************/

static void gbus_entry_fifo_eraser_get_pointer(GBUS_PTR pgbus, struct gbus_entry_fifo_eraser *fifo,
					 RMuint32 *base, RMuint32 *size, RMuint32 *rd_ptr, RMuint32 *wr_ptr, RMuint32 *er_ptr)
{
	*base   = pgbus->gbus_read_uint32((RMuint32) &(fifo->base));
	*size   = pgbus->gbus_read_uint32((RMuint32) &(fifo->size));
	*rd_ptr = pgbus->gbus_read_uint32((RMuint32) &(fifo->rd));
	*wr_ptr = pgbus->gbus_read_uint32((RMuint32) &(fifo->wr));
	*er_ptr = pgbus->gbus_read_uint32((RMuint32) &(fifo->er));
}

struct gbus_entry_fifo_eraser *gbus_entry_fifo_eraser_open(GBUS_PTR pgbus, RMuint32 data_address, RMuint32 size, RMuint32 fifo_address)
{
	struct gbus_entry_fifo_eraser *fifo = (struct gbus_entry_fifo_eraser *) fifo_address;

	pgbus->gbus_write_uint32((RMuint32) &(fifo->base), data_address);
	pgbus->gbus_write_uint32((RMuint32) &(fifo->size), size);
	pgbus->gbus_write_uint32((RMuint32) &(fifo->rd), 0);
	pgbus->gbus_write_uint32((RMuint32) &(fifo->wr), 0);
	pgbus->gbus_write_uint32((RMuint32) &(fifo->er), 0);

	return fifo;
}

void gbus_entry_fifo_eraser_close(GBUS_PTR pgbus, struct gbus_entry_fifo_eraser *fifo)
{
	// warn about pending erasable entries
	RMASSERT(gbus_entry_fifo_eraser_is_empty(pgbus,fifo));
}

RMbool gbus_entry_fifo_eraser_is_empty(GBUS_PTR pgbus, struct gbus_entry_fifo_eraser *fifo)
{
	RMuint32 er, rd, wr;

	er   = pgbus->gbus_read_uint32((RMuint32) &(fifo->er));
	rd   = pgbus->gbus_read_uint32((RMuint32) &(fifo->rd));
	wr   = pgbus->gbus_read_uint32((RMuint32) &(fifo->wr));

	return ((er==rd)&&(rd==wr));
}

void gbus_entry_fifo_eraser_flush(GBUS_PTR pgbus, struct gbus_entry_fifo_eraser *fifo)
{
	pgbus->gbus_write_uint32((RMuint32) &(fifo->rd), 0);
	pgbus->gbus_write_uint32((RMuint32) &(fifo->wr), 0);
	pgbus->gbus_write_uint32((RMuint32) &(fifo->er), 0);
}

RMuint32 gbus_entry_fifo_eraser_get_info(GBUS_PTR pgbus, struct gbus_entry_fifo_eraser *fifo, RMuint32 *data_start, RMuint32 *writable, RMuint32 *readable, RMuint32 *erasable)
{
	RMuint32 start, size, rd, wr, er;

	gbus_entry_fifo_eraser_get_pointer(pgbus, fifo, &start, &size, &rd, &wr, &er);

	*data_start = start;

	*writable = er - wr + size - 1;
	if ((*writable) >= size)
		(*writable) -= size;

	*readable = wr - rd + size;
	if ((*readable) >= size)
		(*readable) -= size;

	(*erasable) = size - 1 - (*readable) - (*writable);

	return size;
}

RMuint32 gbus_entry_fifo_eraser_get_writable_size(GBUS_PTR pgbus, struct gbus_entry_fifo_eraser *fifo,
						RMuint32 entry_size, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2)
{
	RMuint32 base, size, rd, wr, er;
	gbus_entry_fifo_eraser_get_pointer(pgbus, fifo, &base, &size, &rd, &wr, &er);

	*wr_ptr1 = base + wr*entry_size;

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

RMuint32 gbus_entry_fifo_eraser_get_readable_size(GBUS_PTR pgbus, struct gbus_entry_fifo_eraser *fifo,
						RMuint32 entry_size, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2)
{
	RMuint32 base, size, rd, wr, er;
	gbus_entry_fifo_eraser_get_pointer(pgbus, fifo, &base, &size, &rd, &wr, &er);

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

RMuint32 gbus_entry_fifo_eraser_get_erasable_size(GBUS_PTR pgbus, struct gbus_entry_fifo_eraser *fifo,
						 RMuint32 entry_size, RMuint32 *er_ptr1, RMuint32 *er_size1, RMuint32 *er_ptr2)
{
	RMuint32 base, size, rd, wr, er;
	gbus_entry_fifo_eraser_get_pointer(pgbus, fifo, &base, &size, &rd, &wr, &er);

	*er_ptr1 = base + er*entry_size;

	if (rd >= er) {
		*er_size1 = rd - er;
		*er_ptr2 = 0;
		return (*er_size1);
	}
	else {
		*er_size1 = size - er;
		*er_ptr2 = base;
		return (*er_size1 + rd);
	}
}

RMuint32 gbus_entry_fifo_eraser_incr_write_ptr(GBUS_PTR pgbus, struct gbus_entry_fifo_eraser *fifo,
						RMuint32 entry_size, RMuint32 incr)
{
	RMuint32 base, size, rd, wr, er;
	gbus_entry_fifo_eraser_get_pointer(pgbus, fifo, &base, &size, &rd, &wr, &er);

	wr += incr;
	if (wr >= size)
		wr -= size;

	pgbus->gbus_write_uint32((RMuint32) &(fifo->wr), wr);

	return base + wr*entry_size;
}

RMuint32 gbus_entry_fifo_eraser_incr_read_ptr(GBUS_PTR pgbus, struct gbus_entry_fifo_eraser *fifo,
						RMuint32 entry_size, RMuint32 incr)
{
	RMuint32 base, size, rd, wr, er;
	gbus_entry_fifo_eraser_get_pointer(pgbus, fifo, &base, &size, &rd, &wr, &er);

	rd += incr;
	if (rd >= size)
		rd -= size;

	pgbus->gbus_write_uint32((RMuint32) &(fifo->rd), rd);

	return base + rd*entry_size;
}

RMuint32 gbus_entry_fifo_eraser_incr_erase_ptr(GBUS_PTR pgbus, struct gbus_entry_fifo_eraser *fifo,
						RMuint32 entry_size, RMuint32 incr)
{
	RMuint32 base, size, rd, wr, er;
	gbus_entry_fifo_eraser_get_pointer(pgbus, fifo, &base, &size, &rd, &wr, &er);

	er += incr;
	if (er >= size)
		er -= size;

	pgbus->gbus_write_uint32((RMuint32) &(fifo->er), er);

	return base + er*entry_size;
}

