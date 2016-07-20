/*****************************************
 Copyright © 2001-2011 
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   i2c_hal.h

  @brief implemetation for I2C - using GPIOs
  @author Aurelia Popa-Radu, Christian Wolff
  @date   2003-07-01
*/

#ifndef __I2C_HAL_H__
#define __I2C_HAL_H__

struct i2c {
	struct gbus *pGBus;
	RMuint32 RegBase;	// base address for hardware registers
	RMuint8 PioClock;
	RMuint8 PioData;
	RMuint32 DelayUs;
	RMuint8 WrAddr;
	RMuint8 RdAddr;
};

RM_EXTERN_C_BLOCKSTART

RMstatus I2C_Write(struct i2c* pI2C, RMuint8 SubAddr, const RMuint8* pData, RMuint32 n, RMbool SendDevAddr, RMbool SendSubAddr, RMbool SendStop);

RMstatus I2C_Read(struct i2c* pI2C, RMuint8 SubAddr, RMuint8* pData, RMuint32 n, RMbool SendDevAddr, RMbool SendSubAddr, RMbool SendStop);

RM_EXTERN_C_BLOCKEND

#endif // __I2C_HAL_H__

