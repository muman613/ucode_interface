/*****************************************
 Copyright � 2005, 2006, 2007
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmmacros_c.h
  @brief  

  Macros / inline functions in general C syntax (no gcc extensions).

  @author Emmanuel Michon
  @date   2011-06-30
*/

#ifndef __RMMACROS_C_H__
#define __RMMACROS_C_H__

#ifndef __STR
#define __STR(x...) #x
#define STR(x) __STR(x)
#endif

#define __KEEP_END(str, len)		(str + sizeof(str) - (sizeof(str) <= len ? sizeof(str) : len))
#define RM_CODE_STAMP(size)			__KEEP_END(__FILE__":"STR(__LINE__), size)

#ifdef __ASSEMBLY__

#define RMALIGNTO(x,nbits) (((x)>>(nbits))<<(nbits))
#define RMALIGNTONEXT(x,nbits) RMALIGNTO( (x) + ((1<<(nbits))-1) , nbits )
#define RMALIGNOS(x,nbits) ((x)&((1<<(nbits))-1))

#else /* !__ASSEMBLY__ */


/*************** LEAF MACROS ****************/

#define RM_ARRAY_ENTRYCOUNT(x) (sizeof(x) / sizeof((x)[0]))
#define RM_BUILD_ASSERT(cond) do { (void) sizeof(RMuint32 [1 - 2*!(cond)]); } while(0)
#define RM_FIELD_OFFSET(x,y) ((RMuint32)(&((x *)NULL)->y))
#define RM_FIELD_SIZE(x,y) sizeof(((x *)NULL)->y)

// usually compiler is smart enough to put the target processor rotate instruction when this one occurs
#define ROTR_c(x, n)   (((x) >> (n)) | ((x) << ((sizeof(x) << 3) - (n))))
#define ROTL_c(x, n)   (((x) << (n)) | ((x) >> ((sizeof(x) << 3) - (n))))

/* those ones nicely self-adapt when int8, int16, int32 */
#define RMmin(x,y) (((x) < (y)) ? (x) : (y))
#define RMmax(x,y) (((x) < (y)) ? (y) : (x))
#define RMabs(x) (((x) >= 0) ? (x) : (-(x)))
#define RMsign(x) (((x) >= 0) ? (1) : (-1))

#define FIELD64(f) (*(RMuint64 *)&(f##lo))
#define RMuint32LSBfromRMuint64(l)     ( (RMuint32)   (l)                      )
#define RMuint32MSBfromRMuint64(l)     ( (RMuint32) ( ((l)>>32) & 0xffffffff ) )
#define RMuint64from2RMuint32(MSB,LSB) ( (RMuint64) ( (((RMuint64)(MSB))<<32) + ((RMuint64)(LSB)) )      )
#define RMuint64fromRMuint32ShiftLeft(l,n)  ( ((RMuint64)(l))<<(n) )
#define RMuint32fromRMuint64ShiftRight(l,n)  ( (RMuint32) ((RMuint64)(l)>>(n)) )

static inline RMuint32 RMcountBits_c(RMuint32 x)
{
	RMuint32 i;
	
	for (i = 0; x; i++) 
		x &= x - 1;  // remove least significant set bit
	
	return i;
}
#undef RMcountBits
#define RMcountBits RMcountBits_c

/*
  RMinsShiftBitsVar_c(&v,x,3,13);

  inserts 3 lsb of x in v at position 13 (hence clearing positions 13,14,15).

  The Var syntax allows bits and shift to be variables.
 */
#define RMinsShiftBitsVar_c(ptr, data, bits, shift) \
	*(ptr) = ( \
		((*(ptr)) & (~((RMuint32)((1 << (bits)) - 1) << (shift)))) | \
		(((RMuint32)(data) & ((1 << (bits)) - 1)) << (shift)) \
	)
#undef RMinsShiftBitsVar
#define RMinsShiftBitsVar RMinsShiftBitsVar_c

#define RMunshiftBitsVar_c(data, bits, shift) ( \
        (((RMuint32)(data)) >> (shift)) & ((1 << (bits)) - 1) )
#undef RMunshiftBitsVar
#define RMunshiftBitsVar RMunshiftBitsVar_c

#undef RMinsShiftBits
#define RMinsShiftBits RMinsShiftBitsVar

#undef RMunshiftBits
#define RMunshiftBits RMunshiftBitsVar

