#include <stdio.h>

int main() {
  int giorno, mese, anno;
  printf("Inserire una data (DD MM YYYY): ");
  scanf("%d %d %d", &giorno, &mese, &anno);
  while (mese > 12 || mese < 1) {
    printf("Errore. Inserire data valida (DD MM YYYY): ");
    scanf("%d %d %d", &giorno, &mese, &anno);
  }
  switch (mese) {
    case 1:
    case 3:
    case 7:
    case 8:
    case 10:
    case 12:
      (giorno >= 1 && giorno <=31) ? printf("La data inserita è valida\n") : printf("La data inserita non è valida\n");
      break;
    case 4:
    case 6:
    case 9:
    case 11:
      (giorno >= 1 && giorno <=30) ? printf("La data inserita è valida\n") : printf("La data inserita non è valida\n");
      break;
    case 2:
      if ((anno%4 == 0 && anno % 100) || (anno%400 == 0)) {
        (giorno >= 1 && giorno <= 29) ? printf("La data inserita è valida\n") : printf("La data inserita non è valida\n");
      }
      else {
        (giorno >= 1 && giorno <= 28) ? printf("La data inserita è valida\n") : printf("La data inserita non è valida\n");
      }
    break;

  }
  return 0;
}
