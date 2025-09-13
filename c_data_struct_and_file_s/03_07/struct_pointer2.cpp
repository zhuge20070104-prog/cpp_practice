#include <cstdlib>
#include <cstdio>
#include <cstring>


int main(int argc, char* argv[]) {  
    struct person {
        char name[32];
        int age;
    } *you;

    you = (person*)malloc(sizeof(person) * 1);
    if(you == nullptr) {
        puts("Unable to allocate storage");
        exit(1);
    }

    printf("Enter your name: ");
    fgets(you->name, 32, stdin);

    printf("Enter your age: ");
    scanf("%d", &you->age);


    printf("You are %s", you->name);
    printf("You are %d years old\n", you->age);
    
    return 0;
}