#include <stdio.h>
#define MAX_SIZE 10000

int main() {
  char buffer[MAX_SIZE];
  int count = 0;
  count += sprintf(buffer, "prova");
  count += sprintf(buffer + count, "viene sovrascritto?");
  count += sprintf(buffer + count, "\n");
  printf("%s", buffer);

  return 0;
}
