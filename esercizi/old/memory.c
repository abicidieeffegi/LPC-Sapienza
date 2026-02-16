#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

// gioco del memory
// matrice 2n x 2n 
// numeri da accoppiare
// come inizializzare i numeri??

unsigned int posrandom(int min, int max) {
  int source = open("/dev/urandom", O_RDONLY);
  unsigned int randomnumber;
  read(source, &randomnumber, sizeof(randomnumber));
  randomnumber = randomnumber % (max-min+1) + min;
  close(source);
  return randomnumber;
}

void shufflecarte(int** array, int grid) {
  int rowseed, colseed, maxnumber;
  maxnumber = grid*grid/2;
  for (int i=1; i<=maxnumber; i++) {
    for (int j=0; j<2; j++) {
      do {
      rowseed = posrandom(0, grid-1);
      colseed = posrandom(0, grid-1);
      } while (array[rowseed][colseed] != 0);
      array[rowseed][colseed] = i;
    }
  }
}

void input(char* x, int* y, int grid) {
  do {
    printf("Indovina: ");
    scanf(" %c%d", x, y);
    *x = (*x < 97) ? *x % 65 :  *x % 97;
    // A, a = 0, B, b = 1, C, c = 2,...
    (*y)--;
    // printf(" %d %d %d\n", *x, *y, grid); // debugging
  } while (*x >= grid || *y >= grid);
}

void gioco(char** display, int** hidden, int grid, int* score) {
  int y1, y2;
  char x1, x2;

  // stampo il campo di gioco iniziale
  //  A B C D...
  //1 # # # #...
  //2 # # # #...
  system("clear");
  for (int i=0; i<grid; i++)
    printf("\t%c", i+65);
  printf("\n");
  for (int i=0; i<grid; i++) {
    printf("%d\t", i+1);
    for (int j=0; j<grid; j++) {
      printf("%c\t", display[i][j]);
    }
    printf("\n");
  }

  // chiedo il primo input
  input(&x1, &y1, grid);

  // rivelo la carta pescata (hidden[y1][x1])
  system("clear");
  for (int i=0; i<grid; i++)
    printf("\t%c", i+65);
  printf("\n");
  for (int i=0; i<grid; i++) {
    printf("%d\t", i+1);
    for (int j=0; j<grid; j++) {
      if (j == x1 && i == y1)
        printf("%d\t", hidden[y1][x1]);
      else
        printf("%c\t", display[i][j]);
    }
    printf("\n");
  }
  
  // chiedo il secondo input controllando che sia diverso dal primo
  do {
    input(&x2, &y2, grid);
  } while(x1 == x2 && y1 == y2);

  // rivelo la seconda carta pescata (hidden[y2][x2])
  system("clear");
  for (int i=0; i<grid; i++)
    printf("\t%c", i+65);
  printf("\n");
  for (int i=0; i<grid; i++) {
    printf("%d\t", i+1);
    for (int j=0; j<grid; j++) {
      if (j == x1 && i == y1)
        printf("%d\t", hidden[y1][x1]);
      else if (j == x2 && i == y2)
        printf("%d\t", hidden[y2][x2]);
      else
        printf("%c\t", display[i][j]);
    }
    printf("\n");
  }

  if (hidden[y1][x1] == hidden[y2][x2]) {
    display[y1][x1] = '0' + hidden[y1][x1];
    display[y2][x2] = '0' + hidden[y1][x1];
    (*score)++;
  }
  else
    usleep(1000000);

  return;
}

int score(char** array, int grid) {
  return 1;
}

void liberamatrix(int** array, int grid) {
  for (int i=0; i<grid; i++) {
    free(array[i]);
  }
  free(array);
}

int main() {
  int **numeri, grid, x1, y1, x2, y2, score;
  char **display;
  printf("Inserire difficoltà (1-3): ");
  scanf(" %d", &grid);
  grid *= 2;

  numeri = (int**)malloc(grid * sizeof(*numeri));
  display = (char**)malloc(grid * sizeof(*display));
  if (numeri == NULL || display == NULL) {
    printf("Errore di allocazione memoria.\n");
    return 1;
  }
  for (int i=0; i<grid; i++) {
    numeri[i] = (int*)malloc(grid * sizeof(int));
    display[i] = (char*)malloc(grid * sizeof(char));
    if (numeri[i] == NULL || display[i] == NULL) {
      printf("Errore di allocazione memoria.\n");
      return 1;
    }
    for (int j=0; j<grid; j++)
      display[i][j] = '#';
  }

  shufflecarte(numeri, grid);

  do {
    gioco(display, numeri, grid, &score);
  } while (score<(grid*grid)/2);

  liberamatrix(numeri, grid);
  liberamatrix((int**)display, grid);


  system("clear");
  printf("Complimenti!!! Hai vinto!\n");
  usleep(3000000);
  system("clear");

  return 0;
}
