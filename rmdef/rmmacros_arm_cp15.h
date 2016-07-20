/*****************************************
 Copyright © 2005, 2006, 2007
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmmacros_arm_cp15.h
  @brief  

  A bunch of macros mostly related to ARM CP15 structure

  @author Emmanuel Michon
  @date   2011-07-04
*/

#ifndef __RMMACROS_ARM_CP15_H__
#define __RMMACROS_ARM_CP15_H__

/* from ARM ARM page B1-6 */
#define RM_ARM_MODE_USR 16
#define RM_ARM_MODE_FIQ 17
#define RM_ARM_MODE_IRQ 18
#define RM_ARM_MODE_SVC 19 /* supervisor */
#define RM_ARM_MODE_MON 22 /* monitor */
#define RM_ARM_MODE_ABT 23 /* abort */
#define RM_ARM_MODE_UND 27 /* undefined */
#define RM_ARM_MODE_SYS 31

/* definition of the following see ARM ARM page B3-65
 *      coproc reg name      opc1, rt, Crn, Crm, (opc2) 
 */
#define RM_ARM_CP15_MIDR(x)        p15, 0, x, c0, c0, 0  /* Main ID */
#define RM_ARM_CP15_CTR(x)         p15, 0, x, c0, c0, 1  /* Cache Type */
#define RM_ARM_CP15_TCMTR(x)       p15, 0, x, c0, c0, 2  /*implementation defined*/
#define RM_ARM_CP15_TLBTR(x)       p15, 0, x, c0, c0, 3  /* TLB type */
#define RM_ARM_CP15_MPIDR(x)       p15, 0, x, c0, c0, 5
#define RM_ARM_CP15_CCSIDR(x)      p15, 1, x, c0, c0, 0  /* Cache Size ID */
#define RM_ARM_CP15_CCLIDR(x)      p15, 1, x, c0, c0, 1  /* Cache Level ID */
#define RM_ARM_CP15_AIDR(x)        p15, 1, x, c0, c0, 7
#define RM_ARM_CP15_CCSELR(x)      p15, 2, x, c0, c0, 0  /* Cache Size Selection */
/* System control */
#define RM_ARM_CP15_SCTLR(x)       p15, 0, x, c1, c0, 0
#define RM_ARM_CP15_ACTLR(x)       p15, 0, x, c1, c0, 1
#define RM_ARM_CP15_CPACR(x)       p15, 0, x, c1, c0, 2
/* Security Extensions */
#define RM_ARM_CP15_SCR(x)         p15, 0, x, c1, c1, 0  /* Secure Configuration */
#define RM_ARM_CP15_SDER(x)        p15, 0, x, c1, c1, 1  /* Secure Debug Enable */
#define RM_ARM_CP15_NSACR(x)       p15, 0, x, c1, c1, 2  /* Non-Secure Access Control */
/* MMU and page tables */
#define RM_ARM_CP15_TTBR0(x)       p15, 0, x, c2, c0, 0
#define RM_ARM_CP15_TTBR1(x)       p15, 0, x, c2, c0, 1
#define RM_ARM_CP15_TTBCR(x)       p15, 0, x, c2, c0, 2
#define RM_ARM_CP15_DACR(x)        p15, 0, x, c3, c0, 0
/* Memory System Fault */
#define RM_ARM_CP15_DFSR(x)        p15, 0, x, c5, c0, 0  /* Data Fault Status */
#define RM_ARM_CP15_IFSR(x)        p15, 0, x, c5, c0, 1  /* Instruction Fault Status */
#define RM_ARM_CP15_DFAR(x)        p15, 0, x, c6, c0, 0  /* Data Fault Address*/
#define RM_ARM_CP15_IFAR(x)        p15, 0, x, c6, c0, 2  /* Data Fault Address*/

#define RM_ARM_CP15_NOP(x)         p15, 0, x, c7, c0, 4
/* Va to Pa translation */
#define RM_ARM_CP15_PAR(x)         p15, 0, x, c7, c4, 0
#define RM_ARM_CP15_V2PCWPR(x)     p15, 0, x, c7, c8, 0
#define RM_ARM_CP15_V2PCWPW(x)     p15, 0, x, c7, c8, 1
#define RM_ARM_CP15_V2PCWUR(x)     p15, 0, x, c7, c8, 2
#define RM_ARM_CP15_V2PCWUW(x)     p15, 0, x, c7, c8, 3

/* Caches maintenance */
#define RM_ARM_CP15_ICIALLU(x)     p15, 0, x, c7, c5, 0
#define RM_ARM_CP15_ISB(x)         p15, 0, x, c7, c5, 4
#define RM_ARM_CP15_DSB(x)         p15, 0, x, c7, c10, 4
#define RM_ARM_CP15_DMB(x)         p15, 0, x, c7, c10, 5

