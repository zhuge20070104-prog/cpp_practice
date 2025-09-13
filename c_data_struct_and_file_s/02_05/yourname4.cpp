#include <cstdio>

int main(int argc, char* argv[]) {
    char input[10];
    int i;

    printf("Your name? ");
    fgets(input, 10, stdin);

    // 替换 换行符为 null character
    for(i=0; i<10; ++i) {
        if(input[i] == '\n') {
            input[i] = '\0';
        }
    }

    printf("Pleased to meet you, %s\n", input);
    
    return 0;
}