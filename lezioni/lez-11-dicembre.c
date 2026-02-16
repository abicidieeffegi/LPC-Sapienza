#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void jacobiSolve(double** A, double* x, double* b, int size, int maxIter, double tol) {
  // dichiariamo un nuovo array
  double *xNew = malloc(size * sizeof(*xNew));
  // check allocazione

  // ciclo sulle iterazioni
  for (int k=0; k<maxIter; k++) {
    // calcolare nuova iterazione di jacobi riga per riga
    for (int i=0; i<size; i++) {
      double somma = 0.0;
      for (int j=0; j<size; j++) {
        if (j != i)
          somma += A[i][j] * x[j];
      }
      xNew[i] = (b[i] - somma)/A[i][i];
    }
    // criteri di arresto
    double err = 0.0;
    for (int i=0; i<size; i++) {
      double diff = fabs(xNew[i] - x[i]);
      if (diff > err) {
        (err = diff);
        continue;
      }
    }
    // copio xNew in x
    for (int i=0; i<size; i++) {
      x[i] = xNew[i];
    }
    // verifico criteri di arresto
    if (err < tol) {
      printf("Jacobi converge in %d iterazioni con errore %.3lf\n",k+1,err);
      free(xNew);
      return;
    }
  }
  printf("Jacobi non converge in %d iterazioni\n", maxIter);
  free(xNew);

  return;
}

int main() {

  // chiedere a utente di inserire matrice A, i termini noti b
  // max iterazioni, tolleranza, guess iniziale

  return 0;
}
