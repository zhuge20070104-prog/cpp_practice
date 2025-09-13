#include <cstdio>
#include <dirent.h>

int main(int argc, char* argv[]) {
    DIR* directory;
    dirent* file;
    directory = opendir(".");
    if(directory == nullptr) {
        puts("Unable to open current directory");
        return -1;
    }

    while((file = readdir(directory)) != nullptr) {
        printf("Found the file %s\n", file->d_name);
    }
    
    closedir(directory);
    return 0;
}