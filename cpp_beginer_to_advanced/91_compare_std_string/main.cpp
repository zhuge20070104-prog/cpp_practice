#include <iostream>
#include <string>
#include <cstring>

enum op_t {
    STR_CMP,
    STR_CSTR_CMP,
    STR_WITH_NULL_TERMINATOR
};

struct str_cmp_demo_t {
    void str_cmp() {
        std::string hello_str {"Hello"};
        std::string bello_str {"Bello"};

        std::cout << std::endl;
        std::cout << "Comparing with comparison operators: " << std::endl;

        std::cout << std::boolalpha;
        std::cout << hello_str << "==" << bello_str << ": " << (hello_str == bello_str) << std::endl;
        std::cout << hello_str << "!=" << bello_str << ": " << (hello_str != bello_str) << std::endl;
        std::cout << hello_str << ">" << bello_str << ": " << (hello_str > bello_str) << std::endl;
        std::cout << hello_str << ">=" << bello_str << ": " << (hello_str >= bello_str) << std::endl;
        std::cout << hello_str << "<" << bello_str << ": " << (hello_str < bello_str) << std::endl;    
        std::cout << hello_str << "<=" << bello_str << ": " << (hello_str <= bello_str) << std::endl;    
    }

    void str_cstr_cmp() {
        char const* c_string1 {"Bello"};
        std::string hello_str = "Hello";
        std::cout << "hello_str.size(): " << hello_str.size() << std::endl;
        std::cout << "std::strlen(c_string1): " << std::strlen(c_string1) << std::endl;
        std::cout << hello_str << "==" <<  c_string1 <<" (C-String) : " << (hello_str == c_string1) << std::endl; //false
        std::cout << c_string1 << " (C-String) ==" <<  hello_str <<" : " << (c_string1 == hello_str) << std::endl;//false
        std::cout << c_string1 << " (C-String) >=" <<  hello_str <<" : " << (c_string1 >= hello_str) << std::endl;//false
        std::cout << c_string1 << " (C-String) <" <<  hello_str <<" : " << (c_string1 < hello_str) << std::endl; // true
    }

    void str_with_null_terminator() {
        //Be careful about char arrays not terminated with null character
        std::string hello_str {"hello"};
        char const hello_char_array[] {'h','e','l','l','o','\0'};
        std::cout << hello_str << "== hello_char_array: " << (hello_str == hello_char_array) << std::endl;
    }

    void operator()(op_t type_) {
        switch (type_) {
        case STR_CMP:
            str_cmp();
            break;
        case STR_CSTR_CMP:
            str_cstr_cmp();
            break;
        case STR_WITH_NULL_TERMINATOR:
            str_with_null_terminator();
            break;
        default:
            break;
        }
    }
};

int main(int argc, char* argv[]) {
    str_cmp_demo_t s_c_demo;
    s_c_demo(op_t::STR_CMP);
    s_c_demo(op_t::STR_CSTR_CMP);
    s_c_demo(op_t::STR_WITH_NULL_TERMINATOR);

    return EXIT_SUCCESS;
}