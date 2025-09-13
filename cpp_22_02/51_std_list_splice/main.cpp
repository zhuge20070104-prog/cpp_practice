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

template <class T>
void print(T start, T end) {
  while(start != end) {
    std::cout << *start << " ";
    start++;
  }
}


int main(int argc, char* argv[]) {
  std::string t1[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};
  std::list<std::string> l1(t1, t1+10);
  std::list<std::string> l2(l1);

  l2.reverse();

  l1.splice(l1.end(), l2);
  l1.unique();

  // Expect output: 1 2 3 4 5 6 7 8 9 10 9 8 7 6 5 4 3 2 1
  print(l1.begin(), l1.end());
  std::cout << std::endl;  

  return EXIT_SUCCESS;
} 

