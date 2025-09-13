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

int main(int argc, char* argv[]) {
    int t[] = {3, 4, 2, 1, 6, 5, 7, 9, 8, 0};
    std::vector<int> v(t, t+10);
    std::multiset<int> s1(v.begin(), v.end());
    s1.insert(v.begin(), v.end());
    std::pair<std::multiset<int>::iterator, std::multiset<int>::iterator> range;

    range = s1.equal_range(6);
    // output 6 6
    while(range.first != range.second) {
        std::cout << *range.first << " ";
        range.first++;
    }

    return EXIT_SUCCESS;
}