#define RMinsShiftBool(ptr, val, shift) RMinsShiftBits(ptr, (val)!=0, 1, shift)
#define RMinsShiftBoolVar(ptr, val, shift) RMinsShiftBitsVar(ptr, (val)!=0, 1, shift)
#define RMunshiftBool(data, shift) RMunshiftBits(data, 1, shift)

// e.m. deprecated --- use RMinsShiftBitsVar()
#define RMsetConsecutiveBitsVar(target,begin,end,value) RMinsShiftBitsVar(target, value, (end)-(begin)+1, begin)

// e.m. deprecated --- use RMinsShiftBits()
#if RMCOMPILERID==RMCOMPILERID_MIPSEL_GCC & !defined(XOS_COMPACT)

#define RMsetConsecutiveBits(target,begin,end,value)			\
do __asm__ __volatile__(							\
		     "ins %0, %1, " STR(begin) ", (" STR(end) "-(" STR(begin) ")+1)"	\
		     : "=r" (*(target)) /* may be same reg */		\
		     : "r" (value), "0" (*(target))); while (0)

#else
#define RMsetConsecutiveBits RMsetConsecutiveBitsVar
#endif


#define RMHASIMBIT(x,log2im) ((int)( ((RMuint32)(x)<<(31-(log2im))) )<0)
#define RMHASIMBIT64(x,i) (((i)>=32)?RMHASIMBIT(RMuint32MSBfromRMuint64(x),(i)-32):RMHASIMBIT(x,i))

/*
  returns the number of the highest bit set
  in other words, the base 2 logarithm of an unsigned 32bit integer
  
  log2 0xffffffff = 31
  log2 0x1003 = 12
  log2 0x1000 = 12
  log2 0x1 = 0
  log2 (nil) = -1

  There is a mips32r2 variant that works in O(1) with clz
 */
static inline RMint32 RMlog2_c(RMuint32 a)
{
	RMint32 rv = -1;
	
	while (a) {
		rv++;
		a >>= 1;
	}
	
	return rv;
}
#undef RMlog2
#define RMlog2 RMlog2_c

/*
  returns the number of the lowest bit set
  
  0: -1
  1: 0
  4: 2
  0x8C: 2
  0x8000: 15
 */
static inline RMint32 RMlbs_c(RMuint32 a)
{
	return RMlog2(a - (a & (a - 1)));
}
#undef RMlbs
#define RMlbs RMlbs_c

/*
  Is a power of two?

  0: FALSE
  1: TRUE
  8: TRUE
  0x1000: TRUE
  0x1003: FALSE
 */
static inline RMbool RMisPot_c(RMuint32 a) 
{
	return (!(a & (a - 1)) && a);  // check if non-zero after removing least significant set bit
}
#undef RMisPot_c
#define RMisPot RMisPot_c

static inline RMuint32 RMswapBytesUint32_c(RMuint32 a)
{									
	RMuint32 tmp=a;				
	
	tmp = (((tmp >> 8) & 0x00ff00ff) | ((tmp & 0x00ff00ff) << 8)); 
	tmp = ((tmp >> 16) | (tmp << 16));	
	
	return tmp;							
}
#undef RMswapBytesUint32
#define RMswapBytesUint32 RMswapBytesUint32_c

/* 0x10111213 -> 0x088848c8 */
static inline RMuint32 RMswapBitsInByteUint32_c(RMuint32 x)
{
	RMuint32 y = 0x55555555;
	x = (((x >> 1) & y) | ((x & y) << 1));
	y = 0x33333333;
	x = (((x >> 2) & y) | ((x & y) << 2));
	y = 0x0f0f0f0f;
	x = (((x >> 4) & y) | ((x & y) << 4));
	return x;
}
#undef RMswapBitsInByteUint32
#define RMswapBitsInByteUint32 RMswapBitsInByteUint32_c

#define RMprepend(x,y,z) (x-y-z)

/****************************************************/
/* BUFFER REARRANGEMENT up to 8 bytes ***************/
static inline RMuint32 RMbeBufToUint32(const RMuint8 *buf)
{
	return (((RMuint32) buf[0] << 24) + \
		((RMuint32) buf[1] << 16) + \
		((RMuint32) buf[2] << 8) + \
		(RMuint32)  buf[3]);
}

