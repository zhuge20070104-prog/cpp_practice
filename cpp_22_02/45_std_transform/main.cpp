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

  void operator() (T const& val) const {
    out << val << " "; 
  }
};


int main(int argc, char* argv[]) {
  int t1[] = {3,2,4,1,5};
  int t2[] = {6,10,8,7,9};

  std::vector<int> v1(5);

  // expect output: 9 12 12 8 14
  std::transform(t1, t1+5, t2, v1.rbegin(), std::plus<int>());
  std::for_each(v1.rbegin(), v1.rend(), Out<int>(std::cout));
  std::cout << std::endl;

  return EXIT_SUCCESS;
} 

