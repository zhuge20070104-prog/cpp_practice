#include <cstdio>

void change(char s[]) {
    s[1] = 'a';
}

int main(int argc, char* argv[]) {
    char pet[] = "cot";
    puts(pet);

    change(pet);
    puts(pet);

    return 0;
}