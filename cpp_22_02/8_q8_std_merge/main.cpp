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

class B {
    int val;

public:
    B(int v): val(v) {}

    // Default constructor, 
    // B(): val(0) {}

    int getV() const {
        return val;
    }

    bool operator<(B const& v) const {
        return val < v.val;
    }
};

  
std::ostream& operator<<(std::ostream& os, B const& v) {
    os << v.getV();
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
    B t2[] = {6, 10, 8, 7, 9};

    // Compilation error, no default constructor
    std::vector<B> v1(10);
    std::sort(t1, t1+5);
    std::sort(t2, t2+5);

    std::merge(t1, t1+5, t2, t2+5, v1.begin());

    std::for_each(v1.begin(), v1.end(), Out<B>(std::cout));
    std::cout << std::endl;

    return EXIT_SUCCESS;
} 

