/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmplatform.h
  @brief  

  Supported platforms: to avoid confusion, the platform name should
  not embed the name of its processor (keep it for RMARCHID_...)

  So far here is the list and the default is the first:
  RMPLATFORMID_PCLINUX 
  RMPLATFORMID_JASPERMAMBO
  RMPLATFORMID_SUN
  RMPLATFORMID_WALNUT
  RMPLATFORMID_WIN9X
  
  Porting guide: create a new RMPLATFORMID_... for yours,
  if not already present, a new RMCOMPILERID_...,
  if not already present, a new RMARCHID_...
  Then edit as well rmcompilerid.h and rmnonasciitype.h to reflect
  your platform pecularities.

  @author Emmanuel Michon
  @date   2003-04-14
*/

#ifndef __RMPLATFORM_H__
#define __RMPLATFORM_H__

/* platform ids **************************************************
*****************************************************************/

#define RMPLATFORMID_PCLINUX       1000
#define RMPLATFORMID_JASPERMAMBO   2000
#define RMPLATFORMID_TANGO2        2001
/* tango3 is just the same as tango2, platform-wise */
#define RMPLATFORMID_TANGO3        2001
#define RMPLATFORMID_TANGO3_CE     2002
#define RMPLATFORMID_TANGO2_CE     2003
#define RMPLATFORMID_SUN           3000
#define RMPLATFORMID_WALNUT        4000
#define RMPLATFORMID_iPUMP         4001
#define RMPLATFORMID_EVOLUTION     4002
#define RMPLATFORMID_NEURON        4003
#define RMPLATFORMID_WIN9X         5000
#define RMPLATFORMID_WINNT         6000
#define RMPLATFORMID_RBTX          7000
#define RMPLATFORMID_MARBO         7001
#define RMPLATFORMID_COUGAR        7002
#define RMPLATFORMID_PMCS          7003
#define RMPLATFORMID_VR1           7004
#define RMPLATFORMID_JUBILO        7005
#define RMPLATFORMID_PXA           9000
#define RMPLATFORMID_IXDP425       9001
#define RMPLATFORMID_FEROCEON      9002
#define RMPLATFORMID_GEODELINUX    0xA000
#define RMPLATFORMID_CENTAUR       0xB000
#define RMPLATFORMID_AOE6_SH4      0xC000
#define RMPLATFORMID_SEV           0xD000

/* compiler ids **************************************************
*****************************************************************/

#define RMCOMPILERID_GCC        1000
#define RMCOMPILERID_ARMELF_GCC 2000
/* used for both sde-gcc and mipsel-gcc, as well as native `gcc' on linux/mips */
#define RMCOMPILERID_MIPSEL_GCC 3000
/* `last gcc' is when you want to toggle on all gcc's at once, or all visual's at once using <= */
#define RMCOMPILERID_LAST_GCC   8000

#define RMCOMPILERID_VISUALC    9000
#define RMCOMPILERID_CEPB      10000


/* arch ids ******************************************************
*****************************************************************/
 
#define RMARCHID_X86    	1000
#define RMARCHID_ARM    	2000
#define RMARCHID_SPARC  	3000
#define RMARCHID_PPC405 	4000
#define RMARCHID_MIPS		5000
#define RMARCHID_SUPERH		6000
#define RMARCHID_ARM_XSCALE	7000 /* StrongARM based - ARM V5TE */

/* alignments ****************************************************
*****************************************************************/

#ifndef __ASSEMBLY__
typedef enum {
	RM_ALIGNMENTNONE  =0, /* e.g. one byte: processor can access anywhere (pentium) */
	RM_ALIGNMENT2BYTES=1,
	RM_ALIGNMENT4BYTES=2,
	RM_ALIGNMENT8BYTES=3, /* sparc4 requires this when accessing 64bit integers */
	RM_ALIGNMENTMAX   =RM_ALIGNMENT8BYTES,
} RMalignment;
#endif /* __ASSEMBLY__ */

/* endianness ****************************************************
*****************************************************************/

#define RMLITTLEENDIAN 4321
#define RMBIGENDIAN 1234

/*****************************************************************
*****************************************************************/

#ifndef RMPLATFORM
/* #warning fallback to RMPLATFORMID_PCLINUX, but please define RMPLATFORM properly! */
#define RMPLATFORM RMPLATFORMID_PCLINUX
#endif /* RMPLATFORM */

#if   (RMPLATFORM==RMPLATFORMID_PCLINUX)
/* #warning you are in RMPLATFORMID_PCLINUX */
#define RMCOMPILERID RMCOMPILERID_GCC
#define RMARCHID     RMARCHID_X86
/* starting from RedHat9.0, semaphores cannot be located at odd addresses ;-( */
#define RM_MACHINEALIGNMENT RM_ALIGNMENT4BYTES
#define RMENDIANNESS RMLITTLEENDIAN

