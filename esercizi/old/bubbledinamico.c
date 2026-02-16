#include <stdio.h>
#include <stdlib.h>

void bubblesort(int** array, int nrighe, int ncolonne, int colonnatosort) {
  colonnatosort--; // lo rendo human friendly
  for (int j=0; j<nrighe; j++) {
    for (int i=0; i<nrighe-1; i++) {
      if (array[i][colonnatosort] > array[i+1][colonnatosort]) {
        for (int k=0; k<ncolonne; k++) {
          int temp = array[i][k];
          array[i][k] = array[i+1][k];
          array[i+1][k] = temp;
        }
      }
    }
  }
}
void stampamatrice(int** array, int nrighe, int ncolonne) {
  // si potrebbero omettere nrighe e ncolonne facendo qualche magheggio con sizeof
  for (int i=0; i<nrighe; i++){
    for (int j=0; j<ncolonne; j++) {
      printf("%d\t", array[i][j]);
    }
    printf("\n");
  }
}

int main() {
  int **lista, n, m, daordinare;
  scanf(" %d %d %d", &n, &m, &daordinare);
  lista = (int**)malloc(n * sizeof(int*));
  for (int i=0; i<n; i++) {
    lista[i] = (int*)calloc(m, sizeof(int));
  }
  for (int i=0; i<n; i++) {
    for (int j=0; j<m; j++) {
      lista[i][j] = rand() % 50;
    }
  }
  printf("La lista disordinata:\n");
  stampamatrice(lista, n, m);
  bubblesort(lista, n, m, daordinare);
  printf("La lista ordinata:\n");
  stampamatrice(lista, n, m);
  printf("\n");
  for (int i=0; i<n; i++) {
    free(lista[i]);
  }
  free(lista);
  return 0;
}

// come implementare su array e scegliere su che colonna ordinare?
