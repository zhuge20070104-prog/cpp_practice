#include <cstdio>

int main(int argc, char* argv[]) {
    char const* filename = "../sonnet18.txt";
    FILE* fh;

    fh = fopen(filename, "r");
    if(fh == nullptr) {
        printf("Unable to read from file %s\n", filename);
        return -1;
    }

    printf("File '%s' opened\n", filename);
    fclose(fh);
    
    return 0;
}