#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

int main() {
  srand(time(NULL));
  // due numeri X e Y
  double **punti;
  // chiedo all'utente quante volte reiterare
  unsigned int sample;
  char flag;
  printf("Quanti punti vuoi inserire? ");
  scanf(" %d", &sample);
  do {
    printf("Vuoi visualizzare l'animazione? ");
    scanf(" %c", &flag);
  } while (flag != 'y' && flag != 'Y' && flag != 'n' && flag != 'N');
  punti = malloc(sample * sizeof(*punti));
  if (punti == NULL) {
    perror("Errore allocazione memoria");
    exit(1);
  }
  for (int i=0; i<sample; i++) {
    punti[i] = malloc(2 * sizeof(**punti));
    if (punti[i] == NULL) {
      perror("Errore allocazione memoria");
      exit(1);
    }
  }
  // sparo una posizione a caso
  // apro un dump per le posizioni
  unsigned long long int k=0;
  if (flag == 'y' || flag == 'Y') {
    FILE *dump = fopen(".pi.txt", "w"); fflush(dump);
    FILE *plot = popen("gnuplot -p", "w");
    if (dump == NULL || plot == NULL) {
      perror("Errore apertura file");
      exit(1);
    }
    // plot settings
    // perchè non plotta il cerchio?
    fprintf(plot, "set xrange[0:1]\n");
    fprintf(plot, "set yrange[0:1]\n");
    fprintf(plot, "set size square\n");
    fprintf(plot, "plot sqrt(1-x**2), '.pi.txt' using 1:2 with dots\n");
    fflush(plot);
    // plot animato, conto quanti entrano nel cerchio
    for (int i=0; i<sample; i++) {
      punti[i][0] = (double)rand()/RAND_MAX;
      punti[i][1] = (double)rand()/RAND_MAX;
      fprintf(dump, "%lf\t%lf\n", punti[i][0], punti[i][1]); fflush(dump);
      if (pow(punti[i][0], 2) + pow(punti[i][1], 2) <= 1)
        k++;
      if (i%10 == 0) {
        fprintf(plot, "replot\n"); fflush(plot);
        usleep(16666);
      }
    }
  }
  else {
    for (int i=0; i<sample; i++) {
      punti[i][0] = (double)rand()/RAND_MAX;
      punti[i][1] = (double)rand()/RAND_MAX;
      if (pow(punti[i][0], 2) + pow(punti[i][1], 2) <= 1)
        k++;
    }
  }

  // stampo a video il valore stimato di pi
  printf("Secondo questa simulazione, il valore di PI è:\n%lf\n", (double)(k*4)/sample);
  
  // libero memoria
  for (int i=0; i<sample; i++)
    free(punti[i]);
  free(punti);

  return 0;
}
