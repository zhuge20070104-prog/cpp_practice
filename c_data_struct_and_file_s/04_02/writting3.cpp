#include <cstdio>

int main(int argc, char* argv[]) {
    FILE* fh;

    fh = fopen("alphabet.txt", "a");
    if(fh == nullptr) {
        puts("Fail to create file.");
        return -1;
    }

    fputc('\n', fh);
    
    fclose(fh);
    
    return 0;
}