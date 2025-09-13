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

void myfunction(int i) {
    std::cout << " " << i;
}

bool classifier(int v) {
    return v % 2 == 0;
}

int main(int argc, char* argv[]) {
    int t[] = {1, 5, 2, 5, 2, 4, 4, 3, 3, 1};
    std::vector<int> v1(t, t+10);

    std::set<int> s1(t, t+10);

    /***
     * 
     *  for (; __first != __last; ++__first)
	if (__pred(*__first))
	  *__first = __new_value;
     */
    // std::replace_if的输出:  1 5 10 5 10 10 10 3 3 1
    std::replace_if(v1.begin(), v1.end(), classifier, 10);
    // std::replace 是编译错误
    // std::replace(v1.begin(), v1.end(), classifier, 10);
    std::for_each(v1.begin(), v1.end(), myfunction);


    return EXIT_SUCCESS;
} 

