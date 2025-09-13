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
struct Out {
  std::ostream& out;

  Out(std::ostream& o): out(o) {}

  void operator()(T const& val) {
    out << val << " ";
  }
};


int main(int argc, char* argv[]) {
  
  int t1[] = {3, 2, 4, 1, 5};
  int t2[] = {6, 10, 8, 7, 9};

  std::vector<int> v1(20);

  std::sort(t1, t1 + 5);
  std::sort(t2, t2 + 5);

  std::copy(t1, t1+5, v1.begin());
  std::copy(t2, t2+5, v1.begin()+5);

  // Expect output: Compilation error
  // 参数不足
  // std::merge(v1.begin(), v1.begin() + 5, v1.end());

  // expect output: 1 2 3 4 5 6 7 8 9 10 1 2 3 4 5 6 7 8 9 10
  std::merge(v1.begin(), v1.begin()+5, v1.begin() +5, v1.begin() + 10, v1.begin() + 10);
  std::for_each(v1.begin(), v1.end(), Out<int>(std::cout));
  std::cout << std::endl;
  return EXIT_SUCCESS;
} 

