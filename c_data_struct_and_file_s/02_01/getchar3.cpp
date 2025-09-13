#include <cstdio>

int main(int argc, char* argv[]) {
    char ch1, ch2;
    printf("Type two characters: ");
    ch1 = getchar();
    ch2 = getchar();

    printf("Characters '%c' and '%c' received\n", ch1, ch2);
    return 0;
}