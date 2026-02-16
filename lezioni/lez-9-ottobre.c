#include <stdio.h>
#include <math.h>
#include <unistd.h>

int main(){
  /*
  char scala;
  double temp_user, temp_conv;

  printf("Inserisci temperatura e scala: ");
  scanf("%lf %c", &temp_user, &scala);
  
  // inserisco un loop per accettare temperature solo in farenheit o celsius
  while (scala != 'c' && scala != 'C' && scala != 'F' && scala != 'f'){
    printf("Errore. Inserire una temperatura in Celsius o Farenheit: ");
    scanf("%lf %c", &temp_user, &scala);
  }

  printf("Hai inserito %.2lf %c\n", temp_user, scala);
  */

  /* utilizzo l'operatore ternario
   *(scala == 'c' || scala == 'C') ? printf("La temperatura  in F: %.2lf\n", 9.0/5.0 * temp_user + 32) : printf("La temperatura in C: %.2lf\n", (temp_user - 32)*5.0/9.0);
   * l'operatore ternario fa cagare per cose un po' più lunghe
   */
  
  /* Costrutto IF - ELSE
  if (scala == 'F' || scala == 'f') {
    temp_conv = (temp_user -32)*5.0/9.0;
    printf("La temperatura convertita in Celsius vale %.2lf\n", temp_conv);
  }
  else if (scala == 'C' || scala == 'c') {
    temp_conv = 9.0/5.0*temp_user+32;
    printf("La temperatura convertita in Farenheit vale %.2lf\n", temp_conv);
  }
  // serve solo se non avessi inserito il while loop all'inizio
  else {
  printf("Scala non nota");
  }
   */

  /* Costrutto SWITCH - CASE
  switch (scala) {
    case 'f':
    case 'F': 
      temp_conv = (temp_user -32)*5.0/9.0;
      printf("La temperatura convertita in Celsius vale %.2lf\n", temp_conv);
      break;
    case 'c':
    case 'C':
      temp_conv = 9.0/5.0*temp_user+32;
      printf("La temperatura convertita in Farenheit vale %.2lf\n", temp_conv);
      break;
    default: printf("Scala non nota"); // analogo all'else in in-else, non serve perché c'è il while loop all'inizio
  }
   */

  // for loop
  // i è detto contatore
  // calcolo il fattoriale di un numero n
  /* int n, fattoriale;
  fattoriale = 1;
  printf("Inserire un numero di cui calcolare il fattoriale: ");
  scanf("%d", &n);
  for (int i=1; i<=n; i++) {
    fattoriale *= i;
  }
  printf("%d! = %d\n", n, fattoriale); */
  
  //calcolo la somma di n numeri inseriti dall'utente
  int n, N, s;
  printf("Inserire quanti N interi sommare: ");
  scanf("%d", &N);
  //s=0;
  for (int i=1; i<=N; i++) {
    printf("Inserisci un numero: ");
    scanf("%d", &n);
    s += n;
  }
  printf("La somma dei numeri inseriti vale %d\n", s);
  return 0;
}
