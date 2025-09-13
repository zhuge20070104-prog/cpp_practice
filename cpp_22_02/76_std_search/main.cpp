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

class A {
  int a;
public:
  A(int a): a(a) {}

  int getA() const {
    return a;
  }

  void setA(int a) {
    this->a = a;
  }

  bool operator==(A& b) {
    return a == b.a;
  }
};

struct Compare {
  bool operator()(A const& a, A const& b)  {
    return a.getA() == b.getA();
  }
};


int main(int argc, char* argv[]) {
  int t[] = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
  std::vector<A> v(t, t+10);

  std::vector<A>::iterator it;
  A m1[] = {A(1), A(2), A(3)};
  it = std::search(v.begin(), v.end(), m1, m1+3, Compare());
  // Expect output: First found at position 0
  std::cout << "First found at position: " << it - v.begin() << std::endl;
  return EXIT_SUCCESS;
} 

