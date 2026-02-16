#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int continua() {
  char flag;
  do {
    printf("Continuare? (Y-N) ");
    scanf(" %c", &flag);
  } while (flag != 'y' && flag != 'Y' && flag != 'n' && flag != 'N');
  if (flag == 'y' || flag == 'Y')
    return 1;
  else 
    return 0;
}

void max_min(double* array, double* max, double* min, int n) {
  n--;
  *min = array[0];
  *max = array[0];
  for (int i=1; i<n; i++) {
    if (array[i] < *min)
      *min = array[i];
    if (array[i] > *max)
      *max = array[i];
  }
}

int main() {
  double *numeri, max, min;
  int n=1;
  numeri = malloc(n * sizeof(*numeri));
  if (numeri == NULL) {
    printf("Errore di allocazione memoria\n");
    return 1;
  }
  do {
    numeri = realloc(numeri, n * sizeof(*numeri));
    if (numeri == NULL) {
      printf("Errore di allocazione memoria\n");
      return 1;
    }
    printf("Inserire un numero: ");
    scanf("%lf", &numeri[n-1]);
    n++;
  } while (continua());
  max_min(numeri, &max, &min, n);
  printf("Tra i numeri inseriti, il massimo era %.2lf e il minimo %.2lf\n", max, min);
  return 0;
}
