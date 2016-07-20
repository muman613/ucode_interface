/*****************************************
 Copyright � 2005, 2006, 2007
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmmacros_g.h
  @brief  

  Macros / inline functions that specifically require gcc extensions.
  Generic GNU assembler can also happen but there is little to be found in that category

  Reminder: gcc specific constructs
  - packed attribute
  - 1ULL large immediate syntax
  - ({...}) operator
  - __attribute__((things))
  - variable arg macros
  - inline assembly
  - constant initialization: {.a=1,.b=2} 

  @author Emmanuel Michon
  @date   2011-06-30
*/

#ifndef __RMMACROS_G_H__
#define __RMMACROS_G_H__

#ifndef __GNUC__
#error This is only GNU C compiler material
#endif

#ifdef __ASSEMBLY__
#else /* !__ASSEMBLY__ */

/***************************************************/
/**************      Leaf macros    ****************/
/***************************************************/
struct uaRMuint32 {
	RMuint32 value;
} __attribute__((packed));

#define srl64to64_le32(x,s)					\
	({							\
		RMuint32 rhi=RMuint32MSBfromRMuint64(x),	\
			rlo=RMuint32LSBfromRMuint64(x);	\
								\
		rlo>>=(s);	\
		rlo|=rhi<<(32-(s)); \
		rhi>>=(s);	\
								\
		RMuint64from2RMuint32(rhi,rlo);			\
	})

#define sll64to64_le32(x,s)					\
	({							\
		RMuint32 rhi=RMuint32MSBfromRMuint64(x),	\
			rlo=RMuint32LSBfromRMuint64(x);	\
								\
		rhi<<=(s);	\
		rhi|=rlo>>(32-(s)); \
		rlo<<=(s);	\
								\
		RMuint64from2RMuint32(rhi,rlo);			\
	})

/*
  See mips run second edition 9.5.1
  You can only take pointers to those obviously

  Don't assume they're 32bit aligned
  _ftext <= etext
  _fdata <= edata
  _fbss <= end

  Do not do assumptions on the location of _frodata. When using harvard model, rodata can't be in text.
*/
extern RMascii _ftext[], _frodata[], etext[], _fdata[], edata[], _fbss[], end[], _gp[];

/*
  expect this macro to sleep too long when clocks <= 50 
  if you need so short delays, you should use dedicated hardware, not a general purpose cpu
*/
#define RMclocksBusySleep(clocks)			\
do {						\
	RMuint32 clocks_nosideeffect=(clocks);	\
	RMuint32 mark=GETCOUNT();	\
	while (RMclocksElapsedSince(mark)<(clocks_nosideeffect));	\
} while (0)

/*
  Could be the same if we were not plagued by 32bit mul overflow
 */
#define RMmicrosecondsBusySleep(f_hz,us) RMclocksBusySleep((RMuint32)(us)*((f_hz)/1000000))
#define RMmillisecondsBusySleep(f_hz,ms) RMclocksBusySleep((RMuint32)(ms)*((f_hz)/1000))

#undef RMlog2
#define RMlog2(x) (31-__builtin_clz(x))
#define RMlog2_64(a) (RMuint32MSBfromRMuint64(a)?(32+RMlog2(RMuint32MSBfromRMuint64(a))):RMlog2(a))

/*
  Turn off individual warnings and optionally restore them to the original levels

  For GCC versions prior to 4.2 neither GCC_DIAG_OFF(x) nor GCC_DIAG_ON(x) have any effect (not supported)
  For GCC versions 4.2-4.5 GCC_DIAG_OFF(x) has file scope and GCC_DIAG_ON(x) has no effect
  For GCC versions 4.6 and beyond GCC_DIAG_OFF(x)'s scope is from it's position in the file
  to that of the following GCC_DIAG_ON(x)

  Courtesy of Jonathan Wakely as per http://dbp-consulting.com/tutorials/SuppressingGCCWarnings.html
 */
#if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 402
#define GCC_DIAG_STR(s) #s
#define GCC_DIAG_JOINSTR(x,y) GCC_DIAG_STR(x ## y)
# define GCC_DIAG_DO_PRAGMA(x) _Pragma (#x)
# define GCC_DIAG_PRAGMA(x) GCC_DIAG_DO_PRAGMA(GCC diagnostic x)
# if ((__GNUC__ * 100) + __GNUC_MINOR__) >= 406
#  define GCC_DIAG_OFF(x) GCC_DIAG_PRAGMA(push) \
	GCC_DIAG_PRAGMA(ignored GCC_DIAG_JOINSTR(-W,x))
