#include <cstdio>
#include <cstring>


int main(int argc, char* argv[]) {
    char first[16] = "George";
    char last[16] = "Washington";
    char full[32];

    strcpy(full, first);
    strcat(full, last);
    printf("Pleased to meet you, %s\n", full);
    
    return 0;
}