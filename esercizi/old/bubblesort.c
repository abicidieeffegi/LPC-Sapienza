#include <stdio.h>

int main() {
  /* double a, b, c, d, e, cambio;
  printf("Inserire 5 numeri: ");
  scanf(" %lf %lf %lf %lf %lf", &a, &b, &c, &d, &e);

  for (int i=1; i<=5; i++) {
    if (a>b) {
      cambio = a;
      a = b;
      b = cambio;
    }
    if (b>c) {
      cambio = b;
      b = c;
      c = cambio;
    }
    if (c>d) {
      cambio = c;
      c = d;
      d = cambio;
    }
    if (d>e) {
      cambio = d;
      d = e;
      e = cambio;
    }
  }
  printf("La tua lista ordinata:\n%.2lf %.2lf %.2lf %.2lf %.2lf\n", a, b, c, d, e); */
  int n;
  printf("Quanti numeri vuoi inserire? ");
  scanf(" %d", &n);

  double numeri[n], temp;
  for (int i=0; i<n; i++) {
    printf("Inserire il numero %d: ", i+1);
    scanf(" %lf", &numeri[i]);
  }
  for (int j=0; j<n; j++) {
    for (int i=0; i<n-1; i++) {
      if (numeri[i]>numeri[i+1]) {
        temp = numeri[i];
        numeri[i] = numeri[i+1];
        numeri[i+1] = temp;
      }
    }
  }
  printf("Ecco la tua lista ordinata!\n");
  for (int i=0; i<n; i++) {
    printf("%.2lf\t", numeri[i]);
  }
  printf("\n");
  return 0;
}
