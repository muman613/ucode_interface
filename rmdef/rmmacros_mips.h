/*****************************************
 Copyright © 2005, 2006, 2007
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmmacros_mips.h
  @brief  

  Macros / inline functions that specifically use MIPS 32bit assembly

  It's usually smarter, to have a deep look in a fancy cross compiler intrinsic and built-ins,
  like __builtin_mips_bitrev(). That can do immediate evaluation and better toggles, and
  implementation is debugged already ;-)

  @author Emmanuel Michon
  @date   2011-06-30
*/

#ifndef __RMMACROS_MIPS_H__
#define __RMMACROS_MIPS_H__

#ifndef __mips__
#error This is only for a MIPS toolchain
#endif

#include "rmmacros_mips_cp0.h"

#ifdef __ASSEMBLY__


/*
  code sourcery adds `frame sp...' something that fails to build because sp is written $sp.
 */
#undef LEAF

/*
  bug in assembler (?) you cannot pad mips16 asm with a sequence like 0x65 0x00 (nop).
  So I had to choose a byte-repeating pattern.
  This one is roughly safe

  7777      	cmpi	a3,119
*/
#define LEAF(symbol)                                    \
                .globl  symbol;                         \
	.align 2,0x77;				\
                .type   symbol,@function;               \
                .ent    symbol,0;                       \
symbol:

#ifndef END
#define END(symbol)                                   \
                .end    symbol;                       \
                .size   symbol,.-symbol
#endif

#define RM_KVA_TO_PA(x) ((x)&((1<<29)-1))
#define RM_PA_TO_KVA0(x) ((x)|(4<<29))
#define RM_PA_TO_KVA1(x) ((x)|(5<<29))

#define add add_dont_use_overflow_variants_see_mips_run_8_7_4
#define sud sub_dont_use_overflow_variants_see_mips_run_8_7_4

#else /* !__ASSEMBLY__ */

#define FORCE16 __attribute__((mips16)) 
#define FORCE32 __attribute__((nomips16)) 

#define ASMPROLOGUE ".set push\n.set noreorder\n"
#define ASMEPILOGUE ".set pop\n"
#define PADNOP(x) do { __asm__ __volatile__(".rept " #x "\n nop\n .endr\n"); } while (0)
#define MARK(x) do { __asm__ __volatile__("addu $v0, " #x "\nsubu $v0, "#x); } while (0)

#define RM_KVA_TO_PA(x) RMunshiftBits(x,29,0)
#define RM_KVA_TO_PA_c(x) ((RMuint32)(x)&((1<<29)-1))
#define RM_PA_TO_KVA0(x) (RMuint32)((RMuint32)(x)|(4<<29))
#define RM_PA_TO_KVA1(x) (RMuint32)((RMuint32)(x)|(5<<29))

/*
  Basically this is

  x=c?a:b;

  but forcing this assembly implementation is for cryptography microanalysis resistance
  both branches are garanteed to take the same time
 */
#define RMmovn(c,a,b)							\
({									\
	RMuint32 __hidden_rv;						\
									\
	__asm__ __volatile__ (ASMPROLOGUE				\
			      "move %0, %2\n"				\
			      "movn %0, %1, %3\n"			\
			      ASMEPILOGUE				\
			      : "=&r" (__hidden_rv)			\
			      : "r" ((RMuint32)(a)), "r" ((RMuint32)(b)), "r" ((RMuint32)(c)));	\
									\
	__hidden_rv;							\
})

/*
  obviously conflicting with gcc register allocation
  useful in some cases, like getting $sp, or using $k0/$k1 to make spaghettis.
 */
#define RMgetReg(reg) \
({ \
	RMuint32 __hidden_rv;					   \
	__asm__ __volatile__ (ASMPROLOGUE "move %0, " reg "\n" ASMEPILOGUE \
			    : "=r" (__hidden_rv) );			\
	__hidden_rv;							\
})

