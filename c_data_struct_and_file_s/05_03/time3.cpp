#include <cstdio>
#include <ctime>


int main(int argc, char* argv[]) {
    time_t now;
    struct tm* timestamp;

    time(&now);

    timestamp = localtime(&now);

    printf("It's now %d:%02d:%02d\n",
        timestamp->tm_hour,
        timestamp->tm_min,
        timestamp->tm_sec);

    return 0;
}