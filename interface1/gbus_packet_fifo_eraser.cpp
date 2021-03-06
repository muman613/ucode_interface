/*****************************************
 Copyright � 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/


#include "include/gbus_packet_fifo_eraser.h"

static void gbus_packet_fifo_eraser_get_pointer(struct gbus *pgbus, struct gbus_packet_fifo_eraser *fifo, 
					 RMuint32 *base, RMuint32 *size, RMuint32 *rd_ptr, RMuint32 *wr_ptr, RMuint32 *er_ptr)
{
	*base = gbus_read_uint32(pgbus, (RMuint32) &(fifo->base));
	*size = gbus_read_uint32(pgbus, (RMuint32) &(fifo->size));
	*rd_ptr = gbus_read_uint32(pgbus, (RMuint32) &(fifo->rd));
	*wr_ptr = gbus_read_uint32(pgbus, (RMuint32) &(fifo->wr));
	*er_ptr = gbus_read_uint32(pgbus, (RMuint32) &(fifo->er));
}

struct gbus_packet_fifo_eraser *gbus_packet_fifo_eraser_open(struct gbus *pgbus, RMuint32 data_address, RMuint32 size, RMuint32 fifo_address)
{
	struct gbus_packet_fifo_eraser *fifo = (struct gbus_packet_fifo_eraser *) fifo_address;

	gbus_write_uint32(pgbus, (RMuint32) &(fifo->base), data_address);
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->size), size);
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->rd), 0);
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->wr), 0);
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->er), 0);
	
	return fifo;
}

void gbus_packet_fifo_eraser_close(struct gbus *pgbus, struct gbus_packet_fifo_eraser *fifo)
{
	// warn about pending erasable entries 
	RMASSERT(gbus_packet_fifo_eraser_is_empty(pgbus,fifo));
}

RMbool gbus_packet_fifo_eraser_is_empty(struct gbus *pgbus, struct gbus_packet_fifo_eraser *fifo)
{
	RMuint32 er, rd, wr;
	
	er   = gbus_read_uint32(pgbus, (RMuint32) &(fifo->er));
	rd   = gbus_read_uint32(pgbus, (RMuint32) &(fifo->rd));
	wr   = gbus_read_uint32(pgbus, (RMuint32) &(fifo->wr));
	
	return ((er==rd)&&(rd==wr));
}

RMuint32 gbus_packet_fifo_eraser_get_info(struct gbus *pgbus, struct gbus_packet_fifo_eraser *fifo, RMuint32 offset, RMuint32 *data_start, RMuint32 *writable, RMuint32 *readable, RMuint32 *erasable)
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

RMuint32 gbus_packet_fifo_eraser_get_writable_size(struct gbus *pgbus, struct gbus_packet_fifo_eraser *fifo,
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

RMuint32 gbus_packet_fifo_eraser_get_readable_size(struct gbus *pgbus, struct gbus_packet_fifo_eraser *fifo,
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

RMuint32 gbus_packet_fifo_eraser_get_erasable_size(struct gbus *pgbus, struct gbus_packet_fifo_eraser *fifo,
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

RMuint32 gbus_packet_fifo_eraser_incr_write_ptr(struct gbus *pgbus, struct gbus_packet_fifo_eraser *fifo,
						RMuint32 offset, RMuint32 entry_size, RMuint32 incr)
{
	RMuint32 base, size, rd, wr, er;
	gbus_packet_fifo_eraser_get_pointer(pgbus, fifo, &base, &size, &rd, &wr, &er);
	
	wr += incr;
	if (wr >= size)
		wr -= size;
	
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->wr), wr);
		
	/* convert relative DMEM word address to relative GBUS byte address */ 
	return offset + base*4 + wr*entry_size;
}

RMuint32 gbus_packet_fifo_eraser_incr_read_ptr(struct gbus *pgbus, struct gbus_packet_fifo_eraser *fifo,
						RMuint32 offset, RMuint32 entry_size, RMuint32 incr)
{
	RMuint32 base, size, rd, wr, er;
	gbus_packet_fifo_eraser_get_pointer(pgbus, fifo, &base, &size, &rd, &wr, &er);
	
	rd += incr;
	if (rd >= size)
		rd -= size;
		
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->rd), rd);
	
	/* convert relative DMEM word address to relative GBUS byte address */ 
	return offset + base*4 + rd*entry_size;
}

RMuint32 gbus_packet_fifo_eraser_incr_erase_ptr(struct gbus *pgbus, struct gbus_packet_fifo_eraser *fifo,
						RMuint32 offset, RMuint32 entry_size, RMuint32 incr)
{
	RMuint32 base, size, rd, wr, er;
	gbus_packet_fifo_eraser_get_pointer(pgbus, fifo, &base, &size, &rd, &wr, &er);
	
	er += incr;
	if (er >= size)
		er -= size;
		
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->er), er);
	
	/* convert relative DMEM word address to relative GBUS byte address */ 
	return offset + base*4 + er*entry_size;
}

