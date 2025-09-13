#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <algorithm>

enum test_type {
    pure_lines,
    for_loop_unsigned,
    for_loop_size_t,
    for_loop_size_t_outer,
    for_loop_counter_outer
};


struct loop_tests {
    std::function<void(void)> pure_lines_func = [] () {
        std::cout << "Pure lines" << std::endl;
        std::cout << "I love C++" << std::endl;
        std::cout << "I love C++" << std::endl;
        std::cout << "I love C++" << std::endl;
        std::cout << "I love C++" << std::endl;
        std::cout << "I love C++" << std::endl;
        std::cout << "I love C++" << std::endl;
        std::cout << "I love C++" << std::endl;
        std::cout << "I love C++" << std::endl;
        std::cout << "I love C++" << std::endl;
        std::cout << "I love C++" << std::endl;
    };

    std::function<void(void)> for_loop_unsigned_func = []() {
        std::cout << "For loop unsigned func" << std::endl;
        for(unsigned int i{0}; i<10; ++i) {
            std::cout << i << ": I love C++" << std::endl;
        }
        std::cout << "loop done" << std::endl;
    };

    std::function<void(void)> for_loop_size_t_func = []() {
        std::cout << "for_loop_size_t_func" << std::endl;
        for(std::size_t i{0}; i<10; ++i) {
            std::cout << i << ": I love C++" << std::endl;
        }
        std::cout << "loop done" << std::endl;
    };

    std::function<void(void)> for_loop_size_t_outer_func = []() {
        std::cout << "for_loop_size_t_outer_func" << std::endl;
        std::size_t i {0};
        for(; i<10 ; ++i) {
            std::cout << i << ": I love C++" << std::endl;
        }
        std::cout << "loop done" << std::endl;
    };

    std::function<void(void)> for_loop_counter_outer_func = []() {
        std::size_t const COUNT {10};
        for(std::size_t i {0}; i < COUNT; ++i) {
            std::cout << i << ": I love C++" << std::endl;
        }
        std::cout << "loop done" << std::endl;
    };

    void operator()(test_type type) {
        if(func_map.find(type) == func_map.end()) {
            std::cerr << "not supported func type" << std::endl;
            exit(-1);
        }
        func_map[type]();
    }
private:
    std::map<test_type, std::function<void(void)>> func_map {
        {pure_lines, pure_lines_func},
        {for_loop_unsigned, for_loop_unsigned_func},
        {for_loop_size_t, for_loop_size_t_func},
        {for_loop_size_t_outer, for_loop_size_t_outer_func},
        {for_loop_counter_outer, for_loop_counter_outer_func}
    };
};

int main(int argc, char* argv[]) {
    std::vector<test_type> tests{
        pure_lines,
        for_loop_unsigned,
        for_loop_size_t,
        for_loop_size_t_outer,
        for_loop_counter_outer
    };

    loop_tests t;
    std::for_each(tests.begin(), tests.end(), [&t](test_type const& type) {
        t(type);
    });
       
    return EXIT_SUCCESS;
}