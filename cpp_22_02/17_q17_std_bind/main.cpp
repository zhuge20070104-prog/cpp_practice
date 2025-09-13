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


int Add(int a, int b) {
    return a + b;
}


int main(int argc, char* argv[]) {
    int t[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v1(t, t + 10);
    std::vector<int> v2(10);

    std::transform(v1.begin(), v1.end(), v2.begin(), std::bind2nd(std::ptr_fun(Add), 1));

    std::vector<int>::iterator it = std::find_if(v2.begin(), v2.end(), std::bind2nd(std::equal_to<int>(), 10));
    // Expect output: 10
    std::cout << *it << std::endl;

    return EXIT_SUCCESS;
} 

