#include <iostream>
#include <thread>

struct MyClass {
    void output_msg() {
        std::cout << "MyClass output msg..." << std::endl;
    }
};

int main(int argc, char* argv[]) {
    MyClass my_cls;

    std::thread th(&MyClass::output_msg, my_cls);
    th.join();

    std::cout << "Hello World" << std::endl;
    return EXIT_SUCCESS;
}