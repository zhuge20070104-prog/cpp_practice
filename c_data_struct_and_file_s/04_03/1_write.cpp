#include <cstdio>

int main(int argc, char* argv[]) {
    char const* file_name = "integers.dat";
    FILE* fp;
    int a;

    fp = fopen(file_name, "w");
    if(fp == nullptr) {
        printf("Unable to create %s\n", file_name);
        return -1;
    }

    a = 10;
    for(int i=0; i<10; ++i) {
        fwrite(&a, sizeof(int), 1, fp);
        a += 5;
    }

    fclose(fp);

    return 0;
}