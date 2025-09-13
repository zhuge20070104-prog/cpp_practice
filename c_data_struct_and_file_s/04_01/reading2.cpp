#include <cstdio>

int main(int argc, char* argv[]) {
    char const* filename = "../sonnet18.txt";
    int ch;
    FILE* fh;

    fh = fopen(filename, "r");
    if(fh == nullptr) {
        printf("Unable to read from file %s\n", filename);
        return -1;
    }
    
    printf("File '%s' opened\n", filename);

    while(1) {
        ch = fgetc(fh);
        if(ch == EOF) {
            break;
        }

        putchar(ch);
    }
    
    fclose(fh);
    
    return 0;
}