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
public:
    B(int v=0): val(v) {}
    int getV() const { return val; }

    operator int() const {
        return val;
    }

private:
    int val;
};

B  operator+(B const& a, B const& b) {
    return B(a.getV() + b.getV());
}

std::ostream& operator<<(std::ostream& out, B const& b) {
    out << b.getV();    
    return out;
}


template <class T>
struct Out {
    std::ostream& out;

    Out(std::ostream& o): out(o) {}

    void operator()(T const& val) {
        out << val << " ";
    }
};

struct Add {
    B operator()(B const& a, B const& b) const {
        return a + b;
    }
};


int main(int argc, char* argv[]) {
    
    int t[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<B> v1(t, t+10);
    std::vector<B> v2(10);
    
    // Expect output: bind1st会造成编译错误
    // 改成lambda: 输出 11 10 9 8 7 6 5 4 3 2
    std::transform(v1.begin(), v1.end(), v2.begin(), [](B const& b) {
        return B(1) + b;
    });

    std::for_each(v2.rbegin(), v2.rend(), Out<B>(std::cout));

    std::cout << std::endl;
    return EXIT_SUCCESS;
} 

