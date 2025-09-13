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
    // Expect output: 10, 跟那个Out类没关系
    std::cout << *std::max_element(v1.begin(), v1.end());

    return EXIT_SUCCESS;
} 

