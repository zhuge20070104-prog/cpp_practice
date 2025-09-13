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
  A(T v);
};

// Expect output: Compilation error
// template <class T>
// A::A(T v): _v(v) {}

template <class T>
A<T>::A(T v): _v(v) {}

int main(int argc, char* argv[]) {
  A<int> a(2);
  std::cout << 1 << std::endl;

  return EXIT_SUCCESS;
} 

