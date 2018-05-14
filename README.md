## floating_point_real
Simple library providing the flexible real type in accordance with IEEE 754 standard

It supports:
- single precision number (32 bits)
- double precision number (64 bits)
- extended precision number (80 bits)

Choose proper variable in include/real.h

Library provide:
- real type (the wrapper for float, double or long double)
- realFields type (the struct containing fields):
  - sign (byte)
  - exponent (int16_t)
  - mantissa (uint64_t)
- reading/writing byte by byte
- printing real and realFields types
