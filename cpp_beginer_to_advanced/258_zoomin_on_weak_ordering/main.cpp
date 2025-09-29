#include <iostream>
#include "comparable_string.h"

int main(int argc, char* argv[]) {

    ComparableString s1 {"FOG"};
    ComparableString s2 {"DOG"};

    std::cout << std::boolalpha;
    
    std::cout << "s1 == s2: " << (s1 == s2) << "\n";
    std::cout << "s1 < s2: " << (s1 < s2) << "\n";
    std::cout << "s1 > s2: " << (s1 > s2) << "\n";
    return EXIT_SUCCESS;
}