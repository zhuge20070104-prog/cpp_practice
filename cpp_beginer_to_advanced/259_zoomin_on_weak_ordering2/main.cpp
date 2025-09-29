#include <iostream>
#include "case_insensitive_string.h"

int main(int argc, char* argv[]) {

    CaseInsensitiveString s1 {"hello"};
    CaseInsensitiveString s2 {"HELLO"};

    std::cout << std::boolalpha;
    
    std::cout << "s1 == s2: " << (s1 == s2) << "\n";
    std::cout << "s1 < s2: " << (s1 < s2) << "\n";
    std::cout << "s1 > s2: " << (s1 > s2) << "\n";

    std::cout << "s2 == hellO: " << (s2 == "hellO") << "\n";
    std::cout << "HELLO == s1: " << ("HELLO" == s1) << "\n";

    return EXIT_SUCCESS;
}