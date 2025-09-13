#include <iostream>
#include <memory>

int main(int argc, char* argv[]) {
    std::shared_ptr<int> a = std::make_shared<int>(8);
    std::cout << *a << std::endl;
    a.reset();

    std::shared_ptr<int> d = a;
    std::shared_ptr<int> e = a;
    std::shared_ptr<int> f = a;

    std::cout << "Reach the end" << std::endl;
    
    return EXIT_SUCCESS;
}