/**********************************************************************************************************************************/

static void gbus_entry_fifo_eraser_get_pointer(struct gbus *pgbus, struct gbus_entry_fifo_eraser *fifo, 
					 RMuint32 *base, RMuint32 *size, RMuint32 *rd_ptr, RMuint32 *wr_ptr, RMuint32 *er_ptr)
{
	*base = gbus_read_uint32(pgbus, (RMuint32) &(fifo->base));
	*size = gbus_read_uint32(pgbus, (RMuint32) &(fifo->size));
	*rd_ptr = gbus_read_uint32(pgbus, (RMuint32) &(fifo->rd));
	*wr_ptr = gbus_read_uint32(pgbus, (RMuint32) &(fifo->wr));
	*er_ptr = gbus_read_uint32(pgbus, (RMuint32) &(fifo->er));
}

struct gbus_entry_fifo_eraser *gbus_entry_fifo_eraser_open(struct gbus *pgbus, RMuint32 data_address, RMuint32 size, RMuint32 fifo_address)
{
	struct gbus_entry_fifo_eraser *fifo = (struct gbus_entry_fifo_eraser *) fifo_address;

	gbus_write_uint32(pgbus, (RMuint32) &(fifo->base), data_address);
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->size), size);
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->rd), 0);
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->wr), 0);
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->er), 0);
	
	return fifo;
}

void gbus_entry_fifo_eraser_close(struct gbus *pgbus, struct gbus_entry_fifo_eraser *fifo)
{
	// warn about pending erasable entries 
	RMASSERT(gbus_entry_fifo_eraser_is_empty(pgbus,fifo));
}

RMbool gbus_entry_fifo_eraser_is_empty(struct gbus *pgbus, struct gbus_entry_fifo_eraser *fifo)
{
	RMuint32 er, rd, wr;
	
	er   = gbus_read_uint32(pgbus, (RMuint32) &(fifo->er));
	rd   = gbus_read_uint32(pgbus, (RMuint32) &(fifo->rd));
	wr   = gbus_read_uint32(pgbus, (RMuint32) &(fifo->wr));
	
	return ((er==rd)&&(rd==wr));
}

void gbus_entry_fifo_eraser_flush(struct gbus *pgbus, struct gbus_entry_fifo_eraser *fifo)
{
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->rd), 0);
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->wr), 0);
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->er), 0);
}

RMuint32 gbus_entry_fifo_eraser_get_info(struct gbus *pgbus, struct gbus_entry_fifo_eraser *fifo, RMuint32 *data_start, RMuint32 *writable, RMuint32 *readable, RMuint32 *erasable)
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

RMuint32 gbus_entry_fifo_eraser_get_writable_size(struct gbus *pgbus, struct gbus_entry_fifo_eraser *fifo,
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

RMuint32 gbus_entry_fifo_eraser_get_readable_size(struct gbus *pgbus, struct gbus_entry_fifo_eraser *fifo,
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

RMuint32 gbus_entry_fifo_eraser_get_erasable_size(struct gbus *pgbus, struct gbus_entry_fifo_eraser *fifo,
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

RMuint32 gbus_entry_fifo_eraser_incr_write_ptr(struct gbus *pgbus, struct gbus_entry_fifo_eraser *fifo,
						RMuint32 entry_size, RMuint32 incr)
{
	RMuint32 base, size, rd, wr, er;
	gbus_entry_fifo_eraser_get_pointer(pgbus, fifo, &base, &size, &rd, &wr, &er);
	
	wr += incr;
	if (wr >= size)
		wr -= size;
	
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->wr), wr);
		
	return base + wr*entry_size;
}

RMuint32 gbus_entry_fifo_eraser_incr_read_ptr(struct gbus *pgbus, struct gbus_entry_fifo_eraser *fifo,
						RMuint32 entry_size, RMuint32 incr)
{
	RMuint32 base, size, rd, wr, er;
	gbus_entry_fifo_eraser_get_pointer(pgbus, fifo, &base, &size, &rd, &wr, &er);
	
	rd += incr;
	if (rd >= size)
		rd -= size;
		
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->rd), rd);
	
	return base + rd*entry_size;
}

RMuint32 gbus_entry_fifo_eraser_incr_erase_ptr(struct gbus *pgbus, struct gbus_entry_fifo_eraser *fifo,
						RMuint32 entry_size, RMuint32 incr)
{
	RMuint32 base, size, rd, wr, er;
	gbus_entry_fifo_eraser_get_pointer(pgbus, fifo, &base, &size, &rd, &wr, &er);
	
	er += incr;
	if (er >= size)
		er -= size;
		
	gbus_write_uint32(pgbus, (RMuint32) &(fifo->er), er);
	
	return base + er*entry_size;
}

