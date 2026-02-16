#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#define MAX 10000
// serie geometrica

double geometricaK(double q, int k) { 
  return pow(q, k);
}

double serieGeometrica(double q, double tol, double* limite, double* errore, FILE* stream) {
  double serie=0;
  if (q > 1){
    printf("La serie non converge\n");
    return 0;
  }
  *limite = 1/(1-q);
  for (int i=0; i<MAX; i++) {
    serie += geometricaK(q, i);
    *errore = fabs(serie - *limite);
    fprintf(stream, "%.15lf\t%.15lf\n", serie, *errore);
    if (*errore < tol) {
      printf("Tolleranza raggiunta\n");
      return serie;
    }
  }
  printf("Numero massimo di iterazioni raggiunto\n");
  return serie;
}

// serie di leibniz
double leibnizK(int k) {
  double result;
  if (k%2 == 0) {
    result = (double)(4)/(2*k+1);
    return result;
  }
  else {
    result = (double)(-4)/(2*k+1);
    return result;
  }
}

double serieLeibniz(double q, double tol, double* limite, double* errore, FILE* stream) {
  double serie=0;
  *limite = M_PI;
  for (int i=0; i<MAX; i++) {
    serie += leibnizK(i);
    *errore = fabs(serie - *limite);
    fprintf(stream, "%.15lf\t%.15lf\n", serie, *errore);
    if (*errore < tol) {
      printf("Tolleranza raggiunta\n");
      return serie;
    }
  }
  printf("Numero massimo di iterazioni raggiunto\n");
  return serie;
}

int main() {
  double (*serie[])(double, double, double*, double*, FILE*) = {&serieGeometrica, &serieLeibniz};
  double tol, q;
  int choice;
  printf("Opzioni disponibili:\n1. Calcolare la serie geometrica\n2. Calcolare la serie di Leibniz\n");
  do {
    printf("Inserire opzione(1-2): ");
    scanf(" %d", &choice);
  } while (choice != 1 && choice != 2);
  choice--;
  if (choice == 0) {
    printf("Inserire ragione della serie: ");
    scanf(" %lf", &q);
  }
  double limiteTeorico, limiteCalcolato, errore;
  printf("Inserire tolleranza: ");
  scanf(" %lf", &tol);
  // scrivo su file tutti i passaggi
  FILE* dump = fopen(".serie.txt", "w");
  limiteCalcolato = serie[choice](q, tol, &limiteTeorico, &errore, dump);


  printf("Il limite richiesto risulta %lf\nL'errore è di %lf rispetto al limite teorico\n", limiteCalcolato, errore);
  fclose(dump);
  // RICORDA DI CHIUDERE I FILE
  system("echo \"plot '.serie.txt' using :1 with dots, '.serie.txt' using :2 with dots\" | gnuplot -p");
  return 0;
}
