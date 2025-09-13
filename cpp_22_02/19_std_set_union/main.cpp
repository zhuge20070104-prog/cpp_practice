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
    
    int t1[] = {3, 2, 4, 1, 5};
    int t2[] = {5, 6, 8, 2, 1};

    std::vector<int> v1(10);

    std::sort(t1, t1+5);
    std::sort(t2, t2+5);

    std::set_union(t1, t1+5, t2, t2+5, v1.begin());

    // Expect output, 1 2 3 4 5 6 8 0 0 0
    // 参考set_union的定义
    std::for_each(v1.begin(), v1.end(), Out<int>(std::cout));
    std::cout << std::endl;

    return EXIT_SUCCESS;
} 

