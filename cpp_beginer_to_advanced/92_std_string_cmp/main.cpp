#include <iostream>
#include <string>

enum op_t {
    STR_TO_STR_CMP,
    STR_CMP_WITH_POS,
    STR_CMP_WITH_CSTR
};

struct str_cmp_method_demo_t {
    void str_to_str_cmp() {
        //Compare (1)
        //int compare( const basic_string& str ) const noexcept;(1)
        //Compares this string to str.

        std::string str1 {"Hello"};
        std::string str2 {"World"};

        std::cout << "str1: " << str1 << std::endl;
        std::cout << "str2: " << str2 << std::endl;
        std::cout << "str1.compare(str2): " << str1.compare(str2) << std::endl;
        std::cout << "str2.compare(str1): " << str2.compare(str1) << std::endl;
    }

    void str_cmp_with_pos() {
        //Compare (2)
        //int compare( size_type pos1, size_type count1,const basic_string& str ) const; (2)
	    //Compares a  substring  of this string(from pos1, going count1 positions) to str
        std::string str1 {"Hello"};
        std::string str3 {"Hello World"};
        std::cout << "Comparing 'World' to 'Hello': " << str3.compare(6, 5, str1) << std::endl;
    }

    void str_cmp_with_cstr() {
        //Compare (3)
        //int compare( const CharT* s ) const;(4)
        //Compares this string to the null-terminated character sequence beginning 
        //at the character pointed to by s.

        std::string str5 {"Hello"};
        char const* message {"World"};
        std::cout << "Comparing Hello to World: " << str5.compare(message) << std::endl;
        std::cout << "Comparing Hello to World: " << str5.compare("World") << std::endl;
    }

    void operator()(op_t type_) {
        switch (type_) {
        case STR_TO_STR_CMP:
            str_to_str_cmp();
            break;
        case STR_CMP_WITH_POS:
            str_cmp_with_pos();
            break;
        case STR_CMP_WITH_CSTR:
            str_cmp_with_cstr();
            break;
        default:
            break;
        }
    }
};

int main(int argc, char* argv[]) {
    str_cmp_method_demo_t sc_demo;
    sc_demo(op_t::STR_TO_STR_CMP);
    sc_demo(op_t::STR_CMP_WITH_POS);
    sc_demo(op_t::STR_CMP_WITH_CSTR);

    return EXIT_SUCCESS;
}