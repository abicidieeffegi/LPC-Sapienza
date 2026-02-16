#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// srand(time(0));

void mergesort(int arr[], int low, int high) {
  int pivot = arr[rand() % length]; // scelgo un elemento casuale contro cui confrontare tutti gli altri
  int i=-1;
  for (int j=0; j<length; j++) {
    if (arr[j] < pivot) {
      i++;
      int temp = arr[j];
      arr[j] = arr[i];
      arr[i] = temp;
    }
    else continue;
  }
  for (int k=0; k<length; k++) {
    printf("%d\t", arr[k]);
  }
  printf("\n");
}

int main() {
  int tosort[5];
  for (int i=0; i<5; i++) {
    scanf(" %d", &tosort[i]);
  }
  mergesort(tosort, 5);
  return 0;
}
