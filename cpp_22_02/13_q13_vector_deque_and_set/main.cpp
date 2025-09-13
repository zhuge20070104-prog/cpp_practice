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
    std::vector<int> v1(t, t + 10);
    std::deque<int> d1(t, t + 10);
    std::set<int> s1(t, t + 10);

    // Expect output:  10 5 9 6 2 4 7 8 3 1 10 5 9 6 2 4 7 8 3 1 1 2 3 4 5 6 7 8 9 10
    // 只有set会做输出排序
    std::for_each(v1.begin(), v1.end(), myfunction);
    std::for_each(d1.begin(), d1.end(), myfunction);
    std::for_each(s1.begin(), s1.end(), myfunction);
    return EXIT_SUCCESS;
} 