#define RMsetReg(reg,val)	\
do { \
	__asm__ __volatile__ (ASMPROLOGUE "move " reg ", %0\n" ASMEPILOGUE \
			      : : "r" ((RMuint32)(val)) );		\
} while (0)

/*
  beyond this point, this is only for kernel mode.
 */
#define RMmfc0(reg, sel) \
({ \
	RMuint32 __hidden_rv;						\
	__asm__ __volatile__ (ASMPROLOGUE "mfc0 %0, " STR(reg) ", " #sel "\n" ASMEPILOGUE \
			    : "=r" (__hidden_rv));			\
	__hidden_rv;							\
})

/*
  The memory is a clobber here because you may change a TLB setting, e.g. have a part of addressing space
  move under gcc's feet.
*/
#define RMmtc0(reg, sel, val) \
do { \
	__asm__ __volatile__ (ASMPROLOGUE "mtc0 %0, " STR(reg) ", " #sel "\n" ASMEPILOGUE \
                        : \
			      : "r" ((RMuint32)(val))	\
                        : "memory"); \
} while (0)

/*
  RMrdhwr allows reading the following registers from user mode.
  Access to these registers must have been previously enabled in RM_C0_HWRENA
  (bug#9046 and See MIPS run second edition section 8.5.12)
 */
#define RMrdhwr(reg) \
({ \
        RMuint32 __hidden_rv;                                           \
        __asm__ __volatile__ (ASMPROLOGUE "rdhwr %0, $" STR(reg) "\n" ASMEPILOGUE \
                            : "=r" (__hidden_rv));                      \
        __hidden_rv;                                                    \
})

/***************************************************/
/* timing functions --- in clocks ******************/
/***************************************************/

#define GETCOUNT() RMrdhwr(RM_HWR_COUNT)
#define RMclocksElapsedSince(val) (RMuint32)( /*every other*/ 2* /* <--- ! */ (GETCOUNT()-(val)))

/***************************************************/
/* timing functions --- end ************************/
/***************************************************/

/**
   Setup a watchpoint on [start&(~mask), start|mask[ area

   Example: setwatch(5,3,0x90100010,0x1ff,3);

   sets the watchpoint #5 to monitor load&store in 0x90100000..0x901001ff
   on asid 3

   Refer to MIPS software manual section 5.2.26

   This has to be implemented as a macro because there is no
   way to transmit the first parameter nr to the third operand of `mtc0'

   @param nr: 0..7
   @param mode: 1=sw 2=lw 4=instruction fetch (can be or'ed)
   @param start: will be aligned to 8 byte boundary
   @param mask: 2^n-1 with 7 <= mask <= 0xfff
   @param asid: asid, or WATCH_G for `global'
*/
#define RMsetWatch(nr,mode,start,mask,asid)				\
do {									\
	__asm__ __volatile__(ASMPROLOGUE				\
			     "mtc0 %0, " STR(RM_C0_WATCHHI) ", " #nr "\n"	\
			     "mtc0 %1, " STR(RM_C0_WATCHLO) ", " #nr "\n"	\
			     ASMEPILOGUE				\
			     :						\
			     : "r" (((asid)<<16)|((mask)&~7)), "r" (((RMuint32)(start)&~7)|(mode))); \
}									\
while (0)
#define RMclearWatch(nr) \
do {									\
	__asm__ __volatile__(ASMPROLOGUE				\
			     "mtc0 $0, " STR(RM_C0_WATCHHI) ", " #nr "\n"	\
			     "mtc0 $0, " STR(RM_C0_WATCHLO) ", " #nr "\n"	\
			     ASMEPILOGUE);				\
}									\
while (0)

/*
  ON 8656ES3 and up all the ?cache_* are obsoleted by cache_range_op() that better handles
  the `cache stepping' with rdhwr $1. It is planned the ipu goes from L1 lines of 16 bytes -> 32 bytes at some point

  Archop hardcodes 16 bytes which works on 16/32 byte lines
 */

