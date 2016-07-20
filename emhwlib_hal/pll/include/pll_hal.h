/*
 * emhwlib_hal/pll/include/pll_hal.h
 *
 * Copyright (c) 2005 Sigma Designs, Inc. 
 * All Rights Reserved. Proprietary and Confidential.
 *
 */
 
/**
  @file emhwlib_hal/pll/include/pll_hal.h
  @brief clock generation and routing HAL
  
  @author Christian Wolff
*/

#ifndef __EMHWLIBHAL_PLL_H__
#define __EMHWLIBHAL_PLL_H__

#include "llad/include/gbus.h"
#include "pll_hal_types.h"
#include "pll_hal_chipspecific.h"

/* 
	most pll_hal functions are complimented by a .._regs version of the same,
	which allows to fill a PLLRegSet struct with the changes instead of 
	writing directly into the hardware registers. To use this, define the 
	struct and initialize it with pll_hal_init_regs(). After filling
	the struct with the other functions, use pll_hal_apply_regs()
	to write the data into the hardware registers.
*/


RM_EXTERN_C_BLOCKSTART

/**
	initialize and empty regs struct
	
	@param regs  address of register holding struct
*/
RMstatus pll_hal_init_regs(
	struct PLLRegSet *regs);
/**
	Return register content from addr, or, if present, from regs
	
	@param pGBus
	@param addr  GBus address of the register
	@param regs  address of register holding struct
*/
RMuint32 pll_hal_get_reg(
	struct gbus *pGBus, 
	RMuint32 addr, 
	struct PLLRegSet *regs);

/**
	set register in regs, remove older duplicates
	
	@param pGBus
	@param addr  GBus address of the register
	@param reg   data to be stored in register
	@param regs  address of register holding struct
*/
RMstatus pll_hal_set_reg(
	struct gbus *pGBus, 
	RMuint32 addr, 
	RMuint32 reg, 
	struct PLLRegSet *regs);

/**
	write content of regs to registers, then empty regs
	
	@param pGBus
	@param regs  address of register holding struct
*/
RMstatus pll_hal_apply_regs(
	struct gbus *pGBus, 
	struct PLLRegSet *regs);


/**
	Query the current settings of a PLL
	
	@param pGBus
	@param pll_number  Number of the PLL to be queried, range 0..3
	@param f_in        nominal input frequency of the PLL.
	@param f_out_0     return value containing the frequency of the PLL before the post dividers.
	@param f_out_1     return value containing the frequency of the PLL after post divider 1.
	@param f_out_1     return value containing the frequency of the PLL after post divider 2.
	
	Return pointers set to NULL will not be filled.
	Unavailable outputs will return zero.
*/
RMstatus pll_hal_get_pll_regs(
	struct gbus *pGBus, 
	enum PLLGen pll, 
	RMuint32 f_in, 
	RMuint32 *f_out_0, 
	RMuint32 *f_out_1, 
	RMuint32 *f_out_2, 
	struct PLLRegSet *regs);

RMstatus pll_hal_get_pll(
	struct gbus *pGBus, 
	enum PLLGen pll, 
	RMuint32 f_in, 
	RMuint32 *f_out_0, 
	RMuint32 *f_out_1, 
	RMuint32 *f_out_2);


/**
	Set up a PLL
	
	@param pGBus
	@param pll_number  Number of the PLL to be set, range: 0..3
	@param f_in        Nominal input frequency of the PLL.
	@param max_m       Maximum value of the 'M' enumerator inside the PLL, range: 0..127 (0 == hw. max.)
	@param *f_out_0    Frequency to be set as intermediate frequency.
	@param *f_out_1    Frequency to be output from post divider 1.
	@param *f_out_2    Frequency to be output from post divider 2.
	
	All *f_out_ values can be set to zero for "don't care".
	All *f_out_ values will be set to the actual frequencies of the PLL.
	Each f_out_ might be NULL and will then be ignored
	*f_out_0 has precedence over *f_out_1 and *f_out_2; If *f_out_0
	is specified, the other two might be wildly inaccurate.
*/
RMstatus pll_hal_set_pll_regs(
	struct gbus *pGBus, 
	enum PLLGen pll, 
	RMuint32 f_in, 
	RMuint32 max_m, 
	RMuint32 *f_out_0, 
	RMuint32 *f_out_1, 
	RMuint32 *f_out_2, 
	struct PLLRegSet *regs);

