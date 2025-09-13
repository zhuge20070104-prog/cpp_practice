#include <stdio.h>

int main(int argc, char* argv[]) {
    char tictactoe[27];
    int x, y, z;

    // 初始化
    for(x=0; x<27; ++x) {
        tictactoe[x] = '.';
    }

    // 显示
    puts("Tic Tac Toe");
    for(x=0; x<3; ++x) {
        printf("%*c", x+1, ' ');
        for(y=0; y<3; ++y) {
            for(z=0; z<3; ++z) {
                printf(" %c ", tictactoe[9*x+y*3+z]);
            }
            printf("     "); // 3个z打完以后，后面空5个空格
        }

        putchar('\n');
    }

    return 0;
}