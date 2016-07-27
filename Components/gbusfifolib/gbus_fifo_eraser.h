#ifndef __GBUS_FIFO_ERASER_H__
#define __GBUS_FIFO_ERASER_H__

#include "rmdef/rmdef.h"
#include "remote_client/llad.h"
#include "remote_client/gbus.h"

struct gbus_fifo_eraser {
	RMuint32 base;
	RMuint32 size;
	RMuint32 er;
	RMuint32 rd;
	RMuint32 wr;
};

struct gbus_fifo_eraser *gbus_fifo_eraser_open(GBUS_PTR h, RMuint32 data_address, RMuint32 data_size, RMuint32 fifo_address);
void gbus_fifo_eraser_close(GBUS_PTR h, struct gbus_fifo_eraser *fifo);
RMbool gbus_fifo_eraser_is_empty(GBUS_PTR h, struct gbus_fifo_eraser *fifo);
void gbus_fifo_eraser_flush(GBUS_PTR h, struct gbus_fifo_eraser *fifo);
RMuint32 gbus_fifo_eraser_get_info(GBUS_PTR h, struct gbus_fifo_eraser *fifo, RMuint32 *start_address, 	RMuint32 *writable, RMuint32 *readable, RMuint32 *erasable);
RMuint32 gbus_fifo_eraser_get_writable_size(GBUS_PTR h, struct gbus_fifo_eraser *fifo, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2);
RMuint32 gbus_fifo_eraser_get_readable_size(GBUS_PTR h, struct gbus_fifo_eraser *fifo, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2);
RMuint32 gbus_fifo_eraser_get_erasable_size(GBUS_PTR h, struct gbus_fifo_eraser *fifo, RMuint32 *er_ptr1, RMuint32 *er_size1, RMuint32 *er_ptr2);
RMuint32 gbus_fifo_eraser_incr_write_ptr(GBUS_PTR h, struct gbus_fifo_eraser *fifo, RMuint32 incr);
RMuint32 gbus_fifo_eraser_incr_read_ptr(GBUS_PTR h, struct gbus_fifo_eraser *fifo, RMuint32 incr);
RMuint32 gbus_fifo_eraser_incr_erase_ptr(GBUS_PTR h, struct gbus_fifo_eraser *fifo, RMuint32 incr);

#endif // __GBUS_FIFO_ERASER_H__
