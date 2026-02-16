#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include "libmz.h"

int casuale() {
  FILE* source = fopen("/dev/urandom", "rb");
  int randomnumber;
  fread(&randomnumber, sizeof(randomnumber), 1, source);
  fclose(source);
  return randomnumber;
}

unsigned int poscasuale() {
  FILE* source = fopen("/dev/urandom", "rb");
  unsigned int randomnumber;
  fread(&randomnumber, sizeof(randomnumber), 1, source);
  fclose(source);
  return randomnumber;
}

void allocMatrix(void*** matrix, int rows, int cols, varType tipo) {
  switch (tipo) {
    case INT: 
      *matrix = malloc(rows * sizeof(int*));
      for (int i=0; i<rows; i++)
        (*matrix)[i]= malloc(cols * sizeof(int));
      break;
    case CHAR: 
      *matrix = malloc(rows * sizeof(char*));
      for (int i=0; i<rows; i++)
        (*matrix)[i]= malloc(cols * sizeof(char));
      break;
    case FLOAT: 
      *matrix = malloc(rows * sizeof(float*));
      for (int i=0; i<rows; i++)
        (*matrix)[i]= malloc(cols * sizeof(float));
      break;
    case DOUBLE: 
      *matrix = malloc(rows * sizeof(double*));
      for (int i=0; i<rows; i++)
        (*matrix)[i]= malloc(cols * sizeof(double));
      break;
    default:
      perror("Errore allocazione matrice");
      exit(1);
  }
  return;
}

void allocArray(void** array, int rows, varType tipo) {
  switch (tipo) {
    case INT: 
      *array = malloc(rows * sizeof(int));
      break;
    case CHAR: 
      *array = malloc(rows * sizeof(char));
      break;
    case FLOAT: 
      *array = malloc(rows * sizeof(float));
      break;
    case DOUBLE: 
      *array = malloc(rows * sizeof(double));
      break;
    default:
      printf("Tipo non riconosciuto\n");
      exit(1);
  }
  return;
}

void checkPtr (void* ptr) {
  if (ptr == NULL) {
    perror("Error pointer NULL");
    exit(1);
  }
  return;
}

void grid(double a, double b, int samples, double* grid) {
  for (int i=0; i<samples; i++) {
    grid[i] = a + i*(b-a)/samples;
  }
}

double lagrangeBasis(double (*f)(double), double x, double* xNodes, int nNodes, int i){
  double lagrangeBasis = 1.0;
  int j=0;
  do {
    if (j != i)
      lagrangeBasis *= (x - xNodes[j])/(xNodes[i] - xNodes[j]);
    j++;
  } while (j < nNodes);
  return lagrangeBasis;
}

double lagrangeInterpolate(double (*f)(double), double x, double* xNodes, int nNodes, double* error) {
  double interpolated = 0.0;
  int i=0;
  do {
    interpolated += f(xNodes[i]) * lagrangeBasis(f, x, xNodes, nNodes, i);
    *error = fabs(interpolated - f(x));
    i++;
  } while (i<nNodes);
  return interpolated;
}

void getData (const char* str, void* ptr, varType type) {
  printf("%s", str);
  switch (type) {
    case INT:
      scanf(" %d", (int*)ptr);
      break;
    case DOUBLE:
      scanf(" %lf", (double*)ptr);
      break;
    case CHAR:
      scanf(" %c", (char*)ptr);
      break;
    case FLOAT:
      scanf(" %f", (float*)ptr);
      break;
  }
  return;
}

void plotfunc (double (*func)(double), ...) {
  // initializing variable arguments
  va_list args;
  va_start(args, func);
  // default values:
  double range[] = {-10, 10, 0, 0};
  int i=0, flag=0;
  // read from list:
  do {
    double tmp = va_arg(args, double);
    if (isnan(tmp)) break;
    else range[i] = tmp;
    i++;
  } while (i<4);
  // checking how many arguments I passed
  if (i==4) {
    flag = 1;
  }
  va_end(args);

  // make a grid for the function
  int samples = (range[1] - range[0]) * 100;
  double *x = malloc(samples * sizeof(*x));
  double *y = malloc (samples * sizeof(*y));
  checkPtr((void*)x); checkPtr((void*)y);
  i=0;
  do {
    x[i] = range[0] + i*(range[1] - range[0])/samples;
    y[i] = func(x[i]);
    i++;
  } while (i<samples);
  i = 0;
  // plot
  FILE* plot = popen("gnuplot -p", "w");
  checkPtr((void*)plot);
  fprintf(plot, "set xrange [%lf:%lf]\n", range[0], range[1]);
  if (flag == 1) {
    fprintf(plot, "set yrange [%lf:%lf]\n", range[2], range[3]);
  }
  fprintf(plot, "set grid\n");
  fprintf(plot, "plot '-' w l t 'f(x)' lt rgb 'red'\n");
  do {
    fprintf(plot, "%lf\t%lf\n", x[i], y[i]);
    i++;
  } while (i<samples);
  fprintf(plot, "e\n");

  free(x); free(y);
  va_end(args);
  return;
}

int bisection (double (*func)(double), double* x, double a, double b, double tol, int max) {
  if (func(a)*func(b) > 0) {
    printf("No zeroes found in interval.\n");
    return 0;
  }
  int i=0;
  do {
    *x = (a+b)/2;
    if (func(a)*func(*x) < 0)
      b = *x;
    else
      a = *x;
    if (fabs(b-a) < tol) {
      printf("b-a < tol\n");
      printf("x = %lf\n", *x);
      return i+1;
    }
    if (fabs(func(*x)) < tol) {
      printf("|f(x)| < tol\n");
      printf("x = %lf\n", *x);
      return i+1;
    }
    i++;
  } while (i<max);
  printf("Max iterations reached.\nx = %lf\n", *x);
  return max;
}

double midpoint_integrate (double (*func)(double), double start, double end, int samples) {
  double integral=0;
  double h = (end - start)/samples;
  double midpoint = start + 0.5*h;
  int i=0;
  do {
    integral += func(midpoint);
    midpoint += h;
    i++;
  } while (i < samples);
  integral *= h;
  return integral;
}