/**
   @param buf 4 bytes-long buffer.
   @return a RMuint32 from 4 bytes of a littleendian buffer
*/
static inline RMuint32 RMleBufToUint32(const RMuint8 *buf)
{
	return (((RMuint32) buf[3] << 24) + \
		((RMuint32) buf[2] << 16) + \
		((RMuint32) buf[1] << 8) + \
		(RMuint32)  buf[0]);
}

/**
   @param buf 8 bytes-long buffer.
   @return a RMuint64 from 8 bytes of a littleendian buffer
*/
static inline RMuint64 RMbeBufToUint64(const RMuint8 *buf)
{
	return (((RMuint64) buf[0] << 56) + \
		((RMuint64) buf[1] << 48) + \
		((RMuint64) buf[2] << 40) + \
		((RMuint64) buf[3] << 32) + \
		((RMuint64) buf[4] << 24) + \
		((RMuint64) buf[5] << 16) + \
		((RMuint64) buf[6] << 8) + \
		(RMuint64)  buf[7]);
}

/**
   @param buf 8 bytes-long buffer.
   @return a RMuint64 from 8 bytes of a littleendian buffer
*/
static inline RMuint64 RMleBufToUint64(const RMuint8 *buf)
{
	return (((RMuint64) buf[7] << 56) + \
		((RMuint64) buf[6] << 48) + \
		((RMuint64) buf[5] << 40) + \
		((RMuint64) buf[4] << 32) + \
		((RMuint64) buf[3] << 24) + \
		((RMuint64) buf[2] << 16) + \
		((RMuint64) buf[1] << 8) + \
		(RMuint64)  buf[0]);
}

/**
   Transforms a 32 bits integer into 4 bytes in big endian order

   @param val 
   @param buf   
*/
static inline void RMuint32ToBeBuf(RMuint32 val, RMuint8 *buf)
{
	buf[0] = (RMuint8)(val >> 24) & 0xff;
	buf[1] = (RMuint8)(val >> 16) & 0xff;
	buf[2] = (RMuint8)(val >>  8) & 0xff;
	buf[3] = (RMuint8)val & 0xff;
}

/**
   Transforms a 32 bits integer int o 4 bytes in little endian order

   @param val 
   @param buf   
*/
static inline void RMuint32ToLeBuf(RMuint32 val, RMuint8 *buf)
{
	buf[3] = (RMuint8)(val >> 24);
	buf[2] = (RMuint8)(val >> 16);
	buf[1] = (RMuint8)(val >>  8);
	buf[0] = (RMuint8)val;
}

/**
   Transforms a 64 bits integer int to 8 bytes in little endian order

   @param val 
   @param buf   
*/
static inline void RMuint64ToLeBuf(RMuint64 val, RMuint8 *buf)
{
	buf[7] = (RMuint8)(val >> 56);
	buf[6] = (RMuint8)(val >> 48);
	buf[5] = (RMuint8)(val >> 40);
	buf[4] = (RMuint8)(val >> 32);
	buf[3] = (RMuint8)(val >> 24);
	buf[2] = (RMuint8)(val >> 16);
	buf[1] = (RMuint8)(val >>  8);
	buf[0] = (RMuint8)val;

}

/**
   Transforms array of 16 bits integer into an RMuint64

   @param array 
   @param val   
*/
static inline void RMuint16ArrayToRMuint64(RMuint16 * array, RMuint64 *val)
{
	*val =  (RMuint64) (array[0])
	| (RMuint64)(array[1]) << 16
	| (RMuint64)(array[2]) << 32
	| (RMuint64)(array[3]) << 48;
}

/**
   Transforms a 64 bits integer int to 8 bytes in big endian order

   @param val 
   @param buf   
*/
static inline void RMuint64ToBeBuf(RMuint64 val, RMuint8 *buf)
{
	buf[0] = (RMuint8)(val >> 56) & 0xff;
	buf[1] = (RMuint8)(val >> 48) & 0xff;
	buf[2] = (RMuint8)(val >> 40) & 0xff;
	buf[3] = (RMuint8)(val >> 32) & 0xff;
	buf[4] = (RMuint8)(val >> 24) & 0xff;
	buf[5] = (RMuint8)(val >> 16) & 0xff;
	buf[6] = (RMuint8)(val >>  8) & 0xff;
	buf[7] = (RMuint8)val & 0xff;
}

