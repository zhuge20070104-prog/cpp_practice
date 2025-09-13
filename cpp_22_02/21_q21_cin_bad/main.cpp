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
    
    std::list<int> l;
    // Expect output: std::cin.bad()会卡住，因为检测不到cin.bad()
    for(;;) {
        int i;
        std::cin >> i;
        if(std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            break;
        }
        l.push_back(i);
    }

    std::for_each(l.begin(), l.end(), Out<int>(std::cout));
    
    return EXIT_SUCCESS;
} 

