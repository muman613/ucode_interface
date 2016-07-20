/*
Copyright (C) 2003  Sigma Designs, Inc.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __KLLAD_COMMON_H__
#define __KLLAD_COMMON_H__

#include "gbus.h"

/* the main chip ids */



//#define RMCHIP_ID_SMP8910 (8910)

//required by kllad.c
//(taken from rmchip/registers)
#define REG_BASE_cpu_block 0x00060000 /* width RMuint32 */
#define CPU_remap 0xf000
#define CPU_remap1 0xf004
#define CPU_remap2 0xf008
#define CPU_remap_address 0x1fc00000 /* width RMuint32 */
#define CPU_remap1_address 0 /* width RMuint32 */
#define CPU_remap2_address 0x04000000 /* width RMuint32 */
#define CPU_remap3_address 0x08000000 /* width RMuint32 */
#define CPU_remap4_address 0x0c000000 /* width RMuint32 */
#define CPU_irq_softset 0xe010 /* width RMuint32 */
#define CPU_irq_softclr 0xe014 /* width RMuint32 */

//(taken from rmchip/lram_t3)
#define LR_CHANNEL_INDEX         0x000019a4

#endif //__KLLAD_COMMON_H__
