#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <algorithm>


enum test_type {
    regular_if,
    telnary_op
};

struct if_tests {
    if_tests(): a(35), b(200) {

    }

    std::function<void(void)> regular_if_func = [this]() {
        int max_;
        std::cout << std::endl;
        std::cout << "using regular if " << std::endl;
        if(a > b) {
            max_ = a;
        } else {
            max_ = b;
        }
        std::cout << "max: " << max_ << std::endl;
    };


    std::function<void(void)> telnary_op_func = [this]() {
        int max_ = (a > b)? a: b;
        std::cout << "max: " << max_ << std::endl;
    }; 

    void operator()(test_type type) {
        if(func_map.find(type) == func_map.end()) {
            std::cerr << "not supported func type" << std::endl;
            exit(-1);
        }
        func_map[type]();
    }
private:
    std::map<test_type, std::function<void(void)>> func_map{
        {regular_if, regular_if_func},
        {telnary_op, telnary_op_func}
    };
    int a;
    int b;  
};


int main(int argc, char* argv[]) {
    std::vector<test_type> tests {
        regular_if,
        telnary_op
    };
    if_tests t;
    std::for_each(tests.begin(), tests.end(), [&t](test_type const& type){
        t(type);
    });
    return EXIT_SUCCESS;
}