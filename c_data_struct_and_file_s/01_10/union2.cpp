#include <cstdio>

int main(int argc, char* argv[]) {
    union storage {
        char a;
        int b;
    } reg;

    reg.a = 'A';
    printf("reg.a stores %c\n", reg.a);

    // 0000 0101 / 0100 0010
    // 后面一半是 66 'B' 输出 'B'
    reg.b = 1346;
    printf("reg.b stores %d\n", reg.b);
    printf("reg.a stores %c\n", reg.a);

    return 0;
}