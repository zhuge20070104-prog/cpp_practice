#include <cstdio>
#include <cstdlib>
#include <ctime>

int main(int argc, char* argv[]) {
    int x, r;
    srand((unsigned)time(nullptr));

    for(x=0; x<100; ++x) {
        r = rand() % 100 + 1;
        printf("%4d", r);
    }

    putchar('\n');
    return 0;
}