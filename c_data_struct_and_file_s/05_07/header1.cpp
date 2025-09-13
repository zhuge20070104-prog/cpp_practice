#include <cstdio>
#include <cstdlib>
#include <ctime>

#define MAX 100
#define SIZE 3


int main(int argc, char* argv[]) {
    struct data {
        int a;
        char b;
    };

    struct data stuff[SIZE];
    int x;

    srand((unsigned)time(nullptr));

    for(x=0; x<SIZE; ++x) {
        stuff[x].a = rand() % MAX + 1;
        stuff[x].b = rand() % 26 + 'A';
    }

    return 0;
}

