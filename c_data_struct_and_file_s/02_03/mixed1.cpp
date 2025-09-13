#include <cstdio>
#include <ctype.h>

int main(int argc, char* argv[]) {
    char str[] = "Nifty TEXT! 123\n";
    int ch;
    int x = 0;

    while((ch = str[x]) != '\0') {
        if(isupper(ch)) {
            putchar((char)tolower(ch));
        } else if(islower(ch)) {
            putchar((char)toupper(ch));
        } else {
            putchar((char)ch);
        }
        ++x;
    }
    
    return 0;
}