#include <stdio.h>
#include <stdlib.h>
int main() {
  // int righe, colonne;
  // printf("Quante righe ha la tua matrice? ");
  // scanf(" %d", &righe);
  // printf("Quante colonne ha la tua matrice? ");
  // scanf(" %d", &colonne);
  // int A[righe][colonne], B[righe][colonne], somma[righe][colonne];
  // // inizializzo le matrici a valori casuali
  // for (int i=0; i<righe; i++) {
  //   for (int j=0; j<colonne; j++) {
  //     A[i][j]=rand();
  //     B[i][j]=rand();
  //   }
  // }
  // // calcolo la somma delle matrici
  // for (int i=0; i<righe; i++) {
  //   for (int j=0; j<colonne; j++) {
  //     somma[i][j] = A[i][j] + B[i][j];
  //   }
  // }
  // // stampo le due matrici e il risultato
  // printf("La somma di A:\n");
  // for (int i=0; i<righe; i++) {
  //   for (int j=0; j<colonne; j++) 
  //     printf("%2d\t", A[i][j]);
  //   printf("\n");
  // }
  // printf("e B:\n");
  // for (int i=0; i<righe; i++) {
  //   for (int j=0; j<colonne; j++) 
  //     printf("%2d\t", B[i][j]);
  //   printf("\n");
  // }
  // printf("vale:\n");
  // for (int i=0; i<righe; i++) {
  //   for (int j=0; j<colonne; j++) 
  //     printf("%2d\t", somma[i][j]);
  //   printf("\n");
  // }

  // PUNTATORI
  // int a=5, *puntatorea=&a;    // dichiaro a e il suo pointer a intero
  // char c='l', *puntatorec=&c; // dichiaro c e il suo pointer a carattere
  // 
  // printf("a vale %d, il suo indirizzo di memoria %p e il valore del suo pointer %d, l'indirizzo a cui punta il pointer %p\n", a, &a, *puntatorea, puntatorea);
  // printf("c vale %c, il suo indirizzo di memoria %p e il valore del suo pointer %c, l'indirizzo a cui punta il pointer %p\n", c, &c, *puntatorec, puntatorec);
  // printf("L'indirizzo di memoria del puntatore vale %p\n", &puntatorea);
  // Esempio di utilizzo

  // Puntatori e array
  int numeri[100];
  int *v;
  v = numeri; // equivalente a dire v = &numeri[0], ovvero numeri è puntatore al primo elemento dell'array
  // array allocato dinamicamente
  int *arraydinamico;
  int n;
  printf("Dammi la dimensione dell'array: ");
  scanf("%d", &n);
  // uso la funzione malloc (presente in stdlib)
  arraydinamico = malloc( n * sizeof(int) );
 // controllo che malloc sia andato a buon fine
  if (arraydinamico == NULL) {
    printf("Errore di allocazione memoria, suca\n");
    return 1;
  }
  // inizializzo gli elementi a caso e li stampo
  for (int i=0; i<n; i++) {
    arraydinamico[i] = rand();
    printf("%d\t", arraydinamico[i]);
  }
  printf("\n");
  // calloc alloca la memoria e svuota tutto: inizializza tutto a 0
  arraydinamico = calloc(n, sizeof(int));
  for (int i=0; i<n; i++) {
    printf("%d\t", arraydinamico[i]);
  }
  // controllo che calloc sia andato a buon fine
  if (arraydinamico == NULL) {
    printf("Errore di allocazione memoria, suca\n");
    return 1;
  }
  printf("\n");
  // dealloco la memoria occupata dall'array
  free(arraydinamico);
  return 0;
}
