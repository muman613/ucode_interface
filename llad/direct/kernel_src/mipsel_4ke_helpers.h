
/*****************************************
 Copyright © 2004-2005
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   helpers_4ke_mipsel.h
  @brief  

  Various functions calling assembly. Most of them require CP0 usable (typically kernel mode)

  Same as helpers_4ke.h but for mipsel-linux-gcc

  Requires: -mips32r2 -Wa,-mips32r2 for proper build

  @author Emmanuel Michon
  @date   2005-01-01
*/

#ifndef __MIPSEL_4KE_HELPERS_H__
#define __MIPSEL_4KE_HELPERS_H__


// see mips run page 256. You can only take pointers to those obviously
extern RMuint8 _ftext[], etext[], _fdata[], edata[], _fbss[], end[], _gp[];

#include <asm/asm.h>
#include <asm/regdef.h>
#include <asm/mipsregs.h>
#include <asm/cacheops.h>
#define write_c0_ebase(val) __write_32bit_c0_register($15, 1, val)

#define __STR(x) #x
#define STR(x) __STR(x)

#ifndef mb
#define mb() __asm__ __volatile__ ("/* mb marker */\n" : : : "memory")
#endif

/// 
/**
   Setup a watchpoint on [start&(~mask), start|mask[ area

   To remove a watchpoint use mode=0: setwatch(nr,0,0,0).

   Example: setwatch(5,3,0x9010010,0x1ff);

   sets the watchpoint #5 to monitor load&store in 0x90100000..0x901001ff

   Refer to MIPS software manual section 5.2.26

   This has to be implemented as a macro because there is no
   way to transmit the first parameter nr to the third operand of `mtc0'

   @param nr: 0..7
   @param mode: 1=sw 2=lw 4=instruction fetch (can be or'ed)
   @param start: will be aligned to 8 byte boundary
   @param mask: 7 <= mask <= 0xfff
   @return <ReturnValue>
*/
// static inline void setwatch(int nr,int mode,RMuint32 start,RMuint32 mask);
#ifndef setwatch
#define setwatch(nr,mode,start,mask)					\
__asm__ __volatile__(							\
		     ".set noreorder\n"					\
		     "mtc0 %0, " STR(CP0_WATCHHI) ", " #nr "\n"		\
		     "mtc0 %1, " STR(CP0_WATCHLO) ", " #nr "\n"		\
		     ".set reorder\n"					\
		     :							\
		     : "r" ((1<<30)|((mask)&~7)), "r" (((start)&~7)|(mode)));
#endif

#define RMuint32_sizeof(x) (sizeof(x)/4)

static inline void RMuint32_memcpy(RMuint32 *dest, const RMuint32 *src, RMuint32 RMuint32size)
{
	__asm__ __volatile__(
".set noreorder\n"
"       beqz    %2, 2f\n"
"	sll	$10, %2, 2\n"
"	addu	$10, %1\n"
"1:\n"
"	lw	$8, 0(%1)\n"
"	addu	%1, 4\n"
"	sw	$8, 0(%0)\n"
"	bne	%1, $10, 1b\n"
"	addu	%0, 4\n"
"2:\n"
".set reorder\n"
: "=&r" (dest), "=&r" (src)
: "r" (RMuint32size), "0" (dest), "1" (src)
: "$8", "$10");
}

static inline int RMuint32_memcmp(const RMuint32 *s1, const RMuint32 *s2, RMuint32 RMuint32size)
{
	int rc;

	__asm__ __volatile__(
".set noreorder\n"
"       move    %2, zero\n"
"       beqz    %3, 3f\n"
"	sll	$10, %3, 2\n"
"	addu	$10, %1\n"
"1:\n"
"	lw	$9, 0(%1)\n"
"	lw	$8, 0(%0)\n"
"	bne	$8, $9, 2f\n"
"	addu	%1, 4\n" // Yes, we do lose a load delay slot above --- but do not put two succ cond branches (see B55)
"	bne	%1, $10, 1b\n"
"	addu	%0, 4\n"
"2:\n"
"	subu	%2, $8, $9\n"
"3:\n"
".set reorder\n"
: "=&r" (s1), "=&r" (s2), "=&r" (rc)
: "r" (RMuint32size), "0" (s1), "1" (s2)
: "$8", "$9", "$10"); 

	return rc;
}	
	
