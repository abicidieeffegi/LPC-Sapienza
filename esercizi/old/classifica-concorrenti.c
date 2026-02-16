#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* void bubblesortold(int** array, int nrighe, int ncolonne, int colonnatosort) {
  colonnatosort--; // lo rendo human friendly
  for (int j=0; j<nrighe; j++) {
    for (int i=0; i<nrighe-1; i++) {
      if (array[i][colonnatosort] < array[i+1][colonnatosort]) {
        for (int k=0; k<ncolonne; k++) {
          int temp = array[i][k];
          array[i][k] = array[i+1][k];
          array[i+1][k] = temp;
        }
      }
    }
  }
} */

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

void stampaclassifica(int** array, int nrighe, int ncolonne) {
  printf("Classifica finale:\n");
  printf("\tID\tPunteggio\n");
  for (int i=0; i<nrighe; i++){
    printf("%d.\t", i+1);
    for (int j=0; j<ncolonne; j++) {
      printf("%d\t", array[i][j]);
    }
    printf("\n");
  }
}

void libera(int** array, int nrighe, int ncolonne) {
  for (int i=0; i<nrighe; i++) {
    free(array[i]);
  }
  free(array);
}

int main() {
  int **classifica, nconcorrenti, nprove, punteggio;
  printf("Inserire il numero di concorrenti: ");
  scanf("%d", &nconcorrenti);
  printf("Inserire il numero di prove: ");
  scanf("%d", &nprove);
  printf("------------------------------------\n");

  classifica = (int**)malloc(nconcorrenti * sizeof(int*));
  for (int i=0; i<nconcorrenti; i++) {
      classifica[i] = (int*)calloc(2, sizeof(int)); // alloco solo due colonne: ID e punteggio totale
      printf("Inserire ID concorrente: ");
      scanf(" %d", &classifica[i][0]);
    // come fare controllo su unicità ID?
    for (int j=1; j<=nprove; j++) {
      do {
      printf("Inserire punteggio del concorrente %d nella prova %d: ", classifica[i][0], j);
      scanf(" %d", &punteggio);
      } while (punteggio < 1 || punteggio > 10);
      classifica[i][1] += punteggio;
    }
  }
  bubblesort(classifica, nconcorrenti, 2, 2);
  printf("Classifica: ");
  stampaclassifica(classifica, nconcorrenti, 2);
  libera(classifica, nconcorrenti, nprove);
  return 0;
}
