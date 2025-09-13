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

void myfunction(std::pair<int, int> i) {
  std::cout << " " << i.first;
}

int main(int argc, char* argv[]) {
  int t[] = {10, 5, 9, 6, 2, 4, 7, 8, 3, 1};

  std::map<int, int> m;
  for(int i=0; i<10; i++) {
    m[i] = t[i];
  } 

  // Expect output:  0 1 2 3 4 5 6 7 8 9
  std::for_each(m.begin(), m.end(), myfunction);

  return EXIT_SUCCESS;
} 

