#include <iostream>
#include <cassert>
#include <map>
#include <functional>
#include <vector>
#include <algorithm>


struct family {
    static bool car() {
        std::cout << "car function running" << std::endl;
        return false;
    }

    static bool house() {
        std::cout << "house function running" << std::endl;
        return true;
    }

    static bool job() {
        std::cout << "job function running" << std::endl;
        return false;
    }

    static bool spouse() {
        std::cout << "spouse function running" << std::endl;
        return false;
    }
};

struct short_circuit_test {
    enum test_type {
        simple_and_or,
        family_and,
        family_or
    };

    std::function<void(void)> simple_and_or_func = [](){
        bool a{true}, b{true}, c{true}, d{false};
        bool p{false}, q{false}, r{false}, m{true};

        // 如果有一个false, 结果就是false
        std::cout << std::endl;
        std::cout << "AND short circuit" << std::endl;
        bool result = a && b && c && d;
        std::cout << "result: " << std::boolalpha << result << std::endl;

        // 如果其中有一个true, 结果就是true
        std::cout << std::endl;
        std::cout << "OR short circuit" << std::endl;
        result = p || q || r || m;
        std::cout << "result: " << std::boolalpha << result << std::endl;
    };

    
    std::function<void(void)> family_and_func = []() {
        if(family::car() && family::house() && family::job() && family::spouse()) {
            std::cout << "I'm happy" << std::endl;
        } else {
            std::cout << "I'm sad" << std::endl;
        }
    };

    std::function<void(void)> family_or_func = []() {
        if(family::car() || family::house() || family::job() || family::spouse()) {
            std::cout << "I'm happy" << std::endl;
        } else {
            std::cout << "I'm sad" << std::endl;
        }
    };

    void operator()(test_type type) {
        if(func_map.find(type) == func_map.end()) {
            std::cerr << "Can't find corresponding function, please check!" << std::endl;
            return;
        }

        func_map[type]();
    }

    private:
    std::map<test_type, std::function<void(void)>> func_map{
        {simple_and_or, simple_and_or_func}, 
        {family_and, family_and_func},
        {family_or, family_or_func}
    };
};


int main(int argc, char* argv[]) {
    std::vector<short_circuit_test::test_type> tests {
        short_circuit_test::simple_and_or, 
        short_circuit_test::family_and,
        short_circuit_test::family_or
    };

    short_circuit_test t;
    std::for_each(tests.begin(), tests.end(), [&](short_circuit_test::test_type& type){
        t(type);
    });

    return EXIT_SUCCESS;
}