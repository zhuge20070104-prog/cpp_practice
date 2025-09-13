#include <cstdio>

int main(int argc, char* argv[]) {
    int ints[10];
    int* pt = ints;

    printf("Address of ints = %p\n", ints);
    printf("Address of pt = %p\n", pt);
    
    return 0;
}