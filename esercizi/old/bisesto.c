#include <stdio.h>

int main() {
  int anno;
  printf("Inserire un anno: ");
  scanf("%d", &anno);
  
  if ((anno%4 == 0 && anno % 100) || (anno%400 == 0)) {
    printf("Male male! L'anno %d è un bisestile.\nAnno bisesto, anno funesto!", anno);
  }
  else {
    printf("Meno male! L'anno che hai scelto (%d) non è bisestile.\n", anno);
  }

  return 0;
}
