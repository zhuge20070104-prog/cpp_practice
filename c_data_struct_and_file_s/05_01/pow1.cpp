#include <cstdio>
#include <cmath>


int main(int argc, char* argv[]) {
    for(double a=0.0; a<20.0; a+=1.0) {
        printf("%.0f\n", pow(2.0, a));
    }
    return 0;
}