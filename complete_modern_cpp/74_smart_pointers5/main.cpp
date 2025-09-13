#include <iostream>
#include <memory>

class Printer {
    std::weak_ptr<int> m_pvalue;

public:

    void set_value(std::weak_ptr<int> p) {
        m_pvalue = p;
    }

    void print() {
        std::cout << "Ref count: " << m_pvalue.use_count() << std::endl;

        if(m_pvalue.expired()) {
            std::cout << "Resource is no longer available" << std::endl;
            return;
        }

        auto sp = m_pvalue.lock();
        std::cout << "Value is: " << *sp << std::endl;
    }

};


int main(int argc, char* argv[]) {

    Printer prn;
    int num{};
    std::cout << "Please input a number: ";
    std::cin >> num;
    
    std::shared_ptr<int> p (new int{num});
    prn.set_value(p);
    if(*p > 10) {
        p = nullptr;
    }
    
    prn.print();
    return EXIT_SUCCESS;
}