RMstatus pll_hal_set_pll(
	struct gbus *pGBus, 
	enum PLLGen pll, 
	RMuint32 f_in, 
	RMuint32 max_m, 
	RMuint32 *f_out_0, 
	RMuint32 *f_out_1, 
	RMuint32 *f_out_2);




/**
	Query a fractional divider
	
	@param pGBus
	@param pll_number  Number of the fractional "clean divider" to be set, range 0..10
	@param f_in        nominal input frequency of the CD (same for all CD, ClockSignal_CD).
	
	returns the output frequency of the CD.
*/
RMuint32 pll_hal_get_fractional_regs(
	struct gbus *pGBus, 
	enum PLLGen pll, 
	RMuint32 f_in, 
	struct PLLRegSet *regs);

RMuint32 pll_hal_get_fractional(
	struct gbus *pGBus, 
	enum PLLGen pll, 
	RMuint32 f_in);


/**
	Set a fraction divider
	
	@param pGBus
	@param pll_number  Number of the fractional "clean divider" to be set, range 0..10
	@param f_in        nominal input frequency of the CD (same for all CD, ClockSignal_CD).
	@param f_out       frequency to be output from the CD.
*/
RMstatus pll_hal_set_fractional_regs(
	struct gbus *pGBus, 
	enum PLLGen pll, 
	RMuint32 f_in, 
	RMuint32 f_out, 
	struct PLLRegSet *regs);

RMstatus pll_hal_set_fractional(
	struct gbus *pGBus, 
	enum PLLGen pll, 
	RMuint32 f_in, 
	RMuint32 f_out);

/**
   get the proportion between divider N and divider N-1 to get a
   closer clock.
   
   @param f_in 
   @param f_out 
   @param reg_div 
   @param min_count 
   @param max_count 
*/
RMstatus pll_hal_get_cleandiv_adjustment(
        enum PLLGen pll, 
	RMuint32 f_in, 
	RMuint32 f_out, 
	RMuint32 reg_div,
	RMuint64 *target_incr, 
	RMuint64 *target_den);

/**
	Retrieve a clock source to a PLL
	
	@param pGBus
	@param pll          PLL to be set
	returns clock source of the PLL
*/
enum PLLSource pll_hal_get_source_regs(
	struct gbus *pGBus, 
	enum PLLGen pll, 
	struct PLLRegSet *regs);

enum PLLSource pll_hal_get_source(
	struct gbus *pGBus, 
	enum PLLGen pll);


/**
	Assign a clock source to a PLL
	
	@param pGBus
	@param pll          PLL to be set
	@param source       clock source to be taken as the input for the PLL
	
	source defaults to PLLSource_xtal at boot up.
	This might affect all clocks derived from the specified PLL, 
	the application is responsible to re-set all of them.
*/
RMstatus pll_hal_set_source_regs(
	struct gbus *pGBus, 
	enum PLLGen pll, 
	enum PLLSource source, 
	struct PLLRegSet *regs);

RMstatus pll_hal_set_source(
	struct gbus *pGBus, 
	enum PLLGen pll, 
	enum PLLSource source);




/**
	Route a PLL or CD output to a clock signal
	
	@param pGBus
	@param pll          PLL or CD to be set
	@param pll_out      output of the PLL/CD to be used
	@param clk          clock signal where to route the clock
	
	Assigning a new clock to ClockSignal_CD will affect all other clocks 
	derived from clean divides, those will have to be set again.
	It is recommended to set ClockSignal_CD only once before everything 
	else, if at all neccessary.
*/
RMstatus pll_hal_route_clock_regs(
	struct gbus *pGBus, 
	enum PLLGen pll, 
	enum PLLOut pll_out, 
	enum ClockSignal clk, 
	struct PLLRegSet *regs);

RMstatus pll_hal_route_clock(
	struct gbus *pGBus, 
	enum PLLGen pll, 
	enum PLLOut pll_out, 
	enum ClockSignal clk);

/**
	Route a clock source other than from a PLL or CD to a clock signal
	
	@param pGBus
	@param source       clock source to be routed directly to the clock signal
	@param clk          clock signal where to route the clock
	
	This assigns a clock source directly to a clock signal, 
	bypassing any PLL or CD.
*/
RMstatus pll_hal_route_clock_source_regs(
	struct gbus *pGBus, 
	enum PLLSource source, 
	enum ClockSignal clk, 
	struct PLLRegSet *regs);

RMstatus pll_hal_route_clock_source(
	struct gbus *pGBus, 
	enum PLLSource source, 
	enum ClockSignal clk);


