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

    void operator()(T const& val) {
        out << val << " ";
    }
};

int main(int argc, char* argv[]) {
    
    int t[] = {3, 2, 4, 1, 5, 6, 10, 8, 7, 9};
    std::vector<int> v1(t, t+10);

    std::for_each(v1.begin(), v1.end(), std::bind2nd(std::plus<int>(), 1));

    // std::plus的返回值没有被接收，所以还是原值
    // Expect output: 9 7 8 10 6 5 1 4 2 3
    // 注意是 rbegin, rend， 是反着输出
    std::for_each(v1.rbegin(), v1.rend(), Out<int>(std::cout));
    
    std::cout << std::endl;

    return EXIT_SUCCESS;
} 

