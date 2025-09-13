#include <cstdio>
#include <cstdlib>

char* allocate(int size) {
    char* p;
    p = (char*)malloc(size);

    if(p == nullptr) {
        puts("Unable to allocate memory");
        exit(1);
    }

    return p;
}

int main(int argc, char* argv[]) {
    char* a, *b;

    printf("Allocating 256 bytes:");
    a = allocate(256);  
    puts("Done");

    printf("Allocateing 512 bytes:");
    b = allocate(512); 
    puts("Done");

    return 0;
}