/*****************************************
 Copyright © 2005, 2006, 2007
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmmacros_mips_cp0.h
  @brief  

  A bunch of macros mostly related to MIPS CP0 structure

  @author Emmanuel Michon
  @date   2011-07-04
*/

#ifndef __RMMACROS_MIPS_CP0_H__
#define __RMMACROS_MIPS_CP0_H__

#define RM_C0_INDEX        $0
#define RM_C0_RANDOM       $1
#define RM_C0_ENTRYLO0     $2
#define RM_C0_ENTRYLO1     $3
#define RM_C0_CONTEXT      $4
#define RM_C0_PAGEMASK     $5
#define RM_C0_PAGEGRAIN    $5,1
#define RM_C0_WIRED        $6
#define RM_C0_HWRENA       $7
#define RM_C0_BADVADDR     $8
#define RM_C0_COUNT        $9
#define RM_C0_ENTRYHI      $10
#define RM_C0_COMPARE      $11
#define RM_C0_STATUS       $12
#define RM_C0_INTCTL       $12,1
#define RM_C0_SRSCTL       $12,2
#define RM_C0_SRSMAP       $12,3
#define RM_C0_CAUSE        $13
#define RM_C0_EPC          $14
#define RM_C0_PRID         $15
#define RM_C0_EBASE        $15,1
#define RM_C0_CONFIG       $16
#define RM_C0_CONFIG0      $16,0
#define RM_C0_CONFIG1      $16,1
#define RM_C0_CONFIG2      $16,2
#define RM_C0_CONFIG3      $16,3
#define RM_C0_CONFIG7      $16,7
#define RM_C0_LLADDR       $17
#define RM_C0_WATCHLO      $18
#define RM_C0_WATCHLO1     $18,1
#define RM_C0_WATCHLO2     $18,2
#define RM_C0_WATCHLO3     $18,3
#define RM_C0_WATCHHI      $19
#define RM_C0_WATCHHI1     $19,1
#define RM_C0_WATCHHI2     $19,2
#define RM_C0_WATCHHI3     $19,3
#define RM_C0_DEBUG        $23
#define RM_C0_DEPC         $24
#define RM_C0_PERFCNT      $25
#define RM_C0_ERRCTL       $26
#define RM_C0_CACHEERR     $27

/* 4KE */
#define RM_C0_TAGLO  $28   
#define RM_C0_DATALO $28,1 
/* provisioned by 4KE cache setup routine but actually not implemented on 4KE */
#define RM_C0_TAGHI  $29   
#define RM_C0_DATAHI $29,1 

/* 24K */
#define RM_C0_ITAGLO  $28
#define RM_C0_IDATALO $28,1
#define RM_C0_DTAGLO  $28,2
#define RM_C0_DDATALO $28,3

#define RM_C0_IDATAHI $29,1

/* 74K */
#define RM_C0_ITAGHI $29
#define RM_C0_DTAGHI $29,2

#define RM_C0_ERRPC        $30
#define RM_C0_DESAVE       $31

/* L2 (e.g. mostly for 1004K) */
#define RM_C0_L23TAGLO $28,4
#define RM_C0_L23DATALO $28,5

/* this one is provisioned by the l2 cache setup routine but actually absent on 24K, 74K, 1004K L2 access routines */
#define RM_C0_L23TAGHI $29,4

#define RM_C0_L23DATAHI $29,5

/*
  no dollar
 */
#define C0_INDEX        0
#define C0_RANDOM       1
#define C0_ENTRYLO0     2
#define C0_ENTRYLO1     3
#define C0_CONTEXT      4
#define C0_PAGEMASK     5
#define C0_WIRED        6
#define C0_HWRENA       7
#define C0_BADVADDR     8
#define C0_COUNT        9
#define C0_ENTRYHI      10
#define C0_COMPARE      11
#define C0_STATUS       12
#define C0_CAUSE        13
#define C0_EPC          14
#define C0_PRID         15
#define C0_CONFIG       16
#define C0_LLADDR       17
#define C0_WATCHLO      18
#define C0_WATCHHI      19
#define C0_DEBUG        23
#define C0_DEPC         24
#define C0_PERFCNT      25
#define C0_ERRCTL       26
#define C0_CACHEERR     27
#define C0_TAGLO  28   
#define C0_TAGHI  29   
#define C0_ITAGLO  28
#define C0_ITAGHI 29
#define C0_ERRPC        30
#define C0_DESAVE       31

/*
 * Exception Codes
 */
#define RM_EXC_INTR     0
#define RM_EXC_MOD      1
#define RM_EXC_TLBL     2
#define RM_EXC_TLBS     3
#define RM_EXC_ADEL     4
#define RM_EXC_ADES     5
#define RM_EXC_IBE      6
#define RM_EXC_DBE      7
#define RM_EXC_SYS      8
#define RM_EXC_BP       9
#define RM_EXC_RI       10
#define RM_EXC_CPU      11
#define RM_EXC_OVF      12
#define RM_EXC_TRAP     13
#define RM_EXC_RES14    14
#define RM_EXC_FPE      15
#define RM_EXC_IS1      16
#define RM_EXC_IS2      17
#define RM_EXC_C2E      18
#define RM_EXC_RES19    19
#define RM_EXC_RES20    20
#define RM_EXC_RES21    21
#define RM_EXC_MDMX     22
#define RM_EXC_WATCH    23
#define RM_EXC_MCHECK   24
#define RM_EXC_THREAD   25
#define RM_EXC_DSPU     26
#define RM_EXC_RES27    27
#define RM_EXC_RES28    28
#define RM_EXC_RES29    29
#define RM_EXC_RES30    30
#define RM_EXC_RES31    31

