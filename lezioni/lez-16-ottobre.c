#include <stdio.h>
#include <math.h>

int main(){
  // printf("Calcolatore distanze tra punti facile e veloce!\n");
  // double x1, x2, y1, y2;
  //
  // printf("Inserire le coordinate del primo punto:\n");
  // printf("x1 = ");
  // scanf("%lf", &x1);
  // printf("y1 = ");
  // scanf("%lf", &y1);
  //
  // printf("Inserire le coordinate del secondo punto:\n");
  // printf("x2 = ");
  // scanf("%lf", &x2);
  // printf("y2 = ");
  // scanf("%lf", &y2);
  //
  // double distanza = sqrt(pow(x2-x1, 2)+pow(y2-y1, 2));
  // printf("La distanza tra il punto (%.2lf, %.2lf) e il punto (%.2lf, %.2lf) è %.2lf\n", x1, y1, x2, y2, distanza);
  
  // Array: strutture dati che permettono di memorizzare più informazioni
  // rispetto a una variabile singola
  // In questo caso possiamo rappresentare le coordinate del punto in un array
  int dimensioni;
  printf("In quante dimensioni ti trovi? ");
  scanf("%d", &dimensioni);
  double P[dimensioni], Q[dimensioni];

  for (int i = 0; i<dimensioni; i++) {
    printf("Inserire la coordinata %d del punto P: ", i+1);
    scanf("%lf", &P[i]); // ricorda il giusto specificatore di formato (mannaggia a tutti i santi)
  }
  
  for (int i = 0; i<dimensioni; i++) {
    printf("Inserire la coordinata %d del punto Q: ", i+1);
    scanf("%lf", &Q[i]);
  }

  double distanza, somma = 0;
  for (int i=0; i<dimensioni; i++) {
    somma += pow((P[i] - Q[i]), 2);
  }

  distanza = sqrt(somma);
  printf("La distanza tra il punto P e il punto Q è %.2lf\n", distanza);

  return 0;
}
