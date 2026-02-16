#include <stdio.h>

int main() {
  double tuser, tconv;
  char scala, conv;
  
  printf("Convertitore di temperature\nInserire una temperatura: ");
  scanf("%lf %c", &tuser, &scala);

  // costruisco un while loop per accettare solo valori in c, f, k
  while (scala != 'c' && scala != 'C' && scala != 'f' && scala != 'F' && scala != 'k' && scala != 'K') {
    printf("Errore. Scala non riconosciuta. Inserire una temperatura: ");
    scanf("%lf %c", &tuser, &scala);
  }
  printf("Scegliere in cosa convertire la temperatura inserita: ");
  scanf(" %c", &conv);

  // costruisco un while loop per accettare solo valori in c, f, k
  while (conv != 'c' && conv != 'C' && conv != 'f' && conv != 'F' && conv != 'k' && conv != 'K') {
    printf("Errore. Scala non riconosciuta. Inserire un'unità di misura (C - F - K): ");
    scanf(" %c", &conv);
  }
  
  // construisco uno switch case per ogni possibilità (c'è un modo migliore?)
  switch (scala) {
    case 'c':
    case 'C':
      switch (conv) {
        case 'f':
        case 'F': 
          tconv = 32 + 9.0/5.0 * tuser;
          printf("%.2lf %c equivale a %.2lf %c\n", tuser, scala, tconv, conv);
          break;
        case 'k':
        case 'K': 
          tconv = tuser + 273.15;
          printf("%.2lf %c equivale a %.2lf %c\n", tuser, scala, tconv, conv);
          break;
      }
    break;
    case 'f':
    case 'F':
      switch (conv) {
        case 'c':
        case 'C':
          tconv = (tuser - 32) * 5.0/9.0;
          printf("%.2lf %c equivale a %.2lf %c\n", tuser, scala, tconv, conv);
          break;
        case 'k':
        case 'K':
          tconv = (tuser - 32) * 5.0/9.0 + 273.15;
          printf("%.2lf %c equivale a %.2lf %c\n", tuser, scala, tconv, conv);
          break;
      }
      break;
    case 'k':
    case 'K':
      switch (conv) {
        case 'c':
        case 'C':
          tconv = tuser - 273.15;
          printf("%.2lf %c equivale a %.2lf %c", tuser, scala, tconv, conv);
          break;
        case 'f':
        case 'F':
          tconv = 32 + 9.0/5.0 * (tuser - 273.15);
          printf("%.2lf %c equivale a %.2lf %c", tuser, scala, tconv, conv);
          break;
      }
    break;
  }

  return 0;
}
