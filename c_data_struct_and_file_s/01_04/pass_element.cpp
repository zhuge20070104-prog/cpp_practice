#include <stdio.h>

void incshow(char a) {
    a++;
    putchar(a);
}

int main(int argc, char* argv[]) {
    char text[] = "Gdkkn";
    int x = 0;
    for(x=0; x<6; ++x) {
        incshow(text[x]);
    }    
    putchar('\n');
    
    // 这个没有改变原值，因为每个char都是值传递
    puts(text);
    
    return 0;
}