/**
   All cache related instructions below operate on cache lines.
   A cache line is 32bytes on 24Kf and 16bytes on 4KE.

   For the *_range_* that come afterwards, the address increment is hardcoded to 16, so they will be
   correct, but twice slower, on 24K.

   When relocating a piece of code, you will have to writeback data cache, invalidate instruction cache.
   As soon as the size exceeds the cache size, the *_range_* functions will work but take too long.
   In this case, the ROM has functions to operate on the entire cache instead.

   When locking a range, first come, first served.

   If hit on address, invalidate the line in instruction cache (16 bytes)
   Refer to 4KE SUM page 250

   @param address 
*/
FORCE32 extern inline void icache_line_i(RMuint32 address);
FORCE32 extern inline void icache_line_i(RMuint32 address)
{
	__asm__ __volatile__(ASMPROLOGUE "cache " STR(RM_Hit_Invalidate_I) ", 0(%0)\n" ASMEPILOGUE : : "r" (address) : "memory");
}

/**
   Fetch and lock by address.

   @param address       
*/
FORCE32 extern inline void icache_line_fl(RMuint32 address);
FORCE32 extern inline void icache_line_fl(RMuint32 address)
{
	__asm__ __volatile__(ASMPROLOGUE "cache " STR(RM_Fetch_Lock_I) ", 0(%0)\n" ASMEPILOGUE : : "r" (address) : "memory");
}

/**
   Fetch and lock by address.

   @param address       
*/
FORCE32 extern inline void dcache_line_fl(RMuint32 address);
FORCE32 extern inline void dcache_line_fl(RMuint32 address)
{
	__asm__ __volatile__(ASMPROLOGUE "cache " STR(RM_Fetch_Lock_D) ", 0(%0)\n" ASMEPILOGUE : : "r" (address) : "memory");
}

/**
   If hit on address, invalidate the line in data cache (16 bytes)
   Refer to 4KE SUM page 250

   This operation unlocks locked lines.
   Intentionally, this does not writeback the dirty lines.

   @param address       
*/
FORCE32 extern inline void dcache_line_i(RMuint32 address);
FORCE32 extern inline void dcache_line_i(RMuint32 address)
{
	__asm__ __volatile__(ASMPROLOGUE "cache " STR(RM_Hit_Invalidate_D) ", 0(%0)\n" ASMEPILOGUE : : "r" (address) : "memory");
}

/**
   If hit on address, writeback the line in data cache (16 bytes)
   Refer to 4KE SUM page 250

   @param address       
*/
FORCE32 extern inline void dcache_line_w(RMuint32 address);
FORCE32 extern inline void dcache_line_w(RMuint32 address)
{
	__asm__ __volatile__(ASMPROLOGUE "cache " STR(RM_Hit_Writeback_D) ", 0(%0)\n" ASMEPILOGUE : : "r" (address) : "memory");
}

/**
   If hit on address, writeback and invalidate the line in data cache (16 bytes)
   Refer to 4KE SUM page 250

   Some fuzzy people call this `flush'

   @param address       
*/
FORCE32 extern inline void dcache_line_wi(RMuint32 address);
FORCE32 extern inline void dcache_line_wi(RMuint32 address)
{
	__asm__ __volatile__(ASMPROLOGUE "cache " STR(RM_Hit_Writeback_Inv_D) ", 0(%0)\n" ASMEPILOGUE : : "r" (address) : "memory");
}

/**
   Fetch and lock by address.

   @param address       
*/
FORCE32 extern inline void scache_line_fl(RMuint32 address);
FORCE32 extern inline void scache_line_fl(RMuint32 address)
{
	__asm__ __volatile__(ASMPROLOGUE "cache " STR(RM_Fetch_Lock_S) ", 0(%0)\n" ASMEPILOGUE : : "r" (address) : "memory");
}

