/*****************************************
 Copyright © 2001-2004  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   rmfifo.h
  @brief  Implementation of circular FIFO structures

  @author Aurelia Popa-Radu
  @date   03/12/2004
  @ingroup rmcoreapi
*/

#ifndef __RMFIFO_H__
#define __RMFIFO_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup rmcoreapi
 *  @{
 */

struct RMfifo {
	RMuint32 base;
	RMuint32 size;
	RMuint32 rd;
	RMuint32 wr;
};

RM_LIBRARY_IMPORT_EXPORT struct RMfifo	*RMfifo_open			(RMuint32 data_address, RMuint32 data_size, RMuint32 fifo_address);
RM_LIBRARY_IMPORT_EXPORT void		RMfifo_flush			(struct RMfifo *fifo);
RM_LIBRARY_IMPORT_EXPORT void		RMfifo_close			(struct RMfifo *fifo);
RM_LIBRARY_IMPORT_EXPORT RMbool		RMfifo_is_empty			(struct RMfifo *fifo);
RM_LIBRARY_IMPORT_EXPORT RMuint32	RMfifo_get_info			(struct RMfifo *fifo, RMuint32 *data_start);
RM_LIBRARY_IMPORT_EXPORT RMuint32	RMfifo_get_writable_size	(struct RMfifo *fifo, RMuint32 *wr_ptr1, RMuint32 *wr_size1, RMuint32 *wr_ptr2);
RM_LIBRARY_IMPORT_EXPORT RMuint32	RMfifo_get_readable_size	(struct RMfifo *fifo, RMuint32 *rd_ptr1, RMuint32 *rd_size1, RMuint32 *rd_ptr2);
RM_LIBRARY_IMPORT_EXPORT RMuint32	RMfifo_incr_write_ptr		(struct RMfifo *fifo, RMuint32 incr);
RM_LIBRARY_IMPORT_EXPORT RMuint32	RMfifo_incr_read_ptr		(struct RMfifo *fifo, RMuint32 incr);

RM_LIBRARY_IMPORT_EXPORT RMstatus RMFifoRead( RMuint8 *dest, RMuint32 size,
	RMuint8 **src1, RMuint32 *size1, RMuint8 **src2, RMuint32 *size2,  RMuint32 fifo );
RM_LIBRARY_IMPORT_EXPORT RMstatus RMFifoWrite( RMuint8 *src, RMuint32 size,
	RMuint8 **dest1, RMuint32 *size1, RMuint8 **dest2, RMuint32 *size2, RMuint32 fifo );

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMFIFO_H__
