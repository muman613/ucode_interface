/*****************************************
 Copyright © 2005, 2006, 2007
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmmacros_divisions.h
  @brief  

  -long description-

  @author Emmanuel Michon
  @date   2011-07-04
*/

#ifndef __RMMACROS_DIVISIONS_H__
#define __RMMACROS_DIVISIONS_H__

/* It divides two RMuint64 and returns quotient = a / b and reminder */
static inline RMuint64 RM64div64rem64(RMuint64 a, RMuint64 b, RMuint64 *rem)
{
	RMuint64 remainder = 0, quotient = 0;
	RMuint32 r32, d, b_low;
	RMint32 i;
	RMuint8 nbits = sizeof(RMuint64) * 8;
	
	if(rem)
		*rem = 0;

	if (! b) {
		/* RMDBGLOG((ENABLE, "RM64div64() DIVIDE BY 0!\n" )); */
		return a;
	}
	
	if (a == b) {
		return 1;
	}
	
	if (((b >> 32) == 0) && ((a >> 32) == 0)) {
		/* Simplest Case, 32 bits division */
		quotient = (RMuint64)((RMuint32)a / (RMuint32)b);
		if(rem)
			*rem = a - quotient * (RMuint32)b;
		return quotient;
	}
	
	if ((b >> 28) == 0) {
		/* Divisor is less than 28bit length */
		b_low = (RMuint32)b;
		d = (RMuint32)(a >> 32);
		quotient = (d / b_low);
		
		for (i = 0; i < 8; i++) {
			r32 = d % b_low;
			d = (RMuint32)((r32 << 4) | (srl64to64_le32(a , (7 - i) * 4) & 0xf));
			quotient = (quotient << 4) | (d / b_low);
		}
		if(rem)
			*rem =  d % b_low;
		return quotient;
	}
	
	/* Skip first zeros */
	quotient = (((RMuint64)1) << (nbits - 1));
	while (quotient && ((a & quotient) == 0)) {
		nbits--;
		quotient >>= 1;
	}
	
	/* Compute, simple 2-radix */
	quotient = 0;
	for (i = (nbits - 1); i >= 0; i--) {
		remainder = remainder << 1 | RMHASIMBIT64(a,i) ;
		quotient <<= 1;
		if (remainder >= b) {
			remainder -= b;
			quotient |= 1;
		}
	}
	if(rem)
		*rem = remainder;
	return quotient;
}

static inline RMuint64 RM64div64(RMuint64 a, RMuint64 b)
{
	return RM64div64rem64(a, b, (RMuint64 *)NULL );
}

/*
  DEPRECATED. See #5142. em2007apr17 
  
  This funtion divides two signed 64 bit integer, 
   and writes the resulting integer quotient, the
   remainder and the first 64 bits of the fractional 
   part into 3 64 bit integer, whose references are 
   passed to the function. Each of the references
   can be NULL, if the result is not desired.
*/
static inline RMstatus RM64divfrac64rem64(
	RMint64 numer,   /* enumerator                  */
	RMint64 denom,   /* denominator                 */
	RMint64 *pQuot,  /* result of integer division  */
	RMint64 *pRem,   /* remainder of division       */
	RMint64 *pFrac)  /* fractional part of division */
{
	RMint64 quot;
	RMint64 frac;
	RMint32 shift;
	RMint64 sign = 1;
	
	/* division by zero? */
	if (!denom) return RM_ERROR;
	
	/* remove and remember sign */
	if (numer < 0) {
		numer = -numer;
		sign = -sign;
	}
	if (denom < 0) {
		denom = -denom;
		sign = -sign;
	}
	
	/* align denom with numer */
	quot = frac = 0;
	shift = 0;
	while ((denom < numer) && ((denom & (((RMint64)1)<<63)) == 0)) {
		denom <<= 1;
		shift++;
	}
	
	/* divide numer by denom */
	while (1) {
		if (numer >= denom) {
			numer -= denom;
			quot |= 1;
		}
		if (! shift) break;
		denom >>= 1;
		quot <<= 1;
		shift--;
	}
	
	/* write results and check if fractional part is needed */
	if (pQuot) *pQuot = quot * sign;
	if (pRem) *pRem = numer * sign;
	if (!pFrac) return RM_OK;
	
	/* keep dividing remainder for fractional part */
	while (1) {
		if (numer & (((RMint64)1)<<63)) {
			if ( ((numer == (denom >> 1)) && (!(denom & 1))) || (numer > (denom >> 1))) {
				numer -= (denom >> 1);
				frac |= 1;
			}
			numer <<= 1;
			if (denom & 1) numer -= 1;
		} else {
			numer <<= 1;
			if (numer >= denom) {
				numer -= denom;
				frac |= 1;
			}
		}
		if (shift <= -63) break;
		frac <<= 1;
		shift--;
	}
	
	/* write fractional part and return */
	*pFrac = frac * sign;
	
	return RM_OK;
}

