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
#include <stack>
#include <forward_list>
#include <iomanip>

class B {
    int val;

public:
    B(int v): val(v) {}

    int getV() const {
        return val;
    }

    bool operator<(B const& other) const {
        return val < other.val;
    }
};

std::ostream& operator<<(std::ostream& os, B const& b) {
    os << b.getV();
    return os;
}


template <class T>
struct Out {
    std::ostream& out;

    Out(std::ostream& o): out(o) {}

    void operator()(T const& val) {
        out << val << " ";
    }
};

int main(int argc, char* argv[]) {
    
    B t1[] = {3, 2, 4, 1, 5};
    B t2[] = {5, 6, 8, 2, 1};

    std::vector<B> v1(10, 0);

    std::sort(t1, t1 + 5);
    std::sort(t2, t2 + 5);

    // 就是排序以后，找寻不一样的值
    // 1 2 3 4 5
    // 1 2 5 6 8
    // Expect output:  3 4 6 8
    std::set_symmetric_difference(t1, t1+5, t2, t2+5, v1.begin());

    std::for_each(v1.begin(), v1.end(), Out<B>(std::cout));
    
    std::cout << std::endl;  
    return EXIT_SUCCESS;
} 

