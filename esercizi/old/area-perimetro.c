#include <stdio.h>
#include <math.h>
// scrivere un programma che, dato un numero l di lati, calcoli 
// il perimetro e l'area del poligono regolare di l lati.

double perimetro(unsigned int nlati, double lunghezza) {
  double perimetro;
  if (nlati == 0) perimetro = 2*M_PI*lunghezza;
  else perimetro = nlati * lunghezza;
  return perimetro;
}

double area(unsigned int nlati, double lunghezza) {
  double area;
  if (nlati == 0) area = M_PI*pow(lunghezza, 2);
  else area = (nlati*pow(lunghezza, 2)*(1/tan(M_PI/nlati)))/4;
  return area;
}

int main() {
  unsigned int nlati;
  printf("Inserire il numero di lati del poligono (0 se è un cerchio): ");
  scanf("%d", &nlati);
  
  while (nlati != 0 && nlati < 3) {
    printf("Errore. Numero di lati non valido: ");
    scanf("%d", &nlati);
  }
  double lunghezza;
  switch (nlati) {
    case 0:
      printf("Inserire la lunghezza del raggio: ");
      scanf("%lf", &lunghezza);
      printf("Il cerchio di raggio %.3lf ha\narea = %.3lf\ncirconferenza = %.3lf\n", lunghezza, area(nlati, lunghezza), perimetro(nlati, lunghezza));
      break;
    default:
      printf("Inserire la lunghezza del lato: ");
      scanf("%lf", &lunghezza);
      printf("Il poligono regolare di %d lati di lunghezza %.3lf ha\narea = %.3lf\nperimetro = %.3lf\n", nlati, lunghezza, area(nlati, lunghezza), perimetro(nlati, lunghezza));
      break;
  }
  return 0;
}