#define RM_CR_BD        0x80000000
#define RM_CR_IMASK     0x0000ff00

#define LOG2_RM_SR_IE      0
#define LOG2_RM_SR_EXL     1
#define LOG2_RM_SR_UM      4
#define LOG2_RM_SR_IM0     8
#define LOG2_RM_SR_IM1     9
#define LOG2_RM_SR_IM2     10
#define LOG2_RM_SR_IM3     11
#define LOG2_RM_SR_IM4     12
#define LOG2_RM_SR_IM5     13
#define LOG2_RM_SR_IM6     14
#define LOG2_RM_SR_IM7     15
#define LOG2_RM_SR_BEV     22
#define LOG2_RM_SR_MX      24
#define LOG2_RM_SR_FR      26
#define LOG2_RM_SR_CU0     28
#define LOG2_RM_SR_CU1     29 /* e.g. FPU */

#define RM_SR_IE           (1<<LOG2_RM_SR_IE)      /* interrupt enable */
#define RM_SR_EXL          (1<<LOG2_RM_SR_EXL)
#define RM_SR_UM           (1<<LOG2_RM_SR_UM) 
#define RM_SR_IM0          (1<<LOG2_RM_SR_IM0)
#define RM_SR_IM1          (1<<LOG2_RM_SR_IM1)
#define RM_SR_IM2          (1<<LOG2_RM_SR_IM2)
#define RM_SR_IM3          (1<<LOG2_RM_SR_IM3)
#define RM_SR_IM4          (1<<LOG2_RM_SR_IM4)
#define RM_SR_IM5          (1<<LOG2_RM_SR_IM5)
#define RM_SR_IM6          (1<<LOG2_RM_SR_IM6)
#define RM_SR_IM7          (1<<LOG2_RM_SR_IM7)
#define RM_SR_BEV          (1<<LOG2_RM_SR_BEV)
#define RM_SR_MX          (1<<LOG2_RM_SR_MX)
#define RM_SR_FR          (1<<LOG2_RM_SR_FR)
#define RM_SR_CU0          (1<<LOG2_RM_SR_CU0)
#define RM_SR_CU1          (1<<LOG2_RM_SR_CU1)

#define RM_CFG_C_UNCACHED             2
#define RM_CFG_C_WBACK                3
#define RM_CFG_C_WBACK_COH_EX         4	/* Coherent, read misses request Exclusive */
#define RM_CFG_C_WBACK_COH_SH         5	/* Coherent, read misses request Shared */
#define RM_CFG_C_MASK                 7 

#define RM_TLB_PFNMASK       0x3fffffc0
#define RM_TLB_PFNSHIFT      6
#define RM_TLB_FLAGS         0x0000003f
#define RM_TLB_CMASK         0x00000038
#define RM_TLB_CSHIFT        3

#define RM_TLBHI_VPN2MASK    0xffffe000
#define RM_TLBHI_VPN2SHIFT   13
#define RM_TLBHI_VPNMASK     0xfffff000
#define RM_TLBHI_VPNSHIFT    12
#define RM_TLBHI_PIDMASK     0x000000ff
#define RM_TLBHI_PIDSHIFT    0x00000000

#define RM_TLBHIVPN(hi)      ((hi)>>RM_TLBHI_VPNSHIFT)
#define RM_TLBHIID(hi)       ((hi)&RM_TLBHI_PIDMASK)
#define RM_TLBLOPN(lo)       ((lo)>>RM_TLB_PFNSHIFT)
#define RM_TLBLOFLAGS(lo)    ((lo)&RM_TLB_FLAGS)

#define RM_TLB_G             0x00000001
#define RM_TLB_V             0x00000002
#define RM_TLB_D             0x00000004
#define RM_TLB_UNCACHED      (RM_CFG_C_UNCACHED<<RM_TLB_CSHIFT)
#define RM_TLB_WBACK         (RM_CFG_C_WBACK<<RM_TLB_CSHIFT)
#define RM_TLB_WBACK_COH_EX  (RM_CFG_C_WBACK_COH_EX<<RM_TLB_CSHIFT)
#define RM_TLB_WBACK_COH_SH  (RM_CFG_C_WBACK_COH_SH<<RM_TLB_CSHIFT)

#define WATCH_G (1<<14)
#define ERRCTL_WST	(1<<29) /* way select / tag array */
#define ERRCTL_SPR	(1<<28) /* scratchpad ram select */

/*
  Index_* operate on a cache index (global operation on the cache or explicit feed)
  Hit_* operate on a virtual address.

  Some features like Writeback_D do not exist in the first flavour. For instance you can't
  writeback the whole d-cache without doing _wi (RM_Index_Writeback_Inv_D).
 */

