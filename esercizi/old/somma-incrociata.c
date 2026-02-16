#include <stdio.h>
#include <stdlib.h>

int main() {
  int *a, *b, n;
  printf("Quanto ce l'hai lungo il vettore? ");
  scanf("%d", &n);
  a = malloc(n*sizeof(int));
  b = malloc(n*sizeof(int));
  if (a == NULL || b == NULL) {
    printf("Errore di allocazione memoria\n");
    return 1;
  }

  for (int i=0; i<n; i++) {
    printf("Inserire la componente %d del vettore A: ", i+1);
    scanf("%d", a+i);
  }

  for (int i=0; i<n; i++) {
    printf("Inserire la componente %d del vettore B: ", i+1);
    scanf("%d", b+i);
  }

  printf("A = \t");
  for (int i=0; i<n; i++) 
    printf("%d\t", a[i]);
  printf("\n");

  printf("B = \t");
  for (int i=0; i<n; i++) 
    printf("%d\t", b[i]);
  printf("\n");

  printf("A + B = ");
  for (int i=0; i<n; i++)
    printf("%d\t", a[i]+b[n-(i+1)]);
  printf("\n");

  free(a);
  free(b);
  return 0;
}
