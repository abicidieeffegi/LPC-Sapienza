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
  fp = fopen("dati.bin", "wb");
  if (fp == NULL) {
    printf("Errore apertura file\n");
    return 1;
  }

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
  }

  // adesso ho scritto dimensione, energia, massa, velocità
  fwrite(&n, sizeof(n), 1, fp);
  fwrite(&energia, sizeof(energia), 1, fp);
  fwrite(m, sizeof(*m), n, fp);
  fwrite(v, sizeof(*v), n, fp);
  
  fclose(fp);

  // rileggo i dati da file
  fp = fopen("dati.bin", "rb");
  double *mread, *vread, energiaread;
  int nread;
  fread(&nread, sizeof(nread), 1, fp);
  mread = malloc(nread * sizeof(*mread));
  vread = malloc(nread * sizeof(*vread));
  fread(&energiaread, sizeof(double), 1, fp);
  fread(mread, sizeof(*mread), nread, fp);
  fread(vread, sizeof(*vread), nread, fp);

  if (n != nread) {
    perror("Errore apertura file");
    return 1;
  }
  if (energia != energiaread) {
    printf("Errore di lettura da file energia\n");
    return 1;
  }
  for (int i=0; i<nread; i++) {
    if (mread[i] != m[i] || vread[i] != v[i]) {
      printf("Errore di lettura da file 2\n");
      return 1;
    }
  }
  free(v);
  free(m);
  printf("File scritto e riletto con successo\n");

  return 0;
}
