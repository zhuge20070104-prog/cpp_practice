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

    std::string s[] = {"one", "one", "two", "two", "three", "three", "four", "four", "five", "five"};

    std::map<int, std::string> m;

    // Expect output: map没有push_back函数,compilation error
    for(int i=0; i<10; i++) {
        m.insert(std::pair<int, std::string>(t[i], s[i]));
        // m.push_back(std::pair<int, std::string>(t[i], s[i]));
    }

    for(std::map<int, std::string>::iterator i=m.begin(); i!=m.end(); i++) {
        std::cout << i->first << " ";
    }


    return EXIT_SUCCESS;
} 

