#include <cstdio>
#include <cstdlib>

int main(int argc, char* argv[]) {
    char* buffer;
    buffer = (char*)malloc(sizeof(char) * 128);
    if(buffer == nullptr) {
        puts("Unable to allocate memory");
        return -1;
    }

    puts("Buffer allocated");
    free(buffer);
    puts("Buffer freed");
    return 0;
}