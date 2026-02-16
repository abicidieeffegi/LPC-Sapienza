#include <stdio.h>
#include <math.h>
#include <unistd.h>

int main() {
//   double angolouser;
//   int ch, i = 0;
//   char misura[4];
//
//   printf("Inserire l'angolo: ");
//   scanf("%lf", &angolouser);
//   printf("Inserire la misura dell'angolo: ");
//   do {
//     ch = getchar();
//     misura[i] = ch;
//     i++;
//   } while (ch != '\n' && ch != ' ');
//   printf("La misura inserita è: %s", misura);

  printf("Inserire un numero: ");
  int N;
  scanf("%d", &N);
  printf("Ok, conto fino a %d\n", N);

//   con un ciclo for:
//   for (int i=0; i<=N; i++) {
//     printf("%d\t", i);
//     usleep(500000);
//   }
//
//   printf("\nora conto i dispari\n");
//   for (int i=0; i<=N; i++) {
//     if (i%2 == 0)
//       continue;
//     printf("%d", i);
//     usleep(500000);
//   }

// con un ciclo while:
  int i=0;
  while (i<=N) {
    printf("%d\n", i);
    i++;
    usleep(50000);
  }
  return 0;
}
