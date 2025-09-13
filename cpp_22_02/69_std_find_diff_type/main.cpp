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
  std::vector<int>v1;
  std::deque<int>d1;

  for(int i=0; i<5; i++) {
    // Compilation error: std::vector has no push_front
    v1.push_back(i); /*v1.push_front(i);*/ v1.insert(v1.begin(), i);
    d1.push_back(i); d1.push_front(i);
  } 

  // 4 4 3 3 2 2 1 1 0 0 0 0 1 1 2 2 3 3 4 4
  for(int i=0; i<d1.size(); i++) {
    std::cout << d1[i] << " " << v1[i] << " ";
  }

  std::cout << std::endl;

  return EXIT_SUCCESS;
} 

