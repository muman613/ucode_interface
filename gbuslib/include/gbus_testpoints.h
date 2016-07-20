/*****************************************
 Copyright © 2004-2005
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   gbus_testpoints.h
  @brief  

  Scope-based debugging of timing-related issues (bug#4067)
  using design 8634ES4 board design 849E1 testpoints TP15, TP16, TP17
  mapped respectively on GPIO 13 14 and 15.

  On standalone design 852-01, 
  T29 <-> TP16 (GPIO14)
  T30 <-> TP17 (GPIO15)

  @author Emmanuel Michon
  @date   2005-08-16
*/

#ifndef __GBUS_TESTPOINTS_H__
#define __GBUS_TESTPOINTS_H__

#define TESTPOINT15 (1<<13)
#define TESTPOINT16 (1<<14)
#define TESTPOINT17 (1<<15)

static inline void gbus_testpoints_init(struct gbus *h)
{
	gbus_write_uint32(h,REG_BASE_system_block+SYS_gpio_dir,
			  ((TESTPOINT15|TESTPOINT16|TESTPOINT17)<<16)
			  |(TESTPOINT15|TESTPOINT16|TESTPOINT17));
}

static inline void gbus_testpoint_set(struct gbus *h,RMuint32 testpoint,RMuint32 value)
{
	gbus_write_uint32(h,REG_BASE_system_block+SYS_gpio_data,(testpoint<<16)|((value)?testpoint:0));
}

/// 
/**
   Use pwm mode.

   Need a low pass filter on output (R= C=), cannot move faster than ~100Hz.

   value x appears as a DC signal of 0.2x volts (fits scope vertical divisions)

   @param h     
   @param testpoint: only TESTPOINT16 and TESTPOINT17
   @param value: 0..7 (could do more but scope would be blurry)
*/
static inline void gbus_testpoint_setlevel(struct gbus *h,RMuint32 testpoint,RMuint32 value)
{
	gbus_write_uint32(h,
			  REG_BASE_system_block+(testpoint==TESTPOINT17)?SYS_gpio15_pwm:SYS_gpio14_pwm,
			  (1<<24)+(0<<16)+(value*3900));
}

#endif /* __GBUS_TESTPOINTS_H__ */
