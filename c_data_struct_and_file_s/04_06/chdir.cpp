#include <cstdio>
#include <unistd.h>

int main(int argc, char* argv[]) {
    char path[512];
    chdir("..");
    getcwd(path, 512);
    printf("This program's parent directory is %s\n", path);
    
    return 0;
}