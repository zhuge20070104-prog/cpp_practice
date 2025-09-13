#include <cstdio>


int main(int argc, char* argv[]) {
    int a;

    while(1) {
        a = getchar();
        if(a == EOF) {
            break;
        }

        putchar(a);
    }
    return 0;
}