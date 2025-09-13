#include <cstdio>

// 这个程序有问题，第二个char接不到
int main(int argc, char* argv[]) {
    int ch1, ch2;

    printf("Type a character: ");
    ch1 = getchar();
    printf("Type a character: ");
    ch2 = getchar();
    printf("Characters: '%c' and '%c' received\n", ch1, ch2);
    return 0;
}