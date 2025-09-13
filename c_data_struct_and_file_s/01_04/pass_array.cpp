#include <stdio.h>

void incshow(char array[]) {
    int x;
    for(x=0; x<6; ++x) {
        array[x]++;
        putchar(array[x]);
    }
}

int main(int argc, char* argv[]) {
    char text[] = "Gdkkn";
    incshow(text);
    putchar('\n');
    puts(text);
    
    return 0;
}