#  define GCC_DIAG_ON(x) GCC_DIAG_PRAGMA(pop)
# else
#  define GCC_DIAG_OFF(x) GCC_DIAG_PRAGMA(ignored GCC_DIAG_JOINSTR(-W,x))
#  define GCC_DIAG_ON(x)  GCC_DIAG_PRAGMA(warning GCC_DIAG_JOINSTR(-W,x))
# endif
#else
# define GCC_DIAG_OFF(x)
# define GCC_DIAG_ON(x)
#endif

#endif /* __ASSEMBLY__ */

#if defined __mips__ 
#include "rmmacros_mips.h"
#elif defined __arm__

#define FORCE16
#define FORCE32
/* There is a remap from 0xb0000000 to 0 */
#ifdef __ASSEMBLY__
#define RM_PA_TO_UNCACHED(x) ((x) + 0xb0000000)
#else
#define RM_PA_TO_UNCACHED(x) ((void *)(x) + 0xb0000000)
#endif

#ifdef __ARMCC_VERSION
/* we don't optimize for RVDS */
#else
#include "rmmacros_arm.h"
#endif

#elif defined __i386__ || defined __amd64__

/*
  it does not make much sense to optimize for intel. The code we build for intel,
  is mostly debug stubs; in that case, readability is better than speed.
 */

//HACK: I still have to figure out why rmtime.c is being built with RMCOMPILERID==RMCOMPILERID_MIPSEL_GCC in withhost mode
#define GETCOUNT()  0

#else
#error unsupported processor
#endif

/***************************************************/
/**************   Non-leaf macros   ****************/
/***************************************************/
#ifdef __ASSEMBLY__
#else
static inline RMuint32 RMbeBufToUint32_gcc(const RMuint8 *buf)
{
	struct uaRMuint32 *p=(struct uaRMuint32 *)buf;
	return RMswapBytesUint32(p->value);
}
#undef RMbeBufToUint32
#define RMbeBufToUint32 RMbeBufToUint32_gcc

static inline RMuint32 RMleBufToUint32_gcc(const RMuint8 *buf)
{
	struct uaRMuint32 *p=(struct uaRMuint32 *)buf;
	return p->value;
}
#undef RMleBufToUint32
#define RMleBufToUint32 RMleBufToUint32_gcc

static inline RMuint64 RMbeBufToUint64_gcc(const RMuint8 *buf)
{
	struct uaRMuint32 *p=(struct uaRMuint32 *)buf;
	return RMuint64from2RMuint32(RMswapBytesUint32(p[0].value),RMswapBytesUint32(p[1].value));
}
#undef RMbeBufToUint64
#define RMbeBufToUint64 RMbeBufToUint64_gcc

static inline RMuint64 RMleBufToUint64_gcc(const RMuint8 *buf)
{
	struct uaRMuint32 *p=(struct uaRMuint32 *)buf;
	return RMuint64from2RMuint32(p[1].value,p[0].value); 
}
#undef RMleBufToUint64
#define RMleBufToUint64 RMleBufToUint64_gcc

static inline void RMuint32ToBeBuf_gcc(RMuint32 val, RMuint8 *buf)
{
	struct uaRMuint32 *p=(struct uaRMuint32 *)buf;
	p->value=RMswapBytesUint32(val);
}
#undef RMuint32ToBeBuf
#define RMuint32ToBeBuf RMuint32ToBeBuf_gcc

static inline void RMuint32ToLeBuf_gcc(RMuint32 val, RMuint8 *buf)
{
	struct uaRMuint32 *p=(struct uaRMuint32 *)buf;
	p->value=val;
}
#undef RMuint32ToLeBuf
#define RMuint32ToLeBuf RMuint32ToLeBuf_gcc

static inline void RMuint64ToBeBuf_gcc(RMuint64 val, RMuint8 *buf)
{
	struct uaRMuint32 *p=(struct uaRMuint32 *)buf;

	p[0].value=RMswapBytesUint32(RMuint32MSBfromRMuint64(val));
	p[1].value=RMswapBytesUint32(RMuint32LSBfromRMuint64(val));
}
#undef RMuint64ToBeBuf
#define RMuint64ToBeBuf RMuint64ToBeBuf_gcc

static inline void RMuint64ToLeBuf_gcc(RMuint64 val, RMuint8 *buf)
{
	struct uaRMuint32 *p=(struct uaRMuint32 *)buf;

	p[0].value=RMuint32LSBfromRMuint64(val);
	p[1].value=RMuint32MSBfromRMuint64(val);
}
#undef RMuint64ToLeBuf
#define RMuint64ToLeBuf RMuint64ToLeBuf_gcc

#endif

#endif /* __RMMACROS_G_H__ */
