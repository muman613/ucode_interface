/*****************************************
 Copyright © 2004-2005
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   xenv2.h
  @brief  

  The prototypes below act on a clear area respecting the xenv2 format.

  (De)ciphering the area, as well as committing the changes (writing the
  area to flash) are trivial add-ons on top of this API.

  The underlying implementation is not optimized for speed 
  (read and write in O(nrecords)). There is no fragmentation (data completely
  rearranged at each write).

  It is not advised to repeatedly act on flash stored data, for
  the device does not support unlimited read/write operations (refer to spec)

  Power loss when committing the changes cause loss of the stored data.
  This can be avoided by storing the same data twice to two different sectors.

  --------------------------------------------------------------------------
  Specification of a secure storage on serial flash of reboot-persistent data (xenv2 format)

  We describe a way to concatenate (at most 4KByte area (12bits limit)) variable length
  records identified by a string, the `key' (working much like Windows registry)

  Page, seen as a byte array, is 
  
  0          4                     36                                             env_size   probsize
  | env_size | SHA-256 of following | xenv2_record0 | xenv2_record1 | .. | xenv2_recordn | xx xx .. |

  The SHA-256 extent is env_size-36.

  Description of a xenv2_record (bytes):

  |4bits   12bits (2bytes)   | variable, NULL terminated | variable         |
  attr     total record size   record name (string)        record value

  attr = 
   XENV_ATTR_RW 
   XENV_ATTR_RO can be written once only but can be deleted	
   XENV_ATTR_OTP this record can be written once only and cannot be deleted

  An individual record cannot exceed 4KBytes
  The complete environment size can be up to 32bit. However, you should probe on much less (probsize)
  --------------------------------------------------------------------------

  @author Emmanuel Michon
  @date   2005-05-17
*/

#ifndef __XENV_H__
#define __XENV_H__

// only 13 and 14 are special. You may put other attributes of your own that will work just like 15
#define XENV_ATTR_OTP 13
#define XENV_ATTR_RO  14
#define XENV_ATTR_RW  15

#define XENV2_EMPTY_SIZE 36

/**
   Initial xenv2 formatting to `empty'

   Passing the size is not necessary, however, minimum 24bytes must be accessible starting at base.

   @param base  
*/
void xenv2_format(RMuint32 *base);

/// 
/**
   Check for compliance with xenv2 format

   May be corrupted by: 
   - forgot to format
   - power loss during sflash write
   - intrusion

   @param base  
   @param probesize: prevent runaway in case of dos
   @return -ReturnValue-: env_size>=0 if valid, -1 if not.
*/
int xenv2_isvalid(RMuint32 *base,RMuint32 probesize);

/**
   Look for `recordname' in the clear area pointed to by base,size
   
   Returns 
   RM_NOT_FOUND if the record is absent
   RM_INSUFFICIENT_SIZE if provided *datasize cannot hold result, *datasize is updated with how much you need
   RM_ERROR if clear area is not compliant with xenv2 format (data uninitialized or corrupted).

   In these error cases, dst won't be written. If return is RM_OK, dst receives the value.

   Example
   {
     RMuint32 data[5];
     
     xenv2_get(cleararea,PAGE_SIZE,"myhash",data);
   }

   @param base  
   @param size  
   @param recordname    
   @param dst   
   @param datasize: will be updated to actual size 
   @return -ReturnValue-
*/
RMstatus xenv2_get(RMuint32 *base, RMuint32 size, RMascii *recordname, void *dst, RMuint32 *datasize);

/**
   Sets `recordname' in the clear area pointed to by base,size
   The area is rearranged to take the change into account (no fragmentation)
   
   The empty string is a valid key. 
   Storage of zero-length records is ok.
   Updating a record with a smaller or larger size is ok.
   
   Special: passing a NULL src means: delete the existing record. In this case, datasize is ignored.
   
   A record of attr XENV_ATTR_RW can be updated to a different attr. Others are immutable.
   
   It is advised to call the `commit' (write sector to flash) function if this
   call is successful.

   Returns 
   RM_INVALIDMODE if setting an existing XENV_ATTR_RO/_OTP for the second time, 
                  or deleting a XENV_ATTR_OTP record
   RM_INSUFFICIENT_SIZE if room is exhausted
   RM_ERROR if clear area is not compliant with xenv2 format (data uninitialized or corrupted).

   @param base  
   @param size  
   @param recordname    
   @param src
   @param attr  
   @param datasize
   @return -ReturnValue-
*/
RMstatus xenv2_set(RMuint32 *base, RMuint32 size, RMascii *recordname,void *src,RMuint8 attr,RMuint32 datasize);

#ifdef _DEBUG
void xenv2_dump(RMuint32 *base,RMuint32 size);
#else
#define xenv2_dump(base,size) do {} while (0)
#endif

#endif // __XENV_H__
