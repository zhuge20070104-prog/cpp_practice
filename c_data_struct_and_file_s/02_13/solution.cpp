#include <cstdio>
#include <cstring>


int main(int argc, char* argv[]) {
    char name[32];
    char buffer[64];
    char last[] = "passed the challenge!\n";

    int ch, a;
    printf("What is your name? ");
    a = 0;
    while((ch = getchar()) != '\n') {
        name[a] = ch;
        ++a;
        if(a == 31) {
            break;
        }
    }

    name[a] = '\0';
    strcpy(buffer, name);
    strcat(buffer, " ");
    strcat(buffer, last);

    // Display the result
    a = 0;
    while(putchar(buffer[a++]));

    return 0;
}