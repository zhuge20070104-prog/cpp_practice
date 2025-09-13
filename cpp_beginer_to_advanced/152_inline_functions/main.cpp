#include <iostream>

// we want the definition organized, but want to avoid the function call overhead
inline int max(int a, int b) {
    return (a > b) ? a : b;
}

int main(int argc, char* argv[]) {

    // max definition will be pasted here by the complier
    std::cout << max(11, 9) << '\n';
    return EXIT_SUCCESS;
}