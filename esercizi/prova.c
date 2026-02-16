#include <stdlib.h>

int coinflip() {
    if (rand()%2 == 0)
        return 1;
    else
        return -1;
}

int main() {
    return 0;
}
