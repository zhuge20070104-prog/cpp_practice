#include <cstdio>
#include <cstring>

int main(int argc, char* argv[]) {
    char needle[] = "heart";
    char haystack[] = "Get to the heart of the matter";

    char* found = nullptr;
    found = strstr(haystack, needle);
    if(found == nullptr) {
        printf("The string \"%s\" was not found in \"%s\".\n", needle, haystack);
    } else {
        printf("The string \"%s\" was found at offset %ld in  \"%s\".\n", 
            needle, found - haystack, haystack);
    }
    return 0;
    return 0;
}