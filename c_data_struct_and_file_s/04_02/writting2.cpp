#include <cstdio>

int main(int argc, char* argv[]) {
    FILE* fh;

    fh = fopen("alphabet.txt", "w");
    if(fh == nullptr) {
        puts("Fail to create file.");
        return -1;
    }

    for(int i='A'; i<'Z'; ++i) {
        fputc(i, fh);
    }

    fclose(fh);
    
    return 0;
}