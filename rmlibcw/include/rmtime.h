/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   rmtime.h
  @ingroup os
  @brief  Defines some functions to collect time informations.

  Never expect time functions to be extremely accurate especially
  on true multitasking operating systems, and if you ask for delays
  under the system scheduler timeslice (typically 10 milliseconds).

  @author Emmanuel Michon
  @date   2001-01-26
  @ingroup libcapi
*/

#ifndef __RMTIME_H__
#define __RMTIME_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup libcapi
 *  @{
 */

///
/**
	returns the number of elapsed cycles from time ref0 to time ref1, with 32 bit wraparound
	
	Wraparound only guaranteed for distances below 0x80000000
	Both parameter have to be of the same time unit, which will also be the 
	time unit of the return value (Seconds, Microseconds, Clocks, etc.)
	
	Equivalent:
	#define RMCyclesElapsed32(ref0, ref1) ((ref1) - (ref0))
	
	@param ref0  time origin
	@param ref1  time destination
	@return      numerical distance from ref0 to ref1
*/
RM_LIBRARY_IMPORT_EXPORT RMuint32 RMCyclesElapsed32(RMuint32 ref0, RMuint32 ref1);

///
/**
	returns the number of elapsed cycles from time ref0 to time ref1, with 64 bit wraparound
	
	Wraparound only guaranteed for distances below 0x8000000000000000
	Both parameter have to be of the same time unit, which will also be the 
	time unit of the return value (Seconds, Microseconds, Clocks, etc.)
	
	Equivalent:
	#define RMCyclesElapsed64(ref0, ref1) ((ref1) - (ref0))
	
	@param ref0  time origin
	@param ref1  time destination
	@return      numerical distance from ref0 to ref1
*/
RM_LIBRARY_IMPORT_EXPORT RMuint64 RMCyclesElapsed64(RMuint64 ref0, RMuint64 ref1);

/// 
/**
   Sleep _at least_ microsec.
   
   Be aware that most multitasking OS cannot implement idle sleep for less
   than a scheduler timeslice.

   So, an accurate sleep under this limit has to be implemented as 
   an active loop. Sending bits over an i2c bus needs such very short sleeps.

   @param microsec      
*/
RM_LIBRARY_IMPORT_EXPORT void RMMicroSecondSleep(RMuint64 microsec);

/// 
/**
   Returns the number of microseconds elapsed since some origin.

   There is no assumption concerning this origin, so this function
   shall always be called to compute differences. The return value 
   will span the complete value range, and wrap around at the highest
   value. Except for the wraparound case, each return value will be 
   greater or equal to previous return values.

   @param   none
   @return  current time reference value in microseconds
*/
RM_LIBRARY_IMPORT_EXPORT RMuint64 RMGetTimeInMicroSeconds(void);

/// 
/**
   Same thing as RMGetTimeInMicroSeconds, but time unit is system 
   clock reference (MPEG-2 unit) (90kHz).
   
   @param   none
   @return  current time reference value in 90kHz units

   @see RMGetTimeInMicroSeconds
*/
RM_LIBRARY_IMPORT_EXPORT RMuint64 RMGetTimeInSCR(void);

/// 
/**
   Sleeps for a random duration between 0 and microsec with uniform probability.

   Only used in stress tests to trap synchronization functions bugs.

   Warning!!! unlike most time function, the argument is only a RMuint32.

   @param microsec      
*/
RM_LIBRARY_IMPORT_EXPORT void RMRandomMicroSecondSleep(RMuint32 microsec);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMTIME_H__
