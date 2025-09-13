#include <cstdio>
#include <ctype.h>

int main(int argc, char* argv[]) {
    char str[] = "stop shouting at me!\n";
    int ch;
    int x = 0;

    while((ch = str[x]) != '\0') {
        putchar((char)toupper(ch));
        ++x;
    }
    
    return 0;
}