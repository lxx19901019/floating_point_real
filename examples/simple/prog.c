//
// Copyright (c) 2018 Maciej Gorzkowski
//
// This file is licensed under the MIT License.
// Full license text is available in 'LICENSE'.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "real.h"

void print_real(real arg)
{
  realFields fields = real_to_realFields(arg);
  real assembled = realFields_to_real(fields);

  print_realValue(arg);
  print_realBytes(arg);
  print_realFields(fields);
  print_realValue(assembled);
}

int main()
{
  real my_key;

  while(true)
  {
    scanf("%Lf", &my_key.value);
    print_real(my_key);
    printf("\n");
    if(my_key.value == 0)
    {
      break;
    }
  }

  return 0;
}
