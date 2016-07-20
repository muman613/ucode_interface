/*****************************************
 Copyright © 2005, 2006, 2007
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmmacros_arm.h
  @brief  

  Macros / inline functions that specifically use ARM 32bit assembly

  It's usually smarter, to have a deep look in a fancy cross compiler intrinsics and built-ins.
  That can do immediate evaluation and better toggles, and
  implementation is debugged already ;-)

  @author Emmanuel Michon
  @date   2011-06-30
*/

#ifndef __RMMACROS_ARM_H__
#define __RMMACROS_ARM_H__

#ifndef __arm__
#error This is only for an ARM toolchain
#endif

#include "rmmacros_arm_cp15.h"

#ifdef __ASSEMBLY__
#define LEAF(symbol)                   \
	.global  symbol;                \
	.type symbol, %function;	\
symbol:

/* mips has this one more elaborate. Like, a facility to display the size in .nm */
#define END(symbol)                  

#else /* !__ASSEMBLY__ */

#define MARK(x) do { __asm__ __volatile__("add r11, " #x "\nsub r11, "#x); } while (0)

#define PADNOP(x) do { __asm__ __volatile__(".rept " #x "\n nop\n .endr\n"); } while (0)

#define GETCOUNT() (RMuint32)RMgetLocalCycleCount()

#define RMclocksElapsedSince(val) (RMuint32)(GETCOUNT()-(val))

#define RMgetTableBaseAddress() (void *)(RMmoveFromCp15(RM_ARM_CP15_TTBR0) & ~0xff)


/*** Counters ***/
// Cycle counter, initialized in boot routine, should only be read
#define RMgetGlobalCycleCount() \
({ \
	volatile RMuint32 *base = RM_PA_TO_UNCACHED(RMmoveFromCp15(RM_ARM_CP15_CBAR) + 0x200); \
	RMuint32 upper = base[1],lower;				\
	while (1) { \
		lower = base[0]; \
		RMuint32 upperagain = base[1]; \
		if (upper == upperagain) break; /* this is how we cope with non-atomicity of a 64bit read in two steps. */	\
		upper = upperagain; \
	} \
	RMuint64from2RMuint32(upper,lower); \
})
	
#define RMgetLocalCycleCount() RMmoveFromCp15(RM_ARM_CP15_PMCCNTR)

/* Event counter: 6 counters that can count 64 different events */
#define RM_ARM_EVENT_SWINC               0x00
#define RM_ARM_EVENT_IFETCH_CACHE_REFILL 0x01
#define RM_ARM_EVENT_IFETCH_TLB_REFILL   0x02
#define RM_ARM_EVENT_DATA_REFILL         0x03
#define RM_ARM_EVENT_DATA_ACCESS         0x04
#define RM_ARM_EVENT_EXCEPTION           0x09
#define RM_ARM_EVENT_BRANCH              0x0d
#define RM_ARM_EVENT_CYCLE_COUNT         0x11 /* the event, not the dedicated counter */
/* cortex A9 specific */
#define RM_ARM_EVENT_STREX_FAILED        0x64
#define RM_ARM_EVENT_FP_INSTR            0x73
#define RM_ARM_EVENT_NEON_INSTR          0x74

/* counter ranges from 0 to 5 */
#define RMinitCounter(counter, event) \
do { \
	RMmoveToCp15(RM_ARM_CP15_PMCNTENSET, 1 << (counter)); \
	RMmoveToCp15(RM_ARM_CP15_PMSELR, (counter)); \
	RMmoveToCp15(RM_ARM_CP15_PMXEVTYPER, (event)); \
	RMmoveToCp15(RM_ARM_CP15_PMXEVCNTR, 0); \
} while(0)

#define RMgetCounter(counter) \
({ \
	RMmoveToCp15(RM_ARM_CP15_PMSELR, (counter)); \
	RMmoveFromCp15(RM_ARM_CP15_PMXEVCNTR); \
})

#define RMdisableCounter(counter, event) \
do { \
	RMmoveToCp15(RM_ARM_CP15_PMCNTENCLR, 1 << (counter)); \
} while(0)

#define RMgetCpuNum() \
({ \
	RMuint32 __hidden_rv = RMmoveFromCp15(RM_ARM_CP15_MPIDR) & 0xf;	       \
	__hidden_rv;                                              \
})

#define RMgetNumberOfCpus() \
({ \
 	RMuint32 base = RMmoveFromCp15(RM_ARM_CP15_CBAR);        \
 	RMuint32 __hidden_rv = 1 + (gbus_read_uint32_ireg(pgbus, base + 4) & 0x3);            \
 	__hidden_rv;                                              \
})

#define RMgetReg(reg) \
({ \
	RMuint32 __hidden_rv;					   \
	__asm__ __volatile__ ("mov %0, " reg "\n" \
			    : "=r" (__hidden_rv) );			\
	__hidden_rv;							\
})

#define RMsetReg(reg,val)	\
do { \
	__asm__ __volatile__ ("mov " reg ", %0\n" \
			      : : "r" ((RMuint32)(val)) );		\
} while (0)

#define RMinsShiftBits_arm(ptr, data, bits, shift) \
do __asm__ __volatile__(\
		"bfi %0, %1, #" STR(shift)", #" STR(bits)  \
		: "=&r" (*(ptr)) \
		: "r" (data), "0" (*(ptr))); while(0)
#undef RMinsShiftBits
#define RMinsShiftBits RMinsShiftBits_arm

/* no RMunshiftBits since the compiler recognizes it and maps to the correct
 * ubfx instruction. (codesourcery arm-2011.03) 
 * tc20110713 */

#define RMswapBytesUint32_arm(a)			\
({							\
	RMuint32 __hidden_rv;				\
							\
	__asm__ __volatile__(				\
			     "rev %0, %1\n"	\
			     : "=r" (__hidden_rv) /* may be same reg */ \
			     : "r" (a));		\
							\
	__hidden_rv;					\
})
#undef RMswapBytesUint32
#define RMswapBytesUint32 RMswapBytesUint32_arm

#define RMswapBitsUint32_arm(a)			\
({							\
	RMuint32 __hidden_rv;				\
							\
	__asm__ __volatile__(				\
			     "rbit %0, %1\n"	\
			     : "=r" (__hidden_rv) /* may be same reg */ \
			     : "r" (a));		\
							\
	__hidden_rv;					\
})
#undef RMswapBitsUint32
#define RMswapBitsUint32 RMswapBitsUint32_arm

/* enforce it has constant execution time whatever value of condition. hack */
#define RMmovn(c,a,b) ((c)?(a):(b))

// check existence of __builtin_popcount (intel isse3)

#endif /* __ASSEMBLY__ */

#endif /* __RMMACROS_ARM_H__ */
