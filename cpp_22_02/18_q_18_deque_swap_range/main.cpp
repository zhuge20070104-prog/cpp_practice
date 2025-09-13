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
#include <deque>
#include <list>
#include <iomanip>


void myfunction(int i) {
    std::cout << " " << i;
}


int main(int argc, char* argv[]) {
    int t[] = {10, 5, 9, 6, 2, 4, 7, 8, 3, 1};
    std::deque<int> d1(t, t + 10);
    std::vector<int> v1(d1.rbegin(), d1.rend());

    std::sort(d1.begin(), d1.end());
    std::swap_ranges(v1.begin(), v1.end(), d1.begin());

    std::for_each(v1.begin(), v1.end(), myfunction);
    std::for_each(d1.begin(), d1.end(), myfunction);
    
    return EXIT_SUCCESS;
} 

