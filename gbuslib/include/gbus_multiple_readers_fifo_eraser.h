/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   gbus_multiple_readers_fifo_eraser.h
  @brief  

  @author Julien Soulier
  @date   2005-11-30
*/

#ifndef __GBUS_MULTIPLE_READERS_FIFO_ERASER_H__
#define __GBUS_MULTIPLE_READERS_FIFO_ERASER_H__

#include "llad/include/gbus.h"

#define MAX_GBUS_FIFO_READER_COUNT 4

struct gbus_multiple_readers_fifo_eraser {
	RMuint32 base;
	RMuint32 size;
	RMuint32 wr;
	RMuint32 er; 
	RMuint32 rd[MAX_GBUS_FIFO_READER_COUNT];
	RMuint32 re[MAX_GBUS_FIFO_READER_COUNT];
};

RM_EXTERN_C_BLOCKSTART

struct gbus_multiple_readers_fifo_eraser *gbus_multiple_readers_fifo_eraser_open(
	struct gbus *h, RMuint32 data_address, RMuint32 data_size, RMuint32 fifo_address);

void gbus_multiple_readers_fifo_eraser_close(
	struct gbus *h, struct gbus_multiple_readers_fifo_eraser *fifo);

RMbool gbus_multiple_readers_fifo_eraser_is_empty(
	struct gbus *h, struct gbus_multiple_readers_fifo_eraser *fifo);

RMuint32 gbus_multiple_readers_fifo_eraser_get_latest_releaser(
	struct gbus *h, struct gbus_multiple_readers_fifo_eraser *fifo, RMuint32 *readable);

RMuint32 gbus_multiple_readers_fifo_eraser_connect_reader(
	struct gbus *h, struct gbus_multiple_readers_fifo_eraser *fifo, RMuint32 reader_idx);

void gbus_multiple_readers_fifo_eraser_disconnect_reader(
	struct gbus *h, struct gbus_multiple_readers_fifo_eraser *fifo, RMuint32 reader_idx);

RMuint32 gbus_multiple_readers_fifo_eraser_get_info(
	struct gbus *h, struct gbus_multiple_readers_fifo_eraser *fifo, RMuint32 reader_idx, 
	RMuint32 *start_address, RMuint32 *writable, RMuint32 *readable, RMuint32 *releasable, RMuint32 *erasable);

RMuint32 gbus_multiple_readers_fifo_eraser_get_writable_size(
	struct gbus *h, struct gbus_multiple_readers_fifo_eraser *fifo, 
	RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2);

RMuint32 gbus_multiple_readers_fifo_eraser_get_readable_size(
	struct gbus *h, struct gbus_multiple_readers_fifo_eraser *fifo, RMuint32 reader_idx, 
	RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2);

RMuint32 gbus_multiple_readers_fifo_eraser_get_releasable_size(
	struct gbus *h, struct gbus_multiple_readers_fifo_eraser *fifo, RMuint32 reader_idx, 
	RMuint32 *re_ptr1, RMuint32 *re_size1, RMuint32 *re_ptr2);

RMuint32 gbus_multiple_readers_fifo_eraser_get_erasable_size(
	struct gbus *h, struct gbus_multiple_readers_fifo_eraser *fifo, 
	RMuint32 *er_ptr1, RMuint32 *er_size1, RMuint32 *er_ptr2);

RMuint32 gbus_multiple_readers_fifo_eraser_incr_write_ptr(
	struct gbus *h, struct gbus_multiple_readers_fifo_eraser *fifo, RMuint32 incr);

RMuint32 gbus_multiple_readers_fifo_eraser_incr_read_ptr(
	struct gbus *h, struct gbus_multiple_readers_fifo_eraser *fifo, RMuint32 reader_idx, RMuint32 incr);

RMuint32 gbus_multiple_readers_fifo_eraser_incr_release_ptr(
	struct gbus *h, struct gbus_multiple_readers_fifo_eraser *fifo, RMuint32 reader_idx, RMuint32 incr);

RMuint32 gbus_multiple_readers_fifo_eraser_incr_erase_ptr(
	struct gbus *h, struct gbus_multiple_readers_fifo_eraser *fifo, RMuint32 incr);

RM_EXTERN_C_BLOCKEND

#endif // __GBUS_MULTIPLE_READERS_FIFO_ERASER_H__
