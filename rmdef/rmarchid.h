/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmarchid.h
  @brief  

  long description

  @author Emmanuel Michon
  @date   2003-04-14
*/

#ifndef __RMARCHID_H__
#define __RMARCHID_H__

#if (RMARCHID==RMARCHID_X86)

#if (RMCOMPILERID==RMCOMPILERID_VISUALC)
// we have to use intel syntax
#define STACKREVIEW do { _asm int 3 } while (0)
#else
// we have to use GNU as syntax
#define STACKREVIEW do { __asm__ __volatile__("int $3"); } while (0)
#endif

#elif (RMARCHID==RMARCHID_ARM) || (RMARCHID==RMARCHID_ARM_XSCALE)

// assume GCC syntax by default
#define STACKREVIEW 					\
do {							\
	/* undefined instruction */			\
	__asm__ __volatile__(".word 0xe7ffdefe"); 	\
} while (0)

#else

#define STACKREVIEW 					\
do {							\
	void *toto = (void *)0xaa3aa311;		\
	/* this causes segfault (unaligned store) on purpose. */		\
	*((int *) toto) = 0xbb4bb422;   		\
} while (0)

#endif

#endif // __RMARCHID_H__
