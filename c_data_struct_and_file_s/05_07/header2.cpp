#include "header2.h"

int main(int argc, char* argv[]) {
  
    struct data stuff[SIZE];
    int x;

    srand((unsigned)time(nullptr));

    for(x=0; x<SIZE; ++x) {
        stuff[x].a = rand() % MAX + 1;
        stuff[x].b = rand() % 26 + 'A';
    }

    return 0;
}