/**
	Retrieves the source of a clock signal
	
	@param pGBus
	@param clk          clock signal where to route the clock
	@param source       clock source to be routed directly to the clock signal
	@param pll          PLL or CD to be set
	@param pll_out      output of the PLL/CD to be used
	@param pllcd        whether the clock signal originates from a PLL or CD (TRUE), or from a direct clock source (FALSE)
	
	If the clock signal originates from a PLL or CD, *pllcd is set to TRUE, 
	*pll is set to the PLL or CD and *pll_out is set to the PLL output or
	CD post divider which is used. If the clock signal originates from a 
	direct clock source, *pllcd is set to FALSE and *source is set to the 
	clock source. No parameters can be NULL!
*/
RMstatus pll_hal_get_route_regs(
	struct gbus *pGBus, 
	enum ClockSignal clk, 
	enum PLLSource *source, 
	enum PLLGen *pll, 
	enum PLLOut *pll_out, 
	RMbool *pllcd, 
	struct PLLRegSet *regs);

RMstatus pll_hal_get_route(
	struct gbus *pGBus, 
	enum ClockSignal clk, 
	enum PLLSource *source, 
	enum PLLGen *pll, 
	enum PLLOut *pll_out, 
	RMbool *pllcd);


/**
	Determine the post divider factor of a clock signal, behind the PLL/CD output
	
	@param pGBus
	@param clk          clock signal where to route the clock
	@param mult         multiplication factor of the frequency between PLL/CD and the clock signal
	@param div          division factor of the frequency between PLL/CD and the clock signal
*/
RMstatus pll_hal_get_post_ratio_regs(
	struct gbus *pGBus, 
	enum ClockSignal clk, 
	RMuint32 *mult, 
	RMuint32 *div, 
	struct PLLRegSet *regs);

RMstatus pll_hal_get_post_ratio(
	struct gbus *pGBus, 
	enum ClockSignal clk, 
	RMuint32 *mult, 
	RMuint32 *div);


/**
	Legacy version of pll_hal_get_post_ratio[_regs](): Determine the post divider factor of a clock signal, behind the PLL/CD output
	
	@param pGBus
	@param clk          clock signal where to route the clock
	@param ratio        division factor of the frequency between PLL/CD and the clock signal
*/
RMstatus pll_hal_get_ratio_regs(
	struct gbus *pGBus, 
	enum ClockSignal clk, 
	RMuint32 *ratio, 
	struct PLLRegSet *regs);

RMstatus pll_hal_get_ratio(
	struct gbus *pGBus, 
	enum ClockSignal clk, 
	RMuint32 *ratio);


/**
	Assign a frequency to a clock signal, utilizing a specific PLL/CD and post divider
	
	@param pGBus
	@param pll          PLL or CD to be set
	@param pll_source_freq   nominal frequency of the clock source of this PLL/CD
	@param max_m        Maximum value of the 'M' enumerator inside the PLL, range: 1..127, 0=ignored
	@param pll_out      output of the PLL/CD to be used
	@param clk          clock signal where to route the clock
	@param freq         frequency to be sent to clk, will be filled with the actual frequency
	
	Assigning a new clock to ClockSignal_CD will affect all other clocks 
	derived from clean divides, those will have to be set again.
	It is recommended to set ClockSignal_CD only once before everything 
	else, if at all neccessary.
	max_m can be used to balance the PLL between higher jitter and higher 
	frequency precision. The higher M is, the more jitter can be expected
	on the output signal, but limiting M too much can result in frequencies
	that are far off from the desired. A value of approx. 31 limits the PLL 
	to an acceptable jitter while allowing a decent accuracy.
	
	This function calls pll_hal_set() or pll_hal_set_fractional(), 
	followed by pll_hal_route_clock().
*/
RMstatus pll_hal_set_frequency_regs(
	struct gbus *pGBus, 
	enum PLLGen pll, 
	RMuint32 pll_source_freq, 
	RMuint32 max_m, 
	enum PLLOut pll_out, 
	enum ClockSignal clk, 
	RMuint32 *freq, 
	struct PLLRegSet *regs);

RMstatus pll_hal_set_frequency(
	struct gbus *pGBus, 
	enum PLLGen pll, 
	RMuint32 pll_source_freq, 
	RMuint32 max_m, 
	enum PLLOut pll_out, 
	enum ClockSignal clk, 
	RMuint32 *freq);


