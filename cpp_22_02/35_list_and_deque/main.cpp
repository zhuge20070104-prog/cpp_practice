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


int main(int argc, char* argv[]) {
    std::list<int> l1;
    std::deque<int> d1;

    // 4 3 2 1 0 0 1 2 3 4
    for(int i=0; i<5; ++i) {
        l1.push_back(i); l1.push_front(i);
        d1.push_back(i); d1.push_front(i);
    }

    // Expect output: compilation error due to line 16
    // std::list has no random access iterator
    // it doesn't support [] operator overloading
    // for(int i=0; i<d1.size(); ++i) {
    //     std::cout << d1[i] << " " << l1[i] << " ";
    // }


    // Expect output: 4 4 3 3 2 2 1 1 0 0 0 0 1 1 2 2 3 3 4 4
    decltype(d1.begin()) d_it;
    decltype(l1.begin()) l_it;
    for(d_it = d1.begin(), l_it = l1.begin();d_it!=d1.end() && l_it != l1.end(); ++d_it, ++l_it) {
        std::cout << *d_it << " " << *l_it << " ";
    }

    std::cout << std::endl;
    return EXIT_SUCCESS;
} 