/*
   Knuth's implementation to divide a 96bits integer by a 32bits integer (Donald E. Knuth, "The Art Of Computer Programming", chapter 4.3.1, algorithm D).
   divides a 64 bit integer (6 x 16) with a 32 bit integer. Stores Quotient in a 96 bits integer (6 x 16) and Rest in a 32 bit integer (2 x 16).
   N = M*Q + R where all operands are positive. 
   
   @param N 96 bits unsigned integer.
   @param M 32 bits unsigned integer.
   @param Q 96 bits unsigned integer.
   @param R 32 bits unsigned integer. R can be the NULL pointer if you dont care the remainder.
*/
static inline RMstatus RMuint96div32(RMuint16 N[6], RMuint16 M[2], RMuint16 Q[6], RMuint16 R[2])
{
	RMint32 i;
	RMuint32 r, q;
	RMuint32 n;
	RMuint32 D;
	RMuint32 ND[7];
	RMuint32 MD[2];
	RMint64 u,v;
	
	if (M[1] == 0 && M[0] == 0) {
/* 		RMDBGLOG((ENABLE, "Division by zero\n")); */
		return RM_ERROR;
	}

	/* simplest case, one digit on the divisor */
	if (M[1] == 0) {
		r = 0;
		
		/* 5 is digits(N) - digits(M) = 6-1, where digits return the number of digit (in 2^16 base) of a number */
		for (i=5 ; i>=0 ; i--) {
			n = (r << 16) + N[i];
			Q[i] = n / M[0];
			r = n - (RMuint32)(Q[i])*(RMuint32)(M[0]);
		}
		if (R) {
			R[1] = 0;
			R[0] = r;
		}
	}
	else {
		/* first normalize : ND = N<<D and MD = M << D, so that MD[1] >= 2^16 / 2 */
		D=0;
		while ((M[1] << D) < (1 << 15)) D++;

		if (D > 0) {
			MD[0] = (((RMuint32) M[0]) << D) & 0xffff;
			MD[1] = (((RMuint32) M[1]) << D) | (M[0] >> (16-D));
			
			ND[0] = (((RMuint32) N[0]) << D) & 0xffff;
			for (i=1 ; i<6 ; i++) 
				ND[i] = ((((RMuint32) N[i]) << D) | (N[i-1] >> (16-D))) & 0xffff;
			ND[6] = N[5] >> (16-D);
		} else {
			for (i=0 ; i<2 ; i++)
				MD[i] = M[i];
			
			for (i=0 ; i<6 ; i++)
				ND[i] = N[i];
			ND[6] = 0;
		}

/* 		RMDBGLOG((DISABLE,"N -> %d:%d:%d:%d:%d:%d, M -> %d:%d\n", N[5], N[4], N[3], N[2], N[1], N[0], M[1], M[0])); */
/* 		RMDBGLOG((DISABLE,"D: %lu, N -> %lu:%lu:%lu:%lu:%lu:%lu:%lu, M -> %lu:%lu\n", D, ND[6], ND[5], ND[4], ND[3], ND[2], ND[1], ND[0], MD[1], MD[0])); */

		v = (((RMuint64) MD[1]) << 16) + MD[0];

		Q[5] = 0;
		
		/* 4 is digits(N) - digits(M) = 6-2, where digits return the number of digit (in 2^16 base) of a number */
		for (i=4 ; i>=0 ; i--) {
			n = (ND[i+2]<<16) + ND[i+1];
			q = n / MD[1];

			if (q >= (1<<16)) {
				q = (1<<16) - 1;
			} else {
				r = n - q*MD[1];
				while (q * MD[0] > (r << 16) + ND[i]) {
					q --;
					r += MD[1];
					if (r >= 1<<16)
						break;
				}
			}
			
			/* no need to use multiprecision multiplication and substraction due to the limited range of the operands */
			u = (((RMuint64) ND[i+2]) << 32) + (((RMuint64) ND[i+1]) << 16) + ((RMuint64) ND[i]);  
			u = u - q*v;
			if (u < 0) {
				u += ((RMuint64) 1) << 48;
				q --;
				u += v;
			}
			
/* 			RMDBGLOG((DISABLE,"ND[%lu]: %lu, ND[%lu]: %lu, Q[%lu]: %lu\n", i+2, ND[i+2], i+1, ND[i+1], i, q)); */
			
			Q[i] = q;
			
			ND[i+2] = (u >> 32) & 0xffff;
			ND[i+1] = (u >> 16) & 0xffff;
			ND[i+0] = (u >>  0) & 0xffff;
		}
		
		u = (ND[1] << 16) + ND[0];
#ifdef CLF_FIX34597
		r = srl64to64_le32(u,D);
#else
		r = u>>D;
#endif
/* 		RMDBGLOG((DISABLE,"u: %lld, r: %lu, N1: %lx, N0: %lx\n", u, r, ND[1], ND[0])); */

		if (R) {
			R[1] = (r >> 16) & 0xffff;
			R[0] = (r >>  0) & 0xffff;
		}
	} 

	return RM_OK;
}

