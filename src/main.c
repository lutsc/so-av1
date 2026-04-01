#include "library.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
  PGM pgm;
  read_pgm("input.pgm", &pgm);

  printf("Header info:\nWidth: %d\nHeight:%d\nMaxv: %d\n", pgm.w, pgm.h, pgm.maxv);
  printf("\nData:");

  for(int i = 0; i < pgm.w * pgm.h; i++)
  {
    printf("%i ", pgm.data[i]);
  }

  return 0;
}
