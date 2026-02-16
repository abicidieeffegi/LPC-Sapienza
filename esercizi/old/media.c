#include <stdio.h>
#include <math.h>

/*int main() {
  printf("Calcolatore media online facile e veloce (GRATUITO - no pubblicità)\n");
  
  int voto1, voto2, voto3;
  printf("Inserire il voto 1: ");
  scanf("%d", &voto1);
  printf("Inserire il voto 2: ");
  scanf("%d", &voto2);
  printf("Inserire il voto 3: ");
  scanf("%d", &voto3);
  
  int somma = voto1+voto2+voto3;
  float media = (float)somma/3.0;
  float var = (pow(voto1 - media, 2) + pow(voto2 - media, 2) + pow(voto3 - media, 2))/3.0;
  printf("La media dei voti inseriti è %.2f con varianza %.2f\n", media, var);
  return 0;
}*/

int main() {
  int N;
  printf("Inserire il numero di voti: ");
  scanf("%d", &N);
  int voti[N-1];
  
  // l'utente aggiunge i voti alla lista
  for (int i=0; i<=N-1; i++) {
    printf("Inserire il voto %d: ", i + 1);
    scanf("%d", &voti[i]);
  }
  
  // calcolo la somma dei voti
  int somma=0;
  for (int i=0; i<=N-1; i++) {
    somma += voto[i]; 
  }
  
}
