/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   gbus_fifo_eraser.h
  @brief  

  Used when data has to be `acknowledged' after being read.

  e.m.:
  This structure is used for decipher-in-place this way:

  ----------er -------------------rd ---------------------wr ------------
  EEEEEEEEEE| ... clear data ...  | ... ciphered data ... |EEEEEEEEEEEEEE
  -----------------------------------------------------------------------
            ^microcode writes     ^xtask writes           ^ih writes
            ^ih reads             ^microcode reads        ^xtask reads

  @author Julien Soulier, Emmanuel Michon
  @date   2003-04-11
*/

#ifndef __GBUS_FIFO_ERASER_H__
#define __GBUS_FIFO_ERASER_H__

#include "llad/include/gbus.h"

struct gbus_fifo_eraser {
	RMuint32 base;
	RMuint32 size;
	RMuint32 er; 
	RMuint32 rd;
	RMuint32 wr;
};

RM_EXTERN_C_BLOCKSTART

struct gbus_fifo_eraser *gbus_fifo_eraser_open(struct gbus *h, RMuint32 data_address, RMuint32 data_size, RMuint32 fifo_address);
void gbus_fifo_eraser_close(struct gbus *h, struct gbus_fifo_eraser *fifo);
RMbool gbus_fifo_eraser_is_empty(struct gbus *h, struct gbus_fifo_eraser *fifo);
void gbus_fifo_eraser_flush(struct gbus *h, struct gbus_fifo_eraser *fifo);
RMuint32 gbus_fifo_eraser_get_info(struct gbus *h, struct gbus_fifo_eraser *fifo, RMuint32 *start_address, 	RMuint32 *writable, RMuint32 *readable, RMuint32 *erasable);
RMuint32 gbus_fifo_eraser_get_writable_size(struct gbus *h, struct gbus_fifo_eraser *fifo, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2);
RMuint32 gbus_fifo_eraser_get_readable_size(struct gbus *h, struct gbus_fifo_eraser *fifo, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2);
RMuint32 gbus_fifo_eraser_get_erasable_size(struct gbus *h, struct gbus_fifo_eraser *fifo, RMuint32 *er_ptr1, RMuint32 *er_size1, RMuint32 *er_ptr2);
RMuint32 gbus_fifo_eraser_incr_write_ptr(struct gbus *h, struct gbus_fifo_eraser *fifo, RMuint32 incr);
RMuint32 gbus_fifo_eraser_incr_read_ptr(struct gbus *h, struct gbus_fifo_eraser *fifo, RMuint32 incr);
RMuint32 gbus_fifo_eraser_incr_erase_ptr(struct gbus *h, struct gbus_fifo_eraser *fifo, RMuint32 incr);

RM_EXTERN_C_BLOCKEND

#endif // __GBUS_FIFO_ERASER_H__
