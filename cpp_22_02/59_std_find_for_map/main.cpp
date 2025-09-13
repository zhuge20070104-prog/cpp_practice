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
  int t[] = {10, 5, 9, 6, 2, 4, 7, 8, 3, 1};

  std::map<int, int> m;
  for(int i=0; i<10; i++) {
    m[i] = t[i];
  }

  // 编译错误, std::find 作用于std::pair才行
  // std::map<int, int>::iterator it = std::find(m.begin(), m.end(), 5);
  std::pair<const int, int> pair_(5, 4);
  std::map<int, int>::iterator it = std::find(m.begin(), m.end(), pair_);
  std::cout << it->first;

  return EXIT_SUCCESS;
} 

