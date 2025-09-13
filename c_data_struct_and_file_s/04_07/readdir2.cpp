#include <cstdio>
#include <dirent.h>

int main(int argc, char* argv[]) {
    DIR* directory;
    struct dirent* file;
    
    directory = opendir(".");
    if(directory == nullptr) {
        puts("Unable to open current directory");
        return -1;
    }

    file = readdir(directory);
    printf("Found the file %s\n", file->d_name);
    
    closedir(directory);
    return 0;
}