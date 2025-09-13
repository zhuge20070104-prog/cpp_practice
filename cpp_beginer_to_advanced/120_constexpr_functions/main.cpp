#include <iostream>

// Marking a function as constexpr gives it the potential 
// to be evaluated at compile time
int constexpr get_value(int multiplier) {
    return 3 * multiplier;
}

int main(int argc, char* argv[]) {
    // For the evaluation to take place at compile time
    // we have to remember to store the return value in a constexpr
    // result variable
    int constexpr result = get_value(4); // Compile time
    std::cout << "result: " << result << std::endl;

    int some_var {5}; // Runtime variable
    int runtime_result = get_value(some_var); // Run time
    std::cout << "Run time result: " << runtime_result << std::endl;
    
    return EXIT_SUCCESS;
}