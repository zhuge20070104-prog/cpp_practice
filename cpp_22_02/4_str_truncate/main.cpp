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
    std::string a;
    std::cin >> a;
    // one two three <Enter>
    // Expect output: one
    std::cout << a << std::endl;

    return EXIT_SUCCESS;
} 

