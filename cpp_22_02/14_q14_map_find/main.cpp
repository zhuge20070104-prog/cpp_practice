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


int main(int argc, char* argv[]) {
    int t[] = {10, 5, 9, 6, 2, 4, 7, 8, 3, 1};
    std::map<int, int> m;
    for(int i=0; i<10; i++) {
        m[i] = t[i];
    }

    std::pair<const int, int> p(5, 5);
    std::map<int, int>::iterator it = std::find(m.begin(), m.end(), p);
    
    // Expect output: Not found. 取决于std::pair的operator==操作符
    // p1.first == p2.first and p1.second == p2.second
    if(it != m.end()) {
        std::cout << it->first << std::endl; 
    } else {
        std::cout << "Not found!\n";
    }


    return EXIT_SUCCESS;
} 

