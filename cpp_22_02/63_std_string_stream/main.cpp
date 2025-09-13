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
  std::string s;
  std::getline(std::cin, s);

  std::stringstream input(s);
  std::stringstream output;

  for(;!input.fail();) {
    int i;
    // 16进制 --> 10进制 
    // 64, 100 --> 100, 256

    // 第一次读256是成功的，第二次没读成功 fail了，退出
    // 值还是 256,
    // Expect output: 100, 256, 256
    input >> std::hex >> i;
    output << std::setw(4) << i;
  }  

  std::cout << output.str();
  return EXIT_SUCCESS;
} 

