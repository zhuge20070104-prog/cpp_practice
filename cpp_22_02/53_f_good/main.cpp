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


int main(int argc, char* argv[]) {
  std::ifstream f("test.in");
  std::list<int> l;
  for(;f.good();) {
    int i;
    f >> i;
    l.push_back(i);
  } 

  f.close();

  // Expect output: 1 2 3 3
  std::for_each(l.begin(), l.end(), Out<int>(std::cout));

  return EXIT_SUCCESS;
} 

