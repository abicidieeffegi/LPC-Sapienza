#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
// metodo del punto fisso per stima di sqrt(2)

double f(double x) { // funzione di cui vogliamo stimare lo zero
  return exp(x) * (x*x - 2);
}

double g(double x) { // funzione per iterare il punto fisso
  double lambda = -0.04;
  return x + (lambda * f(x));
}

void puntoFisso(double* xzero, double tol, int iterMax) {
  double x, distanzaIterate;
  for (int i=0; i<iterMax; i++) {
    x = g(*xzero);
    distanzaIterate = fabs(x - *xzero);
    *xzero = x;
    if (distanzaIterate <= tol) {
      printf("Soluzione trovata dopo %d iterazioni per distanza iterate\n", i+1);
      return;
    }
  }
  printf("Numero massimo di iterazioni raggiunto\n");

  return;
}

int main() {
  double partenza, tolleranza;
  int iterMax;
  printf("Inserire il punto di partenza: ");
  scanf(" %lf", &partenza);
  printf("Inserire tolleranza: ");
  scanf(" %lf", &tolleranza);
  printf("Inserire numero massimo di iterazioni: ");
  scanf(" %d", &iterMax);

  puntoFisso(&partenza, tolleranza, iterMax);
  printf("La soluzione trovata è %lf\n", partenza);
  return 0;
}
