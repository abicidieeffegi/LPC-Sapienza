#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

// // apertura, scrittura e lettura da file
//
// int main() {
//   srand(time(0));
//
//   FILE *filepointer; // dichiaro un puntatore a file
//   filepointer = fopen("dati.txt", "w"); // il secondo parametro è "w", "r", per indicare la modalità con cui si apre
//   // check allocazione puntatore
//   if (filepointer == NULL) {
//     printf("Errore di apertura file\n");
//     return 1;
//   }
//   // NB: se il file non è presente su disco, il file viene creato
//   // prova a trovare implementazioni migliori con unistd?
//   // es: open, read
//
//   // dati da scrivere
//   int n = rand();
//   double pi = (double)rand()/rand();
//
//   // scrivo su file
//   fprintf(filepointer, "Ecco un intero %d\nEcco un double %lf\n", n, pi);
//
//   // chiudo il file
//   fclose(filepointer);
//
//   filepointer = fopen("dati.txt", "w");
//   if (filepointer == NULL) {
//     printf("Errore di apertura file\n");
//     return 1;
//   }
//   // se chiudo e riapro il file, i contenuti di questo vengono sovrascritti
//   fprintf(filepointer, "%d %lf\n", n, pi);
//   fclose(filepointer);
//
//   // apro il file in modalità lettura
//   filepointer = fopen("dati.txt", "r"); // readonly
//   if (filepointer == NULL) {
//     printf("Errore di apertura file\n");
//     return 1;
//   }
//   int m;
//   double y;
//   fscanf(filepointer, "%d %lf", &m, &y);
//   printf("I valori letti sono %d e %.2lf\n", m, y);
//   
//   return 0;
// }

int main() {
  srand(time(0));

  // input array da utente
  // scrittura array su file
  // lettura di array da file e salvataggio in altro array

  double *array;
  int n;
  printf("Inserire lunghezza array: ");
  scanf("%d", &n);
  
  array = (double*)malloc(n * sizeof(*array));
  if (array == NULL) {
    printf("Erore allocazione\n");
    return 1;
  }

  for (int i=0; i<n; i++) {
    array[i] = (double)rand()/rand();
  }

  FILE *filep;
  filep = fopen("array.txt", "w");
  if (filep == NULL) {
    printf("Errore apertura file\n");
    return 1;
  }
  
  fprintf(filep, "%d\n", n);
  for (int i=0; i<n; i++) {
    fprintf(filep, "%lf ", array[i]);
  }
  fprintf(filep, "\n");

  fclose(filep);

  // leggo l'array dal file
  filep = fopen("array.txt", "r");
  if (filep == NULL) {
    printf("Errore di lettura file\n");
    return 1;
  }

  free(array);

  int n_file;
  double *readarray;
  fscanf(filep, "%d", &n_file);
  
  readarray = (double*)malloc(n_file * sizeof(*readarray));
  if (readarray == NULL) {
    printf("Errore allocazione memoria\n");
    return 1;
  }

  for (int i=0; i<n_file; i++)
    fscanf(filep, "%lf", &readarray[i]);
  
  fclose(filep);

  printf("L'array letto da file risulta\n");
  for (int i=0; i<n_file; i++)
    printf("%lf\t", readarray[i]);
  printf("\n");

  free(readarray);

  return 0;
}
