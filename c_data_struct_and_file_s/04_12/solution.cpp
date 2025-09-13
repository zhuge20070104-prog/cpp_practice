#include <cstdio>
#include <unistd.h>
#include <dirent.h>


#define SIZE 512


int main(int argc, char* argv[]) {
    DIR* directory;
    FILE* output;

    struct dirent* entry;

    char path[SIZE];

    char const* filename = "filelist.txt";
    int x, r;

    output = fopen(filename, "w");
    if(output == nullptr) {
        printf("Unable to create file %s\n", filename);
        return -1;
    }

    printf("Enter the directory to examine: ");
    fgets(path, SIZE, stdin);
    for(x=0; x<SIZE; ++x) {
        if(path[x] == '\n') {
            path[x] ='\0';
            break;
        }
    }

    r = chdir(path);
    if(r != 0) {
        printf("Unable to change to '%s'\n", path);
        fclose(output);
        return -1;
    }

    directory = opendir(path);

    if(directory == nullptr) {
        printf("Unable to open directory: %s\n", path);
        fclose(output);
        return -1;
    }


    while((entry=readdir(directory)) != nullptr) {
        fprintf(output, "%s\n", entry->d_name);
    }

    printf("%s created listing files in %s\n", filename, path);

    fclose(output);
    closedir(directory);
    return 0;
}