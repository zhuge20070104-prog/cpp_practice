#include <cstdio>
#include <cstdlib>


int main(int argc, char* argv[]) {
    int x, r;
    for(x=0; x<10; ++x) {
        r = rand();
        printf("%d\n", r);
    }
    return 0;
}