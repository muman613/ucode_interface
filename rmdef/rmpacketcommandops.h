/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmpacketcommandops.h

  @author Emmanuel Michon
  @date   2002-12-06
*/

#ifndef __RMPACKETCOMMANDOPS_H__
#define __RMPACKETCOMMANDOPS_H__

RM_EXTERN_C_BLOCKSTART

typedef struct {
	RMuint8 senseKey;
	RMuint8 asc;
	RMuint8 ascq;
} RMpacketError;

typedef enum {
        RM_PACKET_DATA_WRITE = 1,
	RM_PACKET_DATA_READ  = 2,
} RMpacketDataDirection;

typedef struct {
	RMuint8 cmd[12];
	RMuint8 *buffer;
	RMuint32 buflen;
	RMpacketError packetError;
	RMpacketDataDirection packetDataDirection;
} RMpacketCommand;

typedef RMint32 (*PacketCommandOp)(void *handle,RMpacketCommand *pP);

RM_EXTERN_C_BLOCKEND

#endif // __RMPACKETCOMMANDOPS_H__
