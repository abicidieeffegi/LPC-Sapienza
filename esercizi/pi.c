#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "libmz.h"

double piMonteCarlo(int iterations) {
  int in=0;
  double xRand, yRand, result=0;
  // apro i file e intesto le colonne
  FILE* datiIn = fopen("in.txt", "w"); checkPtr((void*)datiIn);
  FILE* datiOut = fopen("out.txt", "w"); checkPtr((void*)datiOut);
  fprintf(datiIn, "xIn\tyIn\n");
  fprintf(datiOut, "xOut\tyOut\n");
  // apro una pipe
  FILE* plot = popen("gnuplot -p", "w");
  // plot settings
  // fprintf(plot, "set terminal pngcairo\n");
  fprintf(plot, "set parametric\n");
  fprintf(plot, "set trange[0:%lf]\n", 2*M_PI);
  fprintf(plot, "set xrange[-1:1]\n");
  fprintf(plot, "set yrange[-1:1]\n");
  fprintf(plot, "set size square\n");
  fflush(plot);
  // montecarlo
  for (int i=0; i<iterations; i++) {
    // fprintf(plot, "set output '%d.png'\n", i+1);
    fprintf(plot, "set title 'PI = %lf'\n", result);
    fprintf(plot, "plot cos(t),sin(t) t 'Circonferenza goniometrica' lt rgb 'black', 'in.txt' u (column('xIn')):(column('yIn')) t 'IN' w p pt '*' lt rgb '#08FF1A', 'out.txt' u (column('xOut')):(column('yOut')) t 'OUT' w p pt 'x' lt rgb 'red'\n");
    xRand = -1 + 2*((double)rand()/RAND_MAX);
    yRand=-1 + 2*((double)rand()/RAND_MAX);
    if ((pow(xRand, 2) + pow(yRand, 2)) <= 1) {
      fprintf(datiIn, "%.9lf\t%.9lf\n", xRand, yRand);
      fflush(datiIn);
      in++;
    }
    else {
      fprintf(datiOut, "%.9lf\t%.9lf\n", xRand, yRand);
      fflush(datiOut);
    }
    // fprintf(plot, "replot\n"); fflush(plot);
    fflush(plot);
    result = (double)(in*4)/(i+1);
    usleep(20000);
  }
  fclose(datiIn); fclose(datiOut); fclose(plot);
  return result;
}

int main() {
  srand(time(NULL));
  double a = -1;
  double b = 1;
  int M;
  getData("Inserire numero di sample desiderato: ", &M, INT);
  printf("Inizializzando simulazione...\n");
  double result = piMonteCarlo(M);
  printf("Simulazione conclusa correttamente.\n");
  printf("PI = %lf\n", result);
  
  return 0;
}
