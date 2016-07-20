/*
 *
 * Copyright (c) Sigma Designs, Inc. 2011. All rights reserved.
 *
 */

/**
	@file i2c_slave.h
	@brief Main API header file for I2C Slave driver
	
	@author Christian Wolff
*/

#ifndef __I2C_SLAVE_H__
#define __I2C_SLAVE_H__

//#include "rmdef/rmdef.h"
//#include "llad/include/gbus.h"

enum emhwlib_i2cslave_status {
	emhwlib_i2cslave_status_in_ready = 0, 
	emhwlib_i2cslave_status_in_error, 
	emhwlib_i2cslave_status_out_ready, 
	emhwlib_i2cslave_status_out_error, 
};

#define EMHWLIB_I2C_STATUS_IN_READY  (1 << emhwlib_i2cslave_status_in_ready)
#define EMHWLIB_I2C_STATUS_IN_ERROR  (1 << emhwlib_i2cslave_status_in_error)
#define EMHWLIB_I2C_STATUS_OUT_READY (1 << emhwlib_i2cslave_status_out_ready)
#define EMHWLIB_I2C_STATUS_OUT_ERROR (1 << emhwlib_i2cslave_status_out_error)


// Enable I2C Slave block and set device address
RMstatus emhwlib_i2cslave_open(struct gbus *pGBus, RMuint32 RegBase, RMuint8 DevAddr);

// Disable I2C Slave block
RMstatus emhwlib_i2cslave_close(struct gbus *pGBus, RMuint32 RegBase);


// Provide one byte into the output register for transmission
RMstatus emhwlib_i2cslave_send(struct gbus *pGBus, RMuint32 RegBase, RMuint8 Data);

// Retrieve received byte from the input register
RMstatus emhwlib_i2cslave_receive(struct gbus *pGBus, RMuint32 RegBase, RMuint8 *pData);


// Enable interrupt notification for the selected status events
RMstatus emhwlib_i2cslave_set_irq_enable(struct gbus *pGBus, RMuint32 RegBase, RMuint32 Status);

// Reason(s) for the interrupt. Reading this status will NOT clear the irq status register.
RMstatus emhwlib_i2cslave_get_irq_status(struct gbus *pGBus, RMuint32 RegBase, RMuint32 *pStatus);

// Acknowledge reason(s) for the interrupt, will clear the selected bits of the irq status register.
RMstatus emhwlib_i2cslave_ack_irq_status(struct gbus *pGBus, RMuint32 RegBase, RMuint32 Status);

// Current status of the I2C slave block
RMstatus emhwlib_i2cslave_get_raw_status(struct gbus *pGBus, RMuint32 RegBase, RMuint32 *pStatus);


// Mode = FALSE: Issue out_ready interrupt when Tx data register becomes empty (no bus hold, extra intr after last byte)
// Mode = TRUE: Hold bus when master requests data, then issue out_ready interrupt (bus hold, no extra intr)
RMstatus emhwlib_i2cslave_set_irq_mode(struct gbus *pGBus, RMuint32 RegBase, RMbool Mode);


// Hold = TRUE: Hold the bus until requested action or specified timeout occurs
// Timeout: time in Sysclks
RMstatus emhwlib_i2cslave_set_hold_mode(struct gbus *pGBus, RMuint32 RegBase, RMbool Hold, RMuint32 Timeout);

#endif // __I2C_SLAVE_H__

