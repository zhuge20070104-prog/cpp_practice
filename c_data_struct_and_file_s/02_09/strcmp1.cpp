#include <cstdio>
#include <cstring>

int main(int argc, char* argv[]) {
    char r[] = "red";
    char g[] = "green";
    char b[] = "blue";

    if(strcmp(r, "blue") == 0) {
        printf("%s compares with \"blue\"\n", r);
    }

    if(strcmp(g, "blue") == 0) {
        printf("%s compares with \"blue\"\n", g);
    }

    if(strcmp(b, "blue") == 0) {
        printf("%s compares with \"blue\"\n", b);
    }
    
    return 0;
}