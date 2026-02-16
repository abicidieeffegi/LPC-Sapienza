#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "libmz.h"
#define GRAV 9.807

// Scrivere un programma che simuli la caduta libera di una particella soggetta all’ac-
// celerazione di gravità g = 9.81 m/s2.
// • Leggere da tastiera l’altezza iniziale h0, la velocità iniziale v0 e il passo tempo-
// rale ∆t.
// • Calcolare le altezze della particella a ogni intervallo temporale finché la posi-
// zione non diventa minore o uguale a zero (impatto con il suolo).
// • Memorizzare le altezze in un array e stampare la tabella tempo-altezza su file.
// • Rappresentare graficamente l’andamento dell’altezza nel tempo.
//
// facciamo che è un proiettile lmao
// come bloccare il grafico quando il proiettile tocca terra?
double tempocaduta (double v, double deg, double h) {
  v = v * sin(deg);
  double tempo = (v + sqrt(pow(v, 2) + 2 * GRAV * h))/GRAV;
  return tempo;
}

int main() {
  double vzero, angolo, hzero;
  printf("Inserire velocità iniziale: ");
  scanf("%lf", &vzero);
  do {
    printf("Inserire angolo iniziale (in gradi): ");
    scanf("%lf", &angolo);
  } while (angolo > 180 || angolo < 0);
  angolo = (angolo/360) * 2 * M_PI;
  do {
    printf("Inserire altezza iniziale: ");
    scanf("%lf", &hzero);
  } while (hzero <= 0);

  // calcolo il numero di sample necessari per circa 60FPS:
  double T = tempocaduta(vzero, angolo, hzero);
  int N = T * 180 + 1;

  // campionamenti
  double *t, *x, *y;
  t = malloc(N * sizeof(*t));
  x = malloc(N * sizeof(*x));
  y = malloc(N * sizeof(*y));
  if (t == NULL || x == NULL || y == NULL) {
    perror("Errore allocazione memoria");
    exit(1); // che differenza fa tra return 1 e exit 1?
  }
  for (int i=0; i<N; i++) {
    t[i] = i * T/(N-1);  
    x[i] = vzero * cos(angolo) * t[i];
    y[i] = hzero + vzero * sin(angolo) * t[i] - (1.0/2.0) * GRAV * pow(t[i], 2);
  }
  // trovo l'altezza massima
  double hmax = hzero;
  for (int i=1; i<N; i++) {
    if (y[i] > y[i-1]) {
      hmax = y[i];
    }
    else break;
  }

  FILE *dump, *plot;
  // plottiamo!
  dump = fopen(".caduta-libera.txt", "w");
  plot = popen("gnuplot -p", "w");
  fflush(dump); // se io flusho il buffer (anche se vuoto??) crea il file?
  // impostazioni grafico
  fprintf(plot, "set xrange [0:%lf]\n", x[N-1]);
  fprintf(plot, "set xlabel 'X(t)'\n");
  fprintf(plot, "set yrange [0:%lf]\n", hmax);
  fprintf(plot, "set ylabel 'Y(t)'\n");
  fprintf(plot, "set key\n");
  fprintf(plot, "set lt 1 linewidth 3 linecolor rgb 'red'\n");
  fprintf(plot, "plot '.caduta-libera.txt' using 2:3 with lines title 'Traiettoria'\n");
  for (int i=0; i<N; i++) {
    fprintf(dump, "%lf %lf %lf\n", t[i], x[i], y[i]);
    fflush(dump);
    fprintf(plot, "replot\n");
    fflush(plot);
    usleep(16667);
    // usleep(16667 * 2);
  }
  fclose(dump); fclose(plot);
  free(x); free(y); free(t);

  return 0;
}
