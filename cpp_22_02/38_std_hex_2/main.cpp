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
    // Expect output: 64 100 
    std::cout.setf(std::ios::hex, std::ios::basefield);
    std::cout << 100 << " ";

    /**
     * flags 是一步到位，全部改成base,
     * 就是十进制
   
     *  @brief  Setting new format flags all at once.
     *  @param  __fmtfl  The new flags to set.
     *  @return  The previous format control flags.
     *
     *  This function overwrites all the format flags with @a __fmtfl.
    fmtflags
    
    flags(fmtflags __fmtfl)
    {
      fmtflags __old = _M_flags;
      _M_flags = __fmtfl;
      return __old;
    }
     */

    std::cout.flags(std::ios::showbase);
    std::cout << 100 << " ";

    return EXIT_SUCCESS;
} 

