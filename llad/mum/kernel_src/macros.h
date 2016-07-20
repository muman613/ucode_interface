/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   macros.h
  @brief  

  long description

  @author Emmanuel Michon
  @date   2002-11-13
*/

#ifndef __MACROS_H__
#define __MACROS_H__

#define MAXAREABUFFERCOUNT (1024)

#define MUM_DMASIZE (128*1024)

// since the usage mask is an unsigned long you cannot exceed 32 below:
#define MAXDMAPOOL   32

/* buffer size for large data transfer transition into kernel */
#define GBUS_BUF_SIZE (32 * 1024)

/* maximum numbers of processes using the same mum */
#define MAX_OPENERS 8

extern int logboard;
#define PR_RMDBGLOG(x)					\
do {							\
	logboard=pR-Rtable; 				\
	RMDBGLOG(x);					\
	logboard=-1; 					\
} while (0)



#endif // __MACROS_H__
