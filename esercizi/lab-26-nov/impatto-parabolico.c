#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#define GRAV 9.81

// fai in modo che tutto vada in funzione di hZero e vZero 
// btw controlla risoluzione
// derivata

// inizializzo funzione del moto parabolico:
double y(double t, double hZero, double vZero) {
  double altezza = hZero + vZero * t - 0.5*GRAV*t*t;
  return altezza;
}

double dy(double t, double hZero, double vZero) {
  double step = 1e-6;
  return (y(t+step, hZero, vZero)-y(t, hZero, vZero))/step;
}

// metodo di bisezione
int bisezione(double a, double b, int iterMax, double* soluzione, double hZero, double vZero){
  printf("Inizializzazione warm-start\n");
  for (int i=0; i<iterMax; i++) {
    *soluzione = (a+b)*0.5;
    // controllo i criteri di arresto
    if (y(a, hZero, vZero) * y(*soluzione, hZero, vZero) < 0)
      b = *soluzione;
    else 
      a = *soluzione;
  }
  printf("Warm-start terminato\n");
  return iterMax;
}

// newton con warm-start
int newton(double a, double b, double tol, int iterMax, double* x, double* err, double hZero, double vZero) {
  double f, df, temp;
  // ritorna numero di iterazioni necessario
  printf("Metodo di Newton con warm-start chiamato correttamente\n");
  // chiamo il warm-start (3 iter di bisezione)
  bisezione(a, b, 3, x, hZero, vZero);
  for (int i=3; i<iterMax; i++) {
    f = y(*x, hZero, vZero);
    df = dy(*x, hZero, vZero);
    temp = *x;
    *x = *x - (f/df);
    // considero come "errore" la distanza tra iterate
    *err = fabs(temp - *x);
    // controllo i criteri di arresto
    if (*err < tol) {
      printf("Soluzione trovata per errore dopo %d iterazioni.\n", i++);
      return i;
    }
    // altrimenti continuo
  }
  return iterMax;
}

void welcome(double* hZero, double* vZero) {
  printf("Inserire altezza iniziale: ");
  scanf("%lf", hZero);
  printf("Inserire velocità iniziale: ");
  scanf("%lf", vZero);
}

int main() {
  double hZero, vZero;
  welcome(&hZero, &vZero);
  double pivot=0, tempoCaduta, errore;

  do {
    pivot += 10; 
  } while(y(pivot, hZero, vZero) * y(0, hZero, vZero) >= 0);
  newton(0, pivot, 1e-9, 1000, &tempoCaduta, &errore, hZero, vZero);

  printf("La soluzione trovata vale %lf\n", tempoCaduta);
  return 0;
}
