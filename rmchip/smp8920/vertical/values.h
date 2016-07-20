/*****************************************
 Copyright © 2005, 2006, 2007
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   values.h
  @brief  

  -long description-

  @author Emmanuel Michon
  @date   2012-03-06
*/

#ifndef __VALUES_H__
#define __VALUES_H__

// hack document which field in which struct
#define LIN 1
#define DBLE 2
#define RECT 3
#define IRECT 4
#define DRECT 5
#define VERT 6
#define DVERT 7
#define VERTN 8

// hack document which field in which struct
#define CPU_remapboot_address 0x1fc00000
#define CPU_remap04_address   0x04000000
#define CPU_remap08_address   0x08000000
#define CPU_remap0c_address   0x0c000000
#define CPU_remap10_address   0x10000000
#define CPU_remap14_address   0x14000000
#define CPU_remap18_address   0x18000000
#define CPU_remap1c_address   0x1c000000
#define CPU_remap038_address  0x03800000
#define CPU_remap03c_address  0x03c00000

// hack document which field in which struct
#define XPU_sbox_input_MBUS_r0          1
#define XPU_sbox_input_DMA_read         2
#define XPU_sbox_input_ciphers          3
#define XPU_sbox_input_serial_flash     4
#define XPU_sbox_input_dev_zero         14
#define XPU_sbox_input_disconnect       15

// union sp_write_modeReg resp
#define MODE_LE 0
#define MODE_BE 1

#endif /* __VALUES_H__ */
