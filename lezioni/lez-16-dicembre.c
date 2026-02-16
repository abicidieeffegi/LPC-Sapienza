#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// INPUT: matrice n*n A, vettore b
// OUTPUT: A ridotta a scala e b trasformato ugualmente
void gaussReduce(double** A, double* b, int n) {
  double tol = 1e-12;

  for (int k=0; k<n-1; k++) {
    int p=k;
    double max = fabs(A[k][k]);
    for (int i=k+1; i<n; i++) {
      if (fabs(A[i][k]) > max) {
        max = fabs(A[i][k]);
        p = i;
      }
    }
    // controllo che la matrice non sia bizzarra
    if (max < tol) {
      printf("Errore. Matrice troppo vicina ad essere singolare\n");
      exit(1);
    }
    // pivoting vero e proprio
    if (p != k) {
      double* tempptr = A[k];
      A[k] = A[p];
      A[p] = tempptr;
      double temp = b[k];
      b[k] = b[p];
      b[p] = temp;
    }
    // eliminazione
    for (int i=k+1; i<n; i++) {
      double m = A[i][k]/A[k][k];
      for (int j=0; j<n; j++) {
        A[i][j] = A[i][j] - m*A[k][j];
      }
      b[i] = b[i] - m*b[k];
    }
  }
  return;
}

void solveUpper(double** A, double* b, int n, double* xResult){

  return;
}

int main() {

  return 0;
}