#elif (RMPLATFORM==RMPLATFORMID_JASPERMAMBO)
/* #warning you are in RMPLATFORMID_JASPERMAMBO */
#define RMCOMPILERID RMCOMPILERID_ARMELF_GCC
#define RMARCHID     RMARCHID_ARM
#define RM_MACHINEALIGNMENT RM_ALIGNMENT4BYTES
#define RMENDIANNESS RMLITTLEENDIAN

#elif (RMPLATFORM==RMPLATFORMID_TANGO2)
/* #warning you are in RMPLATFORMID_TANGO2 */
#define RMCOMPILERID RMCOMPILERID_MIPSEL_GCC
#define RMARCHID     RMARCHID_MIPS
#define RM_MACHINEALIGNMENT RM_ALIGNMENT4BYTES
#define RMENDIANNESS RMLITTLEENDIAN

#elif (RMPLATFORM==RMPLATFORMID_SUN)
/* #warning you are in RMPLATFORMID_SUN */
#define RMCOMPILERID RMCOMPILERID_GCC
#define RMARCHID     RMARCHID_SPARC
/* recent sparc may be less greedy on alignment constraints */
#define RM_MACHINEALIGNMENT RM_ALIGNMENT8BYTES
#define RMENDIANNESS RMBIGENDIAN

#elif (RMPLATFORM==RMPLATFORMID_WALNUT)
/* #warning you are in RMPLATFORMID_WALNUT */
#define RMCOMPILERID RMCOMPILERID_GCC
#define RMARCHID     RMARCHID_PPC405
#define RM_MACHINEALIGNMENT RM_ALIGNMENT4BYTES
#define RMENDIANNESS RMBIGENDIAN

#elif (RMPLATFORM==RMPLATFORMID_iPUMP)
/* #warning you are in RMPLATFORMID_iPUMP */
#define RMCOMPILERID RMCOMPILERID_GCC
#define RMARCHID     RMARCHID_PPC405
#define RM_MACHINEALIGNMENT RM_ALIGNMENT4BYTES
#define RMENDIANNESS RMBIGENDIAN

#elif (RMPLATFORM==RMPLATFORMID_EVOLUTION)
/* #warning you are in RMPLATFORMID_EVOLUTION */
#define RMCOMPILERID RMCOMPILERID_GCC
#define RMARCHID     RMARCHID_PPC405
#define RM_MACHINEALIGNMENT RM_ALIGNMENT4BYTES
#define RMENDIANNESS RMBIGENDIAN

#elif (RMPLATFORM==RMPLATFORMID_NEURON)
/* #warning you are in RMPLATFORMID_NEURON */
#define RMCOMPILERID RMCOMPILERID_GCC
#define RMARCHID     RMARCHID_PPC405
#define RM_MACHINEALIGNMENT RM_ALIGNMENT4BYTES
#define RMENDIANNESS RMBIGENDIAN

#elif (RMPLATFORM==RMPLATFORMID_CENTAUR)
/* #warning you are in RMPLATFORMID_CENTAUR */
#define RMCOMPILERID RMCOMPILERID_GCC
#define RMARCHID     RMARCHID_ARM
#define RM_MACHINEALIGNMENT RM_ALIGNMENT4BYTES
#define RMENDIANNESS RMLITTLEENDIAN
#define RMPCI_MEM_BASE	KS8695P_PCI_MEM_BASE
#define MAX_BOARDS	1

#elif (RMPLATFORM==RMPLATFORMID_PXA)
/* #warning you are in RMPLATFORMID_PXA */
#define RMCOMPILERID RMCOMPILERID_GCC
#define RMARCHID     RMARCHID_ARM
#define RM_MACHINEALIGNMENT RM_ALIGNMENT4BYTES
#define RMENDIANNESS RMLITTLEENDIAN
#define	RMSDRAM_START_OFFSET	0xA0000000

#elif (RMPLATFORM==RMPLATFORMID_IXDP425)
/* #warning you are in RMPLATFORM_IXDP425 */
#define RMCOMPILERID RMCOMPILERID_GCC
#define RMARCHID     RMARCHID_ARM_XSCALE
#define RM_MACHINEALIGNMENT RM_ALIGNMENT4BYTES
#define RMENDIANNESS RMBIGENDIAN

#elif (RMPLATFORM==RMPLATFORMID_FEROCEON)
#warning you are in RMPLATFORM_FEROCEON
#define RMCOMPILERID RMCOMPILERID_GCC
#define RMARCHID     RMARCHID_ARM
#define RM_MACHINEALIGNMENT RM_ALIGNMENT4BYTES
#define RMENDIANNESS RMLITTLEIGENDIAN

#elif (RMPLATFORM==RMPLATFORMID_WIN9X)
/* #warning you are in RMPLATFORMID_WIN9X */
#define RMCOMPILERID RMCOMPILERID_VISUALC
#define RMARCHID     RMARCHID_X86
#define RM_MACHINEALIGNMENT RM_ALIGNMENTNONE
#define RMENDIANNESS RMLITTLEENDIAN

