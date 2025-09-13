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


void print(int v) {
  std::cout << v << " ";
}

struct Sequence {
  int start;

  Sequence(int start): start(start) {}

  int operator()() {
    return start++;
  }
};

bool predicate(int v) {
  return v % 2 == 0;
} 

int main(int argc, char* argv[]) {
  std::vector<int> v1(10);  
  std::generate_n(v1.begin(), 10, Sequence(1));
  std::set<int> s1(v1.begin(), v1.end());

  // Expect output: Compilation error
  // std::remove_if(s1.begin(), s1.end(), predicate);

  for(auto it = s1.begin(); it!=s1.end();)  {
    if(predicate(*it)) {
      it = s1.erase(it);
    } else {
      ++it;
    }
  }

  std::for_each(s1.begin(), s1.end(), print);

  std::cout << std::endl;

  return EXIT_SUCCESS;
} 

