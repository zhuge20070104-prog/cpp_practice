#include <cstdio>
#include <ctime>

int main(int argc, char* argv[]) {
    time_t now;
    time(&now);

    printf("It is now %ld\n", now);
    return 0;
}