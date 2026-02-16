#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define MAXITER 1000
#define TOL 1e-12
// PERCHE CI VUOLE LO STESSO NUMERO DI ITER?????

/* Generare e risolvere Ax = b di dimensione n = 100
 * A è tridiagonale con entrate casuali, a dominanza diagonale stretta
 * 
 * Scrivere un programma che implementi Jacobi e Gauss-Seidel
 */

// questo è uno strumentopolo misterioso che ci servirà più tardi
 void checkPtr(void* ptr) {
	if (ptr == NULL) {
		printf("Err NULL pointer\n");
		exit(1);
	}
	return;
}

// questa funzione moltiplica matrice e vettore
void multiplication(double** matrix, double* vector, double* result, int size) {
	for (int i=0; i<size; i++) {
		result[i] = 0;
		for (int j=0; j<size; j++) {
			result[i] += matrix[i][j]*vector[j];
		}
	}
	return;
}

/* Genera matrice casuale a dominanza diagonale stretta
 * IN:	Matrix (ptr)
 * 		Size
 * OUT: Matrix (ptr)
 */
void randomMatrix(double** matrix, int size){
	// // dominanza diagonale stretta
	//  for (int i=0; i<size; i++) {
	//  	for (int j=0; j<size; j++) {
	//  		if (i == j)
	//  			matrix[i][j] = 5 + rand()%5;
	//  		else
	//  			matrix[i][j] = -(rand()%3);
	//  	}
	//  }
  // a caso
  for (int i=0; i<size; i++) {
    for (int j=0; j<size; j++) {
      matrix[i][j] = rand()%10 + 1;
    }
  }
	return;
}

// stampa vettore
void printVector(double* vector, int size) {
  for (int i=0; i<size; i++) {
    printf("%lf\n", vector[i]);
  }
  printf("\n");
  return;
}
 
 /* Jacobi:
  * INPUT: 	Matrice dei coefficienti (ptr)
  * 		Vettore termini noti (ptr)
  * 		Size
  * 		Vettore soluzione (ptr)
  * OUTPUT:	Vettore soluzione (ptr)
  * 		Iterazioni necessarie
  */
int jSolve(double** coefficients, double* solution, double* knownTerms, int size) {
	int iter=0, flag = 1;
	double *xIter = malloc(size * sizeof(*xIter));
  double *error = malloc(size * sizeof(*error));
	checkPtr((void*)xIter);
	do{
		// calcolo l'iterazione x^(iter)
		for (int i=0; i<size; i++) {
			xIter[i] = knownTerms[i]/coefficients[i][i];
			for (int j=0; j<i; j++)
				xIter[i] -= coefficients[i][j]*solution[j]/coefficients[i][i];
			for (int j=i+1; j<size; j++)
				xIter[i] -= coefficients[i][j]*solution[j]/coefficients[i][i];
			solution[i] = xIter[i];
		}
    int i=0;
    do {
      // calcolo il residuo
			multiplication(coefficients, solution, error, size);
      error[0] = fabs(error[0] - knownTerms[0]);
			double max = fabs(error[0]);
			for (int j=1; j<size; j++) {
        error[j] = fabs(error[j] - knownTerms[j]);
				if (fabs(error[j]) > max) {
					max = fabs(error[j]);
				}
			}
      // verifico il residuo
			if (max <= TOL) {
				printf("Soluzione trovata per residuo\n");
        flag = 0;
			}
			// verifico elementi diagonali
			for (int j=0; j<size; j++) {
				if (coefficients[j][j] < TOL) {
					printf("Elementi diagonali troppo piccoli\n");
          flag = 0;
				}
			}
      i++;
		} while(i < size && flag == 1);
		iter++;
	} while (iter<MAXITER && flag == 1);
	free(xIter); free(error);
	return iter;
}

/* Gauss-Seidel
 * IN:	Matrice coefficienti (ptr)
 * 		Vettore termini noti (ptr)
 * 		Size
 * 		Vettore soluzione (ptr)
 * OUT: Vettore soluzione (ptr)
 * 		Iterazioni necessarie
 */
