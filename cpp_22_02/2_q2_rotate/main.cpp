#include "scanner.h"
#include "printer.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <string>
#include <map>
#include <set>

template <class T>
struct Out {
    std::ostream& out;
    Out(std::ostream& o): out(o) {}

    void operator()(T const& val) {
        out << val << " ";
    }
};


struct Sequence {
    int start;

    Sequence(int start): start(start) {}

    int operator()() {
        return start++;
    }
};


int main(int argc, char* argv[]) {
    std::vector<int> v1(10);
    std::generate(v1.rbegin(), v1.rend(), Sequence(1));
    std::rotate(v1.begin(), v1.begin() + 1, v1.end());
    
    // Expect Output: 9 8 7 6 5 4 3 2 1 10
    std::for_each(v1.begin(), v1.end(), Out<int>(std::cout));
    std::cout << std::endl;

    return EXIT_SUCCESS;
}


