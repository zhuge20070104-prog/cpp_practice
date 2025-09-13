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
    int t[] = {1, 2, 3, 2, 3, 5, 1, 2, 7, 3, 2, 1, 10, 4, 4, 5};
    std::vector<int> v(t, t + 15);

    // Expect output: 4
    // 4个2
    int number = std::count(v.begin(), v.end(), 2);

    std::cout << number << std::endl;


    return EXIT_SUCCESS;
} 

