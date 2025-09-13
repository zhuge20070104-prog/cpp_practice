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
    std::cout << 100 << " ";

    // 这个只会添加hex样式，
    // 不会去除原来的样式
    // Expect output: 100, 100
    std::cout.setf(std::ios::hex);

    // 这个std::hex操作符可以输出 64
    
    /***
     * 底层就是调用
     * /// Calls base.setf(ios_base::hex, ios_base::basefield).
  inline ios_base&
  hex(ios_base& __base)
  {
    __base.setf(ios_base::hex, ios_base::basefield);
    return __base;
  }
     * 
     */
    std::cout << std::hex << 100 << " ";

    /**
     *  @brief  Setting new format flags.
     *  @param  __fmtfl  Additional flags to set.
     *  @param  __mask  The flags mask for @a fmtfl.
     *  @return  The previous format control flags.
     *
     *  This function clears @a mask in the format flags, then sets
     *  @a fmtfl @c & @a mask.  An example mask is @c ios_base::adjustfield.
    */
    // Expect output: 100, 64
    std::cout.setf(std::ios::hex, std::ios::basefield);
    std::cout << 100 << " ";
    return EXIT_SUCCESS;
} 

