#include <cstdio>

int main(int argc, char* argv[]) {
    char const* original = "../beta.txt";
    char const* duplicate = "../betacopy.txt";

    FILE* org, *dup;

    int c;

    org = fopen(original, "r");
    dup = fopen(duplicate, "w");
    if(org == nullptr || dup == nullptr) {
        puts("Unable to open file for copying");
        return -1;
    }

    while(1) {
        c = fgetc(org);
        if(c == EOF) {
            break;
        }
        fputc(c, dup);
    }


    printf("%s copied to %s\n", original, duplicate);
    fclose(org);
    fclose(dup);

    return 0;
}