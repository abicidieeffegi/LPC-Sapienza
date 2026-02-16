#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void valuta_polinomio(double* pol, double x, int deg, double* out) {
  for (int i=0; i<deg; i++) {
    // valuto ogni termine singolarmente e li sommo
  *out += pol[i] * pow(x, i);
  }
}

void valuta_horner(double* pol, double x, int deg, double* out) {
  *out = pol[deg-1];
  for (int i=deg-2; i>=0; i--) {
    *out = pol[i] + (x * *out);
  }
}

int main() {
  // dichiaro tutto il necessario e richiedo dati in input
  unsigned int deg;
  double x;
  printf("Inserire grado del polinomio: ");
  scanf(" %d", &deg);
  printf("In che x vuoi valutare il polinomio? ");
  scanf(" %lf", &x);
  deg++; // i coefficienti sono uno in più del grado
  double* p = malloc(deg * sizeof(*p));
  // richideo coefficienti in input
  for (int i=0; i<deg; i++) {
    printf("Inserire coefficiente a%d ", i);
    scanf(" %lf", &p[i]);
    // if (i%2 == 0) {
    //   p[i] = 1;
    // }
    // else p[i] = -1;
  }
  // valuto il polinomio in x
  double out, out_h;
  valuta_polinomio(p, x, deg, &out);
  valuta_horner(p, x, deg, &out_h);

  printf("Il polinomio valutato tradizionalmente vale p(%.2lf) = %lf\n", x, out);
  printf("Il polinomio valutato con lo schema di Horner vale p(%.2lf) = %lf\n", x, out_h);
  printf("La differenza tra i due metodi vale %lf\n", fabs(out - out_h));

  // libero memoria
  free(p);

  return 0;
}
