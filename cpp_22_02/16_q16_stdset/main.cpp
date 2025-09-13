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
#include <iomanip>



int main(int argc, char* argv[]) {
    
    int t[] = {1, 1, 2, 2, 3, 3, 4, 4, 5, 5};
    std::list<int> v(t, t+10);

    std::set<int> s1(v.begin(), v.end());
    std::cout << s1.count(3) << std::endl;
    if(s1.count(3) == 2) {
        s1.erase(3);
    } 

    for(std::set<int>::iterator i=s1.begin(); i!=s1.end(); i++) {
        std::cout << *i << " ";
    }

    return EXIT_SUCCESS;
} 

