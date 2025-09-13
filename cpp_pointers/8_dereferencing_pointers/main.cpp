#include <iostream>

int main(int argc, char* argv[]) {
    // 获取指针指向的内容的过程叫解引用
    // *运算符叫做解引用运算法，解引用运算符是对内存的间接访问
    // 获取字符串的地址需要用 static_cast<void*> 或者reintepret_cast<void*>
    // 获取字符串的值不需要解引用
    double scores[5], sum = 0;
    double* p_scores = scores;
    for(int i=0; i<5; ++i) {
        std::cout << "Enter the test score: " << std::endl;
        std::cin >> *(p_scores + i);
        sum += *(p_scores + i);
    }

    for(int i=0; i<5; ++i) {
        std::cout << "scores[" << i << "] = " << *(p_scores + i) << std::endl;
    }

    std::cout << "total for all students: " << sum << std::endl;
    std::cout << "average score: " << sum/ 5 << std::endl;
    return EXIT_SUCCESS;
}