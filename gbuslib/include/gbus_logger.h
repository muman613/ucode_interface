/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   gbus_logger.h
  @brief  

  A fifo based lightweight logging facility 
  
  FIFO and START entry is created by gbus_logger_start(pGBus);
  STOP entry is created by gbus_logger_stop(pGBus);
  
  A logged entry has type struct gbus_logger_entry.
  
  Entries are written in the FIFO by doing (example)

  // log with value x/100 now.
  gbus_logger(pGBus,GBUS_LOGGER_COUNTER0,x/100);
  
  Since there is no way to synchronize properly between
  multiple arm contexts and multiple host contexts, two separate
  FIFO are used.

  Regarding concurrent access from the same CPU, the user has to
  take care of proper locking.
  
  Another thread has to read the log by multiple entries; the
  same function reads from the two FIFOs all it can. Output files
  have to be sorted by increasing time.
  
  Refer to gbus_logger_dump

  @author Emmanuel Michon
  @date   2003-09-22
*/

#ifndef __GBUS_LOGGER_H__
#define __GBUS_LOGGER_H__

#include "emhwlib_hal/include/emhwlib_registers.h"
#include "emhwlib/include/emhwlib_dram.h"
#include "gbuslib/include/gbus_fifo.h"

enum gbus_logger_tag {
	GBUS_LOGGER_FIRST=58,
#define GLDEF(x) GBUS_LOGGER_ ## x,
#include "gbus_logger.inc"
#undef GLDEF
	GBUS_LOGGER_LAST,
};

struct gbus_logger_entry {
	enum gbus_logger_tag tag;
	RMuint32 time_us;
	RMuint32 val;
};

#ifdef WITH_GBUS_LOGGER

#define NTAG (GBUS_LOGGER_LAST-GBUS_LOGGER_FIRST-1)
#define MAXTAG 100 // do not offset memory at each change in gbus_logger.inc

#define GBUS_LOGGER_BASE (MEM_BASE_dram_controller_0+DRAM0_PHOF_GBUS_LOGGER_START)

#define GBUS_LOGGER_FIFOSIZE (128*1024)

#define GBUS_LOGGER_LOSTCOUNT GBUS_LOGGER_BASE

#define GBUS_LOGGER_MPEGFIFO (GBUS_LOGGER_LOSTCOUNT+sizeof(RMuint32))
#define GBUS_LOGGER_MPEGFIFODATA (GBUS_LOGGER_MPEGFIFO+sizeof(struct gbus_fifo))

#define GBUS_LOGGER_ARMFIFO (GBUS_LOGGER_MPEGFIFODATA+GBUS_LOGGER_FIFOSIZE)
#define GBUS_LOGGER_ARMFIFODATA (GBUS_LOGGER_ARMFIFO+sizeof(struct gbus_fifo))

#define GBUS_LOGGER_HOSTFIFO (GBUS_LOGGER_ARMFIFODATA+GBUS_LOGGER_FIFOSIZE)
#define GBUS_LOGGER_HOSTFIFODATA (GBUS_LOGGER_HOSTFIFO+sizeof(struct gbus_fifo))

#define GBUS_LOGGER_END (GBUS_LOGGER_HOSTFIFODATA+GBUS_LOGGER_FIFOSIZE)

// consistency with RAM map
RMmustBeEqual(GBUS_LOGGER_END,MEM_BASE_dram_controller_0+DRAM0_PHOF_GBUS_LOGGER_END,seed0);

#define INVALID 0xdeadbeef

// called by writer
void gbus_logger_start(struct gbus *pgbus);
void gbus_logger(struct gbus *pgbus,enum gbus_logger_tag tag,RMint32 val);
void gbus_logger_stop(struct gbus *pgbus);

// called by reader
RMbool gbus_logger_fetch_isready(struct gbus *pgbus);
RMuint32 gbus_logger_fetch(struct gbus *pgbus,struct gbus_logger_entry *dst,RMuint32 count);
void gbus_logger_invalidate(struct gbus *pgbus);

// spasm does not parse C enums
#include "gbus_logger_ucode.h"
RMmustBeEqual(GBUS_LOGGER_LOSTCOUNT,GBUS_LOGGER_LOSTCOUNT_LO+(GBUS_LOGGER_LOSTCOUNT_HI<<16),seed1)
RMmustBeEqual(GBUS_LOGGER_MPEGFIFO,GBUS_LOGGER_MPEGFIFO_LO+(GBUS_LOGGER_MPEGFIFO_HI<<16),seed2)
RMmustBeEqual(INVALID,INVALID_LO+(INVALID_HI<<16),seed3)
RMmustBeEqual(GBUS_LOGGER_UCODE0,GBUS_LOGGER_UCODE0_LO,seed4)
RMmustBeEqual(GBUS_LOGGER_UCODE7,GBUS_LOGGER_UCODE7_LO,seed5)
RMmustBeEqual(GBUS_LOGGER_16_RD,GBUS_LOGGER_16_RD_LO,seed6)
RMmustBeEqual(GBUS_LOGGER_A15A14,GBUS_LOGGER_A15A14_LO,seed7)

#else

static inline void gbus_logger_start(struct gbus *pgbus) {}
static inline void gbus_logger(struct gbus *pgbus,enum gbus_logger_tag tag,RMint32 val) {}
static inline void gbus_logger_stop(struct gbus *pgbus) {}
static inline RMbool gbus_logger_fetch_isready(struct gbus *pgbus) { return FALSE; }
static inline RMuint32 gbus_logger_fetch(struct gbus *pgbus,struct gbus_logger_entry *dst,RMuint32 count) { return 0; }
static inline void gbus_logger_invalidate(struct gbus *pgbus) {}

#endif // WITH_GBUS_LOGGER

#endif // __GBUS_LOGGER_H__
