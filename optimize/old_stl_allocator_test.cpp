#include "test_driver.h"
#include "simple_allocator.h"
#include "old_block_allocator.h"
#include "stopwatch11.h"

#include <iostream>
#include <string>


using SimpleStringT = std::basic_string<
    char,
    std::char_traits<char>,
    Allocator<char>>;

using fixed_block_string = std::basic_string<
    char,
    std::char_traits<char>,
    block_allocator<char, 10>>;


// 原始的remove ctrl的三种写法 std::string, SimpleStringT, fixed_block_string
std::string remove_ctrl(std::string s) {
    std::string result;
    for(std::size_t i=0; i<s.length(); ++i) {
        if(s[i] >= 0x20) {
            result = result + s[i];
        }
    }
    return result;
}

SimpleStringT remove_ctrl_simple(std::string s) {
    SimpleStringT result;
    for(std::size_t i=0; i<s.length(); ++i) {
        if(s[i] >= 0x20) {
            result = result + s[i];
        }
    }
    return result;
}

fixed_block_string remove_ctrl_fixed_block(std::string s) {
    fixed_block_string result;
    for(std::size_t i=0; i<s.length(); ++i) {
        if(s[i] >= 0x20) {
            result = result + s[i];
        }
    }
    return result;
}

int test_fixed_block_allocator(int test_no, unsigned long multiplier) {
    typedef unsigned counter_t;
    counter_t const iterations = 100 * multiplier;

    std::string s("\07Now is the time\07 for all good men\r\n to come to the aid of their country. \07");
    std::string test("Now is the time for all good men to come to the aid of their country. ");
    s = s + s + s;
    test = test + test + test;

    std::string stdresult;
    fixed_block_string fbresult;
    SimpleStringT spresult;

    bool rc = true;

    switch(test_no) {
        default: return -1;
        case 0: return 2;

        case 1: {
            {
                void* p = block_o_memory::allocate(100);
                void* q = block_o_memory::allocate(200);
                void* r = block_o_memory::allocate(333);
                block_o_memory::deallocate(p);
                block_o_memory::deallocate(q);
                block_o_memory::deallocate(r);
                rc &= (block_o_memory::count() <= 1); 
            }

            std::cout << s.length() << " character argument to remove_ctrl()" << std::endl;
            std::cout << iterations << " iterations" << std::endl;

            {
                std::string verifier;
                verifier = remove_ctrl(s);
                rc &= (verifier.compare(test) == 0);

                SimpleStringT result1 = remove_ctrl_simple(s);
                verifier = result1.data();
                rc &= (verifier.compare(test) == 0);

                fixed_block_string result2 = remove_ctrl_fixed_block(s);
                verifier = result2.data();
                rc &= (verifier.compare(test) == 0);
            }
        }
            break;
        
        case 2: {
            {
                StopWatch sw("remove_ctrl()");
                for(counter_t i=0; i<iterations; ++i) {
                    stdresult = remove_ctrl(s);
                }
            }

            {
                StopWatch sw("remove_ctrl_simple()");
                for(counter_t i=0; i<iterations; ++i) {
                    spresult = remove_ctrl_simple(s);
                }
            }

              {
                StopWatch sw("remove_ctrl_fixed_block()");
                for(counter_t i=0; i<iterations; ++i) {
                    fbresult = remove_ctrl_fixed_block(s);
                }
            }
        }
            break;
    } 

    return (rc)? 1: 0;
}

int (*func[])(int, unsigned long) = {
    test_fixed_block_allocator,
    0
};

int main(int argc, char* argv[]) {
    test_driver(func, argc, argv);
    return EXIT_SUCCESS;
}