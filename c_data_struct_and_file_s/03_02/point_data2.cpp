#include <cstdio>

int main(int argc, char* argv[]) {
    int alpha;
    int* ptr;
    alpha = 99;
    ptr = &alpha;
    printf("The content of variable alpha is %d\n", alpha);
    printf("The content of memory address %p is %d\n", ptr, *ptr);

    return 0;
}