/**
   @param buf 3 bytes-long buffer.
   @return a RMuint24 from 3 bytes of a bigendian buffer
*/
static inline RMuint32 RMbeBufToUint24(const RMuint8 *buf)
{
	return (((RMuint32) buf[0] << 16) + \
		((RMuint32) buf[1] << 8) + \
		(RMuint32) buf[2]);
}

/**
   @param buf 6 bytes-long buffer.
   @return a RMuint48 from 6 bytes of a bigendian buffer
*/
static inline RMuint64 RMbeBufToUint48(const RMuint8 *buf)
{
	return (((RMuint64) buf[0] << 40) + \
		((RMuint64) buf[1] << 32) + \
		((RMuint64) buf[2] << 24) + \
		((RMuint64) buf[3] << 16) + \
		((RMuint64) buf[4] << 8) + \
		(RMuint64) buf[5]);
}

/**
   @param buf 3 bytes-long buffer.
   @return a RMuint24 from 4 bytes of a littleendian buffer
*/
static inline RMuint32 RMleBufToUint24(const RMuint8 *buf)
{
	return (((RMuint32) buf[2] << 16) + \
		((RMuint32) buf[1] << 8) + \
		(RMuint32) buf[0]);
}

/**
   Transform a 24 bits integer (stored in a RMuint32) into 3 bytes in big endian order
   
   @param val
   @param buf
*/
static inline void RMuint24ToBeBuf(RMuint32 val, RMuint8 *buf)
{
	buf[0] = (RMuint8)(val >>  16);
	buf[1] = (RMuint8)(val >>  8);
	buf[2] = (RMuint8)val;
}

/**
   Transforms a 24 bits integer into 2 bytes in little endian order

   @param val 
   @param buf   
*/
static inline void RMuint24ToLeBuf(RMuint32 val, RMuint8 *buf)
{
	buf[2] = (RMuint8)(val >>  16);
	buf[1] = (RMuint8)(val >>  8);
	buf[0] = (RMuint8)val;
}

/**
   @param buf 2 bytes-long buffer.
   @return a RMuint16 from 2 bytes of a bigendian buffer
*/
static inline RMuint16 RMbeBufToUint16(const RMuint8 *buf)
{
	return (((RMuint16) buf[0] << 8) + \
		(RMuint16)  buf[1]);
}

/**
   @param buf 2 bytes-long buffer.
   @return a RMuint16 from 2 bytes of a littleendian buffer
*/
static inline RMuint16 RMleBufToUint16(RMuint8 *buf)
{
 	return 	(((RMuint16) buf[1] << 8) + \
		(RMuint16)  buf[0]);
}

/**
   Transforms a 16 bits integer into 2 bytes in big endian order

   @param val 
   @param buf   
*/
static inline void RMuint16ToBeBuf(RMuint16 val, RMuint8 *buf)
{
	buf[0] = (RMuint8)(val >>  8);
	buf[1] = (RMuint8)val;
}

/**
   Transforms a 16 bits integer into 2 bytes in little endian order

   @param val 
   @param buf   
*/
static inline void RMuint16ToLeBuf(RMuint16 val, RMuint8 *buf)
{
	buf[1] = (RMuint8)(val >>  8);
	buf[0] = (RMuint8)val;
}
/****************************************************/
/****************************************************/

// sometimes RMMemset is remapped on a complex operation. Rather use this to zero memory at location:
#define RMclearmemory(location,size) 				\
do {								\
	RMuint32 _rmmacros_i;							\
	for (_rmmacros_i=0;_rmmacros_i<(RMuint32)(size);_rmmacros_i++) *((RMuint8 *)(location)+_rmmacros_i)=0;	\
} while (0)
#define clearmemory RMclearmemory

#define RMcopymemory(dest, src, size) \
do { \
	RMuint32 _rmmacros_i; \
	for (_rmmacros_i=0;_rmmacros_i<(RMuint32)(size);_rmmacros_i++) *((RMuint8 *)(dest)+_rmmacros_i)=*((RMuint8 *)(src)+_rmmacros_i); \
} while (0)
#define copymemory RMcopymemory

static inline RMint32 RMcomparememory(const void *ptr1, const void *ptr2, RMuint32 size)
{
	RMuint32 i;
	for (i = 0; i < size; i++) {
		if (*((RMuint8 *)ptr1 + i) != *((RMuint8 *)ptr2 + i)) {
			return (RMint32)(*((RMuint8 *)ptr1 + i)) - (RMint32)(*((RMuint8 *)ptr2 + i));
		}
	}
	return 0;
}

