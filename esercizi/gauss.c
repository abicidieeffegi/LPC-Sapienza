#include "libmz.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
// questa variabile globale mi serve per il pivoting
int counter=0;

void printMatrix(double** matrix, size_t n) {
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      printf("%.2lf\t", matrix[i][j]);
    }
    printf("\n");
  }
  return;
}

void printVector(double* vector, size_t n) {
  for (int i=0; i<n; i++) {
    printf("%.9lf\n", vector[i]);
  }
  return;
}

void multiplication(double** matrix, double* vector, double* result, size_t n) {
  for (int i=0; i<n; i++) {
    result[i] = 0;
    for (int j=0; j<n; j++) {
      result[i] += matrix[i][j]*vector[j];
    }
  }
  return;
}

int compare(const void* a, const void* b) {
  return ((*(double**)a)[counter] - (*(double**)b)[counter] > 0) ? 1 : -1;
}

void hilbertMatrix (double** matrix, size_t n) {
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      matrix[i][j] = 1.0/(i+j+1); // immagina cannare ancora la divizione intera
    }
  }
  return;
}

void gaussElimination (double** A, double* x, double* b, int n) {
  // alloco la matrice completa del sistema
  double **Ab;
  Ab = malloc(n * sizeof(*Ab));
  checkPtr((void*)Ab);
  for (int i=0; i<n; i++) {
    Ab[i] = malloc((n+1) * sizeof(**Ab));
    checkPtr((void*)Ab[i]);
    for (int j=0; j<n; j++) {
      Ab[i][j] = A[i][j];
    }
    Ab[i][n] = b[i];
  }
  int k=0;
  do {
    // pivoting: mi aiuto con la funzione qsort di stdlib
    qsort(&Ab[k], n-k-1, sizeof(*Ab), compare);
    // riduzione a scala
    for (int i=k+1; i<n; i++) {
      double mlt = Ab[i][k]/Ab[k][k];
      for (int j=0; j<n+1; j++) {
        Ab[i][j] -= mlt * Ab[k][j];
      }
    }
    // aggiorno i contatori
    k++;
    counter = k;
  } while (k<n);
  // aggiorno la matrice A e il vettore b se servissero ridotti
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      A[i][j] = Ab[i][j];
    }
    b[i] = Ab[i][n];
  }

  // libero memoria
  for (int i=0; i<n; i++) {
    free(Ab[i]);
  }
  free(Ab);
  return;
}

void solveUpper (double** A, double* x, double* b, size_t n) {
  // calcolo l'ultima incognita
  x[n-1] = b[n-1]/A[n-1][n-1];
  // a risalire, calcolo le altre incognite
  for (int i=n-2; i>-1; i--) {
    double tmp = 0;
    for (int j=i+1; j<n; j++) {
      tmp += A[i][j] * x[j];
    }
    x[i] = (b[i] - tmp)/A[i][i];
  }
  return;
}

void gSolve (double** A, double* x, double* b, size_t n) {
  printf("Inizializzando riduzione a scala...\n");
  gaussElimination(A, x, b, n);
  printf("Inizializzando risoluzione sistema...\n");
  solveUpper(A, x, b, n);
  return;
}

int main() {
  srand(time(NULL));
  // dichiaro variabili
  double **A, *b, *x, *r;
  int n;
  getData("Inserire taglia sistema: ", &n, INT);
  // alloco il sistema
  A = malloc(n * sizeof(*A));
  x = malloc(n * sizeof(*x));
  b = malloc(n * sizeof(*b));
  r = malloc(n * sizeof(*r));
  // controllo puntatori
  printf("Controllo puntatori in corso...\n");
  checkPtr((void*)A);
  checkPtr((void*)x);
  checkPtr((void*)b);
  for (int i=0; i<n; i++) {
    // alloco righe
    A[i] = malloc(n * sizeof(**A));
    checkPtr((void*)A[i]);
    // i termini noti sono tutti 1
    b[i] = 1;
  }
  printf("Controllo puntatori completato...\n");
  // inizializzo matrice di hilbert
  printf("Generando matrice di Hilbert\n");
  hilbertMatrix(A, n);
  printf("Matrice di Hilbert generata con successo!\n");

  // risolvo il sistema
  gSolve(A, x, b, n);

  printf("Soluzione trovata con un residuo di:\n");
  multiplication(A, x, r, n);
  double max = fabs(r[0] - b[0]);
  for (int i=0; i<n; i++) {
    if (fabs(r[i] - b[i]) > max) 
      max = fabs(r[i] - b[i]);
  }
  printf("%.9lf\n", max);

  // libero memoria
  printf("Liberando memoria...");
  for (int i=0; i<n; i++) {
    free(A[i]);
  }
  free(A); free(x); free(b); free(r);
  printf("Memoria liberata con successo\n");

  printf("Esecuzione completata con successo.\n");
  return 0;
}