#define RM_Index_Invalidate_I               0x0         /* 0       0 */
#define RM_Index_Writeback_Inv_D            0x1         /* 0       1 */
#define RM_Index_Writeback_Inv_S            0x3         /* 0       3 */

#define RM_Index_Load_Tag_I                 0x4         /* 1       0 */
#define RM_Index_Load_Tag_D                 0x5         /* 1       1 */
#define RM_Index_Load_Tag_S                 0x7

#define RM_Index_Store_Tag_I                0x8         /* 2       0 */
#define RM_Index_Store_Tag_D                0x9         /* 2       1 */
#define RM_Index_Store_Tag_S                0xb

#define RM_Index_Store_Data_I               0xc

#define RM_Hit_Invalidate_I                 0x10        /* 4       0 */
#define RM_Hit_Invalidate_D                 0x11        /* 4       1 */
#define RM_Hit_Invalidate_S                 0x13        /* 4       3 */

#define RM_Fill_I                           0x14        /* 5       0 */
#define RM_Hit_Writeback_Inv_D              0x15        /* 5       1 */
#define RM_Hit_Writeback_Inv_S              0x17        /* 5       3 */

#define RM_Hit_Writeback_D                  0x19        /* 6       1 */
#define RM_Hit_Writeback_S                  0x1b        /* 6       3 */

#define RM_Fetch_Lock_I                     0x1c        /* 7       0 */
#define RM_Fetch_Lock_D                     0x1d        /* 7       1 */
#define RM_Fetch_Lock_S                     0x1f        /* 7       3 */

/*
   Coprocessor2 registers
WARNING: this is implementation specific and subject to change from one
version to another. There is currently a single version... Don't forget
to update those definitions with #ifdefs the day we change registers
mapping... Subject to change!

There is currently two registers set:
   - the first set (set 0) is reserved for remapped registers
       the mapping is currently fixed with each register from
   the first set pointing to the same register in the second
   coprocessor2 registers set.

   - the second set (set 1) contains the following registers map:
       regs 0...15 = inflate registers area
       regs 16..23 = png registers area
       regs 24..27 = backup/restore registers area
       regs 28..31 = backup management registers zone
*/

/*
   Coprocessor2 registers: implementation specific
no dollar
 */

/* inflate registers: set 0,1 */
#define C2_INFLATE_CMDSTAT       0
#define C2_INFLATE_LVLCFG        1
#define C2_INFLATE_SYMCFG        2
#define C2_INFLATE_IN_CTL        3
#define C2_INFLATE_IN_DATA       4
#define C2_INFLATE_OUT_STATUS    5
#define C2_INFLATE_OUT_LITERALS  6
#define C2_INFLATE_OUT_DISTANCES 7
/* png registers: set 0,1 */
#define C2_PNG_CONFIG            16
#define C2_PNG_IN_DATA           17
#define C2_PNG_OUT_DATA          18
#define C2_PNG_PREV_DATA_UP      19
#define C2_PNG_PREV_DATA_UP_LEFT 20
#define C2_PNG_PREV_DATA_LEFT    21
/* backup registers: set 0,1 */
#define C2_BACKUP_ADDRESS        24
#define C2_BACKUP_DATA           25
/* coprocessor2 registers: set 0,1 */
#define C2_IMPLEMENTATION        28

/* TODO: defines masks and bits ops */

/*
   Coprocessor2 registers: implementation specific
dollar declarations
we don't specifiy any registers set here since we wanna
be able to access those registers with swc2/lwc2 instructions
as well. Thus we only use the registers included in the first
registers set, that're currently mapped onto the second register
set. This is subject to change!
 */

/* inflate registers */
#define RM_C2_INFLATE_CMDSTAT       $0
#define RM_C2_INFLATE_LVLCFG        $1
#define RM_C2_INFLATE_SYMCFG        $2
#define RM_C2_INFLATE_IN_CTL        $3
#define RM_C2_INFLATE_IN_DATA       $4
#define RM_C2_INFLATE_OUT_STATUS    $5
#define RM_C2_INFLATE_OUT_LITERALS  $6
#define RM_C2_INFLATE_OUT_DISTANCES $7
/* png registers */
#define RM_C2_PNG_CONFIG            $16
#define RM_C2_PNG_IN_DATA           $17
#define RM_C2_PNG_OUT_DATA          $18
#define RM_C2_PNG_PREV_DATA_UP      $19
#define RM_C2_PNG_PREV_DATA_UP_LEFT $20
#define RM_C2_PNG_PREV_DATA_LEFT    $21
/* backup registers */
#define RM_C2_BACKUP_ADDRESS        $24
#define RM_C2_BACKUP_DATA           $25
/* coprocessor2 registers */
#define RM_C2_IMPLEMENTATION        $28

#define RM_HWR_CPUNUM 0
#define RM_HWR_SYNCI  1
#define RM_HWR_COUNT  2  /* CP0 Count register */
#define RM_HWR_CCRES  3

#endif /* __RMMACROS_MIPS_CP0_H__ */
