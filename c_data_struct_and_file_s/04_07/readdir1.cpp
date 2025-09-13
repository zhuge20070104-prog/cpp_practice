#include <cstdio>
#include <dirent.h>

int main(int argc, char* argv[]) {
    DIR* directory;

    directory = opendir(".");
    if(directory == nullptr) {
        puts("Unable to open current directory");
        return -1;
    }

    puts("Opened current directory");
    closedir(directory);
}