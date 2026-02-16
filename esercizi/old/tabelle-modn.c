#include <stdio.h>
#include <math.h>

int moltiplicazione(int n) {
  printf("La tabella moltiplicativa di Z(mod %d) è:\n", n);
  for (int k=0; k<n; k++) 
    printf("%d\t", k);
  printf("\n");
  for (int i=1; i<n; i++) {
    printf("%d\t", i);
    for (int j=1; j<n; j++) {
      printf("%d\t", (i*j)%n);
    }
    printf("\n");
  }
  return 0;
}

int addizione(int n) {
  printf("La tabella additiva di Z(mod %d) è:\n", n);
  for (int k=0; k<n; k++) 
    printf("%d\t", k);
  printf("\n");
  for (int i=1; i<n; i++) {
    printf("%d\t", i);
    for (int j=1; j<n; j++) {
      printf("%d\t", (i+j)%n);
    }
    printf("\n");
  }
  return 0;
}

int main() {
  printf("Inserire un numero n per cui calcolare tabelle moltiplicative e additive di Z (modn): ");
  int usern;
  scanf("%d", &usern);
  moltiplicazione(usern);
  addizione(usern);
  return 0;
}
