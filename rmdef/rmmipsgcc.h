/*****************************************
 Copyright © 2005, 2006, 2007
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmmipsgcc.h
  @brief  

  This file gathers a series of inline functions / macros to
  do some MIPS specific operations (registers, coprocessor zero, cache, ...)

  some of them only allowed in kernel mode.

  It is under rmdef/ but is not included by default with rmdef.h because:
  * it is mostly gcc stuff (inline assembly is gcc specific)
  * end[] and such could conflict with other compilers.

  It works for sde-gcc and mipsel-gcc.
  To achieve this, you need to use human unfriendly register names ($2, $3, etc);
  the CP0 regs are redefined here (RM_C0_*). On sde-gcc that would be C0_* and CP0_* on mipsel-gcc.
  Same goes for cache maintenance bits.
  Refer to #7319 for more details on this specific topic.

  @author Emmanuel Michon
  @date   2007-03-27
*/

#ifndef __RMMIPSGCC_H__
#define __RMMIPSGCC_H__

/* keep it like this, until phase out of #includes */

#endif /* __RMMIPSGCC_H__ */
