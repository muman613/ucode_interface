#ifndef __GBUS_FIFO_H__
#define __GBUS_FIFO_H__

#include "rmdef/rmdef.h"
#include "remote_client/llad.h"
#include "remote_client/gbus.h"

struct gbus_fifo {
    RMuint32 base;
    RMuint32 size;
    RMuint32 rd;
    RMuint32 wr;
};

struct gbus_fifo *  gbus_fifo_open(GBUS_PTR pgbus, RMuint32 data_address, RMuint32 data_size, RMuint32 fifo_address);
struct gbus_fifo *  gbus_fifo_open_rdwr(GBUS_PTR pgbus, RMuint32 data_address, RMuint32 data_size, RMuint32 fifo_address, RMuint32 rd_ptr, RMuint32 wr_ptr);
void                gbus_fifo_close(GBUS_PTR pgbus, struct gbus_fifo *fifo);
void                gbus_fifo_get_pointer(GBUS_PTR pgbus, struct gbus_fifo *fifo, RMuint32 *base, RMuint32 *size, RMuint32 *rd_ptr, RMuint32 *wr_ptr);
RMbool              gbus_fifo_is_empty(GBUS_PTR pgbus, struct gbus_fifo *fifo);
RMuint32            gbus_fifo_get_info(GBUS_PTR pgbus, struct gbus_fifo *fifo, RMuint32 *data_start, RMuint32 *writable, RMuint32 *readable);
RMuint32            gbus_fifo_get_writable_size(GBUS_PTR pgbus, struct gbus_fifo *fifo, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2);
RMuint32            gbus_fifo_get_readable_size(GBUS_PTR pgbus, struct gbus_fifo *fifo, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2);
RMuint32            gbus_fifo_get_readable_sizeWHATISTHIS(GBUS_PTR pgbus, struct gbus_fifo *fifo, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2, RMuint32 entry_size);
RMuint32            gbus_fifo_incr_write_ptr(GBUS_PTR pgbus, struct gbus_fifo *fifo, RMuint32 incr);
RMuint32            gbus_fifo_incr_read_ptr(GBUS_PTR pgbus, struct gbus_fifo *fifo, RMuint32 incr);
void                gbus_fifo_flush_ptr(GBUS_PTR pgbus, struct gbus_fifo *fifo);

#endif // __GBUS_FIFO_H__
