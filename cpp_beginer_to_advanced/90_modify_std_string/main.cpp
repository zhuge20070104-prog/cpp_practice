#include <iostream>
#include <string>

enum op_t {
    STR_CLEAR,
    STR_INSERT1,
    STR_INSERT2,
    STR_INSERT3,
    STR_INSERT4,
    STR_INSERT5,
    STR_ERASE,
    STR_PUSH_BACK,
    STR_POP_BACK
};

struct modify_str_demo_t {
    void str_clear() {
        std::string str1 {"The Lion Dad"};
        std::cout << "str1: " << str1 << std::endl;
        std::cout << "str1 size: " << str1.size() << std::endl;
        std::cout << "str1 capacity: " << str1.capacity() << std::endl;

        str1.clear();
        std::cout << std::endl;
        std::cout << "str1: " << str1 << std::endl;
        std::cout << "str1 size: " << str1.size() << std::endl;
        std::cout << "str1 capacity: " << str1.capacity() << std::endl;
    }

    void str_insert1() {
        //Insert (1)
        //(1)basic_string& insert( size_type index, size_type count, CharT ch );
        //Inserts count characters in the string starting at index index
        std::string str2 {"122"};
        std::cout << "str2: " << str2 << std::endl;
        str2.insert(1, 4, '3');
        std::cout << std::endl;
        std::cout << "str2: " << str2 << std::endl; // 1333322
    }

    void str_insert2() {
        //(2)basic_string& insert( size_type index, const CharT* s );
        //Inserts null-terminated character string pointed to by s
        //at the position index. The length of the string is determined 
        //by the first null character.
        std::string str3 {"Hello!"};
        char const* txt3 {" World"};
        std::cout << "str3: " << str3 << std::endl;
        str3.insert(5, txt3);
        
        std::cout << std::endl;
        std::cout << "str3: " << str3 << std::endl;
    }

    void str_insert3() {
        //(3)basic_string& insert( size_type index, const CharT* s, size_type count );
        //Inserts the characters in the range [s, s+count) at the position index.
        //The range can contain null characters.

        std::string str4 {"Hello!"};
        char const* txt4 {" World Health Organization"};
        std::cout << "str4: " << str4 << std::endl;

        str4.insert(5, txt4, 6);
        std::cout << std::endl;
        std::cout << "str4: " << str4 << std::endl;
    }

    void str_insert4() {
        //Insert (4)
        //(4)basic_string& insert( size_type index, const basic_string& str );
        //Inserts string str at the position index

        std::string str5 {" World"};
        std::string str6 {"Hello!"};
        std::cout << "str6: " << str6 << std::endl;

        str6.insert(5, str5);
        std::cout << std::endl;
        std::cout << "str6: " << str6 << std::endl;
    }

    void str_insert5() {
        //Insert (5)
        //(5)basic_string& insert( size_type index, const basic_string& str,
        //                  size_type index_str, size_type count = npos);
        //Inserts a string, obtained by str.substr(index_str, count) at the position index
        std::string str7 {"Hello!"};
        std::string str8 {"Statistical Analysis of the World Population."};
        std::cout << "str7: " << str7 << std::endl;
        str7.insert(5, str8, 27, 6);

        std::cout << std::endl;
        std::cout << "str7: " << str7 << std::endl; 
    }

    void str_erase() {
        //Erase
        //basic_string& erase( size_type index = 0, size_type count = npos );
        //Starting at index index, erase count characters from the string
        //Notice that this function returns a referennce
        std::string str9 {"Hello World is a message used to start off things when learning programming!"};
        str9.erase(11, str9.size() - 12);
        std::cout << "str9: " << str9 << std::endl;

        // Reset str9
        str9 = "Hello World is a message used to start off things when learning programming!";
        //Direct print out.Because this method returns a reference to the modified string
        std::cout << "str9: " << str9.erase(11, str9.size() - 12) << std::endl;
    }

    void str_push_back() {
        //push_back
        //void push_back( CharT ch );
        //Appends the given character ch to the end of the string
        std::string str10{"Hello world"};
        str10.push_back('!');
        std::cout << "str10: " << str10 << std::endl;
    }

    void str_pop_back() {
        //pop_back
        //void pop_back();
	    //Removes the last character from the string.
        std::string str11 {"Hello world!!"};
        str11.pop_back();
        std::cout << "str11: " << str11 << std::endl; 
    }

    void operator()(op_t type_) {
        switch (type_) {
        case STR_CLEAR:
            str_clear();
            break;
        case STR_INSERT1:
            str_insert1();
            break;
        case STR_INSERT2:
            str_insert2();
            break;
        case STR_INSERT3:
            str_insert3();
            break;
        case STR_INSERT4:
            str_insert4();
            break;
        case STR_INSERT5:
            str_insert5();
            break;
        case STR_ERASE:
            str_erase();
            break;
        case STR_PUSH_BACK:
            str_push_back();
            break;
        case STR_POP_BACK:
            str_pop_back();
            break;
        default:
            break;
        }
    } 
};

int main(int argc, char* argv[]) {
    modify_str_demo_t m_str_demo;
    m_str_demo(op_t::STR_CLEAR);
    m_str_demo(op_t::STR_INSERT1);
    m_str_demo(op_t::STR_INSERT2);
    m_str_demo(op_t::STR_INSERT3);
    m_str_demo(op_t::STR_INSERT4);
    m_str_demo(op_t::STR_INSERT5);
    m_str_demo(op_t::STR_ERASE);
    m_str_demo(op_t::STR_PUSH_BACK);
    m_str_demo(op_t::STR_POP_BACK);

    return EXIT_SUCCESS;
}