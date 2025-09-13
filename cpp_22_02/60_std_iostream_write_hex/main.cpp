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

  Out(std::ostream& o) : out(o) {}

  void operator()(T const& val) {
    out << std::setw(3) << std::hex << val; 
  }
};

int main(int argc, char* argv[]) {
  int t[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  // 不应该期待输出 1,2,3,4,5,6,7,8,9,10
  // 因为读取的时候没有按16进制读取
  std::fstream f("test.out", std::ios::trunc | std::ios::out);

  std::list<int> l(t, t + 10);

  std::for_each(l.begin(), l.end(), Out<int>(f));

  f.close();

  f.open("test.out");
  for(;!f.eof();) {
    int i;
    f >> std::hex >> i;
    std::cout << i << " ";
  }

  f.close();

  return EXIT_SUCCESS;
} 

