//
// Copyright (c) 2018 Maciej Gorzkowski
//
// This file is licensed under the MIT License.
// Full license text is available in 'LICENSE'.
//

#ifndef __REAL_H__
#define __REAL_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

// Declare your real type precision according to IEEE 754 standard
#define EXTENDED_PRECISION_COMPUTING
//#define DOUBLE_PRECISION_COMPUTING
//#define SINGLE_PRECISION_COMPUTING

#if defined(EXTENDED_PRECISION_COMPUTING)
  typedef long double fpUnit;
#elif defined(DOUBLE_PRECISION_COMPUTING)
	typedef double fpUnit;
#elif defined(SINGLE_PRECISION_COMPUTING)
	typedef float fpUnit;
#else
  #error "Declare your real type precision according to IEEE 754 standard";
#endif

typedef uint8_t byte;

extern const int SIZE_IN_BITS;
extern const int EXP_BIAS;
extern const int BITS_PER_SIGN;
extern const int BITS_PER_EXPONENT;
extern const int BITS_PER_MANTISSA;
extern const bool MANTISSA_FIRST_DIGIT_EXPLICITE;

// Size of long double type depends on declared real type precision
typedef union {
	fpUnit value;
	byte bytes[sizeof(fpUnit)];
} real;

// Floating point number has form: sign mantissa * 2^exponent
// mantissa - fix-point number with point after its fisrt binary digit, eg. 1.0110100(...)
// exponent - unbiased exponent
// sign - 0 means '+', 1 means '-'
typedef struct {
	uint64_t mantissa;
	int16_t exponent;
	byte sign;
} realFields;

realFields real_to_realFields(real arg);
real realFields_to_real(realFields arg);

void print_realFields(realFields arg);
void print_realBytes(real arg);
void print_realValue(real arg);

#endif /* __REAL_H__ */
