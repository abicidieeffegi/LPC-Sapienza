#include "libmz.h"
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#define TOL 1e-6
#define MAX 100


// -------------------------VARIE ED EVENTUALI------------------------- //

double f (double x) {
  return 5.0*x + 8.0*atan(x) - 10.0;
}

double df (double x) {
  return 5.0 + 8.0*(1.0/(1+x*x));
}

// -------------------------------------------------------------------- //

// ---------------------------RICERCA DI ZERI-------------------------- //

// PUNTO FISSO:
// IN:  ptr a func di cui trovare gli zeri
//      ptr a soluzione
//      max iterazioni
// OUT: numero iterazioni
//      soluzione (ptr)
int fixedpoint (double (*func)(double), 
                double* x, 
                int maxiter) {
  double lambda = -0.15;
  *x = 0;
  double oldx = 0;
  int i;
  for (i=0; i<maxiter; i++) {
    *x += lambda * func(*x);
    if (fabs(func(*x)) < TOL) {
      printf("Soluzione trovata per residuo.\n");
      break;
    }
    if (fabs(*x - oldx) < TOL) {
      printf("Soluzione trovata per distanza iterate.\n");
      break;
    }
  }
  return i+1;
}

// BISEZIONE:
// IN:  ptr a func di cui trovare zeri
//      ptr a soluzione
//      intervallo a, b
//      max iter
// OUT: iter necessarie
//      soluzione (ptr)
int bisection (double (*func)(double), 
               double*x, 
               double a, 
               double b, 
               int maxiter) {
  if (func(a)*func(b) > 0) {
    printf("Nessuno zero trovato.\n");
    return 0;
  }
  int i;
  for (i=0; i<maxiter; i++) {
    *x = (a + b)/2;
    if (fabs(func(*x)) < TOL) {
      printf("soluzione trovata per residuo.\n");
      break;
    }
    if (b-a < TOL) {
      printf("Soluzione trovata per distanza estremi.\n");
      break;
    }
    else if (func(a)*func(*x) < 0) {
      b = *x;
    }
    else {
      a = *x;
    }
  }
  return i+1;
}

// NEWTON:
// IN:  ptr a func di cui trovare zeri
//      intervallo a, b
//      ptr a soluzione
//      passaggi di warm-start
//      maxiter
// OUT: iter necessarie
//      soluzione (ptr)
int newton(double (*func)(double),
           double (*dfunc)(double),
           double* x,
           double a,
           double b,
           int warmstart,
           int maxiter) {
  *x = a;
  double xold = a;
  if (warmstart > 0) {
    bisection(func, x, a, b, warmstart);
  }
  int i;
  for (i=0; i<maxiter; i++) {
    if (fabs(dfunc(*x)) < TOL) {
      printf("Derivata numericamente nulla.\n");
      break;
    }
    *x -= func(*x)/dfunc(*x);
    if (fabs(func(*x)) < TOL) {
      printf("Soluzione trovata per residuo.\n");
      break;
    }
    if (fabs(*x - xold) < TOL) {
      printf("Soluzione trovata per distanza iterate.\n");
      break;
    }
    xold = *x;
  }
  return i+1;
}


// -------------------------INTERPOLAZIONE------------------------- //

// BASE di Lagrange
// IN:  x in cui valutare la base
//      griglia dei nodi
//      polinomio da calcolare
//      numero di nodi
// OUT: polinomio di lagrange;
double lagrange_basis (double x,
                       double** nodes,
                       int i,
                       int n) {
  double li = 1.0;
  for (int j=0; j<i; j++) {
    li *= (x - nodes[j][0])/(nodes[i][0] - nodes[j][0]);
  }
  for (int j=i+1; j<n; j++) {
    li *= (x - nodes[j][0])/(nodes[i][0] - nodes[j][0]);
  }
  return li;
}

// INTERPOLAZIONE di Lagrange
// IN:  punto in cui valutare interpolata
//      griglia nodi (x, y)
//      a, b intervallo di interpolazione
//      numero nodi di interpolazione
// OUT: valore nell'interpolata
double lagrange_interpolate (double x, 
                             double** nodes, 
                             double a, 
                             double b, 
                             int n) {
  double l = 0.0;
  for (int i=0; i<n; i++) {
    l += nodes[i][1]*lagrange_basis(x, nodes, i, n);
  }
  return l;
}


// -------------------------INTEGRAZIONE------------------------- //

// RETTANGOLI (midpoint)
// IN:  func da integrare
//      a, b estremi di integrazione
//      N di rettangoli
// OUT: valore dell'integrale
double midpoint (double (*func)(double),
                 double a,
                 double b,
                 int N) {
  double integral = 0;
  double h = (b-a)/N;
  double x = a + 0.5*h;
  for (int i=0; i<N; i++) {
    integral += f(x);
    x += h;
  }
  integral *= h;
  return integral;
}

