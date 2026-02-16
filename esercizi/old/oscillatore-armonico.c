#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "libmz.h"

// Scrivere un programma che calcoli e salvi la posizione e la velocità di un oscillatore
// armonico semplice del tipo x(t) = Acos(omega*t + phi)
// nell'intervallo 0:T
// parametri: A, pulsazione, fasezero, T, N

int main() {
  double pulsazione, fasezero, A, T;
  
  // richiedo dati in input
  printf("Inserire ampiezza oscillazione: ");
  scanf(" %lf", &A);
  printf("Inserire pulsazione oscillazione: ");
  scanf(" %lf", &pulsazione);
  printf("Inserire fase iniziale oscillazione: ");
  scanf(" %lf", &fasezero);
  printf("Inserire T: ");
  scanf(" %lf", &T);
  int N = (int)T * 60 + 1;

  // campiono e valuto posizione e velocità
  double *t, *x, *v;
  allocarray((void**)&t, N, DOUBLE);
  checkarray((void*)t, N);
  allocarray((void**)&x, N, DOUBLE);
  checkarray((void*)x, N);
  allocarray((void**)&v, N, DOUBLE);
  checkarray((void*)v, N);
  griglia(0, T, N, t);

  for (int i=0; i<N; i++) {
    x[i] = A * cos(pulsazione * t[i] + fasezero);
    v[i] = - A * pulsazione * sin(pulsazione * t[i] + fasezero);
  }

  // scrivo su file
  FILE *dati, *plot;
  dati = fopen(".oscillatore.txt", "w");
  plot = popen("gnuplot -p", "w");
  // impostazioni plot
  fprintf(plot, "set xrange[0:%lf]\n", T);
  if (A * pulsazione > A) fprintf(plot, "set yrange[%lf:%lf]\n", -A*pulsazione, A*pulsazione);
  else fprintf(plot, "set yrange[%lf:%lf]\n", -A, A);
  fprintf(plot, "set linetype 1 linewidth 3\n");
  fprintf(plot, "set title 'Oscillatore armonico'\n");
  fprintf(plot, "set key\n");

  // plottiamo!
  // prima iterazione per fare replot
    fprintf(plot, "plot '.oscillatore.txt' using 1:2 with lines title 's(t)' lt rgb 'red', '.oscillatore.txt' using 1:3 with lines title 'v(T)'\n"); 
  for (int i=1; i<N; i++) {
    fprintf(dati, "%lf %lf %lf\n", t[i], x[i], v[i]); 
    fflush(dati);
    fprintf(plot, "replot\n"); 
    fflush(plot);
    usleep(16667);
  }
  fclose(dati); fclose(plot);
  free(t); free(x); free(v);

  return 0;
}
