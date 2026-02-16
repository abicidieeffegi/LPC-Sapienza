#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  // int *array_dinamico, n;
  // printf("Inserire lunghezza array: ");
  // scanf("%d", &n);
  // array_dinamico = (int*)malloc(n * sizeof(int));
  // if (array_dinamico == NULL) {
  //   printf("Errore di allocazione memoria\n");
  //   return 1;
  // }
  // // realloc: riallocare memoria, ovvero
  // // modificare la dimensione di un array già allocato
  // int *temp, m;
  // printf("Quanto lo vuoi lungo adesso? ");
  // scanf("%d", &m);
  // temp = realloc(array_dinamico, m * sizeof(int));
  // if (temp != NULL)
  //   array_dinamico = temp;
  // free(temp);
  // free(array_dinamico);

  // array 2d ovvero matrici
  // matrice linearizzata: tratto una matrice MxN come un array di MxN valori
  int *linearizzata, N, M;
  printf("Quante righe ha la matrice? ");
  scanf("%d", &N);
  printf("Quante colonne ha la matrice? ");
  scanf("%d", &M);
  linearizzata = (int*)(malloc(N*M*sizeof(int)));
  if (linearizzata == NULL) {
    printf("Errore di allocazione memoria\n");
    return 1;
  }
  printf("Ora uso una matrice linearizzata\n");
  for (int i=0; i<N; i++) {
    for (int j=0; j<M; j++) {
      linearizzata[i*M + j] = rand(); // inizializzo ogni elemento della matrice. non posso usare il doppio indice perché è linearizzata
      printf("%d\t", linearizzata[i*M + j]);
    }
    printf("\n");
  }
  // libero la memoria utilizzata
  free(linearizzata);
  // puntatore a puntatori
  int **matrice;
  matrice = (int**)malloc(N * sizeof(int*)); // alloco la memoria per i puntatori alle righe
  if (matrice == NULL) {
    printf("Errore di allocazione memoria\n");
    return 1;
  }
  for (int i=0; i<N; i++) {
    matrice[i] = (int*)malloc(M * sizeof(int)); // alloco la memoria per gli elementi della matrice
    if (matrice[i] == NULL) {
      printf("Errore di allocazione memoria\n");
      return 1;
    }
  }
  // inizializzo gli elementi della matrice: la sintassi è come per gli arrray 2d statici
  printf("Ora uso un puntatore a puntatori\n");
  for (int i=0; i<N; i++) {
    for (int j=0; j<M; j++) {
      matrice[i][j] = rand();
      printf("%d\t", matrice[i][j]);
    }
    printf("\n");
  }
  // libero la memoria allocata per la matrice
  for (int i=0; i<N; i++) {
    free(matrice[i]);
  }
  free(matrice);
  return 0;
}
