#include "scanner.h"
#include "printer.h"
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
    B(int v=0): val(v) {}

    int getV() const {
        return val;
    }

    operator int() const  {
        return val;
    }

    // TODO: 这里不重载是compilation error
    friend std::istream& operator >> (std::istream& is, B& b) {
        is >> b.val;
        return is;
    }
};

template <class T> 
struct Out {
    std::ostream& out;
    Out(std::ostream& o): out(o) {

    }

    void operator()(T const& val) {
        out << std::setw(3) << std::hex << val;
    }
};


int main(int argc, char* argv[]) {
    int t[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::fstream f("test.out",  std::ios::out);
    std::list<B> l(t, t+10);
    std::for_each(l.begin(), l.end(), Out<B>(f));

    f.close();

    f.open("test.out");

    // Expect output: f >> i 这里有个编译错误 
    for(;f.good();) {
        B i;
        f >> i;

        std::cout << i << " ";
    }

    f.close();
    return EXIT_SUCCESS;
} 

