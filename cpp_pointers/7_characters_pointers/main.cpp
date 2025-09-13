#include <iostream>

int main(int argc, char* argv[]) {
    // 打印字符指针需要转换成void* 再打印，否则会产生意想不到的效果
    char initial = 'P';
    char* p_initial = &initial;

    std::cout << "Memory address for initial P: " << (void*)p_initial << std::endl;
    std::cout << "Memory address for initial P: " << static_cast<void*>(p_initial) << std::endl;

    // 注意字符串指针和 其他指针不一样，不需要使用*解引用运算符进行解引用
    // 直接使用变量名就可以获取string的值
    // 字符串指针指向字符串的首地址

    char const* pans1 = "absolutely yes";
    char const* pans2 = "absolutely no";
    char const* pans3 = "the oracle is out, please try again later";
    char const* pans4 = "outlook is good";
    char const* pans5 = "today is your lucky day, yes";
    char const* pans6 = "try again tomorrow";
    char const* pans7 = "most certainly";
    char const* pans8 = "the answer is unclear";
    char const* pans = "the oracle says...";
    int choice = 0;

    std::cout << "think of a yes/no question, then ask the oracle" << std::endl;
    std::cout << "enter a number between 1 and 8: ";
    std::cin >> choice;

    switch (choice) {
    case 1:
        std::cout << pans << pans1 << std::endl;
        break;
    case 2:
        std::cout << pans << pans2 << std::endl;
        break;
    
    case 3:
        std::cout << pans << pans3 << std::endl;
        break;
    
    case 4:
        std::cout << pans << pans4 << std::endl;
        break;
    
    case 5:
        std::cout << pans << pans5 << std::endl;
        break;
    
    case 6: 
        std::cout << pans << pans6 << std::endl;
        break;
    
    case 7:
        std::cout << pans << pans7 << std::endl;
        break;
    case 8:
        std::cout << pans << pans8 << std::endl;        
        break;
    default:
        std::cout << "sorry, you didn't choose a number between 1 and 8." << std::endl;
        break;
    }
    return EXIT_SUCCESS;
}