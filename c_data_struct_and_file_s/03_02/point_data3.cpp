#include <cstdio>

int main(int argc, char* argv[]) {
    int alpha;
    int* ptr;

    alpha = 99;
    ptr = &alpha;

    printf("Varaible alpha = %d\n", alpha);
    *ptr = 66;
    printf("Varaible alpha = %d\n", alpha);

    return 0;
}