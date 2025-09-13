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
    int t[] = {3, 4, 2, 1, 0, 3, 4, 1, 2, 0};

    std::vector<int> v(t, t+10);
    std::multimap<int, std::string> m;
    for(std::vector<int>::iterator i=v.begin(); i!=v.end(); i++) {
        std::stringstream s;
        s << *i << *i;
        m.insert(std::pair<int, std::string>(*i, s.str()));
    }    

    std::pair<std::multimap<int, std::string>::iterator, std::multimap<int, std::string>::iterator> range;

    range = m.equal_range(2);

    // Expect output: 2 2
    for(std::multimap<int, std::string>::iterator i=range.first; i!=range.second; i++) {
        std::cout << i->first << " ";
    }

    return EXIT_SUCCESS;
} 

