#include <stdio.h>
#include <math.h> 

int main() {
  double x, y, abs, deg;
  int mode;
  printf("Convertitore di coordinate: inserire la modalità di utilizzo (1-2)\n");
  printf("1. cartesiane -> polari\n");
  printf("2. polari -> cartesiane\n");
  scanf("%d", &mode);
  
  while (mode != 1 && mode != 2){
    printf("Errore. Scegliere una modalità di utilizzo (1-2)");
    scanf("%d", &mode);
  }
  
  if(mode == 1){
      printf("Inserire le coordinate del punto A(x, y)\n");
      printf("X = ");
      scanf("%lf", &x);
      printf("Y = ");
      scanf("%lf", &y);
      abs = sqrt(pow(x, 2)+pow(y,2));
      deg = atan2(y,x);
      printf("Il punto A(%.2lf, %.2lf) in coordinate polari è A(%.2lf, %.2lf)\n", x, y, abs, deg);
    }
  else{
      printf("Inserire le coordinate del punto A(r, θ) con l'angolo in radianti\n");
      printf("r = ");
      scanf("%lf", &abs);
      printf("θ = ");
      scanf("%lf", &deg);
      x = abs * sin(deg);
      y = abs * cos(deg);
      printf("Le coordinate cartesiane del punto A(%.2lf, %.2lf) sono A(%.2lf, %.2lf)\n", abs, deg, x, y);
    }
  return 0;
}
