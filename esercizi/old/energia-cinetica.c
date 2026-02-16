#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "libmz.h"

int main() {
  double *m, *v, energia=0;
  int n;
  printf("Inserire il numero di particelle: ");
  scanf("%d", &n);

  FILE *fp;
  fp = fopen("dati.txt", "w");
  if (fp == NULL) {
    printf("Errore apertura file\n");
    return 1;
  }
  fprintf(fp, "%d\n", n);

  m = malloc(n * sizeof(*m));
  v = malloc(n * sizeof(*v));
  if (v == NULL || m == NULL) {
    printf("malloc error\n");
    return 1;
  }
  for (int i=0; i<n; i++) {
    v[i] = (double)poscasuale()/poscasuale();
    m[i] = (double)poscasuale()/poscasuale();
    energia += (1.0/2.0) * m[i] * pow(v[i], 2);
    fprintf(fp, "%lf\t%lf\n", m[i], v[i]);
  }
  fprintf(fp, "%.12lf\n", energia);

  fclose(fp);

  fp = fopen("dati.txt", "r");
  printf("Ecco i dati scritti:\n");
  system("cat dati.txt");

  double *mread, *vread, eread;
  int nread;
  fscanf(fp, "%d", &nread);

  if (nread != n) {
    perror("Errore lettura file");
    return 1;
  }

  mread = malloc(nread * sizeof(*mread));
  vread = malloc(nread * sizeof(*vread));
  for (int i=0; i<nread; i++) {
    fscanf(fp, "%lf %lf", &mread[i], &vread[i]);
    if (abs(mread[i] - m[i]) != 0 || abs(vread[i] - v[i]) != 0) {
      perror("Errore lettura file");
      return 1;
    }
  }

  fscanf(fp, "%lf", &eread);
  if (abs(eread-energia) != 0) {
    perror("Errore lettura file");
    return 1;
  }
  usleep(500000);
  system("clear");
  printf("I dati sono stati scritti e letti con successo\n");
  usleep(500000);

  free(v);
  free(m);
  free(vread);
  free(mread);

  return 0;
}
