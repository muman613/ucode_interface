/*
 * emhwlib_hal/pll/include/pll_hal_chipspecific.h
 *
 * Copyright (c) 2011 Sigma Designs, Inc. 
 * All Rights Reserved. Proprietary and Confidential.
 *
 */
 
/**
  @file emhwlib_hal/pll/include/pll_hal_chipspecific.h
  @brief PLL and CD allocation for specific chips
  
  @author Christian Wolff
*/

#ifndef __EMHWLIBHAL_PLL_CHIPSPECIFIC_H__
#define __EMHWLIBHAL_PLL_CHIPSPECIFIC_H__

#include "rmdef/rmdef.h"
#include "rmchip/rmchip.h"
#include "pll_hal_types.h"





/*************************/
/*      TANGO 3 /4       */
/*************************/

/* Tango3: SysClk from PLL1, CDClk from PLL2 */
#define PLL_CD_PLL PLLGen_pll_2
#define PLL_CD_PLLOUT PLLOut_0
#define PLL_CD_FREQ 405000000





/*************************/
/*        COMMON         */
/*************************/

/* Selection of System clock PLL */
#define PLL_SYSTEM PLLGen_pll_3

/* Selection of Audio Engine clock source */
#define PLL_AUDIO PLLGen_cd_0  /* use clean divider on Tango and up */

/* Selection of Video clock sources */
#define PLL_VIDEO_PRI PLLGen_cd_8  /* use CD 8 for primary/digital route */
#define PLL_VIDEO_SEC PLLGen_cd_9  /* use CD 9 for secondary route */
#define PLL_VIDEO_TER PLLGen_cd_10  /* use CD 10 for third route */
#define PLL_VIDEO_OUT PLLOut_0 /* Post divider for video clocks: direct out */

/* Selection of Audio / Video clock sources for VCXO */
#define PLL_AUDIO_ENGINE_0  PLLGen_cd_0
#define PLL_AUDIO_ENGINE_1  PLLGen_cd_1
#define PLL_VIDEO_DIGITAL   PLLGen_cd_8
#define PLL_VIDEO_ANALOG    PLLGen_cd_9
#define PLL_VIDEO_COMPONENT PLLGen_cd_10





#endif /* __EMHWLIBHAL_PLL_CHIPSPECIFIC_H__ */

