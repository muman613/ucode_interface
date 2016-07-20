/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   gbus_fifo.h
  @brief  

  long description

  @author Julien Soulier
  @date   2003-04-08
*/

#ifndef __GBUS_FIFO_H__
#define __GBUS_FIFO_H__

#include "llad/include/gbus.h"

struct gbus_fifo {
	RMuint32 base;
	RMuint32 size;
	RMuint32 rd;
	RMuint32 wr;
};

RM_EXTERN_C_BLOCKSTART

struct gbus_fifo *gbus_fifo_open(struct gbus *h, RMuint32 data_address, RMuint32 data_size, RMuint32 fifo_address);

// HACK!!! Need to be removed
struct gbus_fifo *gbus_fifo_open_rdwr(struct gbus *h, RMuint32 data_address, RMuint32 data_size, RMuint32 fifo_address, RMuint32 rd_ptr, RMuint32 wr_ptr);

void gbus_fifo_close(struct gbus *h, struct gbus_fifo *fifo);

// HACK!!! Need to be removed
void gbus_fifo_get_pointer(struct gbus *h, struct gbus_fifo *fifo, 
	RMuint32 *base, RMuint32 *size, RMuint32 *rd_ptr, RMuint32 *wr_ptr);

RMbool gbus_fifo_is_empty(struct gbus *h, struct gbus_fifo *fifo);

RMuint32 gbus_fifo_get_info(struct gbus *h, struct gbus_fifo *fifo, RMuint32 *data_start, RMuint32 *writable, RMuint32 *readable);

RMuint32 gbus_fifo_get_writable_size(struct gbus *h, struct gbus_fifo *fifo, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2);

RMuint32 gbus_fifo_get_readable_size(struct gbus *h, struct gbus_fifo *fifo, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2);
RMuint32 gbus_fifo_get_readable_sizeWHATISTHIS(struct gbus *h, struct gbus_fifo *fifo, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2, RMuint32 entry_size);

RMuint32 gbus_fifo_incr_write_ptr(struct gbus *h, struct gbus_fifo *fifo, RMuint32 incr);

RMuint32 gbus_fifo_incr_read_ptr(struct gbus *h, struct gbus_fifo *fifo, RMuint32 incr);

// HACK!!! Need to be removed
void gbus_fifo_flush_ptr(struct gbus *h, struct gbus_fifo *fifo);

RM_EXTERN_C_BLOCKEND

#endif // __GBUS_FIFO_H__
