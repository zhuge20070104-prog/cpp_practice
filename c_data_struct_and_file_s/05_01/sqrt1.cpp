#include <cstdio>
#include <cmath>


int main(int argc, char* argv[]) {
    double a = 4294967296.0;
    while(a >= 2.0) {
        printf("%.f\n", a);
        a = sqrt(a);
    }
    return 0;
}