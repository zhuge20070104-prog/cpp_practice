#include <cassert>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <string>
#include <map>
#include <set>
#include <list>
#include <iomanip>


void myfunction(int i) {
    std::cout << " " << i;
}

void multiply(int a) {
    a * 2;
}

int main(int argc, char* argv[]) {
   
    int t[] = {10, 5, 9, 6, 2, 4, 7, 8, 3, 1};

    std::vector<int> v1(t, t+10);
    std::for_each(v1.begin(), v1.end(), multiply);
    std::iter_swap(v1.begin(), t+9);
    // Expect output: 1 5 9 6 2 4 7 8 3 1
    std::for_each(v1.begin(), v1.end(), myfunction);

    return EXIT_SUCCESS;
} 

