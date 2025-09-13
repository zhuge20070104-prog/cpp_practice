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

  B() {}

  int getV() const {
    return val;
  }

  bool operator<(B const& v) const {
    return val < v.val;
  }
};

std::ostream& operator<<(std::ostream& out, B const& v) {
  out << v.getV();
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
  int t[] = {20, 30, 10, 20, 30, 10, 20, 30, 10, 20};
  std::deque<B> d1(t, t+10);
  std::sort(d1.begin(), d1.end());

  // Expect output: 20 20 20 20
  std::pair<std::deque<B>::iterator, std::deque<B>::iterator> result = std::equal_range(d1.begin(),
    d1.end(), B(20));

  std::for_each(result.first, result.second, Out<B>(std::cout));
  std::cout << std::endl;

  return EXIT_SUCCESS;
} 

