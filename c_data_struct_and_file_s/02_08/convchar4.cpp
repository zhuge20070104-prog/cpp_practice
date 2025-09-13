#include <cstdio>

int main(int argc, char* argv[]) {
    char string[] = "Deadly spiders!";

    puts("String displayed with %s:");
    printf("%s\n", string);
    puts("String displayed in a 24-character width:");
    printf("%24s\n", string);
    puts("24-character width, left-justified:");
    printf("%-24s\n", string);  
    puts("24-character width, 6 characters truncated:");
    printf("%24.6s\n", string);
    puts("24-character width, 6 characters truncated, left-justified:");
    printf("%-24.6s\n", string);
    return 0;
}