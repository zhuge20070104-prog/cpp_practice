#include <cstdio>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char* argv[]) {
    DIR* directory;
    struct dirent* file;
    struct stat fstat;

    directory = opendir(".");
    if(directory == nullptr) {
        puts("Unable to open current directory");
        return -1;
    }

    printf("%-25s %-10s %s\n", "Filename", "size", "Timestamp");
    
    while((file = readdir(directory)) != nullptr) {
        stat(file->d_name, &fstat);

        printf("%-25s %10lld ", file->d_name, fstat.st_size);
        printf("%s", ctime(&fstat.st_mtime));
    }

    closedir(directory);
    return 0;
}