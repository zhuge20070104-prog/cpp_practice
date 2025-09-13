#include <cstdio>
#include <cstdlib>

int main(int argc, char* argv[]) {
    int* buffer;
    buffer = (int*)malloc(sizeof(int) * 20);
    if(buffer == nullptr) {
        puts("Unable to allocate memory");
        return -1;
    }

    for(int i=0; i<20; ++i) {
        *(buffer + i) = 10 * (i+1);
        printf("%d\n", *(buffer + i));
    }

    free(buffer);
    
    return 0;
}