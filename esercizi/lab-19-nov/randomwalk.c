#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "libmz.h"
#define SAMPLE 50000

int coinflip() {
  int lancio = rand()%2;
  if (lancio == 0) lancio--;
  return lancio;
}

int comp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
  srand(time(NULL));
  // dichiaro e inizializzo array
  int walk[SAMPLE];
  for (int i=0; i<SAMPLE; i++) {
    walk[i] = 0;
  }

  // chiedo all'utente il numero di passeggiate da fare
  unsigned int N, flag;
  printf("Quanti passi vuoi fare? ");
  scanf(" %d", &N);
  // trova un modo per predire più accuratamente il tempo
  printf("Opzioni disponibili:\n1. Visualizzare animazione (almeno %d s) e grafico\n2. Visualizzare grafico finale\n", (16666 * N) / 500000000);
  do {
    printf("Scegliere opzione (1-2): ");
    scanf(" %d", &flag);
  } while (flag != 1 && flag != 2);

  FILE *dump = fopen(".walk.txt", "w");
  if (dump == NULL) {
    perror("Errore apertura dump");
    exit(1);
  }
  printf("Dump aperto correttamente\n");
  // apro un file per dumpare i dati e la pipe per il plot
  // tenta implementazione 2d
  if (flag == 1) {
    // scrivo posizioni iniziali 
    // 0 0 0... 0
    for (int i=0; i<SAMPLE; i++) {
      fprintf(dump, "%d\n", walk[i]);
    }
    fflush(dump);

    FILE *plot = popen("gnuplot -p", "w");
    if (plot == NULL) {
      perror("Errore apertura plot");
      exit(1);
    }
    printf("Pipe aperta correttamente\n");

    // plot settings
    int range = N/5;
    fprintf(plot, "set xrange[0:%d]\n", SAMPLE);
    fprintf(plot, "set yrange[%d:%d]\n", -range, range);
    fprintf(plot, "plot '.walk.txt' using :1 with dots\n");
    fflush(plot);

    // faccio camminare, plottando la camminata
    for (int i=0; i<N; i++) {
      for (int j=0; j<SAMPLE; j++) {
        walk[j] += coinflip();
      }
      if (i%50 == 0) { // mostro un passo ogni 50 per velocizzare l'animazione
        freopen(".walk.txt", "w", dump);
        for (int j=0; j<SAMPLE; j++) {
          fprintf(dump, "%d\n", walk[j]);
        }
        fflush(dump);
        fprintf(plot, "replot\n"); fflush(plot);
        usleep(16666);
      }
    }
    printf("Animazione completata con successo!\n");
    fclose(plot);
  }
  else {
    // faccio camminare comunque
    for (int i=0; i<N; i++) {
      for (int i=0; i<SAMPLE; i++) {
        walk[i] += coinflip();
      }
    }
  }


  // metto in ordine
  // printf("Ordinando dati...\n");
  // for (int i=0; i<SAMPLE; i++) {
  //   for (int j=0; j<SAMPLE-1; j++) {
  //     if (walk[j] > walk[j+1]) {
  //       int temp = walk[j+1];
  //       walk[j+1] = walk[j];
  //       walk[j] = temp;
  //     }
  //   }
  // }
  qsort(walk, SAMPLE, sizeof(walk[0]), comp);
  printf("Dati ordinati con successo\n");

  // conto i numeri diversi 
  printf("Contando posizioni finali...\n");
  unsigned int size = 1;
  for (int i=1; i<SAMPLE; i++) {
    if (walk[i] != walk[i-1]) {
      size++;
    }
  }
  printf("%d posizioni finali diverse trovate\n", size);

  int **gauss;
  gauss = malloc(size * sizeof(*gauss));
  if (gauss == NULL) {
    perror("Errore allocazione memoria");
    exit(1);
  }
  for (int i=0; i<size; i++) {
    gauss[i] = calloc(2, sizeof(**gauss));
    if (gauss[i] == NULL) {
      perror("Errore allocazione memoria");
      exit(1);
    }
  }

  // conto le occorrenze di ogni posizione finale
  // prendo una flag, la comparo appena cambia il numero
  flag = walk[0];
  int k=0;
  for (int i=0; i<SAMPLE; i++) {
    gauss[k][0] = walk[i];
    gauss[k][1]++;
    if (walk[i] != walk[i+1]) { // perche funziona? non dovrebbe dare segfault?
      k++;
    }
  }

  // scrivo su file e plotto usando system
  freopen(".walk.txt", "w", dump);
  for (int i=0; i<size; i++) {
    fprintf(dump, "%d\t%d\n", gauss[i][0], gauss[i][1]);
    free(gauss[i]);
  }
  free(gauss);
  fflush(dump); fclose(dump);

  system("echo \"plot '.walk.txt' using 1:2 lt rgb 'red'\" | gnuplot -p");

  return 0;
}
