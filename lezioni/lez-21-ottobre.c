#include <stdio.h>
#include <math.h>

int main() {
  // più conciso, ma non dà messaggi di errore
  /* int dimensioni;
  do {
    printf("In quante dimensioni ti trovi? ");
    scanf("%d", &dimensioni);
  } while (dimensioni < 1); // ricorda il ; alla fine

  double P[dimensioni];
  double distanza;
  char flag = 'y';
  do {
    distanza = 0;
    for (int i = 0; i<dimensioni; i++) {
      printf("Inserire la coordinata %d del punto P: ", i+1);
      scanf("%lf", &P[i]); // ricorda il giusto specificatore di formato
      distanza += pow((P[i]), 2);
    }
    distanza = sqrt(distanza);
    printf("La distanza tra il punto P e l'origine è %.2lf\n", distanza);

    printf("Vuoi inserire un altro punto? (y/n) ");
    scanf(" %c", &flag);
  } while (flag == 'y' || flag == 'Y'); */
  // se volessi calcolare la distanza di k punti dall'origine?
  // ARRAY BIDIMENSIONALE
  int dimensioni;
  int punti;
  do {
    printf("Quanti punti vuoi? ");
    scanf("%d", &punti);
  } while (punti < 1);
  do {
    printf("In quante dimensioni ti trovi? ");
    scanf("%d", &dimensioni);
  } while (dimensioni < 1);

  double PP[punti][dimensioni], distanze[punti];
  for (int i=0; i<punti; i++) {
    distanze[i] = 0;
    for (int j=0; j<dimensioni; j++) {
      printf("Inserire la coordinata %d del punto %d: ", j+1, i+1);
      scanf(" %lf", &PP[i][j]);
      distanze[i] += pow(PP[i][j], 2);
    }
    distanze[i] = sqrt(distanze[i]);
  }

  for (int i=0; i<punti; i++) {
    printf("Punto %d ( ", i+1);
    for (int j=0; j<dimensioni; j++) {
      printf("%.2lf ", PP[i][j]);
    }
    printf(")\n");
  }

  for (int i=0; i<punti; i++) {
    printf("La distanza del punto %d dall'origine è %.2lf\n", i+1, distanze[i]);
  }

  // PUNTATORI
  int a=5, *puntatorea=&a;    // dichiaro a e il suo pointer
  char c='l', *puntatorec=&c; // dichiaro c e il suo pointer
  return 0;
}
