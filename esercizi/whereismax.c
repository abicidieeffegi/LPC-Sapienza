#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int whereis_max (double size, double* ptr) {
  int p=0;
  double max = fabs(ptr[0]);
  for (int i=1; i<size; i++) {
    if (fabs(ptr[i]) > max) {
      max = fabs(ptr[i]);
      p = i;
    }
  }
  return p;
}
