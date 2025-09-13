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

template <class T>
struct Out {
    std::ostream& out;

    Out(std::ostream& o): out(o) {}

    void operator()(T const& val) {
        out << val << " ";
    }
};


int main(int argc, char* argv[]) {
    int t[] = {3,2,4,1,5,10,9,7,8,6};
    std::vector<int> v1(t, t+10);
    std::sort(v1.begin(), v1.end(), std::greater<int>());
    // Expect output: std::min_element是一个迭代器，无法直接输出
    std::cout << *std::min_element(v1.begin(), v1.end());

    return EXIT_SUCCESS;
} 

