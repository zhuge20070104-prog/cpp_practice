#include <cstdio>

int main(int argc, char* argv[]) {
    char const* file_name = "./integers.dat";
    FILE* fp;
    int a;

    fp = fopen(file_name, "r");
    if(fp == nullptr) {
        printf("Unable to open file %s\n", file_name);
        return -1;
    }

    for(int i=0; i<10; ++i) {
        fread(&a, sizeof(int), 1, fp);
        printf("%d\n", a);
    }

    fclose(fp);
    
    return 0;
}