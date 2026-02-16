// FUNZIONI
#include <stdio.h>
#include <stdlib.h>
// Le funzioni vanno definite prima del main, precompilatore/preprocessore?
// tipo_funzione nome_funzione(tipo1 parametro1, ..., tipoN parametroN) {
//   codice;
// }
double calcola_media(int n1, int n2) {
  double media;
  media = (double)(n1+n2)/2; 
  return media;
}

int main() {
  int a, b;
  printf("Inserire due interi: ");
  scanf(" %d %d", &a, &b);

  double media;
  media = calcola_media(a, b); // passaggio per valore: passo alla funzione una copia del valore di a e b
  // passaggio per referenza: passo i puntatori alle variabili che mi interessano

  printf("La media tra %d e %d vale: %.2lf\n", a, b, media);

  return 0;
}
