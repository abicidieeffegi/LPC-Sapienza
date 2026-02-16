#include <stdio.h>
#include <math.h>

int main(){
  printf("Calcolatore distanze tra punti facile e veloce!\n");
  double x1, x2, y1, y2;
  printf("Inserire le coordinate del primo punto:\n");
  printf("x1 = ");
  scanf("%lf", &x1);
  printf("y1 = ");
  scanf("%lf", &y1);
  printf("x2 = ");
  scanf("%lf", &x2);
  printf("y2 = ");
  scanf("%lf", &y2);
  double distanza = sqrt(pow(x2-x1, 2)+pow(y2-y1, 2));
  printf("La distanza tra il punto (%.2lf, %.2lf) e il punto (%.2lf, %.2lf) è %.2lf\n", x1, y1, x2, y2, distanza);
  
  return 0;
}
