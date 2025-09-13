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
    return 10*(1+(start++%3));
  }
};

int main(int argc, char* argv[]) {
    std::deque<int> d1(10);
    std::generate(d1.begin(), d1.end(), Sequence(1));

    std::sort(d1.begin(), d1.end());
    std::pair<std::deque<int>::iterator, std::deque<int>::iterator> result = std::equal_range(d1.begin(), d1.end(), 20);

    // Expect output: 20 20 20 20
    std::for_each(result.first, result.second, Out<int>(std::cout));

    std::cout << std::endl;

    return EXIT_SUCCESS;
} 