/**
   Knuth's implementation to divide a 64bits integer by a 32bits integer (Donald E. Knuth, "The Art Of Computer Programming", chapter 4.3.1, algorithm D).
   divides a 64 bit integer (4 x 16) with a 32 bit integer. Stores Quotient in a 64 bits integer (4 x 16) and Rest in a 32 bit integer (2 x 16).
   N = M*Q + R where all operands are positive. 

   @param N 64 bits unsigned integer.
   @param M 32 bits unsigned integer.
   @param Q 64 bits unsigned integer.
   @param R 32 bits unsigned integer. R can be the NULL pointer if you dont care the remainder.
*/

static inline RMstatus RMuint64div32(RMuint16 N[4], RMuint16 M[2], RMuint16 Q[4], RMuint16 R[2])
{
	RMint32 i;
	RMuint32 r, q;
	RMuint32 n;
	RMuint32 D;
	RMuint32 ND[5];
	RMuint32 MD[2];
	RMint64 u,v;

	if (M[1] == 0 && M[0] == 0) {
/* 		RMDBGLOG((ENABLE, "Division by zero\n")); */
		return RM_ERROR;
	}

	/* simplest case, one digit on the divisor */
	if (M[1] == 0) {
		r = 0;

		/* 3 is digits(N) - digits(M) = 4-1, where digits return the number of digit (in 2^16 base) of a number */
		for (i=3 ; i>=0 ; i--) {
			n = (r << 16) + N[i];
			Q[i] = n / M[0];
			r = n - (RMuint32)(Q[i])*(RMuint32)(M[0]);
		}
		if (R) {
			R[1] = 0;
			R[0] = r;
		}
	}
	else {
		/* first normalize : ND = N<<D and MD = M << D, so that MD[1] >= 2^16 / 2 */
		D=0;
		while ((M[1] << D) < (1 << 15)) D++;

		if (D > 0) {
			MD[0] = (((RMuint32) M[0]) << D) & 0xffff;
			MD[1] = (((RMuint32) M[1]) << D) | (M[0] >> (16-D));
			
			ND[0] = (((RMuint32) N[0]) << D) & 0xffff;
			for (i=1 ; i<4 ; i++) 
				ND[i] = ((((RMuint32) N[i]) << D) | (N[i-1] >> (16-D))) & 0xffff;
			ND[4] = N[3] >> (16-D);
		} else {
			for (i=0 ; i<2 ; i++)
				MD[i] = M[i];
			
			for (i=0 ; i<4 ; i++)
				ND[i] = N[i];
			ND[4] = 0;
		}

/* 		RMDBGLOG((DISABLE,"N -> %d:%d:%d:%d, M -> %d:%d\n", N[3], N[2], N[1], N[0], M[1], M[0])); */
/* 		RMDBGLOG((DISABLE,"D: %lu, N -> %lu:%lu:%lu:%lu:%lu, M -> %lu:%lu\n", D, ND[4], ND[3], ND[2], ND[1], ND[0], MD[1], MD[0])); */

		v = (((RMuint64) MD[1]) << 16) + MD[0];
		
		Q[3] = 0;

		/* 2 is digits(N) - digits(M) = 4-2, where digits return the number of digit (in 2^16 base) of a number */
		for (i=2 ; i>=0 ; i--) {
			n = (ND[i+2]<<16) + ND[i+1];
			q = n / MD[1];

			if (q >= (1<<16)) {
				q = (1<<16) - 1;
			} else {
				r = n - q*MD[1];
				while (q * MD[0] > (r << 16) + ND[i]) {
					q --;
					r += MD[1];
					if (r >= 1<<16)
						break;
				}
			}
			
			/* no need to use multiprecision multiplication and substraction due to the limited range of the operands */
			u = (((RMuint64) ND[i+2]) << 32) + (((RMuint64) ND[i+1]) << 16) + ((RMuint64) ND[i]);  
			u = u - q*v;
			if (u < 0) {
				u += ((RMuint64) 1) << 48;
				q --;
				u += v;
			}
			
/* 			RMDBGLOG((DISABLE,"ND[%lu]: %lu, ND[%lu]: %lu, Q[%lu]: %lu\n", i+2, ND[i+2], i+1, ND[i+1], i, q)); */

			Q[i] = q;
			
			ND[i+2] = (u >> 32) & 0xffff;
			ND[i+1] = (u >> 16) & 0xffff;
			ND[i+0] = (u >>  0) & 0xffff;
		}
		
		u = (ND[1] << 16) + ND[0];
#ifdef CLF_FIX34597
		r = srl64to64_le32(u,D); // this is to avoid a call to ashrdi3() in some cases. But it does not assemble the same way.
#else
		r=u>>D;
#endif
/* 		RMDBGLOG((DISABLE,"u: %lld, r: %lu, N1: %lx, N0: %lx\n", u, r, ND[1], ND[0])); */

		if (R) {
			R[1] = (r >> 16) & 0xffff;
			R[0] = (r >>  0) & 0xffff;
		}
	} 
	
	return RM_OK;
}

