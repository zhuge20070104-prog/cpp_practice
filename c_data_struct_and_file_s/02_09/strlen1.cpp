#include <cstdio>
#include <cstring>


int main(int argc, char* argv[]) {
    char str[] = "Hello, you happy planet.";
    int len;

    len = strlen(str);
    printf("The string \"%s\" is %d characters long\n", str, len);
    return 0;
}