/**
	Returns the frequency of a clock signal
	
	@param pGBus
	@param pll_source_freq  frequency of the clock source of the PLL used for this clock signal
	@param clk     clock signal
	
	returns 0 on error or frequency of the specified clock signal
*/
RMuint32 pll_hal_get_frequency_regs(
	struct gbus *pGBus, 
	RMuint32 pll_source_freq, 
	enum ClockSignal clk, 
	struct PLLRegSet *regs);

RMuint32 pll_hal_get_frequency(
	struct gbus *pGBus, 
	RMuint32 pll_source_freq, 
	enum ClockSignal clk);




/** 
	Route a clock source to a configurable counter (ClockCounter_0 through _4)
	
	@param pGBus
	@param ctr        counter
	@param ctr_src    source signal for the counter
*/
RMstatus pll_hal_set_counter_source_regs(
	struct gbus *pGBus, 
	enum ClockCounter ctr, 
	enum ClockCounterSource ctr_src, 
	struct PLLRegSet *regs);

RMstatus pll_hal_set_counter_source(
	struct gbus *pGBus, 
	enum ClockCounter ctr, 
	enum ClockCounterSource ctr_src);


/** 
	Returns the clock source from a configurable counter (ClockCounter_0 through _4)
	
	@param pGBus
	@param ctr        counter
	
	returns 0 on error or source signal of the specified counter
*/
enum ClockCounterSource pll_hal_get_counter_source_regs(
	struct gbus *pGBus, 
	enum ClockCounter ctr, 
	struct PLLRegSet *regs);

enum ClockCounterSource pll_hal_get_counter_source(
	struct gbus *pGBus, 
	enum ClockCounter ctr);


/** 
	Set an initial counter value
	
	@param pGBus
	@param ctr        counter
	@param value      value to write into counter
*/
RMstatus pll_hal_set_counter(
	struct gbus *pGBus, 
	enum ClockCounter ctr, 
	enum ClockCounterSource ctr_src, 
	RMuint32 value);


/** 
	Returns the current counter value 
	
	@param pGBus
	@param ctr   counter
*/
RMuint32 pll_hal_get_counter(
	struct gbus *pGBus, 
	enum ClockCounter ctr);


/** 
	Returns the approximate current frequency of a counter, in Hz
	
	@param pGBus
	@param ctr        counter
	@param uSecDelay  idle-wait time
	
	WARNING: This function will block for the specified time!
	uSecDelay range: 0..159
	The larger uSecDelay, the more accurate the frequency is measured:
	uSecDelay = 100: Freq +/- 3ppm aprox.
	uSecDelay = 10: Freq +/- 33ppm aprox.
	uSecDelay = 1: Freq +/- 333ppm aprox.
	uSecDelay = 0: Freq +/- 100000ppm  aprox.
*/
RMuint32 pll_hal_get_counter_freqency(
	struct gbus *pGBus, 
	enum ClockCounter ctr, 
	RMuint32 uSecDelay);


/**
	Assign a new frequency to ClockSignal_CD while maintaining all CD output frequencies
	
	@param pGBus
	@param pll          PLL or CD to be set
	@param pll_source_freq   nominal frequency of the clock source of this PLL/CD
	@param max_m        Maximum value of the 'M' enumerator inside the PLL, range: 1..127, 0=ignored
	@param pll_out      output of the PLL/CD to be used
	@param freq         frequency to be sent to clk, will be filled with the actual frequency
	
	Assigns a new clock to ClockSignal_CD. All other clocks derived from 
	clean divides will be maintained, but a clock discontinuity may occur.
	It is recommended to set ClockSignal_CD only once before everything 
	else, if at all neccessary.
	
	This function calls pll_hal_set_frequency(), followed by several calls to pll_hal_set_fractional().
*/
RMstatus pll_hal_reset_CD_clock_regs(
	struct gbus *pGBus, 
	enum PLLGen pll, 
	RMuint32 pll_source_freq, 
	RMuint32 max_m, 
	enum PLLOut pll_out, 
	RMuint32 *freq, 
	struct PLLRegSet *regs);

RMstatus pll_hal_reset_CD_clock(
	struct gbus *pGBus, 
	enum PLLGen pll, 
	RMuint32 pll_source_freq, 
	RMuint32 max_m, 
	enum PLLOut pll_out, 
	RMuint32 *freq);

RM_EXTERN_C_BLOCKEND

#endif /* __EMHWLIBHAL_PLL_H__ */

