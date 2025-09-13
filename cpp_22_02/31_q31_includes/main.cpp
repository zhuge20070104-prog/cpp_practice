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

    void operator() (T const& val) {
        out << val << " ";
    }
};


bool Compare(char a, char b) {
    return std::tolower(a) < std::tolower(b);
}

int main(int argc, char* argv[]) {
    char s[] = "qwerty";
    char t1[] = "ert";
    char t2[] = "ERT";

    std::sort(s, s+6);

    /***
     * std::includes源码
     * template<typename _InputIterator1, typename _InputIterator2,
	   typename _Compare>
    _GLIBCXX20_CONSTEXPR
    bool
    __includes(_InputIterator1 __first1, _InputIterator1 __last1,
	       _InputIterator2 __first2, _InputIterator2 __last2,
	       _Compare __comp)
    {
      while (__first1 != __last1 && __first2 != __last2)
	{
	  if (__comp(__first2, __first1))
	    return false;
	  if (!__comp(__first1, __first2))
	    ++__first2;
	  ++__first1;
	}

      return __first2 == __last2;
    }
     * 
     */
    // 输出两个1

    /**
     *  e  q  r   t wy
        e     r   t 
        ERT
     */
    std::cout << std::includes(s, s+6, t1, t1+3, Compare)
    << std::includes(s, s+6, t2, t2+3, Compare) << std::endl;

    return EXIT_SUCCESS;
} 

