/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmpacketcommandioctl.h
  @brief  

  Describes the API to issue ATAPI packet commands to a drive device.

  @author Emmanuel Michon
  @date   2003-02-11
  @ingroup libcapi
*/

#ifndef __RMPACKETCOMMANDIOCTL_H__
#define __RMPACKETCOMMANDIOCTL_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup libcapi
 *  @{
 */

#define RM_ATAPI_DATA_DIRECTION_WRITE	1
#define RM_ATAPI_DATA_DIRECTION_READ	2

/**
 * Open a device identified by a unique platform-specific string.
 * returns a handle to the open device.
 *
 * @naname string identifying the device to open. On Linux, this will
 *         will be /dev/hdd or /dev/scd0 for example.
 * @returns a non-NULL handle on success, NULL on failure.
 */
void *RMOpenPacketCommand(const RMnonAscii *naname);

/**
 * Close the device. The device is automatically closed by the OS upon 
 * process death.
 *
 * @param handle the drive device.
 */
void RMClosePacketCommand(void *handle);

/**
 * Issue an atapi packet command to the device. The atapi commands are described
 * in INF 8020 and INF 8090.
 *
 * @param handle the drive device.
 * @param pP atapi command to issue to the drive.
 * @returns negative values on failure.
 */
RMint32 RMIoctlPacketCommand(void *handle,RMpacketCommand *pP);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMPACKETCOMMANDIOCTL_H__
