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

class A {
  int a;
public:
  A(int a) {
    this->a = a;
  }

  bool operator<(A const& b) {
    return this->a < b.a;
  }

  friend std::ostream& operator<< (std::ostream& c, A const& a);

};

std::ostream& operator<< (std::ostream& c, A const& a) {
  c << a.a;
  return c;
}

template <class T>
void print(T start, T end) {
  while(start != end) {
    std::cout << *start << " ";
    start++;
  }
}

int main(int argc, char* argv[]) {
    A t1[] = {1, 7, 8, 4, 5};
    std::list<A> l1(t1, t1+5);
    A t2[] = {3, 2, 6, 9, 0};
    std::list<A> l2(t2, t2+5);

    l1.sort();
    l2.sort();

    /**
     *  *  @brief  Merge sorted lists.
       *  @param  __x  Sorted list to merge.
       *
       *  Assumes that both @a __x and this list are sorted according to
       *  operator<().  Merges elements of @a __x into this list in
       *  sorted order, leaving @a __x empty when complete.  Elements in
       *  this list precede elements in @a __x that are equal.
       * 
     */

    // merge 之后 l2将会被清空
    l1.merge(l2);

    print(l1.begin(), l1.end());
    print(l2.begin(), l2.end());
    std::cout << std::endl;

    return EXIT_SUCCESS;
} 

