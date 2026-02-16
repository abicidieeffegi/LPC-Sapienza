#include <stdio.h>

int continua(char c) {
  do {
    printf("Vuoi continuare? (y/n) ");
    scanf(" %c", &c);
  } while (c!='y' && c!='Y' && c!='n' && c!='N');
  if (c == 'y' || c == 'Y') return 1;
  else return 0;
}

int main() {
  int i=0;
  double max, min, n, somma, media;
  char flag;
  somma = 0;

  // la prima volta fuori dal ciclo così inizializzo max e min
  printf("Inserire un numero: ");
  scanf("%lf", &n);
  somma += n;
  max=n;
  min=n;
  i++;
  if (continua(flag)) {
    do {
        printf("Inserire un numero: ");
        scanf("%lf", &n);
        somma += n;
        if (n>max) max=n;
        if (n<min) min=n;
        i++;
    } while (continua(flag)); // inserire una flag
  }
  media = somma/i;
  printf("Media = %.3lf\n", media);
  printf("Max = %.3lf\n", max);
  printf("Min = %.3lf\n", min);
  return 0;
  }
