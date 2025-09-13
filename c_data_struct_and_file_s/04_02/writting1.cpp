#include <cstdio>

int main(int argc, char* argv[]) {
    FILE* fh;

    fh = fopen("output.txt", "w");
    if(fh == nullptr) {
        puts("Fail to create file.");
        return -1;
    }

    fprintf(fh, "Hello there, file!\n");

    fclose(fh);
    
    return 0;
}