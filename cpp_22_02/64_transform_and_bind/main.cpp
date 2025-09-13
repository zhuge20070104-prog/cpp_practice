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
struct Out {
  std::ostream& out;

  Out(std::ostream& o): out(o) {}

  void operator()(T const& val) {
    out << val << " ";
  }
};

int Add(int a, int b) {
  return a + b;
}

int main(int argc, char* argv[]) {
  int t[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  std::vector<int> v1(t, t+10);
  std::vector<int> v2(10);
  std::transform(v1.begin(), v1.end(), v2.begin(), std::bind2nd(std::ptr_fun(Add), 1));

  // Expect output: 11 10 9 8 7 6 5 4 3 2
  // 注意这里这个rbegin and rend
  std::for_each(v2.rbegin(), v2.rend(), Out<int>(std::cout));
  std::cout << std::endl;

  return EXIT_SUCCESS;
} 

