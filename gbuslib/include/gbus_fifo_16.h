/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   gbus_fifo_16.h
  @brief  

  long description

  @author Julien Soulier
  @date   2003-05-09
*/

#ifndef __GBUS_FIFO_16_H__
#define __GBUS_FIFO_16_H__

#include "llad/include/gbus.h"
#include "gbus_mutex.h"

struct gbus_fifo_16 {
	RMuint32 base_lo;
	RMuint32 base_hi;
	RMuint32 size_lo;
	RMuint32 size_hi;
	RMuint32 rd_lo;
	RMuint32 rd_hi;
	RMuint32 wr_lo;
	RMuint32 wr_hi;
};

RM_EXTERN_C_BLOCKSTART

struct gbus_fifo_16 *gbus_fifo_16_open(struct gbus *pgbus, struct gbus_mutex *mutex, RMuint32 data_address, RMuint32 data_size, RMuint32 fifo_address);

// HACK!!! Need to be removed
struct gbus_fifo_16 *gbus_fifo_16_open_rdwr(struct gbus *pgbus, struct gbus_mutex *mutex, RMuint32 data_address, RMuint32 data_size, RMuint32 fifo_address, RMuint32 rd_ptr, RMuint32 wr_ptr);

void gbus_fifo_16_close(struct gbus *pgbus, struct gbus_mutex *mutex, struct gbus_fifo_16 *fifo);

// HACK!!! Need to be removed
void gbus_fifo_16_get_pointer(struct gbus *pgbus, struct gbus_mutex *mutex, struct gbus_fifo_16 *fifo, 
	RMuint32 *base, RMuint32 *size, RMuint32 *rd_ptr, RMuint32 *wr_ptr);

RMbool gbus_fifo_16_is_empty(struct gbus *pgbus, struct gbus_mutex *mutex, struct gbus_fifo_16 *fifo);

RMuint32 gbus_fifo_16_get_info(struct gbus *pgbus, struct gbus_mutex *mutex, struct gbus_fifo_16 *fifo, RMuint32 *data_start, RMuint32 *writable, RMuint32 *readable);

RMuint32 gbus_fifo_16_get_writable_size(struct gbus *pgbus, struct gbus_mutex *mutex, struct gbus_fifo_16 *fifo, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2);

RMuint32 gbus_fifo_16_get_readable_size(struct gbus *pgbus, struct gbus_mutex *mutex, struct gbus_fifo_16 *fifo, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2);

RMuint32 gbus_fifo_16_incr_write_ptr(struct gbus *pgbus, struct gbus_mutex *mutex, struct gbus_fifo_16 *fifo, RMuint32 incr);

RMuint32 gbus_fifo_16_incr_read_ptr(struct gbus *pgbus, struct gbus_mutex *mutex, struct gbus_fifo_16 *fifo, RMuint32 incr);

// HACK!!! Need to be removed
void gbus_fifo_16_flush_ptr(struct gbus *pgbus, struct gbus_mutex *mutex, struct gbus_fifo_16 *fifo);


RM_EXTERN_C_BLOCKEND

#endif // __GBUS_FIFO_16_H__
