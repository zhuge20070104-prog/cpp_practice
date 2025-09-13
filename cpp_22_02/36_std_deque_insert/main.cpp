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
    int t[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    std::vector<int> v1(t, t+10);
    std::deque<int> d1(v1.begin(), v1.end());

    std::deque<int> d2 = d1;

    // Expect output: Compilation error
    // 注意这里的不同的问题
    // 情况1: 因为d1.rbegin 是std::deque<int>::reverse_iterator，所以这里迭代器不能兼容，无法插入，编译错误
    // d2.insert(d1.rbegin(), 10);

    // 情况2：Runtime error。因为迭代器兼容了，都是std::deque<int>::iterator
    // 但是insert 只能插入到原有的deque, 不能从一个deque 插入到另一个deque，
    // 所以runtime error
    // d2.insert(d1.begin(), 10);

    /**
     * 详情查看STL注释
     *   /**
       *  @brief  Inserts given rvalue into %deque before specified iterator.
       *  @param  __position  A const_iterator into the %deque.
       *  @param  __x  Data to be inserted.
       *  @return  An iterator that points to the inserted data.
       *
       *  This function will insert a copy of the given rvalue before the
       *  specified location.
    */
   
    // 情况3: 成功运行，在d2.begin前插入10
    d2.insert(d2.begin(),10);
    for(int i=0; i<d1.size(); i++) {
        std::cout << d1[i] << " ";
    }
    return EXIT_SUCCESS;
} 

