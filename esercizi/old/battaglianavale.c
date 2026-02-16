#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

unsigned int posrandom(int min, int max) {
  int source = open("/dev/urandom", O_RDONLY);
  unsigned int randomnumber;
  read(source, &randomnumber, sizeof(randomnumber));
  randomnumber = randomnumber % (max-min+1) + min;
  close(source);
  return randomnumber;
}

void stampacharmatrix(char** array, int grandezza) {
  printf("\x1b[2J\x1b[H");
  printf("\t");
  // stampo i nomi delle righe come A, B, C, ...
  for(int  i=0; i<grandezza; i++) {
    printf("%c\t", i+65);
  }
  printf("\n");
  for (int i=0; i<grandezza; i++) {
    printf("%d\t", i+1);
    for (int j=0; j<grandezza; j++) {
      printf("%c\t", array[i][j]);
    }
    printf("\n");
  }
}

void navi(int** array, int grandezza, int lbarca) {
  int row_seed, col_seed, orientation;
  orientation = posrandom(0, 1);
  if (orientation == 0) {
    row_seed = posrandom(0, grandezza-1);
    col_seed = posrandom(0, (grandezza-3));
  }
  else if (orientation == 1) {
    row_seed = posrandom(0, (grandezza-3));
    col_seed = posrandom(0, grandezza-1);
  }
  for (int i=0; i<lbarca; i++) {
    if (orientation == 0)
      array[row_seed][col_seed + i] = 1;
    else if (orientation == 1)
      array[row_seed + i][col_seed] = 1;
  }
}

void libera(int** array, int grandezza) {
  for (int i=0; i<grandezza; i++) {
    free(array[i]);
  }
  free(array);
}

int main() {
  int **mare, livello, grid;
  int lnavi = 3; // nel caso volessi generalizzare
  int nnavi = 1; //
  char **display;
  printf("Battaglia navale!\n");
  do {
  printf("Scegliere la difficoltà (1-5): ");
  scanf(" %d", &livello);
  } while (livello<1 || livello>5);
  grid = livello+3;

  // alloco la memoria in base alla difficoltà selezionata
  mare = (int**)malloc(grid * sizeof(int*));
  display = (char**)malloc(grid * sizeof(char*));
  if (mare == NULL || display == NULL) {
    printf("Errore allocazione memoria\n");
    return 1;
  }
  for (int i=0; i<grid; i++) {
    mare[i] = (int*)calloc(grid, sizeof(int));
    display[i] = (char*)calloc(grid, sizeof(char));
    if (mare[i] == NULL || display[i] == NULL) {
      printf("Errore allocazione memoria\n");
      return 1;
    }
    for (int j=0; j<grid; j++) {
      display[i][j] = '-';
    }
  }

  navi(mare, grid, lnavi);

  char xchar;
  int x, y, score=0;
  do {
    stampacharmatrix(display, grid);
    x=0;
    y=0;
    do {
      printf("Spara! ");
      scanf(" %c%d", &xchar, &y);
      x = ((int)xchar<97) ? ((int)xchar%65) : ((int)xchar%97); // workaround per accettare sia minuscole che maiuscole (cfr ASCII table)
      y--;
    } while (x<0 || x > grid-1 || y < 0 || y > grid-1);
    if (mare[y][x] == 1) {
      if (display[y][x] != 'X') {
        display[y][x] = 'X';
        score++;
        mare[y][x]--;
      }
    }
    else if (mare[y][x] == 0) {
      if (display[y][x] != 'X') {
        display[y][x] = '0';
      }
    }
  } while (score < lnavi * nnavi);
  stampacharmatrix(display, grid);
  printf("###########################\n# Complimenti! Hai vinto! #\n###########################\n");
  libera(mare, grid);
  libera((int**)display, grid);
  return 0;
}