static inline void RMuint32_memset(RMuint32 *s, int c, RMuint32 RMuint32size)
{
	__asm__ __volatile__(
".set noreorder\n"
"       beqz    %2, 2f\n"
"	sll	$10, %2, 2\n"
"	addu	$10, %0\n"
"1:\n"
"	subu	$10, 4\n"
"	bne	$10, %0, 1b\n"
"	sw	%1, 0($10)\n"
"2:\n"
".set reorder\n"
: 
: "r" (s), "r" (c), "r" (RMuint32size)
: "$10");
}

/// 
/**
   Address is specified in KSEG0

   @param byte_address  
   @return <ReturnValue>
*/
static inline RMuint32 isp_read_uint32(RMuint32 byte_address)
{
	RMuint32 v;

	__asm__ __volatile__(
".set noreorder\n"
"	cache	  " STR(Index_Load_Tag_I) ", 0(%1)\n"
"	mfc0	 %0, " STR(CP0_TAGLO) ", 1\n"
".set reorder\n"
: "=&r" (v)
: "r" (byte_address));

	return v;
}

static inline void isp_write_uint32(RMuint32 byte_address,RMuint32 data)
{
	__asm__ __volatile__(
".set noreorder\n"
"	mtc0	 %1, " STR(CP0_TAGLO) ", 1\n"
"	cache	0xc, 0(%0)      # index store datalo\n"
".set reorder\n"
:
: "r" (byte_address), "r" (data));
}

/// 
/**
   When gbus_time.h facilities are not available: use the processor
   counter (increases at f_clock/2)

   RMuint32 mark=_m32c0_mfc0(CP0_COUNT,0);
   while (delta_ticks(mark,_m32c0_mfc0(CP0_COUNT,0))<desiredticks);

   @param t1    
   @param t2    
   @return <ReturnValue>
*/
static inline RMuint32 delta_ticks(RMuint32 t1,RMuint32 t2)
{ 
	return ((t1)<=(t2))?((t2)-(t1)):(0xffffffff-((t1)-(t2)-1));
}

/// 
/**
   If hit on address, invalidate the line in instruction cache (16 bytes)
   Refer to 4KE SUM page 250

   @param address 
*/
static inline void icache_line_i(RMuint32 address)
{
	__asm__ __volatile__("cache " STR(Hit_Invalidate_I) ", 0x0(%0)" : : "r" (address));
}

/// 
/**
   If hit on address, invalidate the line in data cache (16 bytes)
   Refer to 4KE SUM page 250

   @param address       
*/
static inline void dcache_line_i(RMuint32 address)
{
	__asm__ __volatile__("cache " STR(Hit_Invalidate_D) ", 0x0(%0)" : : "r" (address));
}

/// 
/**
   If hit on address, writeback the line in data cache (16 bytes)
   Refer to 4KE SUM page 250

   @param address       
*/
static inline void dcache_line_w(RMuint32 address)
{
	__asm__ __volatile__("cache " STR(Hit_Writeback_D) ", 0x0(%0)" : : "r" (address) : "memory");
}

/// 
/**
   If hit on address, writeback and invalidate the line in data cache (16 bytes)
   Refer to 4KE SUM page 250

   @param address       
*/
static inline void dcache_line_wi(RMuint32 address)
{
	__asm__ __volatile__("cache " STR(Hit_Writeback_Inv_D) ", 0x0(%0)" : : "r" (address) : "memory");
}

static inline void scache_line_i(RMuint32 address)
{
	// Hit_Invalidate_S
	__asm__ __volatile__("cache 0x13, 0x0(%0)" : : "r" (address) : "memory");
}

static inline void scache_line_w(RMuint32 address)
{
	// Hit_Writeback_S
	__asm__ __volatile__("cache 0x1b, 0x0(%0)" : : "r" (address) : "memory");
}

static inline void scache_line_wi(RMuint32 address)
{ 
	// Hit_Writeback_Inv_S
	__asm__ __volatile__("cache 0x17, 0x0(%0)" : : "r" (address) : "memory");
}

static inline void icache_range_i(RMuint32 address,RMuint32 size) 
{
	RMuint32 la;
	
	for (la=address&~31;la<address+size;la+=32) icache_line_i(la);
}

static inline void dcache_range_i(RMuint32 address,RMuint32 size) 
{
	RMuint32 la;
	
	for (la=address&~31;la<address+size;la+=32) dcache_line_i(la);
}

static inline void dcache_range_w(RMuint32 address,RMuint32 size) 
{
	RMuint32 la;
	
	for (la=address&~31;la<address+size;la+=32) dcache_line_w(la);
}

