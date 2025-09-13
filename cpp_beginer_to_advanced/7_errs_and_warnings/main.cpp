#include <iostream>


int main(int argc, char* argv[]) {
    // 打印 Hello World 忘记换行, 编译期错误
    /**
     * /home/fredric/code/cpp_practice/cpp_beginer_to_advanced/7_errs_and_warnings/main.cpp: In function ‘int main(int, char**)’:
    /home/fredric/code/cpp_practice/cpp_beginer_to_advanced/7_errs_and_warnings/main.cpp:7:5: error: expected ‘;’ before ‘return’
     return EXIT_SUCCESS;
    */
   // std::cout << "Hello, World!" << std::endl
    
    // 运行时错误， 浮点数例外 (核心已转储)
    int value = 7/0;
    std::cout << "value = " << value << std::endl;
    return EXIT_SUCCESS;
}