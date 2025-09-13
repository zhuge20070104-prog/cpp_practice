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


bool identical(int a, int b) {
  return b == 2*a ? true: false;
}

int main(int argc, char* argv[]) {
  int t[] = {1,2,3,2,3,5,1,2,7,3,2,1,10, 4,4,5};
  int u[] = {2,4,6,4,6,10,2,4,14,6,4,2,20,8,8,5};

  std::vector<int> v1(t, t+15);
  std::deque<int> d1(u, u+15);

  std::pair<std::deque<int>::iterator, std::vector<int>::iterator> result;
  result = std::mismatch(d1.begin(), d1.end(), v1.begin(), identical);

  // 選B,輸出 not identical
  if(result.first == d1.end() && result.second == v1.end()) {
    std::cout << "Identical\n";
  } else {
    std::cout << "Not identical\n";
  }
  
  return EXIT_SUCCESS;
} 

