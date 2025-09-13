#include "scanner.h"
#include "printer.h"
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
#include <list>
#include <iomanip>



int main(int argc, char* argv[]) {
    // int t[] = {1, 2, 3, 4, 5};    
    // std::vector<int> v1(t, t+5);
    std::list<int> v1 {1, 2, 3, 4, 5};
    std::list<int> l1;
    // 不能assign 随机访问迭代器，runtime error
    
    // 两个list 赋值的话，输出 1, 2, 3, 4, 5了
    l1.assign(v1.begin(), v1.end());


    // list没有随机访问迭代器，不能at
    // Expect output, compilation error
    // for(int i=0; i<l1.size(); i++) {
    //     std::cout << l1.at(i) << " "; 
    // }

    for(std::list<int>::iterator it = l1.begin(); it!=l1.end(); ++it) {
        std::cout << *it << " ";
    }

    std::cout << std::endl;

    return EXIT_SUCCESS;
} 

