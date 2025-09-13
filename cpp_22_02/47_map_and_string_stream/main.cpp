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


int main(int argc, char* argv[]) {
  int t[] = {3, 4, 2, 1, 6, 5, 7, 9, 8, 0};

  std::vector<int> v(t, t+10);

  std::map<int, std::string> m;
  for(std::vector<int>::iterator i=v.begin(); i!=v.end(); i++) {
    std::stringstream s;
    s << *i << *i;
    m.insert(std::pair<int, std::string>(*i, s.str()));
  }

  // Expect output: Compilation error, std::pair不能直接输出
  for(std::map<int, std::string>::iterator i=m.begin(); i!=m.end(); i++) {
    // std::cout << *i << " ";
    std::cout << i->first << " " << i->second << std::endl;
  }

  return EXIT_SUCCESS;
} 

