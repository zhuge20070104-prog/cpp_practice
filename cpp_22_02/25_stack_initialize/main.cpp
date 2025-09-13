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
    std::deque<int> mydeck;
    std::list<int> mylist;

    // forward_list也可以吗？也不崩？
    // .. 奇葩
    std::forward_list<int> myforwardlist;

    // Expect output: Line I II III IV V VI 
    // 都是对的
    std::vector<int> myvector;
    std::stack<int> first;  // Line I
    std::stack<int> second(mydeck); // Line II
    std::stack<int> third(second); // Line III
    std::stack<int, std::list<int>> forth(mylist); // Line IV
    std::stack<int, std::vector<int>> fifth(myvector); // Line V
    std::stack<int, std::forward_list<int>> sixth(myforwardlist); // Line VI
    return EXIT_SUCCESS;
} 