/**
 multiplies a 64 bit integer (2 x 32) with a 32 bit integer and store it a 96 bit integer (3 x 32).
   @param N 64 bits integer.
   @param m 32 bits integer.
   @param P 96 bits integer.
*/
static inline void RMuint64mul32(RMuint32 N[2], RMuint32 m, RMuint32 P[3])
{
	RMuint64 n1m=(RMuint64)(N[1])*(RMuint64)m;
	RMuint64 n0m=(RMuint64)(N[0])*(RMuint64)m;
	P[0]=n0m;
	P[1]=(n0m>>32)+(RMuint32)n1m;
	P[2]=n1m>>32;
	if (P[1]<(RMuint32)n1m)
		P[2]++;
}

/**
   Greatest Common Divisor

   This function operates on positive integers.
   Origin: http://en.wikipedia.org/wiki/Binary_gcd as of 2012-01-12
   
   If either parameter is zero, the return value will be unpredictable.

   @param u unsigned non-zero integer
   @param v unsigned non-zero integer
   @return -ReturnValue-
*/
static inline RMuint32 RMgcd(RMuint32 u, RMuint32 v)
{
#if 0 // Modulo (division operation)
	RMuint32 tmp;
	
	while (v != 0) {
		tmp = v;
		v = u % v;
		u = tmp;
	}
	
	return u;
#else // Binary (recursive implementation with bit shifting)
	// simple cases (termination)
	if (u == v)
		return u;
	if (u == 0)
		return v;
	if (v == 0)
		return u;
	
	// look for factors of 2
	if (~u & 1) { // u is even
		if (v & 1) // v is odd
			return RMgcd(u >> 1, v);
		else // both u and v are even
			return RMgcd(u >> 1, v >> 1) << 1;
	}
	if (~v & 1) // u is odd, v is even
		return RMgcd(u, v >> 1);
	
	// reduce larger argument
	if (u > v)
		return RMgcd((u - v) >> 1, v);
	return RMgcd((v - u) >> 1, u);
#endif
}

/**
   fraction (aspect ratio) reduction of A/B
 */
static inline void RMReduceRatio(RMuint32 *pA, RMuint32 *pB)
{
	RMuint32 gcd;
	
	if (pA == NULL) return;
	if (pB == NULL) return;
	
	if (*pA == 0) {
		gcd = *pB;
	} else 
	if (*pB == 0) {
		gcd = *pA;
	} else {
		gcd = RMgcd(*pA, *pB);
	}
	if (gcd != 0) {
		*pA /= gcd;
		*pB /= gcd;
	}
}

/**
   fraction (aspect ratio) reduction of A/B
   A and B will be greater or equal than one
 */
static inline void RMReduceRatioNonZero(RMuint32 *pA, RMuint32 *pB)
{
	if (pA == NULL) return;
	if (pB == NULL) return;
	
	RMReduceRatio(pA, pB);
	
	if (*pA == 0) *pA = 1;
	if (*pB == 0) *pB = 1;
}

/**
   fraction (aspect ratio) reduction of A/B with value range limit
   A and B will be greater or equal than one
   A and B will be less or equal than Boundary
 */
static inline void RMReduceRatioLimited(RMuint32 *pA, RMuint32 *pB, RMuint32 Boundary)
{
	if (pA == NULL) return;
	if (pB == NULL) return;
	
	RMReduceRatioNonZero(pA, pB);
	
	if (Boundary > 0) {
		RMuint32 max;
		
		max = RMmax(*pA, *pB);
		
		if (max > Boundary) {
			RMuint32 den;
			
			// max(A,B) / Boundary, rounded up
			den = (max + Boundary - 1) / Boundary;
			
			if (den > 1) {
				*pA /= den;
				*pB /= den;
				if (*pA == 0) *pA = 1;
				if (*pB == 0) *pB = 1;
			} else {
				*pA = *pB = 1;
			}
		}
	}
}

/** Previous reduction macros, deprecated. */
#define RMreduce(x, y)  \
	RMReduceRatioNonZero(&(x), &(y))

#define RMreducelimited(x, y, boundary)  \
	RMReduceRatioLimited(&(x), &(y), boundary)

#endif /* __RMMACROS_DIVISIONS_H__ */
