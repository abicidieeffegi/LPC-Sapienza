#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double puntoMedio(double a, double b, int M) {
  double h = (b-a)/M;
  double Q = 0.0;
  for (int i=0; i<M i++) {
    double xLeft = a + k*h;
    double c = xLeft + h*0.5;
    Q += f(c);
  }
  Q *= h;
  return Q;
}

double montecarlo(double a, double b, int N, double fMax) {
  double areaRettangolo = (b-a) * fMax;
  int counter=0;
  for (int i=0; i<N; i++) {
    double x = a + (b-a)*(double)rand()/RAND_MAX;
    double y = fMax * (double)rand()/RAND_MAX;
    (y<=f(x)) ? counter++ : continue;
  }
  return areaRettangolo * K/N;
}

int main() {
  srand(time(NULL));

  return 0;
}
