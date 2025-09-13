#include <iostream>

int main(int argc, char* argv[]) {
    int value {5};
    value = value + 1; // 6
    std::cout << "The value is: " << value << std::endl;

    value = 5;
    value = value - 1; // 4
    std::cout << "The value is: " << value << std::endl;

    std::cout <<"======Postfix increment and decrement======" << std::endl;

    value = 5;
    std::cout << "The value is (incrementing): " << value ++ << std::endl; // 5
    std::cout << "The value is: " << value << std::endl; // 6
    std::cout << std::endl;

    value = 5;
    std::cout << "The value is (decrementing): " << value -- << std::endl; // 5
    std::cout << "The value is: " << value << std::endl;  // 4

    std::cout << "======Prefix increment and decrement======" << std::endl;
    value = 5;
    ++value;
    std::cout << "The value is (prefix++): " << value << std::endl; // 6
    
    value = 5;
    std::cout << "The value is (prefix++ inplace): " << ++value << std::endl; // 6
    std::cout << std::endl;

    // Prefix: Decementing
    value = 5;
    --value;
    std::cout << "The value is (prefix--): " << value << std::endl; // 4

    value = 5;
    std::cout << "The value is (prefix-- inplace): " << --value << std::endl; // 4
    
    return 0;

 


   return EXIT_SUCCESS;
}