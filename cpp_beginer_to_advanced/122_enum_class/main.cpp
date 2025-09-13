#include <iostream>

// Declare an enum type
// The default type associated with enum classes with C++ is int
// unsigned char: 0 ~ 255
enum class Month: char {
    Jan = -1,
    January = Jan,
    Feb,
    Mar,
    Apr,
    May,
    Jun,
    Jul,
    Aug,
    Sep,
    Oct=100,
    Nov, 
    Dec
};


int main(int argc, char* argv[]) {
    Month mon {Month::Jan};
    std::cout << "month: " << static_cast<int>(mon) << std::endl;
    std::cout << "sizeof(month): " << sizeof(mon) << std::endl;
    return EXIT_SUCCESS;
}