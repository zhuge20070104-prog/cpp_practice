#include <iostream>
#include <map>
#include <functional>
#include <cassert>


struct cond_test {
    enum condtion {
        IF_TEST,
        IF_ELSE_TEST,
        NESTED_IF_TEST,
        NESTED_IF_TEST2
    };
    
    std::function<void(void)> if_test = []() {
        int number1 = 75;
        int number2 = 60;
        bool result = (number1 < number2);

        std::cout << std::boolalpha << "result: " << result << std::endl;

        std::cout << std::endl;
        std::cout << "free standing if statement" << std::endl;
        if(result) {
            std::cout << number1 << " is less than " << number2 << std::endl;
        }

        if(!result) {
            std::cout << number1 << " is not less than " << number2 << std::endl;
        }
    };

    std::function<void(void)> if_else_test = []() {
        int number1 = 75;
        int number2 = 60;
        bool result = (number1 < number2);

        std::cout << std::endl;
        std::cout << "using the else clause" << std::endl;
        if(result) {
            std::cout << number1 << " is less than " << number2 << std::endl;
        } else {
            std::cout << number1 << " is not less than " << number2 << std::endl;
        }
    };

    std::function<void(void)> nested_if_test = [](){
        std::cout << std::endl;
        std::cout << "nesting if statement" << std::endl;

        bool red = false;
        bool green = true;
        bool yellow = false;
        bool police_stop = true;

        if(red) {
            std::cout << "stop" << std::endl;
        }

        if(yellow) {
            std::cout << "slow down" << std::endl;
        }

        if(green) {
            std::cout << "go" << std::endl;
        }

        std::cout << std::endl;
        std::cout << "police officer stops(verbose)" << std::endl;
        if(green) {
            if(police_stop) {
                std::cout << "stop" << std::endl;
            } else {
                std::cout << "go" << std::endl;
            }
        }
    };

    std::function<void(void)> nested_if_test2 = []() {
        std::cout << std::endl;
        bool red = false;
        bool green = true;
        bool yellow = false;
        bool police_stop = true;

        std::cout << "police officer stops(less verbose)" << std::endl;
        if(green && !police_stop) {
            std::cout << "go" << std::endl;
        } else {
            std::cout << "stop" << std::endl;
        }
    };
    
    void operator()(condtion const& cond) {
        if(func_map.find(cond) == func_map.end()) {
            std::cout << "can't find corresponding condition, please check!" << std::endl;
            assert(false);
        }
        func_map[cond]();
    }
private:
    std::map<condtion, std::function<void(void)>> func_map {
        {IF_TEST, if_test},
        {IF_ELSE_TEST, if_else_test},
        {NESTED_IF_TEST, nested_if_test},
        {NESTED_IF_TEST2, nested_if_test2}
    };
};

int main(int argc, char* argv[]) {
    cond_test c_test;
    c_test(cond_test::IF_TEST);
    c_test(cond_test::IF_ELSE_TEST);
    c_test(cond_test::NESTED_IF_TEST);
    c_test(cond_test::NESTED_IF_TEST2);
    return EXIT_SUCCESS;
}