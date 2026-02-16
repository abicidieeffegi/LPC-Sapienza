#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// volgio ordinare il libretto esami di N studenti
// ogni libretto contiene M voti
// ogni studente ha una matricola, i voti sono casuali tra 18 e 30
// classifica in base alla media (stampare)
// salvare dati su file
// visualizzare andamento voti per ogni studente

int casuale(int min, int max) {
  FILE *source = fopen("/dev/urandom", "rb");
  unsigned int random;
  fread(&random, sizeof(int), 1, source);
  random = random % (max - min + 1) + min;
  return random;
}

void ordina(double** matrix, int nrows, int ncols) {
  for (int i=0; i<nrows; i++) {
    for (int j=0; j<nrows-1; j++) {
      if (matrix[j][ncols-1] < matrix[j+1][ncols-1]) {
        double *temp = matrix[j];
        matrix[j] = matrix[j+1];
        matrix[j+1] = temp;
      }
    }
  }
  return;
}

void stampa(double** matrix, int nrows, int ncols) {
  printf("ID:\tVoti");
  for (int i=0; i<ncols-2; i++) {
    printf("\t");
  }
  printf("Media:\n");
  for (int i=0; i<nrows; i++) {
    printf("%.0lf\t", matrix[i][0]);
    for (int j=1; j<ncols; j++) {
      printf("%.0lf\t", matrix[i][j]);
    }
    printf("%.2lf\n", matrix[i][ncols-1]);
  }
}

// matrice:
// matricola  voti    media
// xxxxxxx    xx...   xx.xx
// xxxxxxx    xx...   xx.xx
// N righe, M+2 colonne

int main() {
  // richiedo input (N studenti, M esami)
  int N, M;
  printf("Inserire numero studenti: ");
  scanf(" %d", &N);
  printf("Inserire numero esami: ");
  scanf(" %d", &M);

  // alloco la matrice
  double **A; // implementare una struttura? 
  A = malloc(N * sizeof(double*));
  if (A == NULL) {
    perror("Errore allocazione memoria");
    exit(1);
  }
  for (int i=0; i<N; i++) {
    A[i] = malloc((M+2) * sizeof(double));
    if (A[i] == NULL) {
      perror("Errore allocazione memoria");
      exit(1);
    }
  }
  printf("Matrice allocata\n");

  // inizializzo la matrice.
  // cosa c'è di sbagliato?
  for (int i=0; i<N; i++) {
    A[i][0] = i+1;
    A[i][M+1] = 0;
    for (int j=1; j<M+1; j++) {
      A[i][j] = casuale(18, 30);
      A[i][M+1] = A[i][M+1] + A[i][j];
    }
    A[i][M+1] = (double)(A[i][M+1]/M);
  }
  printf("Matrice inizializzata, media calcolata\n");
  
  // riordino la matrice in base all'ultima colonna
  printf("Libretto non ordinato:\n");
  stampa(A, N, M+2);
  ordina(A, N, M+2);
  printf("Libretto ordinato:\n");
  stampa(A, N, M+2);
  
  // scrivo su file
  FILE *data = fopen(".libretto.txt", "w");
  if (data == NULL) {
    perror("Errore apertura file");
    exit(1);
  }
  
  for (int i=0; i<N; i++) {
    for (int j=0; j<M+1; j++) {
      fprintf(data, "%.2lf", A[i][j]);
    }
    fprintf(data, "\n");
  }

  // rileggo il file

  // plotto i dati

  // libero memoria

  return 0;
}
