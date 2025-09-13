#include <cstdio>

int main(int argc, char* argv[]) {
    char alpha[] = "abcd";
    char* pa;

    pa = alpha;
    printf("%p\n", pa);
    printf("%p\n", pa + 1);
    
    return 0;
}