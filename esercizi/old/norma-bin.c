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
  dati = fopen("dati.bin", "wb");
  if (dati == NULL) {
    printf("Errore di apertura file\n");
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
  // controlla sintassi binaria
  fwrite(&norma_matrix, sizeof(norma_matrix), 1, dati);
  fwrite(&n, sizeof(n), 1, dati);
  fwrite(&m, sizeof(m), 1, dati);
  for (int i=0; i<n; i++) {
    fwrite(matrix[i], sizeof(*matrix[i]), m, dati);
  }
  fclose(dati);
  printf("Matrice scritta con successo su dati.bin.\n");

  // leggo i dati dal file
  int dimensioni[2];
  double **matrixread, normaread;
  dati = fopen("dati.bin", "rb");
  // è FONDAMENTALE sapere cosa ci sia scritto sul file binario
  fread(&normaread, sizeof(double), 1, dati);
  fread(dimensioni, sizeof(int), 2, dati);
  printf("%d %d", dimensioni[0], dimensioni[1]);
  allocamatrice(&matrixread, dimensioni[0], dimensioni[1]);
  checkallocazione(matrixread, dimensioni[0], dimensioni[1]);

  printf("La matrice letta è:\n");
  for (int i=0; i<dimensioni[0]; i++) {
    fread(matrixread[i], sizeof(double), dimensioni[1], dati);
    for (int j=0; j<dimensioni[1]; j++) {
      printf("%.2lf\t", matrixread[i][j]);
    }
    printf("\n");
  }
  printf("Con una norma pari a %.3lf\n", normaread);

  // controllo che i dati letti siano uguali a quelli scritti in precedenza
  if (n != dimensioni[0] || m != dimensioni[1] || abs(norma_matrix - normaread) != 0) {
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