/**
   If hit on address, invalidate the line in secondary cache (32 bytes)
   Refer to 24K SUM page 313

   This operation unlocks locked lines.
   Intentionally, this does not writeback the dirty lines.

   @param address       
*/
FORCE32 extern inline void scache_line_i(RMuint32 address);
FORCE32 extern inline void scache_line_i(RMuint32 address)
{
	__asm__ __volatile__(ASMPROLOGUE "cache " STR(RM_Hit_Invalidate_S) ", 0(%0)\n" ASMEPILOGUE : : "r" (address) : "memory");
}

/**
   If hit on address, writeback the line in secondary cache (32 bytes)
   Refer to 24K SUM page 313

   @param address       
*/
FORCE32 extern inline void scache_line_w(RMuint32 address);
FORCE32 extern inline void scache_line_w(RMuint32 address)
{
	__asm__ __volatile__(ASMPROLOGUE "cache " STR(RM_Hit_Writeback_S) ", 0(%0)\n" ASMEPILOGUE : : "r" (address) : "memory");
}

/**
   If hit on address, writeback and invalidate the line in secondary cache (32 bytes)
   Refer to 24K SUM page 313

   Some fuzzy people call this `flush'

   @param address       
*/
FORCE32 extern inline void scache_line_wi(RMuint32 address);
FORCE32 extern inline void scache_line_wi(RMuint32 address)
{
	__asm__ __volatile__(ASMPROLOGUE "cache " STR(RM_Hit_Writeback_Inv_S) ", 0(%0)\n" ASMEPILOGUE : : "r" (address) : "memory");
}

/*
  No prefetch for i-cache. We use Fill I
 */
FORCE32 extern inline void icache_prefetch_line_load(RMuint32 address);
FORCE32 extern inline void icache_prefetch_line_load(RMuint32 address)
{
	__asm__ __volatile__(ASMPROLOGUE "cache " STR(RM_Fill_I) ", 0(%0)\n" ASMEPILOGUE : : "r" (address) : "memory");
}

FORCE32 extern inline void cache_line_synci(RMuint32 address);
FORCE32 extern inline void cache_line_synci(RMuint32 address)
{
	__asm__ __volatile__(ASMPROLOGUE "synci 0(%0)\n" ASMEPILOGUE : : "r" (address) : "memory");
}

/*
  2007jul17 em seems there is no prefetch ability for i-cache. 
  For meaning of 0 see table 11-16
 */
FORCE32 extern inline void dcache_prefetch_line_load(RMuint32 address);
FORCE32 extern inline void dcache_prefetch_line_load(RMuint32 address)
{
	__asm__ __volatile__(ASMPROLOGUE "pref 0, 0(%0)\n" ASMEPILOGUE : : "r" (address) : "memory");
}

FORCE32 extern inline void icache_range_fl(RMuint32 address,RMuint32 size);
FORCE32 extern inline void icache_range_fl(RMuint32 address,RMuint32 size) 
{
	RMuint32 la;
	
	for (la=address&~15;la<address+size;la+=16) icache_line_fl(la);
}

FORCE32 extern inline void dcache_range_fl(RMuint32 address,RMuint32 size);
FORCE32 extern inline void dcache_range_fl(RMuint32 address,RMuint32 size) 
{
	RMuint32 la;
	
	for (la=address&~15;la<address+size;la+=16) dcache_line_fl(la);
}

FORCE32 extern inline void icache_range_i(RMuint32 address,RMuint32 size); 
FORCE32 extern inline void icache_range_i(RMuint32 address,RMuint32 size) 
{
	RMuint32 la;
	
	for (la=address&~15;la<address+size;la+=16) icache_line_i(la);
}

FORCE32 extern inline void dcache_range_i(RMuint32 address,RMuint32 size); 
FORCE32 extern inline void dcache_range_i(RMuint32 address,RMuint32 size) 
{
	RMuint32 la;
	
	for (la=address&~15;la<address+size;la+=16) dcache_line_i(la);
}

