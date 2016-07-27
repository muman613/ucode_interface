#ifndef __GBUS_PACKET_FIFO_ERASER_H__
#define __GBUS_PACKET_FIFO_ERASER_H__

#include "rmdef/rmdef.h"
#include "remote_client/llad.h"
#include "remote_client/gbus.h"

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

struct gbus_packet_fifo_eraser *gbus_packet_fifo_eraser_open(GBUS_PTR pgbus, RMuint32 data_address, RMuint32 size, RMuint32 fifo_address);
void gbus_packet_fifo_eraser_close(GBUS_PTR pgbus, struct gbus_packet_fifo_eraser *fifo);
RMbool gbus_packet_fifo_eraser_is_empty(GBUS_PTR pgbus, struct gbus_packet_fifo_eraser *fifo);
RMuint32 gbus_packet_fifo_eraser_get_info(GBUS_PTR pgbus, struct gbus_packet_fifo_eraser *fifo, RMuint32 offset, RMuint32 *data_start, RMuint32 *writable, RMuint32 *readable, RMuint32 *erasable);
RMuint32 gbus_packet_fifo_eraser_get_writable_size(GBUS_PTR pgbus, struct gbus_packet_fifo_eraser *fifo,
						RMuint32 offset, RMuint32 entry_size, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2);
RMuint32 gbus_packet_fifo_eraser_get_readable_size(GBUS_PTR pgbus, struct gbus_packet_fifo_eraser *fifo,
						RMuint32 offset, RMuint32 entry_size, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2);
RMuint32 gbus_packet_fifo_eraser_get_erasable_size(GBUS_PTR pgbus, struct gbus_packet_fifo_eraser *fifo,
						 RMuint32 offset, RMuint32 entry_size, RMuint32 *er_ptr1, RMuint32 *er_size1, RMuint32 *er_ptr2);
RMuint32 gbus_packet_fifo_eraser_incr_write_ptr(GBUS_PTR pgbus, struct gbus_packet_fifo_eraser *fifo,
						RMuint32 offset, RMuint32 entry_size, RMuint32 incr);
RMuint32 gbus_packet_fifo_eraser_incr_read_ptr(GBUS_PTR pgbus, struct gbus_packet_fifo_eraser *fifo,
						RMuint32 offset, RMuint32 entry_size, RMuint32 incr);
RMuint32 gbus_packet_fifo_eraser_incr_erase_ptr(GBUS_PTR pgbus, struct gbus_packet_fifo_eraser *fifo,
						RMuint32 offset, RMuint32 entry_size, RMuint32 incr);

struct gbus_entry_fifo_eraser *gbus_entry_fifo_eraser_open(GBUS_PTR pgbus, RMuint32 data_address, RMuint32 size, RMuint32 fifo_address);
void gbus_entry_fifo_eraser_close(GBUS_PTR pgbus, struct gbus_entry_fifo_eraser *fifo);
RMbool gbus_entry_fifo_eraser_is_empty(GBUS_PTR pgbus, struct gbus_entry_fifo_eraser *fifo);
void gbus_entry_fifo_eraser_flush(GBUS_PTR pgbus, struct gbus_entry_fifo_eraser *fifo);
RMuint32 gbus_entry_fifo_eraser_get_info(GBUS_PTR pgbus, struct gbus_entry_fifo_eraser *fifo, RMuint32 *data_start, RMuint32 *writable, RMuint32 *readable, RMuint32 *erasable);

RMuint32 gbus_entry_fifo_eraser_get_writable_size(GBUS_PTR pgbus, struct gbus_entry_fifo_eraser *fifo,
						RMuint32 entry_size, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2);
RMuint32 gbus_entry_fifo_eraser_get_readable_size(GBUS_PTR pgbus, struct gbus_entry_fifo_eraser *fifo,
						RMuint32 entry_size, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2);
RMuint32 gbus_entry_fifo_eraser_get_erasable_size(GBUS_PTR pgbus, struct gbus_entry_fifo_eraser *fifo,
						 RMuint32 entry_size, RMuint32 *er_ptr1, RMuint32 *er_size1, RMuint32 *er_ptr2);
RMuint32 gbus_entry_fifo_eraser_incr_read_ptr(GBUS_PTR pgbus, struct gbus_entry_fifo_eraser *fifo,
						RMuint32 entry_size, RMuint32 incr);
RMuint32 gbus_entry_fifo_eraser_incr_write_ptr(GBUS_PTR pgbus, struct gbus_entry_fifo_eraser *fifo,
						RMuint32 entry_size, RMuint32 incr);
RMuint32 gbus_entry_fifo_eraser_incr_erase_ptr(GBUS_PTR pgbus, struct gbus_entry_fifo_eraser *fifo,
						RMuint32 entry_size, RMuint32 incr);
#endif // __GBUS_PACKET_FIFO_ERASER_H__
