#include <cstdio>
#include <dirent.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
    DIR* directory;
    struct dirent* file;
    struct stat fstat;

    directory = opendir(".");
    if(directory == nullptr) {
        puts("Unable to open current directory");
        return -1;
    }

    printf("%-5s %-20s %-10s %s\n", "Type", "Filename", "Size", "Timestamp");

    while((file=readdir(directory)) != nullptr) {
        stat(file->d_name, &fstat);
        if(S_ISDIR(fstat.st_mode)) {
            printf(" Dir ");
        } else {
            printf("File ");
        }

        printf("%20s %10ld %ld\n", 
            file->d_name, 
            fstat.st_size,
            fstat.st_mtime); // Timestamp (modification time)
    }

    closedir(directory);
    return 0;
}