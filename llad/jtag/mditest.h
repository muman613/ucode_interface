/*****************************************
 Copyright © 2004-2005
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   mditest.h
  @brief  

  -long description-

  @author Emmanuel Michon
  @date   2005-10-27
*/

#ifndef __MDITEST_H__
#define __MDITEST_H__

#include <mdi.h>
#include <mdimips.h>

int
opendevice(int devnr);

int
closedevice(void);

int
ChkMDIerr(int errno);

MDIHandleT Devhandle;

#endif /* __MDITEST_H__ */
