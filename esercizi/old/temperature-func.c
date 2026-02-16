#include <stdio.h>
#include <stdlib.h>

void ctof(double* temperatura, char* misura) {
  *temperatura = 32 + (9.0/5.0) * (*temperatura);
  *misura = 'F';
}

void ftoc(double* temperatura, char* misura) {
  *temperatura = (5.0/9.0) * (*temperatura - 32);
  *misura = 'C';
}

int main() {
  double tuser;
  char unit;
  do {
    printf("Inserire la temperatura da convertire: ");
    scanf(" %lf%c", &tuser, &unit);
  } while (unit != 'F' && unit != 'f' && unit != 'C' &&  unit != 'c');
  if (unit == 'F' || unit == 'f')
    ftoc(&tuser, &unit);
  else if (unit == 'C' || unit == 'c')
    ctof(&tuser, &unit);
  printf("La temperatura converita vale %.2lf %c\n", tuser, unit);
  return 0;
}
