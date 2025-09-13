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

int main(int argc, char* argv[]) {
  int t[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::deque<int> mydeck(t, t+10);
  std::list<int> mylist(t, t+10);

  std::queue<int> first;
  std::queue<int> second(mydeck);

  std::queue<int> third(second);

  std::queue<int, std::list<int>> fourth(mylist);

  mylist.clear();

  while(!third.empty()) {
    third.pop();
  }

  // Queue 没有clear方法， compilation error
  // third.clear();


  // 0, 10 --->  10, 0

  std::cout << third.size() << " " << mydeck.size() << std::endl;
  std::cout << fourth.size() << " " << mylist.size() << std::endl;


  return EXIT_SUCCESS;
} 

