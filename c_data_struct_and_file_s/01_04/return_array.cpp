#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void make_array(int* array, int size) {
    for(int x=0; x<size; ++x) {
        array[x] = rand() % 10 + 1;
    }
}

int main(int argc, char* argv[]) {
    int x, r[5];

    srand((unsigned)time(NULL));
    puts("Here are your five random numbers: ");

    make_array(r, 5);
    for(x=0; x<5; ++x) {
        printf("%d\n", r[x]);
    }
    return 0;
}