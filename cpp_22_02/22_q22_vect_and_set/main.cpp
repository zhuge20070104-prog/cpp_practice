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
void print(T start, T end) {
    while(start != end) {
        std::cout << *start << " ";
        start ++;
    }
}

int main(int argc, char* argv[]) {
    
    std::vector<int> v;
    std::multiset<int> s;

    // Expect output: multiset 和 set没有push_back, 
    // Compilation error
    for(int i=10; i>0; i--) {
        v.push_back(i);
        s.insert(i);
        // s.push_back(i);
    }

    print(v.begin(), v.end());
    print(s.begin(), s.end());
    std::cout << std::endl;

    return EXIT_SUCCESS;
} 