/* TLB maintenance */
#define RM_ARM_CP15_TLBIALL(x)     p15, 0, x, c8, c7, 0

/* Performance monitoring */
#define	RM_ARM_CP15_PMCR(x)         p15, 0, x, c9, c12, 0
#define	RM_ARM_CP15_PMCNTENSET(x)   p15, 0, x, c9, c12, 1
#define RM_ARM_CP15_PMCNTENCLR(x)   p15, 0, x, c9, c12, 2
#define RM_ARM_CP15_PMOVSR(x)       p15, 0, x, c9, c12, 3 /* Overflow Flag status */
#define RM_ARM_CP15_PMSWINC(x)      p15, 0, x, c9, c12, 4 /* Software increment */
#define RM_ARM_CP15_PMSELR(x)       p15, 0, x, c9, c12, 5 /* Event counter selection */
#define RM_ARM_CP15_PMCCNTR(x)      p15, 0, x, c9, c13, 0 /* Cycle counter count */
#define RM_ARM_CP15_PMXEVTYPER(x)   p15, 0, x, c9, c13, 1 /* Event Type Select */
#define RM_ARM_CP15_PMXEVCNTR(x)    p15, 0, x, c9, c13, 2 /* Event Count */
#define RM_ARM_CP15_PMUSERENR(x)    p15, 0, x, c9, c14, 0 /* User Enable */ 
#define RM_ARM_CP15_PMINTENSET(x)   p15, 0, x, c9, c14, 1 
#define RM_ARM_CP15_PMINTENCLR(x)   p15, 0, x, c9, c14, 2 

/* L2 preload engine (PLE) */
#define RM_ARM_CP15_PLEPNC(x,y)       p15, 0, x, y, c11
#define RM_ARM_CP15_PLEIDR(x)       p15, 0, x, c11, c0, 0
#define RM_ARM_CP15_PLEASR(x)       p15, 0, x, c11, c0, 2
#define RM_ARM_CP15_PLEPCR(x)       p15, 0, x, c11, c1, 1

/* Security extensions */
#define RM_ARM_CP15_VBAR(x)         p15, 0, x, c12, c0, 0 /* Vector Base Address */
#define RM_ARM_CP15_MVBAR(x)        p15, 0, x, c12, c0, 1 /* Monitor Vector Base Address */

/* Process, context, thread id */
#define RM_ARM_CP15_CONTEXTIDR(x)   p15, 0, x, c13, c0, 1 /* aka ASID */
#define RM_ARM_CP15_TPIDRURO(x)     p15, 0, x, c13, c0, 3 /* user read-only thread-id */
#define RM_ARM_CP15_TPIDRPRW(x)     p15, 0, x, c13, c0, 4 /* privileged only thread-id */

/* Cortex-A9 specific */
#define RM_ARM_CP15_CBAR(x)        p15, 4, x, c15, c0, 0 /* Configuration Base Address (SCU_BASE) */


#ifndef __ASSEMBLY__

#define RMmoveToCp15(dest_reg, val) \
do { \
	 __asm__ __volatile__ ("mcr " STR(dest_reg(%0)) " \n" \
		 : : "r" ((RMuint32)(val))); \
} while (0)

#define RMdoublemoveToCp15(dest_reg, valhi,vallo)	\
do { \
	__asm__ __volatile__ ("mcrr " STR(dest_reg(%0,%1)) " \n" \
			       : : "r" ((RMuint32)(valhi)), "r" ((RMuint32)(vallo))); \
} while (0)

#define RMmoveFromCp15(source_reg) \
({ \
	RMuint32 __hidden_rv; \
	__asm__ __volatile__ ("mrc " STR(source_reg(%0)) " \n" \
		: "=r" (__hidden_rv) :); \
	__hidden_rv; \
})

#define RMdoISB()	\
do { \
	RMuint32 temp = 0; \
	__asm__ __volatile__ ("mcr " STR(RM_ARM_CP15_ISB(%0))" \n" \
			      : : "r" ((RMuint32)(temp)) );		\
} while (0)

#define RMdoDSB()	\
do { \
	RMuint32 temp = 0; \
	__asm__ __volatile__ ("mcr " STR(RM_ARM_CP15_DSB(%0))" \n" \
			      : : "r" ((RMuint32)(temp)) );		\
} while (0)

#define RMdoDMB()	\
do { \
	RMuint32 temp = 0; \
	__asm__ __volatile__ ("mcr " STR(RM_ARM_CP15_DMB(%0))" \n" \
			      : : "r" ((RMuint32)(temp)) );		\
} while (0)

#endif /* __ASSEMBLY__ */
#endif /* __RMMACROS_ARM_CP15_H__ */
