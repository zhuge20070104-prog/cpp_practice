#include <cstdio>
#include <sys/stat.h>
#include <time.h>


int main(int argc, char* argv[]) {
    char const* filename = "../alpha.txt";
    struct stat fstat;

    stat(filename, &fstat);

    printf("%s is %ld bytes long\n",
        filename, fstat.st_size);
    
    printf("It was modified on %s", ctime(&fstat.st_mtime));
    
    return 0;
}