#include <cstdio>
#include <cstdlib>
#include <cstring>

int main(int argc, char* argv[]) {
    char* fruit[10];
    char buffer[32];

    for(int i=0; i<10; ++i) {
        printf("Enter fruit %d: ", i+1);
        fgets(buffer, 32, stdin);

        fruit[i] = (char*)malloc(strlen(buffer) + 1);
        if(fruit[i] == nullptr) {
            puts("Memory allocation failed");
            exit(1);
        }

        strcpy(*(fruit + i), buffer);
    }

    for(int i=0; i<10; ++i) {
        printf("%s", *(fruit + i));
    }

    return 0;
}