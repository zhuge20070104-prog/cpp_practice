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
  A(int a) : a(a) {}

  int getA() const { return a; }

  bool operator < (A const& b) const {
    return a < b.a;
  }
};


struct R {
  bool operator()(A const& a, A const& b) const {
    return a.getA() < b.getA();
  }
};


int main(int argc, char* argv[]) {
  int t[] = {3, 4, 2, 1, 6, 5, 7, 9, 8, 10};
  std::string s[] = {"three", "four", "two", "one", "six","�ve", "seven", "nine","eight","ten"};

  std::multimap<A, std::string> m;
  for(int i=0; i<10; i++) {
    m.insert(std::make_pair(A(t[i]), s[i]));
  }  

  // lower bound和upper bound的支持，仅需要 < 操作符重载
  // 能比较小于就行
  m.erase(m.lower_bound(2), m.upper_bound(7));

  std::multimap<A, std::string>::iterator i = m.begin();
  for(;i!=m.end(); i++) {
    std::cout << i->second << " ";
  }

  std::cout << std::endl;

  return EXIT_SUCCESS;
} 

