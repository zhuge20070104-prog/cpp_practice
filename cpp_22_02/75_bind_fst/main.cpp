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
  B(int v): val(v){}

  int getV() const {
    return val;
  }

  operator int() const {
    return val;
  }
};


template <class T>
struct Out {
  std::ostream& out;
  Out(std::ostream& o): out(o) {}

  void operator()(T const& val) {
    out << val << " ";
  }
};

int main(int argc, char* argv[]) {
  B t[] = {3,2,4,1,5,6,10,8,7,9};

  std::vector<B> v1(t, t+10);
  std::for_each(v1.begin(), v1.end(), std::bind1st(std::plus<B>(), 1));
  // plus<T> 不会做反向回填给 原数字的操作
  // 所以说 Expect output: 9 7 8 10 6 5 1 4 2 3
  std::for_each(v1.rbegin(), v1.rend(), Out<B>(std::cout));
  std::cout << std::endl;
  return EXIT_SUCCESS;
} 