// integer division a * b / c
#define RM64mult32div32(a,b,c) ( (RMuint64)(a) * (RMuint32)(b) / (RMuint32)(c) )

// rounded integer division a * b / c
#define RM64mult32divrnd32(a,b,c) ( ((RMuint64)(a) * (RMuint32)(b) + ((RMuint32)(c) >> 1)) / (RMuint32)(c) )

/* 

   Example
   RMALIGNTO(0x12345600,2) = 0x12345600 (prev 32bit word align)
   RMALIGNTO(0x12345601,2) = 0x12345600 (prev 32bit word align)
   RMALIGNTO(0x12345609,4) = 0x12345600 (prev 128bit word align)

   With the current implementation, the `Var' form is not different.
*/
#define RMALIGNTO(x,nbits) ((((RMuint32)(x))>>(nbits))<<(nbits))
#define RMALIGNTOVar RMALIGNTO

/* 
   process x as a 32bit integer, align it to next 2^nbits byte boundary.

   Example
   RMALIGNTONEXT(0x12345600,2) = 0x12345600 (next 32bit word align)
   RMALIGNTONEXT(0x12345601,2) = 0x12345604 (next 32bit word align)
   RMALIGNTONEXT(0x12345601,4) = 0x12345610 (next 128bit word align)
*/
#define RMALIGNTONEXT(x,nbits) RMALIGNTO( (RMuint32)(x) + ((1<<(nbits))-1) , nbits )
#define RMALIGNTONEXTVar RMALIGNTONEXT

/*
  Alignment over shoot

  how many bytes you're from the boundary.
 */
#define RMALIGNOS(x,nbits) ((RMuint32)(x)&((1<<(nbits))-1))

#define RMALIGNTO64(x,nbits) ((((RMuint64)(x))>>(nbits))<<(nbits))
#define RMALIGNTO64NEXT(x,nbits) RMALIGNTO( (RMuint64)(x) + ((((RMuint64)1)<<(nbits))-((RMuint64)1)) , nbits )

/*
  check if [p, p+size[ crosses a 2^nbits boundary.

  [0x803,0x803 + 0x20[ does cross a 2^5 boundary.

  [0x800,0x800 + 0x20[ does not cross a 2^5 boundary.
  [0x800,0x800 + 0[ does not cross a 2^5 boundary.

  The alternate with ((RMALIGNTONEXT(p+size,nbits)-RMALIGNTO(p,nbits))>>nbits)<=1 is too much calculus.
 */
#define RMCROSSES(p,size,nbits) (RMALIGNTO(p,nbits)!=RMALIGNTO((RMuint32)(p)+(RMuint32)(size)-1,nbits))

#endif /* __ASSEMBLY__ */

#define RMALIGNOSNEXT(x,nbits) (RMALIGNTONEXT((x)+1/*think twice*/,nbits)-(x))

#define LOG2_RM_PAGE_SIZE 12
#define RM_PAGE_SIZE (1<<LOG2_RM_PAGE_SIZE)
#define RM_PAGE_ALIGN(x) RMALIGNTO(x,LOG2_RM_PAGE_SIZE)

// Typically: p=RMMalloc(size+RM_PAGE_SIZE-1); Give out RM_NEXT_PAGE_ALIGN(p).
#define RM_NEXT_PAGE_ALIGN(x) RMALIGNTONEXT(x,LOG2_RM_PAGE_SIZE)

// actually, cannot be used without rmchip
#define RM_NEXT_TILE_ALIGN(x) RMALIGNTONEXT(x,RMTILE_SIZE_SHIFT)

#if defined __GNUC__

#include "rmmacros_gcc.h"

#else

#endif /* __GNUC__ */


#ifdef __ASSEMBLY__
#else
/*************** NOT-LEAF MACROS ****************/
#ifndef RMswapBitsUint32
/* 0x10111213 -> 0xc8488808 */
static inline RMuint32 RMswapBitsUint32_c(RMuint32 x)
{
	return RMswapBytesUint32(RMswapBitsInByteUint32(x));
}
#undef RMswapBitsUint32
#define RMswapBitsUint32 RMswapBitsUint32_c
#endif /* RMswapBitsUint32 */

#include "rmmacros_divisions.h"

#endif /* __ASSEMBLY__ */

#endif /* __RMMACROS_C_H__ */
