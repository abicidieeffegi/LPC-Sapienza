#include <stdio.h>
#include <math.h>

int main() {
  double a, b, c;
  printf("Inserire i coefficienti di un'equazione di secondo grado (a b c):\n");
  scanf("%lf %lf %lf", &a, &b, &c);
  
  double delta, x1, x2; 
  delta = pow(b, 2) - 4*a*c;
  
  if (delta >= 0) {
    x1 = (-b + sqrt(delta))/(2*a);
    x2 = (-b - sqrt(delta))/(2*a);
    printf("Le soluzioni dell'equazione sono\nx1 = %.3lf\nx2 = %.3lf\n", x1, x2);
  }
  else {
    printf("L'equazione non ha soluzioni reali");
  }
  return 0;
}
