/*
 *
 * Copyright (c) 2001-2012 Sigma Designs, Inc. 
 * All Rights Reserved. Proprietary and Confidential.
 *
 */

/**
	@file hdmi_reg.h
	@brief API header file for embedded HDMI register access
	
	@author Christian Wolff, Yuan Zhong
*/

/**
   @brief This API provides high-level access to the registers of embedded HDMI Tx and Rx chips.

*/

#ifndef __HDMI_REG_H__
#define __HDMI_REG_H__

#include "rmdef/rmdef.h"



/** Context structure for HDMI cores (public instead of anonymous, no malloc available) */
struct hdmi_reg {
	struct gbus *pGBus;  ///< Chip access
	RMbool Rx;           ///< TRUE: Rx, FALSE: Tx
	RMbool Mapped;       ///< TRUE: Directly mapped Tx registers, FALSE: Indirectly accessed Tx registers
	RMbool Direct;       ///< TRUE: Direct access to HDMI Tx, FALSE: HDMI Tx access via internal I2C bus
	struct gbus_mutex *pMutex;  ///< Hardware mutex to atomize non-mapped register access
	RMbool OutputSelect; ///< Local copy of setting
	RMbool DualMode;     ///< HDMI / Pads dual mode
	RMuint16 dev;        ///< PCI ID of the SMP chip
	RMuint8 rev;         ///< Revision ID of the SMP chip
};

/** Operating state of the HDMI core */
enum hdmi_state {
	/** Normal operation */
	hdmi_state_Running = 0, 
	/** Reset configuration in HDMI core */
	hdmi_state_ResetHDMI = 1, 
	/** Reset I2C block and HDCP key memeory @note: Don't use from CPU, if keymem is protected */
	hdmi_state_ResetKeymemI2C = 2, 
	/** Reset complete HDMI core, I2C and HDCP keymem @note: Don't use from CPU, if keymem is protected */
	hdmi_state_ResetConfig = 3, 
};

/** Operating parameter of the HDMI core */
struct hdmi_config {
	/** HDMI clk divider @note: FALSE = clk, TRUE = clk / 2 */
	RMbool ClkDiv;
	/** State of the external physical transmitter @note: FALSE = power down, TRUE = normal operation */
	RMbool PowerUpPhy;
	/** Selects which pads are routet to the VO0 output pins @note: FALSE = DigitalOut (bypassing HDMI), TRUE = HDMI */
	RMbool OutputSelect;
	/** Whether to invert the audio SClk @note: FALSE = not inverted, TRUE = inverted */
	RMbool AudioClkInv;
	/** Select to bypass the HDMI Tx chip and access the DDC bus directly from the HDMI I2C master @note: FALSE = DDC access through HDMI Tx, TRUE = direct DDC access */
	RMbool DDCBypass;
};



/** One CEC message */
struct hdmi_cec_frame {
	RMuint32 Initiator;    ///< Address of transmitting device, 0..15
	RMuint32 Destination;  ///< Address of target device, 0..15
	RMuint32 Size;         ///< Message size, 0..16 (size of Opcode plus Operands)
	RMuint8 Opcode;        ///< Operator
	RMuint8 Operand[15];   ///< Parameter to the operator
};

/** Status of CEC block */
struct hdmi_cec_status {
	RMbool PowerChanged;    ///< TRUE: the power status has changed
	RMbool PowerStatus;     ///< current state of the power
	RMbool HotPlugChanged;  ///< TRUE: the hot plug state has changed
	RMbool HotPlugStatus;   ///< current state of the hot plug signal
	RMbool MessageReceived;    ///< TRUE: a message has been received
	RMbool RxErrorStartBit;    ///< TRUE: message could not be received
	RMbool RxErrorShortPulse;  ///< TRUE: message could not be received
	RMbool RxErrorFIFOOverrun; ///< TRUE: message could not be received
	RMbool MessageSent;        ///< TRUE: a message has been sent and acknowledged by receiver
	RMbool TxErrorRetransmitCountExceeded;  ///< TRUE: message could not be sent
	RMbool TxFIFOEmpty;        ///< TRUE: Another message can now be sent
};

/** enable, configure and calibrate the CEC block */
struct hdmi_cec_config {
	/** Set to 2 */
	RMuint32 APIVersion;
	
	// With APIVersion >= 1
	/** TRUE: enable CEC on GPIO 13, FALSE: disable CEC and revert GPIO 13 to general use */
	RMbool Enable;
	/** Select clock source for the CEC block. FALSE: use the 27 MHz XtalClk, TRUE: use the SysClk */
	RMbool SysClk;
	
	// With APIVersion >= 2
	/** Set the logical address for standby mode */
	RMuint32 LogicalAddress;
	/** Set the physical address for standby mode */
	RMuint32 PhysicalAddress;
};


/** Context structure for CEC core (public instead of anonymous, no malloc available) */
struct hdmi_cec {
	struct gbus *pGBus;  ///< Chip access
	RMuint32 cec_clk;
	RMbool send_frame_pending;
	RMbool send_frame_error;
	RMuint32 send_frame_retry;
	struct hdmi_cec_frame send_frame;
	RMuint32 recv_frame_wr;
	RMuint32 recv_frame_rd;
	struct hdmi_cec_frame recv_frame[16];
	struct hdmi_cec_status cec_status;
};



RM_EXTERN_C_BLOCKSTART

