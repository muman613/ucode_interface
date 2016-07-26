/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   sock_protocol.h
  @brief  

  @author Julien Soulier
  @date   2003-01-14
*/

#ifndef __SOCK_PROTOCOL_H__
#define __SOCK_PROTOCOL_H__

/* llad interface */
#define SOCK_LLAD_WAIT_INTERRUPT 0x1
#define SOCK_LLAD_GET_CONFIG     0x2
#define SOCK_LLAD_LOCK           0x3
#define SOCK_LLAD_UNLOCK         0x4
#define SOCK_LLAD_READY          0x5
#define SOCK_LLAD_GET_OPEN_COUNT 0x6

/* gbus interface */
#define SOCK_GBUS_READ_UINT8     0x1
#define SOCK_GBUS_READ_UINT16    0x2
#define SOCK_GBUS_READ_UINT32    0x3

#define SOCK_GBUS_WRITE_UINT8    0x4
#define SOCK_GBUS_WRITE_UINT16   0x5
#define SOCK_GBUS_WRITE_UINT32   0x6

#define SOCK_GBUS_READ_DATA8     0x7
#define SOCK_GBUS_READ_DATA16    0x8
#define SOCK_GBUS_READ_DATA32    0x9

#define SOCK_GBUS_WRITE_DATA8    0xa
#define SOCK_GBUS_WRITE_DATA16   0xb
#define SOCK_GBUS_WRITE_DATA32   0xc

#define SOCK_GBUS_LOCK_REGION    0xd
#define SOCK_GBUS_UNLOCK_REGION  0xe

/* dmacpy interface */
#define SOCK_DMACPY_GET_INFO     0x1
#define SOCK_DMACPY_WRITE_DATA   0x2
#define SOCK_DMACPY_READ_DATA    0x3


#define SOCK_LLAD_PORT   1664 
#define SOCK_LLAD_SERVICE   0
#define SOCK_GBUS_SERVICE   1
#define SOCK_DMACPY_SERVICE 2


#endif // __SOCK_PROTOCOL_H__
