/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   gbus_time.h
  @brief  

  long description

  @author Emmanuel Michon
  @date   2003-08-07
*/

#ifndef __GBUS_TIME_H__
#define __GBUS_TIME_H__

#include "emhwlib_hal/include/emhwlib_registers.h"

RM_EXTERN_C_BLOCKSTART

/// 
/**
   Compute a time difference taking into account the fact that the counter
   may have cycled *once*

   @param t1    
   @param t2    
   @return ReturnValue
*/
static inline RMuint32 gbus_time_delta(RMuint32 t1,RMuint32 t2)
{ 
#ifdef WITH_QUICKTURN
	// not very accurate (maybe wrong)
	return (t1<=t2)?(t2-t1):(0xffffffff-(t1-t2));
#else
	return (t1<=t2)?(t2-t1):(0xffffffff/XTAL_MHZ-(t1-t2));
#endif
}
		
/// 
/**
   Time origin is unspecified: use only to compute differences

   wraps every 2^32/XTAL_HZ (159 seconds at 27 MHz), so it loops about every three minutes (!)

   @param void  
   @return ReturnValue
*/
static inline RMuint32 gbus_time_us(struct gbus *pgbus)
{
#ifdef WITH_QUICKTURN
	return gbus_read_uint32(pgbus,REG_BASE_system_block+SYS_clk_cnt)*4;
#else
	return gbus_read_uint32(pgbus,REG_BASE_system_block+SYS_xtal_in_cnt)/XTAL_MHZ;
#endif
}

RM_EXTERN_C_BLOCKEND

#endif // __GBUS_TIME_H__
