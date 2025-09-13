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
    int t[] = {3, 4, 2, 1, 6, 5, 7, 9, 8, 0};
    std::vector<int> v(t, t + 10);

    std::set<int> s1(v.begin(), v.end());

    s1.insert(v.begin(), v.end());

    // Expect output: Code not compile
    // bool found = s1.find(7);
    bool found = s1.find(7) != s1.end();
    
    if(found) {
        std::cout << "Element found!\n";
    } else {
        std::cout << "Element not found!\n";
    }
    return EXIT_SUCCESS;
} 