int gsSolve(double** coefficients, double* solution, double* knownTerms, int size) {
	int iter = 0, flag = 1;
  double *error = malloc(size * sizeof(*error));
	do {
		for (int i=0; i<size; i++) {
			solution[i] = knownTerms[i]/coefficients[i][i];
			for (int j=0; j<i; j++)
				solution[i] -= coefficients[i][j]*solution[j]/coefficients[i][i];
			for (int j=i+1; j<size; j++) 
				solution[i] -= coefficients[i][j]*solution[j]/coefficients[i][i];
		}
		// verifico i criteri di arresto
    int i=0;
    do {
      // calcolo il residuo
			multiplication(coefficients, solution, error, size);
      error[0] = fabs(error[0] - knownTerms[0]);
			double max = error[0];
			for (int j=1; j<size; j++) {
        error[j] = fabs(error[j] - knownTerms[j]);
				if (error[j] > max) {
					max = error[j];
				}
			}
			// verifico il residuo
			if (max <= TOL) {
				printf("Soluzione trovata per residuo\n");
        flag = 0;
        break;
			}
			// verifico elementi diagonali
			for (int j=0; j<size; j++) {
				if (coefficients[j][j] < TOL) {
					printf("Elementi diagonali troppo piccoli\n");
          flag = 0;
          break;
				}
			}
      i++;
    } while (i < size && flag == 1);
		iter++;
	} while (iter < MAXITER && flag == 1);
	
  free(error);
	return iter;
}

void gSolve (double** coefficients, double* knownTerms, int size) {
  // pivoting:
  printf("Inizializzando pivoting...\n");
  int p;
  //######################################################//
  for (int i=0; i<size-1; i++) {
    // trovo l'elemento piu grande su una colonna
    double max = fabs(coefficients[i][i]);
    p = i;
    for (int j=i+1; j<size; j++) {
      if (fabs(coefficients[j][i]) > max) {
        max = fabs(coefficients[j][i]);
        p = j;
      }
    }
    if (max <= TOL) {
      printf("Errore: pivot numericamente nullo\n");
      exit(1);
    }
    
    // scambio righe solo se necessario
    if (p != i) {
      // nella matrice
      double* tempPtr = coefficients[i];
      coefficients[i] = coefficients[p];
      coefficients[p] = tempPtr;
      // nella soluzione
      double temp = knownTerms[i];
      knownTerms[i] = knownTerms[p];
      knownTerms[p] = temp;
    }
    //######################################################//

    // riduzione a scala
    for (int k=0; k<size; k++) {
      for (int j=1; j<size; j++) {
        double mlt = coefficients[j][k]/coefficients[k][k];
        for (int h=k; h<size; h++) {
          coefficients[j][h] -= mlt * coefficients[k][h];
        }
      }
    }
  }
  return;
}

/* Hilbert matrix:
 * IN:  Size
 * 		Double** ptr
 * OUT: Hilbert matrix (ptr)
 */
void hilbertMatrix(double** matrix, int size) {
	
	
	return;
}



int main() {
	srand(time(NULL));
	// alloco cose
	double **A, *x, *b;
	int n, iter;
	printf("Inserire dimensione sistema: ");
	scanf("%d", &n);
	A = malloc(n * sizeof(*A));
	x = malloc(n * sizeof(*x));
	b = malloc(n * sizeof(*b));
	checkPtr((void*)A);
	checkPtr((void*)b);
	checkPtr((void*)x);
	for (int i=0; i<n; i++) {
		A[i] = malloc(n * sizeof(**A));
		checkPtr((void*)A[i]);
		x[i] = 0;
		b[i] = rand()%10;
	}
	randomMatrix(A, n);
	
	// risolvo il sistema Ax = b
	
	printf("Coefficienti:\t\tb:\n");
	for (int i=0; i<n; i++) {
		for (int j=0; j<n; j++) {
			printf("%.0lf\t", A[i][j]);
		}
		printf("%.0lf\n", b[i]);
	}
	// // con il metodo di Jacobi
	// iter = jSolve(A, x, b, n);
	// printf("La soluzione è stata trovata in %d iterazioni (Jacobi).\n", iter);
	// printf("\nx = \n");
	// for (int i=0; i<n; i++) {
	// 	printf("%lf\n", x[i]);
	// }
	//
	// // con il metodo gauss-seidel
	// for(int i=0; i<n; i++) {
	// 	x[i] = 0;
	// }
	// iter = gsSolve(A, x, b, n);
	// printf("La soluzione è stata trovata in %d iterazioni (Gauss-Seidel).\n", iter);
	// printf("\nx = \n");
	// for (int i=0; i<n; i++) {
	// 	printf("%lf\n", x[i]);
	// }
	
  gSolve(A, b, n);
  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
        printf("%.0lf\t", A[i][j]);
    }
    printf("\n");
  }
	free(x);
	free(b);
	for (int i=0; i<n; i++) {
		free(A[i]);
	}
	free(A);
	
	return 0;
}