/**
	API Function to initialize HDMI context structure
	
	@param[in] pGBus     SMP Chip access
	@param[in] Rx        Select HDMI link. FALSE: HDMI Tx, TRUE: HDMI Rx
	@param[in] pMutex    Hardware mutex to atomize non-mapped register access (set to AUDIO_0_HDMICORE_MUTEX, or NULL if no mutex is desired)
	@param[in,out] pHDMIReg  Pointer to caller's instance of 'struct hdmi_reg'
*/
RMstatus hdmi_reg_init(
	struct gbus *pGBus, 
	RMbool Rx, 
	struct gbus_mutex *pMutex, 
	struct hdmi_reg *pHDMIReg);



/**
	Write a single register of the HDMI chip
	
	@param[in] pHDMIReg  Context
	@param[in] Addr  Register address
	@param[in] Data  Value to write into specified register
*/
RMstatus hdmi_write_reg(struct hdmi_reg *pHDMIReg, 
	RMuint32 Addr, 
	RMuint8 Data);

/**
	Read a single register of the HDMI chip
	
	@param[in]  pHDMIReg  Context
	@param[in]  Addr   Register address
	@param[out] pData  Value returned from the specified register
*/
RMstatus hdmi_read_reg(struct hdmi_reg *pHDMIReg, 
	RMuint32 Addr, 
	RMuint8 *pData);

/**
	Write multiple registers of the HDMI chip
	
	@param[in] pHDMIReg  Context
	@param[in] Addr   Address of the first register
	@param[in] Size   Number of registers to write
	@param[in] pData  Array of values to write into specified registers
*/
RMstatus hdmi_write_data(struct hdmi_reg *pHDMIReg, 
	RMuint32 Addr, 
	RMuint32 Size, 
	RMuint8 *pData);

/**
	Read multiple registers of the HDMI chip
	
	@param[in]  pHDMIReg  Context
	@param[in]  Addr   Address of the first register
	@param[in]  Size   Number of registers to read
	@param[out] pData  Values returned from the specified registers
*/
RMstatus hdmi_read_data(struct hdmi_reg *pHDMIReg, 
	RMuint32 Addr, 
	RMuint32 Size, 
	RMuint8 *pData);



/**
	Change the operating state of the HDMI core
	
	@param[in] pHDMIReg  Context
	@param[in] State     New state of the core
*/
RMstatus hdmi_set_state(struct hdmi_reg *pHDMIReg, 
	enum hdmi_state State);

/**
	Retrieve the current operating state of the HDMI core
	
	@param[in]  pHDMIReg  Context
	@param[out] pState    Current state of the core
*/
RMstatus hdmi_get_state(struct hdmi_reg *pHDMIReg, 
	enum hdmi_state *pState);

/**
	Apply various operating parameter to the HDMI core
	
	@param[in] pHDMIReg      Context
	@param[in] Config        New configuration of the core
*/
RMstatus hdmi_set_core_config(struct hdmi_reg *pHDMIReg, 
	struct hdmi_config Config);

/**
	Retrieve the current operating parameter of the HDMI core
	
	@param[in]  pHDMIReg  Context
	@param[out] pConfig   Current configuration of the core
*/
RMstatus hdmi_get_core_config(struct hdmi_reg *pHDMIReg, 
	struct hdmi_config *pConfig);

/**
	Apply HDMI / Pads dual mode
	
	@param[in] pHDMIReg  Context
	@param[in] DualMode  TRUE: SMP chip is operating both, digital output pads and HDMI Tx, at the same time (8672 only)
*/
RMstatus hdmi_set_dual_mode(struct hdmi_reg *pHDMIReg, 
	RMbool DualMode);

/**
	Retrieve the current dual mode state
	
	@param[in]  pHDMIReg   Context
	@param[out] pDualMode  TRUE: SMP chip is operating both, digital output pads and HDMI Tx, at the same time (8672 only)
*/
RMstatus hdmi_get_dual_mode(struct hdmi_reg *pHDMIReg, 
	RMbool *pDualMode);

/**
	Retrieve identifying parameter of the HDMI core (e.g. process parameter in nm)
	
	@param[in]  pHDMIReg    Context
	@param[out] pCoreParam  Parameter of the current core
*/
RMstatus hdmi_get_core_param(struct hdmi_reg *pHDMIReg, 
	RMuint32 *pCoreParam);



/**
	Apply various operating parameter to the CEC core
	
	@param[in] pHDMIReg      Context
	@param[in] Config        New configuration of the core
*/
RMstatus hdmi_set_cec_config(struct hdmi_cec *pCECReg, 
	struct hdmi_cec_config Config);

/**
	Queue one CEC message for transmission
	
	@param[in] pHDMIReg  Context
	@param[in] Frame     Message to be sent
*/
RMstatus hdmi_cec_send_message(struct hdmi_cec *pCECReg, 
	struct hdmi_cec_frame Frame);

/**
	Enable reception of messages
	
	@param[in] pHDMIReg     Context
	@param[in] ReceiveMask  Enable bits for reception at device addresses 0..15 (up to 4)
*/
RMstatus hdmi_cec_enable_receive_message(struct hdmi_cec *pCECReg, 
	RMuint16 ReceiveMask);

/**
	Retrieve a received message from the queue
		
	@param[in]  pHDMIReg  Context
	@param[out] pFrame    Received message
*/
RMstatus hdmi_cec_receive_message(struct hdmi_cec *pCECReg, 
	struct hdmi_cec_frame *pFrame);

/**
	Handle any state changes of the CEC core and operate transmit and receive queues
	
	@param[in] pHDMIReg  Context
	@param[out] pStatus  Notifications from the CEC processing
*/
RMstatus hdmi_cec_check_intr(struct hdmi_cec *pCECReg, 
	struct hdmi_cec_status *pStatus);

RM_EXTERN_C_BLOCKEND

#endif // __HDMI_REG_H__

