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

class B {
    int val;

public:
    B(int v): val(v) {}

    int getV() const {
        return val;
    }

    bool operator<(B const& v) const {
        return val < v.val;
    }

    bool operator>(B const& v) const {
        return val > v.val;
    }

};


std::ostream& operator<<(std::ostream& out, B const& v) {
    out << v.getV();
    return out;
}

template <class T>
struct Out {
    std::ostream& out;

    Out(std::ostream& o): out(o) {}

    void operator()(T const& val) const {
        out << val << " ";
    }
};

int main(int argc, char* argv[]) {
    int t[] = {8, 10, 5, 1, 4, 6, 2, 7, 9, 3};
    std::deque<B> d1(t, t+10);

    // 输出第一个小于4的, 3 2 1
    // std::sort和std::upper_bound的排序顺序必须一致
    // std::sort(d1.begin(), d1.end(), std::greater<B>());
    // // Expect output: Compilation error
    // // comp -->  std::greater<B> ==>  需要重载 > 号才行
    // std::deque<B>::iterator it = std::upper_bound(d1.begin(), d1.end(), B(4), std::greater<B>());


    // 第一个不小于4的， 5 6 7 8 9 10
    std::sort(d1.begin(), d1.end());
    std::deque<B>::iterator it = std::upper_bound(d1.begin(), d1.end(), B(4));

    std::for_each(it, d1.end(), Out<B>(std::cout));
    std::cout << std::endl;

    return EXIT_SUCCESS;
} 

