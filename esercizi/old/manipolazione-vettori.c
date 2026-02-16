#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void inizializza(double *vettore, int lvettore) {
  for (int i=0; i<lvettore; i++) {
    vettore[i] = (double)rand()/rand();
  }
}

void stampavec(double *vettore, int lvettore) {
  for (int i=0; i<lvettore; i++) {
    printf("%.2lf\t", vettore[i]);
  }
  printf("\n");
}

void alterna(double *vettore1, double *vettore2, double *risultato, int lvettore) {
  int i, j, k;
  j=0;
  k=0;
  for (i=0; i<lvettore*2; i++) {
    if (i%2 == 0) {
      risultato[i] = vettore1[j];
      j++;
    }
    else {
      risultato[i] = vettore2[k];
      k++;
    }
  }
}

void maggioreminore(double *vettore1, double  *vettore2, double *risultato, int lvettore) {
  for (int i=0; i<lvettore; i++) {
    if (vettore1[i]>vettore2[i]) risultato[i]=1;
    else if (vettore1[i]==vettore2[i]) risultato[i]=0;
    else if (vettore1[i]<vettore2[i]) risultato[i]=-1;
  }
}

int piuvicino(double *vettore, int numero, int lvettore) {
  int i, j=0;
  double distanza = fabs(vettore[j] - numero);
  for (i=0;i<lvettore; i++) {
    if (fabs(vettore[i] - numero) <= distanza) {
      distanza = fabs(vettore[i] - numero);
      j = i;
    }
  }
  return j;
}

int main() {
  srand(time(0));

  double *v1, *v2, *w1, *w2, k;
  int length;
  printf("Inserire la lunghezza del vettore: ");
  scanf(" %d", &length);
  printf("Inserire un intero k: ");
  scanf(" %lf", &k);
  
  v1=(double*)malloc(length * sizeof(double));
  v2=(double*)malloc(length * sizeof(double));
  w1=(double*)malloc(2 * length * sizeof(double));
  w2=(double*)malloc(length * sizeof(double));
  if (v1 == NULL || v2 == NULL || w1 == NULL || w2 == NULL) {
    printf("Errore di allocazione memoria\n");
    return 1;
  }
  inizializza(v1, length);
  inizializza(v2, length);
  printf("L'elemento di V1 più vicino a %.2lf è: %.2lf\n", k, v1[piuvicino(v1, k, length)]);
  printf("V1 = \t");
  stampavec(v1, length);
  printf("V2 = \t");
  stampavec(v2, length);
  alterna(v1, v2, w1, length);
  printf("W1 = \t");
  stampavec(w1, length*2);
  maggioreminore(v1, v2, w2, length);
  printf("W2 = \t");
  stampavec(w2, length);
  
  return 0;
}
