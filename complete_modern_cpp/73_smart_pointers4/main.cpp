#include <iostream>

class Printer {
    int* m_pvalue;

public:

    void set_value(int* p) {
        m_pvalue = p;
    }

    void print() {
        std::cout  << "Address of m_pvalue: "<< m_pvalue << std::endl;
        std::cout << "Value is: " << *m_pvalue << std::endl;
    }

};


int main(int argc, char* argv[]) {

    Printer prn;
    int num{};
    std::cout << "Please input a number: ";
    std::cin >> num;

    int* p = new int{num};
    std::cout  << "Address of p: "<< p << std::endl;
    prn.set_value(p);
    if(*p > 10) {
        // 这里p被回收了，下面解引用那个程序根本不知道p指向的值被回收了。
        // 会解引用出垃圾值
        delete p;
        p = nullptr;
    }
    std::cout  << "Address of p: "<< p << std::endl;
    prn.print();
    delete p;
    return EXIT_SUCCESS;
}