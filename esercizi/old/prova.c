#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libmz.h"
#define SAMPLE 10000

int main() {
  int **array, n, m;
  n = 10;
  m = 5;
  allocamatrix((void***)&array, n, m, INT);
  return 0;
}
