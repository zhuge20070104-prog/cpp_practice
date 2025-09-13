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
  int t1[] = {1,2,3,4,5,6,7,8,9,10};
  int t2[] = {1,2,3,4,5,6,7,8,9,10};

  std::vector<int> v1(t1, t1+10);
  std::vector<int> v2(t2, t2+10);

  std::vector<int> v3(10);

  // Original v3: 1-10 -9, 2-9 -7, -5, -3, -1, 1, 3, 5, 7, 9
  //  rbegin, rend: 9, 7, 5, 3, 1, -1, -3, -5, -7, -9

  // Expect output: 9 7 5 3 1 -1 -3 -5 -7 -9
  std::transform(v1.begin(), v1.end(), v2.rbegin(), v3.begin(), std::minus<int>());

  std::for_each(v3.rbegin(), v3.rend(), Out<int>(std::cout));
  std::cout << std::endl;

  return EXIT_SUCCESS;
} 