static inline void dcache_range_wi(RMuint32 address,RMuint32 size) 
{
	RMuint32 la;
	
	for (la=address&~31;la<address+size;la+=32) dcache_line_wi(la);
}

static inline void scache_range_i(RMuint32 address,RMuint32 size) 
{
	RMuint32 la;
	
	for (la=address&~31;la<address+size;la+=32) scache_line_i(la);
}

static inline void scache_range_w(RMuint32 address,RMuint32 size) 
{
	RMuint32 la;
	
	for (la=address&~31;la<address+size;la+=32) scache_line_w(la);
}

static inline void scache_range_wi(RMuint32 address,RMuint32 size) 
{
	RMuint32 la;
	
	for (la=address&~31;la<address+size;la+=32) scache_line_wi(la);
}

/**
   Direct uncached (kseg1) access above gbus address 0x20000000 is not possible on 4KE.

   As a consequence, write a construct like:
   {
   // cause the range 0x6400_0000-0x67ff_ffff to be accessible thru 0x0800_0000-0x0bff_ffff
   gbus_write_uint32(pgbus,CPU_remap3_address,0x67000000);
   // access data
   gbus_read_uint32(pgbus,sigmaremap(0x67000000));
   }

   Modification of the remap registers must be avoided on a running cpu (refer to SMP8630 sw spec section 3.1.5)

   Remaps 0 and 1 are 64KBytes; 2,3 and 4 are 64MBytes.

   This function resolves to an empty macro when not running on MIPS, allowing shared code

   @param address       
   @return <ReturnValue>
*/
static inline RMuint32 sigmaremap(RMuint32 address)
{
	RMuint32 address31_16=address&~((1<<16)-1),
		address15_0=address&~((1<<16)-1),
		address31_26,address25_0;
	
#ifdef __XOS_H__
#define RB REG_BASE_xpu_block
#else
#define RB REG_BASE_cpu_block
#endif

	if (address31_16==*(volatile RMuint32 *)KSEG1ADDR(RB+CPU_remap_address)) return CPU_remap_address|address15_0;
	if (address31_16==*(volatile RMuint32 *)KSEG1ADDR(RB+CPU_remap1_address)) return CPU_remap1_address|address15_0;

	address31_26=address&~((1<<26)-1);
	address25_0=address&~((1<<26)-1);

	if (address31_26==*(volatile RMuint32 *)KSEG1ADDR(RB+CPU_remap2_address)) return CPU_remap2_address|address25_0;
	if (address31_26==*(volatile RMuint32 *)KSEG1ADDR(RB+CPU_remap3_address)) return CPU_remap3_address|address25_0;
	if (address31_26==*(volatile RMuint32 *)KSEG1ADDR(RB+CPU_remap4_address)) return CPU_remap4_address|address25_0;

#undef RB

	RMPanic(10); // hack kllad does not include statuses (e.m.)
	return -1;
}

/// 
/**
   When the MIPS operates with EXL=1 new exceptions will not set EPC
   This makes debugging painful

   This debug function releases EXL while in handler also keeps IE low

   @param       
*/
static inline void lex(void)
{
	write_c0_status(read_c0_status()&~(ST0_UM|ST0_EXL|ST0_IE));
}

static inline void reboot(void)
{
	write_c0_status(ST0_BEV|ST0_ERL);
	// this is the usual kseg1 rom address cast to void vector(void);
	((void (*)(void))KSEG1ADDR(CPU_remap_address))();
}

/**
   Install a simple jump+nop pair of statements at given exception vector

   @param vec: 0 (tlbrefill) 0x180 (ge)
   @param aja: `absolute' jump address (See MIPS Run page 190)
*/
static inline void setupvec(RMuint32 vec,RMuint32 aja)
{
	RMuint32 *dst=(RMuint32 *) KSEG0ADDR(vec);

	dst[0]=0x08000000|(aja>>4); // j aja
	dst[1]=0; // nop

	// d- and i- caches are not coherent
	dcache_line_w((RMuint32)dst);
	icache_line_i((RMuint32)dst);
}

static inline RMuint32 byterev(RMuint32 x)
{
	RMuint32 revx;

	__asm__ __volatile__(
".set noreorder\n"
"wsbh %0, %1\n"
"rotr %0, %0, 16\n"
".set reorder\n"
: "=&r" (revx)
: "r" (x));

	return revx;
}

#endif //__MIPSEL_4KE_HELPERS_H__
