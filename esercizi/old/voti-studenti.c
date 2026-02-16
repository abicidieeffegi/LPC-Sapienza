#include <stdio.h>
#include <stdlib.h>

int main() {
  int *voti, n, somma=0, max=0, min=30;
  double media;
  printf("Quanti studenti hai? ");
  scanf("%d", &n);
  voti = malloc(n*sizeof(int));
  if (voti == NULL) {
    printf("Errore di allocazione memoria\n");
    return 1;
  }

  for (int i=0; i<n; i++) {
    do {
      printf("Inserire il voto dello studente %d: ", i+1);
      scanf("%d", voti+i);
    } while (voti[i] < 0 || voti[i] > 30);
    somma += voti[i];
    if (voti[i] > max)
      max = voti[i];
    if (voti[i] < min)
      min = voti[i];
  }
  media = somma / n;
  printf("Tra i tuoi %d studenti, la media è stata %.2lf, con un massimo di %d e un minimo di %d\n", n, media, max, min);
  free(voti);

  return 0;
}
