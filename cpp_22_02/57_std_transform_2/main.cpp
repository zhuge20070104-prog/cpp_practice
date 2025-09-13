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

struct Add: public std::binary_function<int, int, int> {
  int operator()(int const& a, int  const& b) const {
    return a + b;
  }
};


int main(int argc, char* argv[]) {
  int t[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> v1(t, t+10);
  std::vector<int> v2(10);

  // Expect output: 2 3 4 5 6 7 8 9 10 11
  std::transform(v1.begin(), v1.end(), v2.begin(), std::bind1st(Add(), 1));

  std::for_each(v2.begin(), v2.end(), Out<int>(std::cout));
  std::cout << std::endl;

  return EXIT_SUCCESS;
} 

