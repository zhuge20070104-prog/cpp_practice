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

  void operator() (T const& val) const {
    out << val << " "; 
  }
};


int main(int argc, char* argv[]) {
  B t1[] = {3, 2, 4, 1, 5};
  // int t2[] = {5, 6, 8, 2, 1};
  B t2[] = {5, 6, 8, 2, 1};
  std::vector<B> v1(10, 0);

  std::sort(t1, t1+5);
  std::sort(t2, t2+5);

  // int 和 B类型不一样，无法比较
  // Expect output: Compilation error

  // 两个都是B类型就可以输出: 1 2 3 4 5 6 8 0 0 0
  std::set_union(t1, t1+5, t2, t2+5, v1.begin());

  std::for_each(v1.begin(), v1.end(), Out<B>(std::cout));
  std::cout << std::endl;
  return EXIT_SUCCESS;
} 