FORCE32 extern inline void dcache_range_w(RMuint32 address,RMuint32 size); 
FORCE32 extern inline void dcache_range_w(RMuint32 address,RMuint32 size) 
{
	RMuint32 la;
	
	for (la=address&~15;la<address+size;la+=16) dcache_line_w(la);
}

FORCE32 extern inline void dcache_range_wi(RMuint32 address,RMuint32 size); 
FORCE32 extern inline void dcache_range_wi(RMuint32 address,RMuint32 size) 
{
	RMuint32 la;
	
	for (la=address&~15;la<address+size;la+=16) dcache_line_wi(la);
}

FORCE32 extern inline void scache_range_i(RMuint32 address,RMuint32 size);
FORCE32 extern inline void scache_range_i(RMuint32 address,RMuint32 size) 
{
	RMuint32 la;
	
	for (la=address&~31;la<address+size;la+=32) scache_line_i(la);
}

FORCE32 extern inline void scache_range_w(RMuint32 address,RMuint32 size);
FORCE32 extern inline void scache_range_w(RMuint32 address,RMuint32 size) 
{
	RMuint32 la;
	
	for (la=address&~31;la<address+size;la+=32) scache_line_w(la);
}

FORCE32 extern inline void scache_range_wi(RMuint32 address,RMuint32 size);
FORCE32 extern inline void scache_range_wi(RMuint32 address,RMuint32 size) 
{
	RMuint32 la;
	
	for (la=address&~31;la<address+size;la+=32) scache_line_wi(la);
}

FORCE32 extern inline void icache_prefetch_range_load(RMuint32 address,RMuint32 size);
FORCE32 extern inline void icache_prefetch_range_load(RMuint32 address,RMuint32 size) 
{
	RMuint32 la;
	
	for (la=address&~15;la<address+size;la+=16) icache_prefetch_line_load(la);
}

FORCE32 extern inline void dcache_prefetch_range_load(RMuint32 address,RMuint32 size);
FORCE32 extern inline void dcache_prefetch_range_load(RMuint32 address,RMuint32 size) 
{
	RMuint32 la;
	
	for (la=address&~15;la<address+size;la+=16) dcache_prefetch_line_load(la);
}

FORCE32 extern inline void cache_range_synci(RMuint32 address,RMuint32 size);
FORCE32 extern inline void cache_range_synci(RMuint32 address,RMuint32 size) 
{
	RMuint32 la;
	
	for (la=address&~15;la<address+size;la+=16) cache_line_synci(la);
}

/***************************************************/
/* Coprocessor2 definitions ************************/
/***************************************************/
/**
   Move 32 bits FROM a coprocessor2 32 bits register

   Example: value = RMmfc2(15,1) to get the value of the coprocessor2
    register 15 in the second register's set.

   Refer to MIPS32 Architecture For Programmers Volume II, rev2.61 page 161

   @param reg: register implementation index
   @param set: register set index
*/
#define RMmfc2(reg,sel) \
   ({ \
    RMuint32 __hidden_rv;                        \
    __asm__ __volatile__ (ASMPROLOGUE "mfc2 %0, " STR(reg) ", " #sel "\n" ASMEPILOGUE \
        : "=r" (__hidden_rv));            \
    __hidden_rv;                            \
    })

/**
   Move 32 bits GPR stored value TO a coprocessor2 32 bits register

   Example: RMmtc2(15,1,17) to move the value 17 to the coprocessor2
    register 15 in the second register's set.

   Refer to MIPS32 Architecture For Programmers Volume II, rev2.61 page 180

   @param reg: register implementation index
   @param set: register set index
   @param val: immediate 32 bits value to be transferred to the coprocessor2
*/
#define RMmtc2(reg, sel, val) \
   do { \
       __asm__ __volatile__ (ASMPROLOGUE "mtc2 %0, " STR(reg) ", " #sel "\n" ASMEPILOGUE \
               : \
               : "r" ((RMuint32)(val))    \
               : "memory"); \
   } while (0)

