#include <math.h>
#include <stdio.h>
#include <stdlib.h>
// INTERPOLAZIONE DI POLINOMI

// Funzione che calzola l'i-esimo polinomio di base di Lagrange
// Input:   vettore di double nodes
//          numero di nodi
//          i-esimo polinomio da calcolare
//          punto di valutazione
// Output:  valutazione dell'i-esimo polinomio di base di Lagrange in i

double lagrangeBases(double* xNodes, int nodeNumber, int i, double x) {
  double lagrangeI = 1.0;
  for (int j=0; j<nodeNumber; j++) {
    if (j != i)
      lagrangeI = lagrangeI * (x - xNodes[j])/(xNodes[i] - xNodes[j]);
  }
  return lagrangeI;
}

// Funzione che calcola il polinomio di interpolazione di Lagrange
// Input:   vettore di double nodes
//          vettore fNodes 
//          i-esimo polinomio da calcolare
//          punto di valutazione
// Output:  valutazione dell'i-esimo polinomio di base di Lagrange in i

double lagrangeInterpolate(double* xNodes, double* fNodes, int nodeNumber, double x) {
  double interpolated;
  for (int i=0; i<nodeNumber; i++) {
    interpolated = interpolated + fNodes[i] * lagrangeBases(xNodes, nodeNumber, i, x); // chiamo la funzione per trovare la base necessaria
  }
  return interpolated;
}

int main() {
  // richiedere intervallo di interpolazione
  // definire la griglia di interpolazione
  // numero di nodi di interpolazione

  // plot:
  // genero una griglia più fitta dove valutare lagrangeInterpolate

  return 0;
}
