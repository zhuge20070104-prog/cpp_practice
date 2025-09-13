#include <cstdio>

int main(int argc, char* argv[]) {
    char const* veeps[5] = {"Adams", "Jefferson", "Burr", "Clinton", "Gerry"};

    for(int i=0; i<5; ++i) {
        printf("%s\n", veeps[i]);
    }

    return 0;
}