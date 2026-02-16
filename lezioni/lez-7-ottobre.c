// iniziamo a fare un po' di condizioni logiche
#include <stdio.h>
#include <math.h>

int main(){
  /* divisione tra intero e float
  int num_int=5, den_int=2;
  float num_float=5, den_float=2;
  double risultato = num_int/den_int;
  printf("La divisione tra interi vale %lf\n", risultato);
  risultato = num_float/den_float;
  printf("La divisione tra float vale %lf\n", risultato);
  risultato = 5/2;
  printf("Il risultato della divisione 5/2 è %lf\n", risultato);
  printf("%d elevato al quadrato vale %.0lf\n", den_int, pow(den_int, 2)); // cfr lez-2-ottobre.c
  
  resto = fmod(num_float, den_float); // operazione modulo inclusa in math.h
  
  // operatori di confronto
  // ==, !=, <, >, <=, >=
  // risultato logico = 1 xor 0
  int logico;
  logico = (5 == 2); // varrà 0 perché falso
  logico = (5 != 2); // varrà 1 perché vera
  // operatori logici:
  // && and logico
  // || or logico
  // ! not logico

  // operatore ternario
  // (espressione logica) ? if_true : if_false
  */
  int mode;
  double celsius, farenheit;
  printf("Convertitore di temperature\nScegliere la modalità di utilizzo (1-2):\n1. Da °C a °F\n2. Da °F a °C\n");
  scanf("%d", &mode);
  while (mode != 1 && mode != 2){
    printf("Errore. Scegliere una modalità (1-2): ");
    scanf("%d", &mode);
  }
  if (mode == 1){
    printf("Inserire la temperatura in Celsius: ");
    scanf("%lf", &celsius);
    farenheit = 9.0/5.0*celsius + 32;
    printf("La temperatura in Farenheit vale %.2lf °F\n", farenheit);
  }
  else {
    printf("Inserire la temperatura in Farenheit: ");
    scanf("%lf", &farenheit);
    celsius = (farenheit - 32)*(5.0/9.0);
    printf("La temperatura in Celsius vale %.2lf °C\n", celsius);
  }

  return 0;
}