#elif (RMPLATFORM==RMPLATFORMID_WINNT)
/* #warning you are in RMPLATFORMID_WINNT */
#define RMCOMPILERID RMCOMPILERID_VISUALC
#define RMARCHID     RMARCHID_X86
#define RM_MACHINEALIGNMENT RM_ALIGNMENTNONE
#define RMENDIANNESS RMLITTLEENDIAN

#elif (RMPLATFORM==RMPLATFORMID_RBTX)
/* #warning you are in RMPLATFORMID_RBTX */
#define RMCOMPILERID RMCOMPILERID_GCC
#define RMARCHID     RMARCHID_MIPS
#define RM_MACHINEALIGNMENT RM_ALIGNMENT4BYTES
#define RMENDIANNESS RMLITTLEENDIAN

#elif (RMPLATFORM==RMPLATFORMID_VR1)
/* #warning you are in RMPLATFORMID_VR1 */
#define RMCOMPILERID RMCOMPILERID_GCC
#define RMARCHID     RMARCHID_MIPS
#define RM_MACHINEALIGNMENT RM_ALIGNMENT4BYTES
#define RMENDIANNESS RMLITTLEENDIAN

#elif (RMPLATFORM==RMPLATFORMID_JUBILO)
/* #warning you are in RMPLATFORMID_JUBILO */
#define RMCOMPILERID RMCOMPILERID_GCC
#define RMARCHID     RMARCHID_MIPS
#define RM_MACHINEALIGNMENT RM_ALIGNMENT4BYTES
#define RMENDIANNESS RMLITTLEENDIAN

#elif (RMPLATFORM==RMPLATFORMID_MARBO)
/* #warning you are in RMPLATFORMID_MARBO */
#define RMCOMPILERID RMCOMPILERID_GCC
#define RMARCHID     RMARCHID_MIPS
#define RM_MACHINEALIGNMENT RM_ALIGNMENT4BYTES
#define RMENDIANNESS RMLITTLEENDIAN

#elif (RMPLATFORM==RMPLATFORMID_COUGAR)
/* #warning you are in RMPLATFORMID_COUGAR */
#define RMCOMPILERID RMCOMPILERID_GCC
#define RMARCHID         RMARCHID_MIPS
#define RM_MACHINEALIGNMENT RM_ALIGNMENT4BYTES
#define RMENDIANNESS RMBIGENDIAN

#elif (RMPLATFORM==RMPLATFORMID_AOE6_SH4)
/* #warning you are in RMPLATFORMID_AOE6_SH4 */
#define RMCOMPILERID RMCOMPILERID_GCC
#define RMARCHID         RMARCHID_SUPERH
#define RM_MACHINEALIGNMENT RM_ALIGNMENT4BYTES
#define RMENDIANNESS RMLITTLEENDIAN

#elif   (RMPLATFORM==RMPLATFORMID_GEODELINUX)
/* #warning you are in RMPLATFORMID_GEODELINUX */
#define RMCOMPILERID RMCOMPILERID_GCC
#define RMARCHID     RMARCHID_X86
#define RM_MACHINEALIGNMENT RM_ALIGNMENTNONE
#define RMENDIANNESS RMLITTLEENDIAN

#elif (RMPLATFORM==RMPLATFORMID_SEV)
/* #warning you are in RMPLATFORMID_SEV */
#define RMCOMPILERID RMCOMPILERID_GCC
#define RMARCHID     RMARCHID_MIPS
#define RM_MACHINEALIGNMENT RM_ALIGNMENT4BYTES
#define RMENDIANNESS RMLITTLEENDIAN

#elif   (RMPLATFORM==RMPLATFORMID_PMCS)
/* #warning you are in RMPLATFORMID_PMCS */
#define RMCOMPILERID RMCOMPILERID_GCC
#define RMARCHID     RMARCHID_MIPS
#define RM_MACHINEALIGNMENT RM_ALIGNMENT4BYTES
#define RMENDIANNESS RMLITTLEENDIAN

#elif   (RMPLATFORM==RMPLATFORMID_TANGO3_CE)
#define RMCOMPILERID RMCOMPILERID_VISUALC
#define RMARCHID     RMARCHID_MIPS
#define RM_MACHINEALIGNMENT RM_ALIGNMENT4BYTES
#define RMENDIANNESS RMLITTLEENDIAN
#pragma warning(disable:4244)
#pragma warning(disable:4146)
#pragma warning(disable:4333)

#define EMHWLIB_NO_MM			1
#define EMHWLIB_NO_PngDecoder   1
#define EMHWLIB_NO_AudioWatermark 1

#elif   (RMPLATFORM==RMPLATFORMID_TANGO2_CE)
#define RMCOMPILERID RMCOMPILERID_VISUALC
#define RMARCHID     RMARCHID_MIPS
#define RM_MACHINEALIGNMENT RM_ALIGNMENT4BYTES
#define RMENDIANNESS RMLITTLEENDIAN
#pragma warning(disable:4244)
#pragma warning(disable:4146)

#define EMHWLIB_NO_MM			1
#define EMHWLIB_NO_PngDecoder	1

#else 
#error RMPLATFORM defined but not recognized

#endif 

#endif /* __RMPLATFORM_H__ */
