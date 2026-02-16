#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// #include "libmz.h" come cazzo si fa mannaggia ai santi
void allocamatrice(double*** matrix, int n, int m) {
  *matrix = malloc(n * sizeof(**matrix));
  for (int i=0; i<n; i++) {
    (*matrix)[i] = malloc(m * sizeof(*matrix[i]));
  }
}
void checkallocazione(double** matrix, int n, int m) {
  if (matrix == NULL) {
    printf("Errore allocazione memoria 1\n");
    exit(1);
  }
  for (int i=0; i<n; i++) {
    if (matrix[i] == NULL) {
      printf("Errore allocazione memoria 2.%d\n", i+1);
      exit(1);
    }
  }
}

void norma_frobenius(double** matrix, int n, int m, double* output) {
  *output = 0;
  for (int i=0; i<n; i++) {
    for (int j=0; j<m; j++) {
      *output += pow(matrix[i][j], 2);
    }
  }
  *output = sqrt(*output);
}

int main() {
  double **matrix, norma_matrix;
  FILE *dati;
  dati = fopen("dati.txt", "w");
  if (dati == NULL) {
    printf("Errore di allocazione file\n");
    return 1;
  }
  int n, m;
  printf("Inserire numero di righe della matrice: ");
  scanf("%d", &n);
  printf("Inserire numero di colonne della matrice: ");
  scanf("%d", &m);

  allocamatrice((&matrix), n, m);
  checkallocazione(matrix, n, m);
  
  // inizializzo come da esercizio
  for (int i=0; i<n; i++) {
    for (int j=0; j<m; j++) {
      matrix[i][j] = (double)(i+j)/(n*m);
    }
  }

  norma_frobenius(matrix, n, m, &norma_matrix);

  // stampo la matrice (debugging)
  for (int i=0; i<n; i++) {
    for(int j=0; j<m; j++) {
      printf("%.2lf\t", matrix[i][j]);
    }
    printf("\n");
  }

  printf("La norma di Frobenius della matrice è %.3lf\n", norma_matrix);

  // scrivo i dati su file
  fprintf(dati, "%d %d %lf\n", n, m, norma_frobenius);
  for (int i=0; i<n; i++) {
    for (int j=0; j<m; j++) {
      fprintf(dati, "%.5lf\t", matrix[i][j]);
    }
    fprintf(dati, "\n");
  }
  fclose(dati);

  // leggo i dati dal file
  int nread, mread;
  double **matrixread, normaread;
  dati = fopen("dati.txt", "r");
  fscanf(dati, "%d %d %lf", &nread, &mread, &normaread);
  allocamatrice(&matrixread, nread, mread);
  checkallocazione(matrixread, nread, mread);

  printf("La matrice letta è:\n");
  for (int i=0; i<nread; i++) {
    for (int j=0; j<mread; j++) {
      fscanf(dati, "%lf\t", &matrixread[i][j]);
      printf("%.2lf\t", matrixread[i][j]);
    }
    printf("\n");
  }
  printf("Con una norma pari a %.3lf\n", normaread);

  // controllo che i dati letti siano uguali a quelli scritti in precedenza
  if (n != nread || m != mread || abs(norma_matrix - normaread) != 0) {
    printf("Dati non corrispondenti\n");
    return 1;
  }
  for (int i=0; i<n; i++) {
    for (int j=0; j<m; j++) {
      if (abs(matrix[i][j] - matrixread[i][j]) != 0) {
        printf("Dati non corrispondenti\n");
        return 1;
      }
    }
  }
  // libero memoria
  fclose(dati);
  for (int i=0; i<n; i++) {
    free(matrix[i]);
    free(matrixread[i]);
  }
  free(matrix);
  free(matrixread);
  printf("Scrittura e lettura avvenute con successo\n");

  return 0;
}
