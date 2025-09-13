#include <cstdio>
#include <cstdlib>

int* make_array(int size) {
    int* p;
    p = (int*) malloc(sizeof(int) * size);

    if(p == nullptr) {
        puts("Unable to allocate memory");
        exit(1);
    }

    for(int i = 0; i < size; ++i) {
        *(p+i) = (i+1) * 10;
    }
    
    return p;
}

int main(int argc, char* argv[]) {
    int* x;
    x = make_array(5);
    
    for(int i = 0; i < 5; ++i) {
        printf("%d\n", *(x+i));
    }
    return 0;
}