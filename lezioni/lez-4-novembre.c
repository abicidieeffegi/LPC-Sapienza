#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "fnbymz.h"
// la libreria va linkata al compilatore

// "out-of-place"
void sort_array(int* array, int size, int *sortedarray, int ordine) {
  for (int i=0; i<size; i++) {
    sortedarray[i] = array[i];
  }
  // voglio che la funzione non sovrascriva il vettore in ingresso
  for (int i=0; i<size; i++) {
    for (int j=0; j<size-1; j++) {
      if (ordine * sortedarray[j] > ordine * sortedarray[j+1]) {
        int temp = sortedarray[j];
        sortedarray[j] = sortedarray[j+1];
        sortedarray[j+1] = temp;
      }
    }
  }
}

// "in-place"
void sort_array_over(int* array, int size, int ordine) {
  for (int i=0; i<size; i++) {
    for (int j=0; j<size-1; j++) {
      if (ordine * array[j] > ordine * array[j+1]) {
        int temp = array[j];
        array[j] = array[j+1];
        array[j+1] = temp;
      }
    }
  }
}

void stampa_array(int* array, int size) {
  for (int i=0; i<size; i++) {
    printf("%d\t", array[i]);
  }
  printf("\n");
}

int main() {
  int *vettore, n, somma, *vettoreordinato;
  printf("Quanto ce l'hai lungo? ");
  scanf(" %d", &n);
  vettore = (int*)malloc(n * sizeof(*vettore));
  vettoreordinato = (int*)malloc(n * sizeof(*vettoreordinato));
  if (vettore == NULL || vettoreordinato == NULL) {
    printf("Errore di allocazione memoria.\n");
    return 1;
  }
  for (int i=0; i<n; i++) {
    vettore[i] = posrandom(0, 100);
  }
  sort_array(vettore, n, vettoreordinato, 1);
  printf("Adesso il vettore non è stato ordinato:\n");
  stampa_array(vettore, n);
  stampa_array(vettoreordinato, n);
  printf("Adesso ho sovrascritto il vettore:\n");
  sort_array_over(vettore, n, 1);
  stampa_array(vettore, n);

  free(vettore);
  free(vettoreordinato);
  
  printf("Adesso uso un po' di funzioni in fnbymz.c:\n5^3 = %d\nLa media tra 7 e 194 è %lf\nEcco un numero a caso tra 0 e 100: %d\n", power(5, 3), average(7, 194), posrandom(0, 100))
  return 0;
}
