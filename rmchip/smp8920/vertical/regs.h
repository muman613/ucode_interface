/*****************************************
 Copyright © 2005, 2006, 2007
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   regs.h
  @brief  

  -long description-

  @author Emmanuel Michon
  @date   2011-03-09
*/

#ifndef __REGS_H__
#define __REGS_H__

#ifndef F32
#ifdef __mips__
#define F32 __attribute__((nomips16))
#else
#define F32
#endif
#endif

/* MRK works in mips16 !!! */
#define MRK(x) do { __asm__ __volatile__("addu $v0, " #x "\nsubu $v0, "#x); } while (0)

#if 0

/* direct mapped at zero!? for DSPs maybe. */

#define R8(P) (P)
#define R32(P) *(RMuint32 *)&(P) /* could a union.value, force it to RMuint32 */
#define W32(P,v) do { *(RMuint32 *)&(P)=v; } while (0)

#define RBF(P,f) (P).bits.f
#define WBF(P,f,v) do { (P).bits.f=v; } while (0)

#else

#define R8(P) gbus_read_uint8_ireg(pgbus,(RMuint32)&(P))
#define R32(P) gbus_read_uint32_ireg(pgbus,(RMuint32)&(P))
#define W32(P,v) do { gbus_write_uint32_ireg(pgbus,(RMuint32)&(P),v); } while (0)

/* example: RMuint32 k=RBF(Pxpu_lbus_address_decoder_MEM_BASE->_misc.d.route,write); */
#define RBF(P,f)							\
	({								\
		typeof(P) q={.value=gbus_read_uint32_ireg(pgbus,(RMuint32)&(P))}; \
		q.bits.f;						\
	})

/* 
   example: WBF(Pxpu_lbus_address_decoder_MEM_BASE->_misc.d.route,write,XPU_sbox_input_disconnect); 

   NOTE: you should be careful when using this one. It will assume perfect behavior regarding
   what-you-wrote-can-be-readback. For instance, it will write IDLE=1 bits. Rather use WONESHOT.
*/
#define WBF(P,f,v)							\
	do {								\
		typeof(P) q={.value=gbus_read_uint32_ireg(pgbus,(RMuint32)&(P))}; \
		q.bits.f=v;						\
		gbus_write_uint32_ireg(pgbus,(RMuint32)&(P),q.value);	\
	} while (0)

#endif

/* constructs on the previous... */
#define WONESHOT(P,com...) do { typeof(P) tmp={.bits={com}}; W32(P,tmp.value); } while (0)
#define WONESHOTFORCETYPE(P,T,com...) do { T tmp={.bits={com}}; W32(P,tmp.value); } while (0)
#define W32N(D,s,nwords) do { int i; for (i=0;i<nwords;i++) W32((RMuint32 *)&(D)[i],((RMuint32 *)(s))[i]); } while (0)
#define R32N(d,S,nwords) do { int i; for (i=0;i<nwords;i++) ((RMuint32 *)(d))[i]=R32(((RMuint32 *)&(S))[i]); } while (0)
#define W32N_rev(D,s,nwords) do { int i; for (i=0;i<nwords;i++) W32(((RMuint32 *)&(D))[nwords-1-i],((RMuint32 *)(s))[i]); } while (0)
#define R32N_rev(d,S,nwords) do { int i; for (i=0;i<nwords;i++) ((RMuint32 *)(d))[nwords-1-i]=R32(((RMuint32 *)&(S))[i]); } while (0)

/* 
   consider field F of old map file OM, and re-compute its address as if map file M had same geometry.

   Ex. let's consider host->rst reg. Now you want to loop on xpu, cpu, ipu to touch rst. 
   for (i in xpu cpu ipu) REBASE(host,rst,i)
*/		
#define REBASE(OM,F,M) ((typeof(OM))(M))->F

#define LO16(x)  ((x) & 0xffff)
#define HI16(x)  ((x) & 0xffff0000)

#define CPU_UART_RBR 0x00 /* width RMuint32 */
#define CPU_UART_THR 0x04 /* width RMuint32 */
#define CPU_UART_IER 0x08 /* width RMuint32 */
#define CPU_UART_IIR 0x0c /* width RMuint32 */
#define CPU_UART_FCR 0x10 /* width RMuint32 */
#define CPU_UART_LCR 0x14 /* width RMuint32 */
#define CPU_UART_MCR 0x18 /* width RMuint32 */
#define CPU_UART_LSR 0x1c /* width RMuint32 */
#define CPU_UART_MSR 0x20 /* width RMuint32 */
#define CPU_UART_SCR 0x24 /* width RMuint32 */
#define CPU_UART_CLKDIV 0x28 /* width RMuint32 */
#define CPU_UART_CLKSEL 0x2c /* width RMuint32 */
#define CPU_UART_GPIODIR 0x30 /* width RMuint32 */
#define CPU_UART_GPIODATA 0x34 /* width RMuint32 */
#define CPU_UART_GPIOMODE 0x38 /* width RMuint32 */

#define PMEM_BASE_xpu_block 0x1e0000
#define ISP_SIZE 0x8000
#define DMEM_BASE_xpu_block 0x1f0000
#define DSP_SIZE 0x6000

// Modules ID. From http://web.asic.sdesigns.com/twiki/bin/view/Main/CalypsoHcHookInfo
#define dummy_module_0          0x00
#define dummy_module_1          0x01
#define dummy_module_2          0x02
#define dummy_module_3          0x03
#define audio_block             0x10
#define audio_io_block          0x14
#define video_decoder_0         0x20
#define video_decoder_1         0x21
#define video_transcoder        0x30
#define xpu_block               0x40
#define host_interface_1        0x50
#define transport_demux_v2      0x60
#define baseband_video_platform 0x70
#define host_interface_2        0x80
#define gpu_block               0x90
#define cpu_block               0xa0

#endif /* __REGS_H__ */
