#include <iostream>

void foo(int a, int b) {
    std::cout << a << ", " << b << std::endl;
}

int get_num() {
    static int i = 0;
    return ++i; 
}


int main(int argc, char* argv[]) {
    // 不同编译器实现不一样，尽量不要这么写  
    foo(get_num(), get_num());
    return EXIT_SUCCESS;
}