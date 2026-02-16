#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

void griglia(double a, double b, int N, double *x) {
  for (int i=0; i<N; i++) {
    x[i] = a + i*(b-a)/N;
  }
}

void campionamento_sin(double *x, int N, double* y) {
  for (int i=0; i<N; i++) {
    y[i] = sin(x[i]);
  }
}

void campionamento_cos(double *x, int N, double* y) {
  for (int i=0; i<N; i++) {
    y[i] = cos(x[i]);
  }
}

int main() {
  double a, b, *campioni, *seno, *coseno;
  int N;
  FILE *plot;
  plot = popen("gnuplot -p", "w");
  if (plot == NULL) {
    perror("Errore apertura pipe");
    return 1;
  }

  printf("Inserire estremi intervallo [a, b]: ");
  scanf(" %lf %lf", &a, &b);

  printf("Quanti punti vuoi campionare? ");
  scanf(" %d", &N);

  campioni = malloc(N * sizeof(*campioni));
  seno = malloc(N * sizeof(*seno));
  coseno = malloc(N * sizeof(*coseno));

  griglia(a, b, N, campioni);
  campionamento_sin(campioni, N, seno);
  campionamento_cos(campioni, N, coseno);
  fprintf(plot, "set xrange[%lf:%lf]\n", a, b);
  fprintf(plot, "set yrange[-1:1]\n", a, b);
  for (int i=1; i<N; i++) {
    fprintf(plot, "plot '-' with lines, '-' with lines\n");

    for (int j=0; j<i; j++) {
      fprintf(plot, "%lf %lf\n", campioni[j], seno[j]);
    }
    fprintf(plot, "e\n");

    for (int j=0; j<i; j++) {
      fprintf(plot, "%lf %lf\n", campioni[j], coseno[j]);
    }
    fprintf(plot, "e\n");

    fprintf(plot, "pause 0.1\n");
    fflush(plot);
  }
  fclose(plot);
  free(campioni); free(seno); free(coseno);

  return 0;
}
