/*****************************************
 Copyright (c) 2004-2010
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmchip.h
  @brief

  @author Sebastian Frias
  @date   2010-08-19
*/

#ifndef __RMCHIP_H__
#define __RMCHIP_H__

#include "rmchip_id.h"

#if (RMCHIP_ID==RMCHIP_ID_SMP8656)&&(RMCHIP_REVISION==4)
#include "rmchip_smp8656r4.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8642)&&(RMCHIP_REVISION==3)
#include "rmchip_smp8642r3.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8644)&&(RMCHIP_REVISION==3)
#include "rmchip_smp8644r3.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8646)&&(RMCHIP_REVISION==3)
#include "rmchip_smp8646r3.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8652)&&(RMCHIP_REVISION==3)
#include "rmchip_smp8652r3.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8654)&&(RMCHIP_REVISION==3)
#include "rmchip_smp8654r3.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8656)&&(RMCHIP_REVISION==1)
#include "rmchip_smp8656r1.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8656)&&(RMCHIP_REVISION==5)
#include "rmchip_smp8656r5.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8656)&&(RMCHIP_REVISION==6)
#include "rmchip_smp8656r6.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8670)&&(RMCHIP_REVISION==3)
#include "rmchip_smp8670r3.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8672)&&(RMCHIP_REVISION==1)
#include "rmchip_smp8672r1.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8672)&&(RMCHIP_REVISION==2)
#include "rmchip_smp8672r2.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8672B)&&(RMCHIP_REVISION==1)
#include "rmchip_smp8672Br1.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8674)&&(RMCHIP_REVISION==1)
#include "rmchip_smp8674r1.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8674)&&(RMCHIP_REVISION==3)
#include "rmchip_smp8674r3.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8680)&&(RMCHIP_REVISION==1)
#include "rmchip_smp8680r1.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8682)&&(RMCHIP_REVISION==1)
#include "rmchip_smp8682r1.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP868A)&&(RMCHIP_REVISION==1)
#include "rmchip_smp868Ar1.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8734)&&(RMCHIP_REVISION==1)
#include "rmchip_smp8734r1.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8756)&&(RMCHIP_REVISION==1)
#include "rmchip_smp8756r1.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8758)&&(RMCHIP_REVISION==1)
#include "rmchip_smp8758r1.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8760)&&(RMCHIP_REVISION==1)
#include "rmchip_smp8760r1.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8910)&&(RMCHIP_REVISION==2)
#include "rmchip_smp8910r2.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8910)&&(RMCHIP_REVISION==3)
#include "rmchip_smp8910r3.h"
#elif (RMCHIP_ID==RMCHIP_ID_SMP8920)&&(RMCHIP_REVISION==1)
#include "rmchip_smp8920r1.h"
#elif (RMCHIP_ID==RMCHIP_ID_DTVSX6B)&&(RMCHIP_REVISION==1)
#include "rmchip_dtvsx6br1.h"
#elif (RMCHIP_ID==RMCHIP_ID_DTVSX7 )&&(RMCHIP_REVISION==1)
#include "rmchip_dtvsx7r1.h"
#elif (RMCHIP_ID==RMCHIP_ID_DTVSX8 )&&(RMCHIP_REVISION==1)
#include "rmchip_dtvsx8r1.h"
#else
#error that RMCHIP_ID not yet handled 
#endif

#endif /* __RMCHIP_H__ */
