#include <cstdio>
#include <cstring>

int main(int argc, char* argv[]) {
    char original[] = "Am I the original?";
    char duplicate[] = "Overwritten";

    printf("Here is the original string: %s\n", original);
    strcpy(duplicate, original);
    printf("Here is the duplicate: %s\n", duplicate); 
    return 0;
}