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
class A {
  T _v;
public:
  A() {}

  A(T v): _v(v) {}

  template <class U>
  friend std::ostream& operator<<(std::ostream& c, A<U> const& v); /*{
    c << v._v;
    return c;
  }*/
};


template <class T>
std::ostream& operator<<(std::ostream& c, A<T> const& v) {
  c << v._v;
  return c;
}

int main(int argc, char* argv[]) {
  A<int> a(10);
  // Expect output: Compilation error
  std::cout << a << std::endl; 
  return EXIT_SUCCESS;
} 

