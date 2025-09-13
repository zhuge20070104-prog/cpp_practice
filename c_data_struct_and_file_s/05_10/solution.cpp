#include <cstdio>
#include <cstdlib>
#include <ctime>

#define COUNT 51
#define BALLS 6


int main(int argc, char* argv[]) {
    int lottball[COUNT];

    int draw, b;
    srand((unsigned)time(nullptr));

    for(int i=0; i<COUNT; ++i) {
        lottball[i] = 0;
    }

    draw = 0;

    while(draw < BALLS) {
        b = rand() % COUNT;

        if(lottball[b] == 0) {
            lottball[b] = 1;
            ++draw;
        }
    }


    puts("Winning Lotto Numbers: ");
    for(int i=0; i<COUNT; ++i) {
        if(lottball[i] == 1) {
            printf("%3d", i+1);
        }
    }

    putchar('\n');

    return 0;
}