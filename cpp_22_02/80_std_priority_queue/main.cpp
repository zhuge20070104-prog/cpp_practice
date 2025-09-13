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
#include <queue>

class compare {
  bool reverse;

public:
  compare(bool revparam=false) {
    reverse = revparam;
  }


  bool operator()(int lhs, int rhs) const {
    if(reverse) {
      return (lhs > rhs);
    } else {
      return (lhs < rhs);
    }
  }
};


int main(int argc, char* argv[]) {
  int myints[] = {3, 4, 2, 1, 6, 5, 7, 9, 8, 0};


  // 默认的比较函数是std::less， 构造的是大顶堆
  std::priority_queue<int, std::deque<int>> first(myints, myints + 10);

  // 下面的这个compare函数默认也是 less， 构造大顶堆
  std::priority_queue<int, std::vector<int>, compare> second(myints, myints + 10, compare(false));

  // Expect output: 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
  while(first.size() > 0) {
    std::cout << first.top() << " ";
    first.pop();
  }

  while(second.size() > 0) {
    std::cout << second.top() << " ";
    second.pop();
  }

  return EXIT_SUCCESS;
} 

