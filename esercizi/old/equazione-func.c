#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void risolviequazione(double* a, double* b, double* c, double* x1, double* x2) {
  double delta = pow(*b, 2) - 4 * (*a) * (*c);
  if (delta < 0)
    printf("L'equazione inserita non ha soluzioni");
  else {
    *x1 = (-(*b) + delta)/(2 * (*a));
    *x2 = (-(*b) - delta)/(2 * (*a));
    printf("Ecco le soluzioni dell'equazione:\nx1 = %.2lf\nx2 = %.2lf\n", *x1, *x2);
  }
}

int main() {
  double a, b, c, x1, x2;
  printf("Inserire i coefficienti di un'equazione di secondo grado:\n");
  printf("a = ");
  scanf(" %lf", &a);
  printf("b = ");
  scanf(" %lf", &b);
  printf("c = ");
  scanf(" %lf", &c);
  risolviequazione(&a, &b, &c, &x1, &x2);
  return 0;
}
