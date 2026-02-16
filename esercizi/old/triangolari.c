#include <stdio.h>

int main() {
  int n;
  printf("Inserire un numero: ");
  scanf("%d", &n);
  printf("I numeri triangolari da 1 a %d sono:\n", n);
  for(int i = 1; i*(i+1)/2 <= n; i++) {
    printf("%d\t", i*(i+1)/2);
    if (i%10==0) printf("\n");
  }
  printf("\n");
  return 0;
}
