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
};

bool operator<(B const& a, B const& b) {
  return a.getV() < b.getV();
} 

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
  int t[] = {8, 10, 5, 1, 4, 6, 2, 7, 9, 3};

  std::deque<B> d1(t, t+10);
  std::sort(d1.begin(), d1.end());

  // 无小于号, Expect output: Compilation error

  std::deque<B>::iterator it = std::lower_bound(d1.begin(), d1.end(), 4);

  std::for_each(it, d1.end(), Out<B>(std::cout));
  std::cout << std::endl;
  return EXIT_SUCCESS;
} 

