/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmcompilerid.h

  @author Emmanuel Michon
  @date   2002-11-04
*/

#ifndef __RMCOMPILERID_H__
#define __RMCOMPILERID_H__

#if (RMCOMPILERID==RMCOMPILERID_VISUALC)

typedef unsigned int RMnewOperatorSize;
#include "rmvisual.h"

#elif (RMCOMPILERID==RMCOMPILERID_ARMELF_GCC)

typedef unsigned long RMnewOperatorSize;
#include "rmgcc.h"

#else

typedef unsigned int RMnewOperatorSize;
#include "rmgcc.h"

#endif // RMCOMPILERID==...

#endif // __RMCOMPILERID_H__
