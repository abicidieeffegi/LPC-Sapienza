#ifndef LIBMZ_H
#define LIBMZ_H

typedef enum {
  INT,
  CHAR,
  FLOAT,
  DOUBLE,
} varType;

int casuale();
unsigned int poscasuale();
void allocMatrix(void*** matrix, int nrows, int ncols, varType tipo);
void allocArray(void** array, int nrows, varType tipo);
void checkPtr(void* ptr);
void grid(double a, double b, int samples, double* grid);
double lagrangeBasis(double (*f)(double), double x, double* xNodes, int nNodes, int i);
double lagrangeInterpolate(double (*f)(double), double x, double* xNodes, int nNodes, double* error);
void getData (const char* str, void* ptr, varType type);
void plotfunc (double (*f)(double), ...);
// int bisection (double (*func)(double), double* x, double a, double b, double tol, int max);
double midpoint_integrate(double (*func)(double), double start, double end, int samples);

#endif
