#include <iostream>

int sum(int a, int b) {
    int result = a + b;
    std::cout << "In: &result(int): " << &result << std::endl;
    return result;
}

std::string add_strings(std::string const& str1, std::string const& str2) {
    std::string result = str1 + str2;
    std::cout << "In &result(std::string): " << &result << std::endl;
    return result; 
}


int main(int argc, char* argv[]) {
    int x{15};
    int y{9};
    int result = sum(x, y);
    std::cout << "Out: &result(int): " << &result << std::endl;
    std::cout << "result: " << result << std::endl;

    std::string str1 {"Hello"};
    std::string str2 {" World!"};
    std::string result_str = add_strings(str1, str2);
    std::cout << "Out: &result(string): " << &result_str << std::endl;
    std::cout << "result_str: " << result_str << std::endl;

    return EXIT_SUCCESS;
}