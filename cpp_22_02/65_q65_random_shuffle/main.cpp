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

struct Sequence {
  int start;
  Sequence(int start): start(start) {}

  int operator()() {
    return start ++;
  }
};

int main(int argc, char* argv[]) {
  std::vector<int> v1(10);
  std::generate_n(v1.begin(), 10, Sequence(1));
  std::random_shuffle(v1.rbegin(), v1.rend());

  std::sort(v1.begin(), v1.end(), std::greater<int>());

  // Expect output: 10 9 8 7 6 5 4 3 2 1
  std::for_each(v1.begin(), v1.end(), Out<int>(std::cout));
  std::cout << std::endl;

  return EXIT_SUCCESS;
} 

