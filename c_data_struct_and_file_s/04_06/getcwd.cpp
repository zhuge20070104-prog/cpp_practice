#include <cstdio>
#include <unistd.h>

int main(int argc, char* argv[]) {
    char path[512];
    getcwd(path, 512);

    printf("This prorgam is running in the %s directory\n", path);

    return 0;
}