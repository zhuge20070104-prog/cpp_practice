#include <cstdio>
#include <cstdlib>
#include <cstring>


int main(int argc, char* argv[]) {
    struct person {
        char* name;
        int age;
    } you;

    char buffer[32];
    printf("Enter your name: ");
    fgets(buffer, 32, stdin);

    you.name = (char*)malloc(strlen(buffer) + 1);
    if(you.name == nullptr) {
        puts("Unable to allocate storage");
        exit(-1);
    }

    strcpy(you.name, buffer);

    printf("Enter your age: ");
    scanf("%d", &you.age);

    printf("You are %s", you.name);
    printf("You are %d years old\n", you.age);

    return 0;
}