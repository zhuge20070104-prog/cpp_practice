#include <cstdio>
#include <cstdlib>
#include <ctime>


#define SIZE 100


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

    for(int i=0; i<SIZE-1; ++i) {
        for(int j=i+1; j<SIZE; ++j) {
            if(list[i] > list[j]) {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }

    printf("%d random values, sorted\n", SIZE);
    for(int i=0; i<SIZE; ++i) {
        printf("%4d", list[i]);
    }

    putchar('\n');

    return 0;
}