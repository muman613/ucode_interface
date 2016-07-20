/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   gbus_packet_fifo_eraser.h
  @brief  

   @brief a fifo of entries instead of a fifo of bytes.
  Useful for a InbandCommand fifos shared with ucode.
  The internal base is relative to DMEM and divided by 4.
  To convert it to gbus the base returned is multiplied by 4
  and added with offset.
  The rd, wr, er pointers returned by functions are multiplied
  by entry_size and added with base*4 + offset.
  The "size" returned is expressed in entry_size unit.
  This works for both 16 and 32 bits RISCS.

  @author Julien Soulier, Aurelia Popa-Radu
  @date   2003-09-18
*/

#ifndef __GBUS_PACKET_FIFO_ERASER_H__
#define __GBUS_PACKET_FIFO_ERASER_H__

#include "llad/include/gbus.h"

struct gbus_packet_fifo_eraser {
	RMuint32 base;	// start of fifo, relative to DMEM and divided by 4
	RMuint32 size;	// unit in entry_size
	RMuint32 rd;	// unit in entry_size, relative to base
	RMuint32 wr;	// unit in entry_size, relative to base
	RMuint32 er;	// unit in entry_size, relative to base
};

/* fifo_eraser of entries instead of a fifo of bytes.
  The data base address is absolute gbus address.
  The rd, wr, er pointers returned by functions are absolute gbus address. 
  The size is expressed in entry_size unit. 
  The internal rd, wr, er pointers are expressed in entry_size unit and are relative to base. 
  Used for inband fifos allocated in DRAM.
 */
struct gbus_entry_fifo_eraser {
	RMuint32 base;	/* start of fifo */
	RMuint32 size;	/* unit in entry_size */
	RMuint32 rd;	/* unit in entry_size, relative to base */
	RMuint32 wr;	/* unit in entry_size, relative to base */
	RMuint32 er;	/* unit in entry_size, relative to base */
};

RM_EXTERN_C_BLOCKSTART

struct gbus_packet_fifo_eraser *gbus_packet_fifo_eraser_open(struct gbus *pgbus, RMuint32 data_address, RMuint32 size, RMuint32 fifo_address);
void gbus_packet_fifo_eraser_close(struct gbus *pgbus, struct gbus_packet_fifo_eraser *fifo);
RMbool gbus_packet_fifo_eraser_is_empty(struct gbus *pgbus, struct gbus_packet_fifo_eraser *fifo);
RMuint32 gbus_packet_fifo_eraser_get_info(struct gbus *pgbus, struct gbus_packet_fifo_eraser *fifo, RMuint32 offset, RMuint32 *data_start, RMuint32 *writable, RMuint32 *readable, RMuint32 *erasable);
RMuint32 gbus_packet_fifo_eraser_get_writable_size(struct gbus *pgbus, struct gbus_packet_fifo_eraser *fifo, RMuint32 offset, RMuint32 entry_size, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2);
RMuint32 gbus_packet_fifo_eraser_get_readable_size(struct gbus *pgbus, struct gbus_packet_fifo_eraser *fifo, RMuint32 offset, RMuint32 entry_size, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2);
RMuint32 gbus_packet_fifo_eraser_get_erasable_size(struct gbus *pgbus, struct gbus_packet_fifo_eraser *fifo, RMuint32 offset, RMuint32 entry_size, RMuint32 *er_ptr1, RMuint32 *er_size1, RMuint32 *er_ptr2);
RMuint32 gbus_packet_fifo_eraser_incr_write_ptr(struct gbus *pgbus, struct gbus_packet_fifo_eraser *fifo, RMuint32 offset, RMuint32 entry_size, RMuint32 incr);
RMuint32 gbus_packet_fifo_eraser_incr_read_ptr(struct gbus *pgbus, struct gbus_packet_fifo_eraser *fifo, RMuint32 offset, RMuint32 entry_size, RMuint32 incr);
RMuint32 gbus_packet_fifo_eraser_incr_erase_ptr(struct gbus *pgbus, struct gbus_packet_fifo_eraser *fifo, RMuint32 offset, RMuint32 entry_size, RMuint32 incr);

struct gbus_entry_fifo_eraser *gbus_entry_fifo_eraser_open(struct gbus *pgbus, RMuint32 data_address, RMuint32 size, RMuint32 fifo_address);
void gbus_entry_fifo_eraser_close(struct gbus *pgbus, struct gbus_entry_fifo_eraser *fifo);
RMbool gbus_entry_fifo_eraser_is_empty(struct gbus *pgbus, struct gbus_entry_fifo_eraser *fifo);
void gbus_entry_fifo_eraser_flush(struct gbus *pgbus, struct gbus_entry_fifo_eraser *fifo);
RMuint32 gbus_entry_fifo_eraser_get_info(struct gbus *pgbus, struct gbus_entry_fifo_eraser *fifo, RMuint32 *data_start, RMuint32 *writable, RMuint32 *readable, RMuint32 *erasable);
RMuint32 gbus_entry_fifo_eraser_get_writable_size(struct gbus *pgbus, struct gbus_entry_fifo_eraser *fifo, RMuint32 entry_size, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2);
RMuint32 gbus_entry_fifo_eraser_get_readable_size(struct gbus *pgbus, struct gbus_entry_fifo_eraser *fifo, RMuint32 entry_size, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2);
RMuint32 gbus_entry_fifo_eraser_get_erasable_size(struct gbus *pgbus, struct gbus_entry_fifo_eraser *fifo, RMuint32 entry_size, RMuint32 *er_ptr1, RMuint32 *er_size1, RMuint32 *er_ptr2);
RMuint32 gbus_entry_fifo_eraser_incr_write_ptr(struct gbus *pgbus, struct gbus_entry_fifo_eraser *fifo, RMuint32 entry_size, RMuint32 incr);
RMuint32 gbus_entry_fifo_eraser_incr_read_ptr(struct gbus *pgbus, struct gbus_entry_fifo_eraser *fifo, RMuint32 entry_size, RMuint32 incr);
RMuint32 gbus_entry_fifo_eraser_incr_erase_ptr(struct gbus *pgbus, struct gbus_entry_fifo_eraser *fifo, RMuint32 entry_size, RMuint32 incr);

RM_EXTERN_C_BLOCKEND

#endif // __GBUS_PACKET_FIFO_ERASER_H__
