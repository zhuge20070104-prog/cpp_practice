#include <cstdio>

int main(int argc, char* argv[]) {
    char const* veeps[5] = {"Adams", "Jefferson", "Burr", "Clinton", "Gerry"};

    // 打印数组的第一个字符
    for(int i=0; i<5; ++i) {
        printf("%c\n", **(veeps + i));
    }

    return 0;
}