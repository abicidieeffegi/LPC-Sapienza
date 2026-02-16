#include <stdio.h>
#include <math.h>
#define SAMPLE 1000

double f(double x) {
  return sin(x)/x;
}

double g(double x) {
  return (1-cos(x))/pow(x, 2);
}

double h(double x) {
  return pow((1+x), 1/x);
}

double sinelimit() {
  double leftResult, rightResult, limit;
  for (int i=0; i<SAMPLE; i++) {
    leftResult = f(-0.1/i);
    rightResult = f(0.1/i);
    limit = (leftResult + rightResult) * 0.5;
    if (fabs(limit - 1) < 1e-9) {
      break;
    }
  }

  return limit;
}

double cosinelimit() {
  double leftResult, rightResult, limit;
  for (int i=0; i<SAMPLE; i++) {
    leftResult = g(-0.1/i);
    rightResult = g(0.1/i);
    limit = (leftResult + rightResult) * 0.5;
    if (fabs(limit - 0.5) < 1e-9) {
      break;
    }
  }

  return limit;
}

double elimit() {
  double leftResult, rightResult, limit;
  for (int i=0; i<SAMPLE; i++) {
    leftResult = h(-0.1/i);
    rightResult = h(0.1/i);
    limit = (leftResult + rightResult) * 0.5;
    if (fabs(limit - exp(1)) < 1e-9) {
      break;
    }
  }

  return limit;
}

int main() {
  // scrivo le funzioni f, g e h
  double (*limit[])() = {&sinelimit, &cosinelimit, &elimit};
  double results[] = {1, 0.5, exp(1)};
  int choice;
  // chiedo all'utente che limite voglia calcolare:
  printf("Opzioni disponibili:\n1. sin(x)/x per x->0\n2. (1-cos(x))/(x^2) per x->0\n3. (1+x)^(1/x) per x->0\n");
  do {
    printf("Inserire opzione (1-3): ");
    scanf(" %d", &choice);
  } while (choice < 1 || choice > 3);
  choice--;
  // calcolo per x sempre più vicini a xzero
  printf("Il limite risulta: %lf\nCon un errore rispetto al limite teorico di: %lf\n", limit[choice](), fabs(limit[choice]() - results[choice]));

  return 0;
}
