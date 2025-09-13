#include <cstdio>
#include <ctype.h>

int main(int argc, char* argv[]) {
    char str[] = "My aunt types her email in ALL CAPS.\n";
    int ch;
    int x = 0;

    while((ch = str[x]) != '\0') {
        putchar((char)tolower(ch));
        ++x;
    }


    return 0;
}