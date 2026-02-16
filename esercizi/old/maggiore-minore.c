#include <stdio.h>

/* Richiedere in ingresso tre valori interi distinti e determinare il maggiore e minore
 * sia usando l’espressione condizionale ?: che controlli di flusso.
 * Sggerimento: è utile inizializzare max = a e min = a e poi confrontare con b e c.
 */

int main() {
  int a, b, c, max, min;
  printf("Inserire 3 numeri (A B C): ");
  scanf("%d %d %d", &a, &b, &c);
  max = (a > b ? (a > c ? a : c) : (b > c ? b : c));
  min = (a < b ? (a < c ? a : c) : (b < c ? b : c));
  
  printf("Il massimo tra %d, %d, e %d è %d.\nIl minimo è invece %d.\n", a, b, c, max, min);
  
  return 0;
}
