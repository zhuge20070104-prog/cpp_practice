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

  bool operator>(B const& v) const {
    return val > v.val;
  }

  // 题目没给这个，编译失败
  bool operator<(B const& v) const {
    return val < v.val;
  }
};

std::ostream& operator<<(std::ostream& o, B const& b) {
  o << b.getV();
  return o;
}

template <class T>
struct Out {
  std::ostream& out;

  Out(std::ostream& o) : out(o) {}

  void operator()(T const& val) {
    out << val << " "; 
  }
};

int main(int argc, char* argv[]) {
  int t[] = {3,2,4,1,5,10,9,7,8,6};
  std::vector<B> v1(t, t+10);
  std::sort(v1.begin(), v1.end(), std::greater<B>());

  // Expect output: Compilation error
  // std::min_element 比较时使用 < 操作符
  // 需要重载 < 操作符
  std::cout << *std::min_element(v1.begin(), v1.end());
  
  return EXIT_SUCCESS;
} 

