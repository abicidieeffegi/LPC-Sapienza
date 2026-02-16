// metodo di bisezione per approssimare sqrt(2)
// ovvero trovare lo zero di f(x) = x^2 - 2

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// dichiaro la mia funzione
double f(double x) {
  return pow(x, 2) - 2;
}

void bisezione(double a, double b, double epsilon, int k, double* risultato) {
  if (f(a) * f(b) > 0) {
    printf("Errore. Nessuna soluzione trovata nell'intervallo\n");
    return;
  }
  for (int i=1; i<=k; i++) {
    *risultato = (a+b)/2;
    if (fabs(f(*risultato)) <= epsilon) {
      printf("Soluzione trovata dopo %d iterazioni per arresto sul residuo.\n", i);
      return;
    } 
    if (fabs(b-a) <= epsilon * fabs(*risultato)) {
      printf("Soluzione trovata dopo %d iterazioni per arresto sull'ampiezza\n", i);
      return;
    }
    if (f(a) * f(*risultato) < 0) b = *risultato;
    else a = *risultato;
  }
  printf("Numero massimo di iterazioni raggiunto\n");
  
  return;
}

int main() {
  double a, b, tolleranza, result;
  unsigned int iterazioniMax;
  printf("Inserire estremi intervallo [a, b]: ");
  scanf(" %lf %lf", &a, &b);
  printf("Inserire tolleranza: ");
  scanf(" %lf", &tolleranza);
  printf("Inserire numero massimo di iterazioni: ");
  scanf(" %d", &iterazioniMax);

  bisezione(a, b, tolleranza, iterazioniMax, &result); // come dare puntatore a funzione?

  printf("La soluzione trovata vale %.15lf\n", result);
  printf("Il residuo vale %.15lf\n", fabs(f(result)));

  return 0;
}
