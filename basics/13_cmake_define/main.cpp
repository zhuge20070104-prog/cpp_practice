#include <string>
#include <iostream>
#include <map>


int main(int argc, char* argv[]) {
#ifdef  TN_SUPPORT_ALGEBRA
    std::cout << "Include Algebra libraries" << std::endl;
#else 
    std::cout << "Unfortunate, Not support Algebra..." << std::endl;
#endif
}