## floating_point_real

### About
Simple library providing the flexible real type in accordance with IEEE 754 standard.

It supports:
- single precision number (32 bits),
- double precision number (64 bits),
- extended precision number (80 bits).

Choose proper variable in include/real.h

Library provide:
- real type (the wrapper for float, double or long double),
- realFields type (the struct containing fields):
  - sign (byte),
  - exponent (int16_t),
  - mantissa (uint64_t),
- reading/writing byte by byte,
- printing real and realFields types.

### Run example
> cd examples/simple
make run

Type a number like '15.65' and survey the individual fields:

> ./prog.elf
15.65
real value: 15.650000
real bytes: 00 00 00 00 00 40 | 40 02 fa 66 66 66 66 66 66 66
real fields: + 1.956250 * 2^(3)
real value: 15.650000

To stop type 0.0

Have fun!
