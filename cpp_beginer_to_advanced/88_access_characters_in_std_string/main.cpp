#include <iostream>
#include <string>

enum op_t {
    FOR_LOOP_INDEX_OPER,
    RANGE_BASED_FOR_LOOP,
    AT_SYNAX,
    MODIFY_AT_AND_INDEX,
    GET_FRONT_AND_BACK_CHAR,
    C_STR,
    C_STR_CHANGE_RAW
};

struct char_access_demo_t {
    void for_loop_index_oper() {
        std::string str1 {"Hello there"};
        std::cout << "str1.size(): " << str1.size() << std::endl;
        std::cout << std::endl;
        std::cout << "For loop with array index notation: " << std::endl;
        std::cout << "str1(for loop): ";
        for(std::size_t i{}; i<str1.size(); ++i) {
            std::cout << " " << str1[i];
        }
        std::cout << std::endl;
    }

    void range_based_for_loop() {
        std::string str1 {"Hello there"};
        std::cout << std::endl;
        std::cout << "Using range based for loop: " << std::endl;
        std::cout << "str1(range based for loop): ";
        for(char value: str1) {
            std::cout << " " << value;
        }
        std::cout << std::endl;
    }

    void at_synax() {
        std::cout << std::endl;
        std::cout << "Using the std::string at() method: " << std::endl;
        std::string str1 {"Hello there"};
        std::cout << "str1(for loop with at()): ";
        for(std::size_t i{}; i<str1.size(); ++i) {
            std::cout << " " << str1.at(i);
        }
        std::cout << std::endl;
    }

    void modify_at_and_index() {
        std::string str1 {"Hello there"};
        str1[0] = 'B';
        str1.at(1) = 'a';
        std::cout << "str1(modified): " << str1 << std::endl;
    }

    void get_front_and_back_char() {
        std::string str2 {"The Phoenix King"};
        char& front_char = str2.front();
        char& back_char = str2.back();
        std::cout << "The front char in str2 is: " << front_char << std::endl;
        std::cout << "The back char in str2 is: " << back_char << std::endl;
        front_char = 'r';
        back_char= 'd';
        std::cout << "str2: " << str2 << std::endl;
    }

    void c_str() {
        std::string str2 {"The Phoenix King"};
        char const* wrapped_c_string = str2.c_str();
        std::cout << "Wrapped c string: " << wrapped_c_string << std::endl;
        // Complier error: error: assignment of read-only location '* wrapped_c_string'
        // wrapped_c_string[0] = 'e';
    }

    void c_str_change_raw() {
        std::string str2 {"Hello World"};
        char* data = str2.data();
        std::cout << "Wrapped c string: " << data << std::endl;
        data[0] = 'B';
        std::cout << "Wrapped c string(after modification): " << data << std::endl;
        std::cout << "Original string(after modification): " << str2 << std::endl;
    }

    void operator()(op_t type_) {
        switch (type_) {
        case FOR_LOOP_INDEX_OPER:
            for_loop_index_oper();
            break;
        case RANGE_BASED_FOR_LOOP:
            range_based_for_loop();
            break;
        case AT_SYNAX:
            at_synax();
            break;
        case MODIFY_AT_AND_INDEX:
            modify_at_and_index();
            break;
        case GET_FRONT_AND_BACK_CHAR:
            get_front_and_back_char();
            break;
        case C_STR:
            c_str();
            break;
        case C_STR_CHANGE_RAW:
            c_str_change_raw();
            break;
        default:
            break;
        }
    }
};

int main(int argc, char* argv[]) {
    char_access_demo_t acc_demo;
    acc_demo(op_t::FOR_LOOP_INDEX_OPER);
    acc_demo(op_t::RANGE_BASED_FOR_LOOP);
    acc_demo(op_t::AT_SYNAX);
    acc_demo(op_t::MODIFY_AT_AND_INDEX);
    acc_demo(op_t::GET_FRONT_AND_BACK_CHAR);
    acc_demo(op_t::C_STR);
    acc_demo(op_t::C_STR_CHANGE_RAW);

    return EXIT_SUCCESS;
}