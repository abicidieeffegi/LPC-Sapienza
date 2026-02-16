#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include "libmz.h"
#define SAMPLE 50000
// quanti sample sono il numero "giusto"?
// come plottare distribuzione normale in 3d

int coinflip() {
  int lancio = rand()%2;
  if (lancio == 0) lancio--;
  return lancio;
}

int compare ( const void *pa, const void *pb ) {
    const int *a = pa;
    const int *b = pb;
    if(a[0] == b[0])
        return a[1] - b[1];
    else
        return a[0] - b[0];
}

// scambio i puntatori invece dei valori
void bubblesort(int** array, int nrighe, int ncolonne, int colonnatosort) {
  colonnatosort--; // lo rendo human friendly
  for (int j=0; j<nrighe; j++) {
    for (int i=0; i<nrighe-1; i++) {
      if (array[i][colonnatosort] < array[i+1][colonnatosort]) {
        int* temp = array[i];
        array[i] = array[i+1];
        array[i+1] = temp;
      }
    }
  }
}

int main() {
  srand(time(NULL));
  // dichiaro e inizializzo array
  int** posizioni;
  posizioni = malloc(SAMPLE * sizeof(*posizioni));
  for (int i=0; i<SAMPLE; i++) {
    posizioni[i] = calloc(2, sizeof(**posizioni));
  }

  // chiedo all'utente il numero di passeggiate da fare
  unsigned int N, flag;
  printf("Quanti passi vuoi fare? ");
  scanf(" %d", &N);
  // trova un modo per predire più accuratamente il tempo
  printf("Opzioni disponibili:\n1. Visualizzare animazione (almeno %d s) e grafico\n2. Visualizzare grafico finale\n", (16666 * N) / 10000000);
  do {
    printf("Scegliere opzione (1-2): ");
    scanf(" %d", &flag);
  } while (flag != 1 && flag != 2);

  // apro un file per dumpare i dati e la pipe per il plot
  FILE *dump = fopen(".walk2d.txt", "w");
  if (dump == NULL) {
    perror("Errore apertura dump");
    exit(1);
  }
  printf("Dump aperto correttamente\n");
  // scrivo posizioni iniziali 
  for (int i=0; i<SAMPLE; i++) {
    fprintf(dump, "%d\t%d\n", posizioni[i][0], posizioni[i][1]);
  }
  fflush(dump);

  if (flag == 1) {
    FILE *plot = popen("gnuplot -p", "w");
    if (plot == NULL) {
      perror("Errore apertura plot");
      exit(1);
    }
    printf("Pipe aperta correttamente\n");
    // plot settings:
    int range = N/5;
    fprintf(plot, "set xrange[%d:%d]\n", -range, range);
    fprintf(plot, "set yrange[%d:%d]\n", -range, range);
    fprintf(plot, "set size square\n");
    fprintf(plot, "plot '.walk2d.txt' using 1:2 with dots lt rgb 'red'\n"); fflush(plot);

    // faccio camminare, plottando la camminata
    for (int i=0; i<N; i++) {
      for (int j=0; j<SAMPLE; j++) {
        if (rand() % 2 == 0)
          posizioni[j][0] += coinflip();
        else 
          posizioni[j][1] += coinflip();
      }
      // questi sono i comandi per animare
      if (i%50 == 0) {
        freopen(".walk2d.txt", "w", dump);
        for (int j=0; j<SAMPLE; j++) {
          fprintf(dump, "%d\t%d\n", posizioni[j][0], posizioni[j][1]);
        }
        fflush(dump);
        fprintf(plot, "replot\n"); fflush(plot);
        usleep(16666);
      }
    }
    printf("Passeggiata completata\n");
    printf("Animazione completata con successo!\n");
    fclose(plot);
  }
  else {
    // faccio camminare comunque
    for (int i=0; i<N; i++) {
      for (int j=0; j<SAMPLE; j++) {
        if (rand() % 2 == 0)
          posizioni[j][0] += coinflip();
        else 
          posizioni[j][1] += coinflip();
      }
    }
    printf("Passeggiata completata\n");
  }

  printf("Ordinando posizioni\n");
  bubblesort(posizioni, SAMPLE, 2, 1);

  return 0;
}
