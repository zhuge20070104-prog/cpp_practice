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

template <typename T>
void print(T start, T end) {
  while(start != end) {
    std::cout << *start++;
  }
}

int main(int argc, char* argv[]) {
    std::string t[] = {"one", "two", "three", "four", "five"};
    std::vector<std::string> v1(t, t+5);
    std::deque<std::string> d1(v1.rbegin(), v1.rend());

    d1.push_back("zero");

    // Expect output: evif
    print(d1[0].rbegin(), d1[0].rend());
    return EXIT_SUCCESS;
} 

