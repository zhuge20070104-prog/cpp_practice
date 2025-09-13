#include <cstdio>

int main(int argc, char* argv[]) {
    char const* veeps[5] = {"Adams", "Jefferson", "Burr", "Clinton", "Gerry"};

    // 交换第二个和第三个元素
    char const* temp;
    temp = veeps[1];
    veeps[1] = veeps[2];
    veeps[2] = temp;

    for(int i=0; i<5; ++i) {
        printf("%s\n", *(veeps + i));
    }

    return 0;
}