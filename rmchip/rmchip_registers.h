/*****************************************
 Copyright © 2005, 2006, 2007
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmchip_registers.h
  @brief  

  -long description-

  @author Emmanuel Michon
  @date   2011-05-26
*/

#ifndef __RMCHIP_REGISTERS_H__
#define __RMCHIP_REGISTERS_H__

#include "rmchip.h"

#if (RMCHIP_ID == RMCHIP_ID_SMP8642)
#include "smp8642/rmchip_registers_smp8642.h"
#include "cpu_lram_maps/tango3_4_lram_map.h"
#elif (RMCHIP_ID == RMCHIP_ID_SMP8644)
#include "smp8644/rmchip_registers_smp8644.h"
#include "cpu_lram_maps/tango3_4_lram_map.h"
#elif (RMCHIP_ID == RMCHIP_ID_SMP8646)
#include "smp8646/rmchip_registers_smp8646.h"
#include "cpu_lram_maps/tango3_4_lram_map.h"
#elif (RMCHIP_ID == RMCHIP_ID_SMP8652)
#include "smp8652/rmchip_registers_smp8652.h"
#include "cpu_lram_maps/tango3_4_lram_map.h"
#elif (RMCHIP_ID == RMCHIP_ID_SMP8654)
#include "smp8654/rmchip_registers_smp8654.h"
#include "cpu_lram_maps/tango3_4_lram_map.h"
#elif (RMCHIP_ID == RMCHIP_ID_SMP8656)
#include "smp8656/rmchip_registers_smp8656.h"
#include "cpu_lram_maps/tango3_4_lram_map.h"
#elif (RMCHIP_ID == RMCHIP_ID_SMP8670)
#include "smp8670/rmchip_registers_smp8670.h"
#include "cpu_lram_maps/tango3_4_lram_map.h"
#elif (RMCHIP_ID == RMCHIP_ID_SMP8672)
#include "smp8672/rmchip_registers_smp8672.h"
#include "cpu_lram_maps/tango3_4_lram_map.h"
#elif (RMCHIP_ID == RMCHIP_ID_SMP8672B)
#include "smp8672B/rmchip_registers_smp8672B.h"
#include "cpu_lram_maps/tango3_4_lram_map.h"
#elif (RMCHIP_ID == RMCHIP_ID_SMP8674)
#include "smp8674/rmchip_registers_smp8674.h"
#include "cpu_lram_maps/tango3_4_lram_map.h"
#elif (RMCHIP_ID == RMCHIP_ID_SMP8680)
#include "smp8680/rmchip_registers_smp8680.h"
#include "cpu_lram_maps/tango3_4_lram_map.h"
#elif (RMCHIP_ID == RMCHIP_ID_SMP8682)
#include "smp8682/rmchip_registers_smp8682.h"
#include "cpu_lram_maps/tango3_4_lram_map.h"
#elif (RMCHIP_ID == RMCHIP_ID_SMP868A)
#include "smp868A/rmchip_registers_smp868A.h"
#include "cpu_lram_maps/tango3_4_lram_map.h"
#elif (RMCHIP_ID == RMCHIP_ID_SMP8734)
#include "smp8734/rmchip_registers_smp8734.h"
#include "cpu_lram_maps/tango3_4_lram_map.h"
#elif (RMCHIP_ID == RMCHIP_ID_SMP8756)
#include "smp8756/rmchip_registers_smp8756.h"
#include "cpu_lram_maps/tango3_4_lram_map.h"
#elif (RMCHIP_ID == RMCHIP_ID_SMP8758)
#include "smp8758/rmchip_registers_smp8758.h"
#include "cpu_lram_maps/tango3_4_lram_map.h"
#elif (RMCHIP_ID == RMCHIP_ID_SMP8760)
#include "smp8760/rmchip_registers_smp8760.h"
#include "cpu_lram_maps/tango5_lram_map.h"
#elif (RMCHIP_ID == RMCHIP_ID_SMP8910)
#include "smp8910/rmchip_registers_smp8910.h"
#include "cpu_lram_maps/tango3_4_lram_map.h"
#elif (RMCHIP_ID == RMCHIP_ID_SMP8920)
#include "smp8920/vertical/rmchip_registers_v2_smp8920.h"
#include "cpu_lram_maps/tango3_4_lram_map.h"
#elif (RMCHIP_ID == RMCHIP_ID_DTVSX6B)
#include "dtvsx6b/vertical/rmchip_registers_v2_dtvsx6b.h"
#elif (RMCHIP_ID == RMCHIP_ID_DTVSX7)
#include "dtvsx7/vertical/rmchip_registers_v2_dtvsx7.h"
#elif (RMCHIP_ID == RMCHIP_ID_DTVSX8)
#include "dtvsx8/vertical/rmchip_registers_v2_dtvsx8.h"

#else
#error that RMCHIP_ID not yet handled 
#endif

#endif /* __RMCHIP_REGISTERS_H__ */
