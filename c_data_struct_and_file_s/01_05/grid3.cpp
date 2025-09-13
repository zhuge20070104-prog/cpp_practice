#include <stdio.h>

int main(int argc, char* argv[]) {
    char tictactoe[3][3][3];
    int x, y, z;

    // 初始化
    for(x=0; x<3; ++x) {
        for(y=0; y<3; ++y) {
            for(z=0; z<3; ++z) {
                tictactoe[x][y][z] = '.';
            }
        }
    }

    // 打印
    puts("Tic Tac Toe");
    for(x=0; x<3; ++x) {
        printf("%*c", x+1, ' '); // 行前面留1, 2, 3空格
        for(y=0; y<3; ++y) {
            for(z=0; z<3; ++z) {
                printf(" %c ", tictactoe[x][y][z]);
            }
            printf("     "); // 每3个z打完之后，间隔 5个空格
        }
        putchar('\n');
    }
    return 0;
}