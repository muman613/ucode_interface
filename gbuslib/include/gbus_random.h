/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   gbus_random.h
  @brief  

  long description

  @author Emmanuel Michon
  @date   2004-03-15
*/

#ifndef __GBUS_RANDOM_H__
#define __GBUS_RANDOM_H__

#include "llad/include/gbus.h"

/// 
/**
   Tweak the given pll to generate eleven bits of good quality random.

   Note: PLL 0 is for CPUs. 
   The usage of PLLs is usually 1 for digital video, 2 for composite, 3 for audio.

   Current implementation takes 10ms to execute.

   USE OF THIS FUNCTION IS INCOMPATIBLE WITH PENDING VIDEO OR AUDIO PLAYBACK.

   This function is not reentrant

   Details
   -------
   Clock at different rates are generated using a programmable PLL. 
   The delay to establish a clean clock is not deterministic.

   In this function, we:
   - route the PLL to `sel' and set `sel' counter to zero.
   - toggle the PLL between two values F1 and F2 during 10 ms.
   - check that `sel' counter is big enough (e.g. at least 20 bits)
   - return the lowest eleven bits of this counter.
   F1 and F2 have to be chosen big enough to increase counter rapidly.

   @param pgbus
   @param pll 1, 2, or 3
   @return ReturnValue
*/
RMuint32 gbus_random_init(struct gbus *pgbus, RMuint32 pll);

/// 
/**
   To get a random number, call this function

   This function is not reentrant if same seed_address

   @param pgbus
   @param seed_address (anywhere in RAM (for instance, RANDOM0 or RANDOM1 in local ram))
   @return ReturnValue
*/
RMuint32 gbus_random_value(struct gbus *pgbus, RMuint32 seed_address);

#endif // __GBUS_RANDOM_H__
