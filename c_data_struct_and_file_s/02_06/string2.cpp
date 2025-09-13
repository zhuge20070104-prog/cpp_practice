#include <cstdio>

int main(int argc, char* argv[]) {
    char string[] = "I'm such a handsome program!\n";
    int a;
    a = 0;
    while(putchar(string[a]) != '\0') {
        ++a;
    }

    return 0;
}