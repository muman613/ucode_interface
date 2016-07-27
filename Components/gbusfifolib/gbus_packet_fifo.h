#ifndef __GBUS_PACKET_FIFO_H__
#define __GBUS_PACKET_FIFO_H__

struct gbus_packet_fifo {
	RMuint32 base;
	RMuint32 size;
	RMuint32 rd;
	RMuint32 wr;
};

struct gbus_entry_fifo {
	RMuint32 base;
	RMuint32 size;
	RMuint32 rd;
	RMuint32 wr;
};

/**/
struct gbus_packet_fifo *gbus_packet_fifo_open(GBUS_PTR pgbus, RMuint32 data_address, RMuint32 entry_count, RMuint32 fifo_address);
void gbus_packet_fifo_close(GBUS_PTR pgbus, struct gbus_packet_fifo *fifo);
RMbool gbus_packet_fifo_is_empty(GBUS_PTR pgbus, struct gbus_packet_fifo *fifo);
RMuint32 gbus_packet_fifo_get_info(GBUS_PTR pgbus, struct gbus_packet_fifo *fifo, RMuint32 *data_start, RMuint32 *writable, RMuint32 *readable);
RMuint32 gbus_packet_fifo_get_writable_size(GBUS_PTR pgbus, struct gbus_packet_fifo *fifo, RMuint32 entry_size, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2);
RMuint32 gbus_packet_fifo_get_readable_size(GBUS_PTR pgbus, struct gbus_packet_fifo *fifo, RMuint32 entry_size, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2);
RMuint32 gbus_packet_fifo_incr_write_ptr(GBUS_PTR pgbus, struct gbus_packet_fifo *fifo, RMuint32 entry_size, RMuint32 incr);
RMuint32 gbus_packet_fifo_incr_read_ptr(GBUS_PTR pgbus, struct gbus_packet_fifo *fifo, RMuint32 entry_size, RMuint32 incr);

/**/
struct gbus_entry_fifo *gbus_entry_fifo_open(GBUS_PTR pgbus, RMuint32 data_address, RMuint32 entry_count, RMuint32 fifo_address);
void gbus_entry_fifo_close(GBUS_PTR pgbus, struct gbus_entry_fifo *fifo);
RMbool gbus_entry_fifo_is_empty(GBUS_PTR pgbus, struct gbus_entry_fifo *fifo);
void gbus_entry_fifo_flush(GBUS_PTR pgbus, struct gbus_entry_fifo *fifo);
RMuint32 gbus_entry_fifo_get_info(GBUS_PTR pgbus, struct gbus_entry_fifo *fifo, RMuint32 *data_start, RMuint32 *writable, RMuint32 *readable);
RMuint32 gbus_entry_fifo_get_writable_size(GBUS_PTR pgbus, struct gbus_entry_fifo *fifo, RMuint32 entry_size, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2);
RMuint32 gbus_entry_fifo_get_readable_size(GBUS_PTR pgbus, struct gbus_entry_fifo *fifo, RMuint32 entry_size, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2);
RMuint32 gbus_entry_fifo_incr_write_ptr(GBUS_PTR pgbus, struct gbus_entry_fifo *fifo, RMuint32 entry_size, RMuint32 incr);
RMuint32 gbus_entry_fifo_incr_read_ptr(GBUS_PTR pgbus, struct gbus_entry_fifo *fifo, RMuint32 entry_size, RMuint32 incr);


#endif // __GBUS_PACKET_FIFO_H__
