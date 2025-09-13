#include <cstdio>
#include <ctime>

int main(int argc, char* argv[]) {
    time_t now;
    time(&now);

    printf("It is now %s", ctime(&now));
    return 0;
}