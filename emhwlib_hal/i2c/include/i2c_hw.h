/*****************************************
 Copyright © 2001-2011 
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   i2c_hw.h

  @brief implemetation for I2C - using hardware I2C block
  @author YH Lin, Christian Wolff
  @date   2004-08-17
*/

#ifndef __I2C_HW_H__
#define __I2C_HW_H__

#ifdef RMFEATURE_HAS_HWI2C

struct emhwi2c {
	RMuint32 APIVersion;  // Set to 1 (used for future extensions)
	struct gbus *pGBus;   // register access pointer
	RMuint32 RegBase;  // base address for hardware registers
	RMuint32 DelayUs;  // I2C delay, in uSec
	RMuint32 SysClk;   // frequency of the I2C block (system clock), in Hz
	RMuint32 Speed;    // frequency of the I2C bit transfer, in kHz (e.g. 100 or 400)
	RMuint8 DevAddr;   // I2C device address (write uses DevAddr, read uses DevAddr + 1)
};

RM_EXTERN_C_BLOCKSTART

RMstatus EmhwI2CWrite(struct emhwi2c *pI2C, RMuint8 SubAddr, const RMuint8 *pData, RMuint32 n, RMbool SendDevAddr, RMbool SendSubAddr, RMbool SendStop);

RMstatus EmhwI2CRead(struct emhwi2c *pI2C, RMuint8 SubAddr, RMuint8 *pData, RMuint32 n, RMbool SendDevAddr, RMbool SendSubAddr, RMbool SendStop);

RMstatus EmhwI2CDisable(struct emhwi2c* pI2C);  // disconnect from the I2C bus

RM_EXTERN_C_BLOCKEND

#endif

#endif // __I2C_HW_H__
