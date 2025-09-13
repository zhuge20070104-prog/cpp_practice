#include <stdio.h>

int main(int argc, char* argv[]) {
    char tictactoe[3][3];
    int x, y;

    // 初始化
    for(x=0; x<3; ++x) {
        for(y=0; y<3; ++y) {
            tictactoe[x][y] = '.';
        }
    }

    // 显示
    puts("Tic Tac Toe");
    for(x=0; x<3; ++x) {
        for(y=0; y<3; ++y) {
            printf(" %c ", tictactoe[x][y]);
        }
        putchar('\n');
    }
    return 0;
}