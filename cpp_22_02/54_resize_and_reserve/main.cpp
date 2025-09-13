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
  int t[] = {1, 2, 3, 4, 5};
  std::vector<int> v1(t, t+5);
  std::vector<int> v2(v1);

  v1.resize(10);
  v2.reserve(10);

  // Expect output: 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1
  std::vector<int>::iterator i = v1.begin(); 
  int ii = 0;
  // pos - ii 刚好是回归到 1的位置
  // i[ii] = i - |ii|
  // Expect output: 1 1 1 1 1 1 1 1 1 1   
  while(i!=v1.end()) {
    std::cout << "i delta pos: " <<  i[ii] << " " << std::endl;
    std::cout << "ii value: " << ii << std::endl;
    std::cout << "i pos: " << i - v1.begin() + 1 << std::endl;
    std::cout << "i value: " <<  *i << std::endl;

    std::cout << " ======= " << std::endl; 
    ii--;
    i++;
  }

  i = v2.begin();
  ii = 0;
  // Expect output: 1 1 1 1 1
  while(i!=v2.end()) {
    std::cout << i[ii] << " ";
    ii--;
    i++;
  }

  return EXIT_SUCCESS;
} 

