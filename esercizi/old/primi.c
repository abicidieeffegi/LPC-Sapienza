#include <stdio.h>
#include <math.h>
#include <stdbool.h>

// WHY THE FUCK DOES THIS NOT WORK????

int isprime(int numero) {
  if (numero == 1)
    return 0;
  else {
    for (int i=2; i*i<=numero; i++) {
      if (numero % i == 0) return 0;
    }
  return 1;
  }
}

int main() {
  int n_utente;
  printf("Inserire un numero: ");
  scanf("%d", &n_utente);
  printf("Ecco i numeri primi da 2 fino a %d:\n", n_utente);
  for (int i = 1; i<=n_utente; i++) {
    if (isprime(i)) {
      printf("%4d\t", i);
    }
    else if (i%10 == 0) printf("\n");
    else printf("\t");
  }
  printf("\n");
  return 0;
}
