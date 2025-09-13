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
    int t[] = {1,2,3,4,5,1,2,3,4,5};

    std::vector<int> v(t, t+10);
    std::vector<int>::iterator it;
    int m1[] = {1, 2, 3};
    it = std::search(v.begin(), v.end(), m1, m1 + 3);
    // Expect output: Found at position 0
    // 原理: 
    /***
     * Searches the range @p [__first1,__last1) for a sub-sequence that
   *  compares equal value-by-value with the sequence given by @p
   *  [__first2,__last2) and returns an iterator to the first element
   *  of the sub-sequence, or @p __last1 if the sub-sequence is not
   *  found.
     */
    std::cout << "found at position: " << it - v.begin() << std::endl;

    return EXIT_SUCCESS;
} 