// TRAPEZI
// IN:  func da integrare
//      a, b estremi di integrazione
//      N di trapezi
// OUT: valore integrale
double trapezi (double (*func)(double),
                double a,
                double b,
                int N) {
  double integral = 0;
  double h = (b-a)/N;
  double x = a;
  for (int i=0; i<N; i++) {
    double xnext = x+h;
    integral += f(x) + f(xnext);
    x = xnext;
  }
  integral *= 0.5*h;
  return integral;
}

// GAUSS:
// IN & OUT analoghi alle altre
double gauss_integrate (double (*func)(double),
                        double a,
                        double b,
                        int N) {
  double integral = 0;
  double h = (b-a)/N;
  double x = a;
  for (int i=0; i<N; i++) {
    double gamma1 = x + 0.5*h*(1 - 1/sqrt(3));
    double gamma2 = x + 0.5*h*(1 + 1/sqrt(3));
    integral += f(gamma1) + f(gamma2);
    x += h;
  }
  integral *= 0.5*h;
  return integral;
}

// SIMPSON:
// IN & OUT analoghi alle precedenti
double simpson (double (*func)(double),
                double a,
                double b,
                int N) {
  double integral = 0;
  double h = (b-a)/N;
  double x = a;
  for (int i=0; i<N; i++) {
    double xnext = x + h;
    double mid = x + 0.5*h;
    integral += (f(x) + 4*f(mid) + f(xnext));
    x = xnext;
  }
  integral *= h/6;
  return integral;
}


// ------------------------------------------------------ //
// -------------------------MAIN------------------------- //
int main() {
  double x, a, b;
  int deg;
  getData("a = ", &a, DOUBLE);
  getData("b = ", &b, DOUBLE);
  getData("deg = ", &deg, INT);
  int N = deg+1;
  int iter = fixedpoint(f, &x, MAX);
  printf("Punto fisso:\nx = %lf\niter = %d\n", x, iter);
  iter = bisection(f, &x, a, b, MAX);
  printf("Bisezione:\nx = %lf\niter = %d\n", x, iter);
  iter = newton(f, df, &x, a, b, 0, MAX);
  printf("Newton:\nx = %lf\niter = %d\n", x, iter);
  iter = newton(f, df, &x, a, b, 1, MAX);
  printf("Newton (WS):\nx = %lf\niter = %d\n", x, iter);

  // inizializzo i nodi per l'interpolata
  double **c_nodes, **e_nodes;
  c_nodes = malloc(N * sizeof(*c_nodes));
  e_nodes = malloc(N * sizeof(*e_nodes));
  for (int i=0; i<N; i++) {
    c_nodes[i] = malloc(2 * sizeof(**c_nodes));
    e_nodes[i] = malloc(2 * sizeof(**e_nodes));
  }
  double h = (b-a)/(N-1);
  for (int i=0; i<N; i++) {
    c_nodes[i][0] = 0.5*(a+b) + 0.5*(b-a)*cos((M_PI*(2*i+1))/(2*N));
    c_nodes[i][1] = f(c_nodes[i][0]);
    e_nodes[i][0] = a + i*h;
    e_nodes[i][1] = f(e_nodes[i][0]);
  }
  // PLOT
  FILE* data = fopen("data.txt", "w");
  int samples = (b-a)*100;
  for (int i=0; i<samples; i++) {
    x = a + i*(b-a)/(samples-1);
    fprintf(data, "%lf\t%lf\t%lf\t%lf\n", x, f(x), lagrange_interpolate(x, c_nodes, a, b, N), lagrange_interpolate(x, e_nodes, a, b, N));
  }
  fclose(data);
  system("echo \"set grid\nplot 'data.txt' u 1:2 w l lw 2 t 'funzione', '' u 1:3 w l lw 1.5 t 'interpolata (chebyshev)', '' u 1:4 w l t 'interpolata (equispaziati)\n\" | gnuplot -p"); 

  // integrale
  printf("rettangoli:\nI = %lf\n", midpoint(f, a, b, 1000));
  printf("trapezi:\nI = %lf\n", trapezi(f, a, b, 1000));
  printf("gauss:\nI = %lf\n", gauss_integrate(f, a, b, 1000));
  printf("simpson\nI = %lf\n", simpson(f, a, b, 1000));

  for (int i=0; i<2; i++) {
    free(c_nodes[i]);
    free(e_nodes[i]);
  }
  free(c_nodes);
  free(e_nodes);
  return 0;
}
