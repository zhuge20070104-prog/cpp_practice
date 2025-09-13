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

class B {
  int val;
public:
  B(int v): val(v) {}

  int getV() const {
    return val;
  }

  bool operator < (B const& b) const {
    return val < b.val;
  }
};

std::ostream& operator<< (std::ostream& out, B const& b) {
  out << b.getV();
  return out;
} 

template <class T>
struct Out {
  std::ostream& out;

  Out(std::ostream& o): out(o) {}

  void operator()(T const& val) {
    out << val << " ";
  }
};


int main(int argc, char* argv[]) {
  int t[] = {8, 10, 5, 1, 4, 6, 2, 7, 9, 3};
  std::vector<B> v1(t, t+10);
  std::sort(v1.begin(), v1.end());

  // Expect output: 1 2 3 4 5 6 7 8 9 10
  std::for_each(v1.begin(), v1.end(), Out<B>(std::cout));

  std::cout << std::endl;

  return EXIT_SUCCESS;
} 

