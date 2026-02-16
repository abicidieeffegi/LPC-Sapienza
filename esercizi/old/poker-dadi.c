#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int continua() {
  char c;
  do {
    printf("Vuoi continuare? (y/n) ");
    scanf(" %c", &c);
  } while (c!='y' && c!='Y' && c!='n' && c!='N');
  if (c == 'y' || c == 'Y') return 1;
  else return 0;
}

int punteggio(int contatore[], int punteggio) {
  for (int i=0; i<2; i++) {
    if (contatore[i]==1 && contatore[i+1]==1 && contatore[i+2]==1 && contatore[i+3]==1 && contatore[i+4]==1) {
      printf("Hai fatto scala!\n");
      return 4;
    }
  }
  for (int i=0; i<6; i++) {
    if (contatore[i]==4) {
      printf("Hai fatto poker!\n");
      return 6;
    }
    else if (contatore[i]==3) {
      for (int j=0; j<6; j++) {
        if (contatore[j]==2) {
          printf("Hai fatto full!\n");
          return 5;
        }
        else {
          printf("Hai fatto tris!\n");
          return 3;
        }
      }
    }
    else if (contatore[i]==2) {
      for (int j=0; j<6; j++) {
        if (contatore[j]==2) {
          printf("Hai fatto doppia coppia!\n");
          return 2;
        }
        else if (contatore[j]==3) {
          printf("Hai fatto full!\n");
          return 5;
        }
        else {
          printf("Hai fatto coppia!\n");
          return 1;
        }
      }
    }
  }
  printf("LOSER! lmao\n");
  return -punteggio;
}

int main() {
  srand(time(0));
  int lanci[5], conteggio[6], punti=0;
  do {
    printf("Sto lanciando...\n");
    usleep(600000);
    // for (int i=0; i<6; i++)
    //   conteggio[i]=0;
    for (int i=0; i<5; i++) {
      lanci[i] = rand()%6 + 1;
      conteggio[lanci[i]-1]++;
    }
    for (int i=0; i<6; i++) {
      printf("Il numero %d è uscito %d volte.\n", i+1, conteggio[i]);
    }
    punti += punteggio(conteggio, punti);
    for (int i=0; i<6; i++)
      conteggio[i]=0;
    printf("Il tuo punteggio adesso è di %d punti\n", punti);
  } while (continua());
  printf("Esci a prendere un po' d'aria\n");
  return 0;
}