/**
   Store 32 bits to memory from coprocessor2 register. This coprocessor2
    register can only be in the first register set (i.e. register 15 means
    register 15 from registers set 0 in the coprocessor2)

   Example: RMswc2(15,a) to move the value to the coprocessor2
    register 15 in the first registers set to the memory operand a.

   Refer to MIPS32 Architecture For Programmers Volume II, rev2.61 page 244

   @param reg: register implementation index
   @param mem: a place in memory address space, just use a variable and let
the compiler make its work
*/
#define RMswc2(reg, mem) \
   do { \
       __asm__ __volatile__ (ASMPROLOGUE "swc2 " STR(reg) ", %0\n" ASMEPILOGUE \
               : "=m" ((RMuint32)(mem))); \
   } while (0)

/**
  Load 32 bits from memory to coprocessor2 register. This coprocessor2
    register can only be in the first register set (i.e. register 15 means
    register 15 from registers set 0 in the coprocessor2)

   Example: RMlwc2(15,a) to move the value of the memory operand a 
to the coprocessor2 register 15 in the first registers set.

   Refer to MIPS32 Architecture For Programmers Volume II, rev2.61 page 150

   @param reg: register implementation index
   @param mem: a place in memory address space, just use a variable and let
the compiler make its work
*/
#define RMlwc2(reg, mem) \
   do { \
       __asm__ __volatile__ (ASMPROLOGUE "lwc2 " STR(reg) ", %0\n" ASMEPILOGUE \
               : \
               : "m" ((RMuint32)(mem))); \
   } while (0)
/***************************************************/
/* Coprocessor2 definitions --- end ****************/
/***************************************************/

#define RMinsShiftBits_mips(ptr, data, bits, shift) \
do __asm__ __volatile__( \
	"ins %0, %1, " STR(shift) ", " STR(bits) \
	: "=r" (*(ptr)) /* may be same reg */ \
	: "r" (data), "0" (*(ptr))); while (0)
#undef RMinsShiftBits
#define RMinsShiftBits RMinsShiftBits_mips

#define RMunshiftBits_mips(data, bits, shift)				\
({									\
	RMuint32 __hidden_rv;						\
									\
	__asm__ __volatile__(						\
			     "ext %0, %1, " STR(shift) ", " STR(bits)	\
			     : "=r" (__hidden_rv) /* may be same reg */	\
			     : "r" (data));				\
									\
	__hidden_rv;							\
})
#undef RMunshiftBits
#define RMunshiftBits RMunshiftBits_mips

#define RMswapBytesUint32_mips(a)				\
({							\
	RMuint32 __hidden_rv;				\
							\
	__asm__ __volatile__(				\
			     "wsbh %0, %1\n"		\
			     "rotr %0, %0, 16\n"	\
			     : "=r" (__hidden_rv) /* may be same reg */ \
			     : "r" (a));		\
							\
	__hidden_rv;					\
})
#undef RMswapBytesUint32
#define RMswapBytesUint32 RMswapBytesUint32_mips

#if defined __mips_dsp_rev
#if __mips_dsp_rev >= 1

static inline RMuint32 RMswapBitsUint32_mips(RMuint32 x)
{
	return __builtin_mips_bitrev(x>>16)|(__builtin_mips_bitrev(x)<<16);
}
#undef RMswapBitsUint32
#define RMswapBitsUint32 RMswapBitsUint32_mips
#endif

#if __mips_dsp_rev >= 2
/* experimental */
#undef RMprepend
#define RMprepend __builtin_mips_prepend

#endif
#endif

#endif /* __ASSEMBLY__ */

#endif /* __RMMACROS_MIPS_H__ */
