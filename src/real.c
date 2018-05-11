//
// Copyright (c) 2018 Maciej Gorzkowski
//
// This file is licensed under the MIT License.
// Full license text is available in 'LICENSE'.
//

#include "../include/real.h"

#if defined(EXTENDED_PRECISION_COMPUTING)
  const int SIZE_IN_BITS = 80;
  const int EXP_BIAS = 16383;
  const int BITS_PER_SIGN = 1;
  const int BITS_PER_EXPONENT = 15;
  const int BITS_PER_MANTISSA = 64;
  const bool MANTISSA_FIRST_DIGIT_EXPLICITE = true;
#elif defined(DOUBLE_PRECISION_COMPUTING)
  const int SIZE_IN_BITS = 64;
  const int EXP_BIAS = 1023;
  const int BITS_PER_SIGN = 1;
  const int BITS_PER_EXPONENT = 11;
  const int BITS_PER_MANTISSA = 53;
  const bool MANTISSA_FIRST_DIGIT_EXPLICITE = false;
#elif defined(SINGLE_PRECISION_COMPUTING)
  const int SIZE_IN_BITS = 32;
  const int EXP_BIAS = 127;
  const int BITS_PER_SIGN = 1;
  const int BITS_PER_EXPONENT = 8;
  const int BITS_PER_MANTISSA = 24;
  const bool MANTISSA_FIRST_DIGIT_EXPLICITE = false;
#else
  #error "Declare your real type precision according to IEEE 754 standard";
#endif

// Private functions prototypes
fpUnit normalize_mantissa(uint64_t arg);
byte get_sign(real arg);
int16_t get_exponent(real arg);
uint64_t get_mantissa(real arg);

// Public functions

realFields real_to_realFields(real arg)
{
	realFields result;
	result.sign = get_sign(arg);
	result.exponent = get_exponent(arg);
	result.mantissa = get_mantissa(arg);
	return result;
}

real realFields_to_real(realFields arg)
{
  real result;
  result.value = normalize_mantissa(arg.mantissa);
  result.value = result.value * powl(2, arg.exponent);
  if(arg.sign != 0)
  {
    result.value = -result.value;
  }
  return result;
}

void print_realFields(realFields arg)
{
	char sign = arg.sign==0 ? '+' : '-';
  fpUnit norm_mantissa = normalize_mantissa(arg.mantissa);
  printf("real fields: %c %Lf * 2^(%d)\n", sign, (long double)norm_mantissa, arg.exponent);
}

void print_realBytes(real arg)
{
  printf("real bytes: ");
  for (size_t i = 0; i < sizeof(fpUnit); i++)
  {
    if(i == sizeof(fpUnit) - (SIZE_IN_BITS/8))
    {
      printf("| ");
    }
    printf("%02x ", arg.bytes[sizeof(fpUnit) - 1 - i]);
  }
  printf("\n");
}

void print_realValue(real arg)
{
  printf("real value: %Lf\n", (long double)arg.value);
}

// Private functions

fpUnit normalize_mantissa(uint64_t arg)
{
  return (fpUnit)arg / ((uint64_t)1<<(BITS_PER_MANTISSA - 1));
}

byte get_sign(real arg)
{
  return (arg.bytes[(SIZE_IN_BITS/8)-1] & (1<<7)) ? 1 : 0;
}

int16_t get_exponent(real arg)
{
  __uint128_t tmp = *((__uint128_t*)&arg);
  __uint128_t mask = ((__uint128_t)1<<(BITS_PER_EXPONENT)) - 1;
  tmp >>= MANTISSA_FIRST_DIGIT_EXPLICITE ? BITS_PER_MANTISSA : BITS_PER_MANTISSA - 1;
  tmp &= mask;
  return tmp - EXP_BIAS;
}

uint64_t get_mantissa(real arg)
{
  __uint128_t tmp = *((__uint128_t*)&arg), mask;
  if(MANTISSA_FIRST_DIGIT_EXPLICITE)
  {
    mask = ((__uint128_t)1<<(BITS_PER_MANTISSA)) - 1;
    tmp &= mask;
  }
  else
  {
    mask = ((__uint128_t)1<<(BITS_PER_MANTISSA -1 )) - 1;
    tmp &= mask;
    tmp += ((__uint128_t)1<<(BITS_PER_MANTISSA -1 )) - 1;
  }

  return (uint64_t)tmp;
}
