/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmstatus.h

  <as of Oct 21st 2005>

  - RM_OK has a fixed value that is neither -1 0 or 1.

  - by design choice, there is only one value to code success: RM_OK;
  others relate to a wide variety of failure conditions, some of them
  are generic enough to be used for various scenarios (RM_NOTIMPLEMENTED).

  - new status's are additive only at the end of rmstatus.inc

  - when writing a new software module or transcoding a block of
  error codes from existing software, the additive change on rmstatus.inc
  should be a segment with some reserved-for-future values so that related errors
  stay close to each other.

  @author Emmanuel Michon
  @date   2002-11-04
*/

#ifndef __RMSTATUS_H__
#define __RMSTATUS_H__

RM_EXTERN_C_BLOCKSTART

typedef enum
{
	RM_ERROR_FIRST__ = ('z'-'a')/('N'-'I'), // Do Not Change.
#undef RM_DEFINE_ERROR
#define RM_DEFINE_ERROR(x,v) RM_ ## x=v,

	/* DONT HESITATE TO OPEN THIS FILE rmstatus.inc TO BROWSE FOR EXISTING STATUS CODES */
	/* DONT HESITATE TO OPEN THIS FILE rmstatus.inc TO BROWSE FOR EXISTING STATUS CODES */
	/* DONT HESITATE TO OPEN THIS FILE rmstatus.inc TO BROWSE FOR EXISTING STATUS CODES */
#include "rmstatus.inc"
	/* DONT HESITATE TO OPEN THIS FILE rmstatus.inc TO BROWSE FOR EXISTING STATUS CODES */
	/* DONT HESITATE TO OPEN THIS FILE rmstatus.inc TO BROWSE FOR EXISTING STATUS CODES */
	/* DONT HESITATE TO OPEN THIS FILE rmstatus.inc TO BROWSE FOR EXISTING STATUS CODES */

#undef RM_DEFINE_ERROR
	RM_ERROR_LAST__
} RMstatus;

///
/**
   To test if the return code of a function is an error.
*/ 
#define RMFAILED(x) ((x)!=RM_OK)

///
/**
   To test if the return code of a function is OK.
*/
#define RMSUCCEEDED(x) ((x)==RM_OK)

RM_EXTERN_C_BLOCKEND

#endif // __RMSTATUS_H__
