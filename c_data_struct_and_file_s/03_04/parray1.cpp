#include <cstdio>

int main(int argc, char* argv[]) {
    char text[10];
    printf("Type something: ");
    scanf("%9s", (char*)text);
    printf("You typed: %s\n", text);
}