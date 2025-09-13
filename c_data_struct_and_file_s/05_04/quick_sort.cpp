#include <cstdio>
#include <cstdlib>
#include <ctime>


#define SIZE 100

int compare(const void* a, const void* b) { 
    return (*((int*)a) - *((int*)b));
}
int main(int argc, char* argv[]) {
    int list[SIZE];
    int b, temp;

    srand((unsigned)time(nullptr));
    printf("%d random values, unsorted\n", SIZE);

    for(int i=0; i<SIZE; ++i) {
        list[i] = rand() % 100 + 1;
        printf("%4d", list[i]);
    }

    putchar('\n');

    qsort(list, SIZE, sizeof(int), compare);
 
    printf("%d random values, sorted\n", SIZE);
    for(int i=0; i<SIZE; ++i) {
        printf("%4d", list[i]);
    }

    putchar('\n');

    return 0;
}