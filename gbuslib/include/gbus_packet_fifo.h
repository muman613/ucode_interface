/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file gbus_packet_fifo.h 
  
  @brief a fifo of entries instead of a fifo of bytes. (useful for a PTS fifo
  shared with ucode for example). Moreover the data base address is a
  relative word address which is converted to a relative byte address
  by multiplying it by 4. This works for both 16 and 32 bits RISCS.
  
  @author Julien Soulier
  @date   2003-09-02
*/

#ifndef __GBUS_PACKET_FIFO_H__
#define __GBUS_PACKET_FIFO_H__

#include "llad/include/gbus.h"

RM_EXTERN_C_BLOCKSTART

struct gbus_packet_fifo {
	RMuint32 base;
	RMuint32 size;
	RMuint32 rd;
	RMuint32 wr;
};

/* fifo of entries instead of a fifo of bytes. The data base address is
  absolute gbus address. Used for pts fifo allocated in DRAM.
 */
struct gbus_entry_fifo {
	RMuint32 base;
	RMuint32 size;
	RMuint32 rd;
	RMuint32 wr;
};

struct gbus_packet_fifo *gbus_packet_fifo_open(struct gbus *pgbus, RMuint32 data_address, RMuint32 data_size, RMuint32 fifo_address);

void gbus_packet_fifo_close(struct gbus *pgbus, struct gbus_packet_fifo *fifo);

RMbool gbus_packet_fifo_is_empty(struct gbus *pgbus, struct gbus_packet_fifo *fifo);

RMuint32 gbus_packet_fifo_get_info(struct gbus *pgbus, struct gbus_packet_fifo *fifo, RMuint32 *data_start, RMuint32 *writable, RMuint32 *readable);

RMuint32 gbus_packet_fifo_get_writable_size(struct gbus *pgbus, struct gbus_packet_fifo *fifo, RMuint32 entry_size, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2);

RMuint32 gbus_packet_fifo_get_readable_size(struct gbus *pgbus, struct gbus_packet_fifo *fifo, RMuint32 entry_size, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2);

RMuint32 gbus_packet_fifo_incr_write_ptr(struct gbus *pgbus, struct gbus_packet_fifo *fifo, RMuint32 entry_size, RMuint32 incr);

RMuint32 gbus_packet_fifo_incr_read_ptr(struct gbus *pgbus, struct gbus_packet_fifo *fifo, RMuint32 entry_size, RMuint32 incr);


struct gbus_entry_fifo *gbus_entry_fifo_open(struct gbus *pgbus, RMuint32 data_address, RMuint32 data_size, RMuint32 fifo_address);

void gbus_entry_fifo_close(struct gbus *pgbus, struct gbus_entry_fifo *fifo);

RMbool gbus_entry_fifo_is_empty(struct gbus *pgbus, struct gbus_entry_fifo *fifo);

void gbus_entry_fifo_flush(struct gbus *pgbus, struct gbus_entry_fifo *fifo);

RMuint32 gbus_entry_fifo_get_info(struct gbus *pgbus, struct gbus_entry_fifo *fifo, RMuint32 *data_start, RMuint32 *writable, RMuint32 *readable);

RMuint32 gbus_entry_fifo_get_writable_size(struct gbus *pgbus, struct gbus_entry_fifo *fifo, RMuint32 entry_size, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2);

RMuint32 gbus_entry_fifo_get_readable_size(struct gbus *pgbus, struct gbus_entry_fifo *fifo, RMuint32 entry_size, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2);

RMuint32 gbus_entry_fifo_incr_write_ptr(struct gbus *pgbus, struct gbus_entry_fifo *fifo, RMuint32 entry_size, RMuint32 incr);

RMuint32 gbus_entry_fifo_incr_read_ptr(struct gbus *pgbus, struct gbus_entry_fifo *fifo, RMuint32 entry_size, RMuint32 incr);

RM_EXTERN_C_BLOCKEND

#endif // __GBUS_PACKET_FIFO_H__
