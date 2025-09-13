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
  int t[] = {1,2,3,4,5,1,2,3,5,4};
  std::vector<int> v(t, t+10);

  std::vector<int>::iterator it;
  int m1[] = {1, 3, 2};
  it = std::find_end(v.begin(), v.end(), m1, m1+3);

  // Expect output: no output
  
  /**
   *  *  @brief  Find last matching subsequence in a sequence.
   *  @ingroup non_mutating_algorithms
   *  @param  __first1  Start of range to search.
   *  @param  __last1   End of range to search.
   *  @param  __first2  Start of sequence to match.
   *  @param  __last2   End of sequence to match.
   *  @return   The last iterator @c i in the range
   * 
   */
  if(it!=v.end()) {
    std::cout << "Found at position: " << it - v.begin() << std::endl;
  } 
  return EXIT_SUCCESS;
} 

