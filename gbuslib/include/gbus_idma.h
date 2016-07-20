/*****************************************
 Copyright © 2004-2005
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   gbus_idma.h
  @brief  

  Synchronous access to irq driven memory allocators

  @author Emmanuel Michon
  @date   2005-10-13
*/

#ifndef __GBUS_IDMA_H__
#define __GBUS_IDMA_H__

struct idma {
	RMuint32 allocator;
	void *p;
	RMuint32 size;
	RMuint32 req;
};

#define IDMA_X ((struct idma *) (REG_BASE_cpu_block+LR_IDMA))

#define COMMENC(buf) (((RMuint32) buf[3] << 24) +	\
		((RMuint32) buf[2] << 16) + \
		((RMuint32) buf[1] << 8) + \
		(RMuint32)  buf[0])

#include "gbuslib/include/gbus_mutex.h"
#include "emhwlib/include/emhwlib_event.h"
#include "emhwlib/include/emhwlib_globaltypes.h"

void *idma_malloc(struct gbus *pgbus,RMuint32 tg,RMuint32 size,RMuint32 comment);
void *idma_malloc(struct gbus *pgbus,RMuint32 tg,RMuint32 size,RMuint32 comment)
{
	void *p;
	
	if (size==0) return NULL;
	
	gbus_mutex_lock(pgbus,IDMA_MUTEX);
	
	gbus_write_uint32(pgbus,(RMuint32)&IDMA_X->allocator,tg);
	gbus_write_uint32(pgbus,(RMuint32)&IDMA_X->p,0);
	gbus_write_uint32(pgbus,(RMuint32)&IDMA_X->size,size);
	
	if (comment)
		gbus_write_uint32(pgbus,(RMuint32)&IDMA_X->req,comment);
	else
		gbus_write_uint32(pgbus,(RMuint32)&IDMA_X->req,'.');
	
	gbus_write_uint32(pgbus,REG_BASE_irq_handler_block+CPU_irq_softset,SOFT_IRQ_IH_MA);
	while (gbus_read_uint32(pgbus,(RMuint32)&IDMA_X->req)!=0);
	
	p=(void *)gbus_read_uint32(pgbus,(RMuint32)&IDMA_X->p);
	
	gbus_mutex_unlock(pgbus,IDMA_MUTEX);
	
	return p;
}

void *idma_realloc(struct gbus *pgbus,RMuint32 tg,void *p,RMuint32 size,RMuint32 comment);
void *idma_realloc(struct gbus *pgbus,RMuint32 tg,void *p,RMuint32 size,RMuint32 comment)
{
	void *rp;
	
	if (size==0) return NULL;
	
	gbus_mutex_lock(pgbus,IDMA_MUTEX);
	
	gbus_write_uint32(pgbus,(RMuint32)&IDMA_X->allocator,tg);
	gbus_write_uint32(pgbus,(RMuint32)&IDMA_X->p,(RMuint32)p);
	gbus_write_uint32(pgbus,(RMuint32)&IDMA_X->size,size);
	
	if (comment)
		gbus_write_uint32(pgbus,(RMuint32)&IDMA_X->req,comment);
	else
		gbus_write_uint32(pgbus,(RMuint32)&IDMA_X->req,'.');
	
	gbus_write_uint32(pgbus,REG_BASE_irq_handler_block+CPU_irq_softset,SOFT_IRQ_IH_MA);
	while (gbus_read_uint32(pgbus,(RMuint32)&IDMA_X->req)!=0);
	
	rp=(void *)gbus_read_uint32(pgbus,(RMuint32)&IDMA_X->p);
	
	gbus_mutex_unlock(pgbus,IDMA_MUTEX);
	
	return rp;
}

void idma_free(struct gbus *pgbus,RMuint32 tg,void *p,RMuint32 comment);
void idma_free(struct gbus *pgbus,RMuint32 tg,void *p,RMuint32 comment)
{
	if (p==NULL) return;
	
	gbus_mutex_lock(pgbus,IDMA_MUTEX);
	
	gbus_write_uint32(pgbus,(RMuint32)&IDMA_X->allocator,tg);
	gbus_write_uint32(pgbus,(RMuint32)&IDMA_X->p,(RMuint32)p);
	gbus_write_uint32(pgbus,(RMuint32)&IDMA_X->size,0);
	
	if (comment)
		gbus_write_uint32(pgbus,(RMuint32)&IDMA_X->req,comment);
	else
		gbus_write_uint32(pgbus,(RMuint32)&IDMA_X->req,'.');
	
	gbus_write_uint32(pgbus,REG_BASE_irq_handler_block+CPU_irq_softset,SOFT_IRQ_IH_MA);
	while (gbus_read_uint32(pgbus,(RMuint32)&IDMA_X->req)!=0);
	
	gbus_mutex_unlock(pgbus,IDMA_MUTEX);
}

#endif /* __GBUS_IDMA_H__ */
