#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "libmz.h"

// usare 10 punti per unità?
int main() {
  double vzero, a, tempo;
  printf("Inserire velocità iniziale: ");
  scanf("%lf", &vzero);
  printf("Inserire accelerazione: ");
  scanf("%lf", &a);
  printf("Inserire tempo totale: ");
  scanf("%lf", &tempo);
  int samples = (int)tempo*10;
  FILE *fbin, *ftxt;
  // fbin = fopen("dati.bin", "wb"); tentare implementazione in un secondo momento
  ftxt = fopen("dati.txt", "w");
  if (ftxt == NULL) {
    perror("Errore apertura file");
    return 1;
  }

  double *t, *v, *s;
  allocarray((void**)&t, samples, DOUBLE);
  allocarray((void**)&v, samples, DOUBLE);
  allocarray((void**)&s, samples, DOUBLE);
  for (int i=0; i<=samples; i++) {
    t[i] = i * (tempo/samples);
    v[i] = vzero + a*t[i];
    s[i] = vzero*t[i] + (1.0/2.0)*a*pow(t[i], 2);
    fprintf(ftxt, "%.12lf\t%.12lf\t%.12lf\n", t[i], v[i], s[i]);
  }
  fclose(ftxt);
  printf("Dati scritti con successo\n");
  
  FILE *plotpipe = popen("gnuplot -p", "w");
  if (plotpipe == NULL) {
    perror("Errore di apertura pipe");
    return 1;
  }
  fprintf(plotpipe, "plot 'dati.txt' using 1:2, 'dati.txt' using 1:3\n");
  int i=1;
  // rendiamolo animato perché sì
  while (1) {
    fprintf(plotpipe, "set linetype 1 pointtype %d\n", i);
    fprintf(plotpipe, "set linetype 2 pointtype %d\n", i);
    fprintf(plotpipe, "replot\n");
    fflush(plotpipe);
    usleep(1000000);
    i = (i+1)%78 + 1;
  }
    fclose(plotpipe);

  return 0;
}
