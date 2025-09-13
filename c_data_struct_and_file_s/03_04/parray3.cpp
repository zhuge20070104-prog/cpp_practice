#include <cstdio>

int main(int argc, char* argv[]) {
    int twos[5] = {2, 4, 6, 8, 10};
    int* pt;
    int x;

    pt = twos;
    for(x=0; x<5; ++x) {
        printf("%p=%p\n", pt + x, &twos[x]);
    }
    return 0;
}