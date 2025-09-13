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
    int t[] = {1, 2, 3, 2, 3, 5, 1, 2, 7, 3, 2, 1, 10, 4, 4, 5};

    std::vector<int> v(t, t+15);

    std::vector<int>::iterator it = std::search_n(v.begin(), v.end(), 4, 2);
    // 没找到 4个连续的2， it == v.end()
    // v.end() - v.begin() = 15

    /**
     * std::search_n函数的注释
     *   *  @brief Search a sequence for a number of consecutive values.
   *  @ingroup non_mutating_algorithms
   *  @param  __first  A forward iterator.
   *  @param  __last   A forward iterator.
   *  @param  __count  The number of consecutive values.
   *  @param  __val    The value to find.
   *  @return The first iterator @c i in the range @p
   *  [__first,__last-__count) such that @c *(i+N) == @p __val for
   *  each @c N in the range @p [0,__count), or @p __last if no such
   *  iterator exists.
   *
   *  Searches the range @p [__first,__last) for @p count consecutive elements
   *  equal to @p __val.
     */
    
    std::cout << it - v.begin() << std::endl;

    return EXIT_SUCCESS;
} 

