#include <stdio.h>

int main() {
  printf("In un'aia vi sono conigli e polli. In tutto ci sono x zampe e y teste. Quanti conigli e polli ci sono?\n");

  int x, y;
  printf("Inserire quante zampe ci sono: ");
  scanf("%d", &x);
  printf("Inserire quante teste ci sono: ");
  scanf("%d", &y);

  int polli, conigli;
  polli = (4*y - x)/2;
  conigli = (x - 2*y)/2;
  printf("In tutto ci sono %d polli e %d conigli\n", polli, conigli);
}
