#include <iostream>
#include <string>

enum op_t {
    THE_BAD_WAY,
    RAW_STR_LITERALS_INIT,
    RAW_STR_LITERALS_ASSIGN,
    RAW_STR_LITERALS_C_STR,
    OTHER_ESCAPED_STR,
    PROBMATIC_RAW_STR_LITERALS
};

struct string_literal_demo_t {

    void the_bad_way() {
        std::string todo_list {"\tClean the house\n\tWalk the dog\n\tDo laundry\n\tpick groceries"};
        std::string windows_path {"D:\\sandbox\\testProject\\hello.txt"};
        std::string linux_path {"/home/username/files/hello.txt"};
        std::string hint {" \"\\\\\" escapes a backslash character like \\."};
        
        std::cout << "todo_list : " << std::endl;
        std::cout << todo_list << std::endl;
        std::cout << "windows_path : " << windows_path << std::endl;
        std::cout << "linux_path : " << linux_path << std::endl;
        std::cout << "hint : " << hint << std::endl;
    }

    void raw_str_literals_init() {
        std::string to_do_list {R"(        Clean the house
        Walk the dog
        Do Laundry
        Pick groceries)"};
        std::cout << "to_do_list: " << std::endl;
        std::cout << to_do_list << std::endl;
    }

    void raw_str_literals_assign() {
        std::string to_do_list = R"(        Clean the house
        Walk the dog
        Do Laundry
        Pick groceries)";
        std::cout << "to_do_list: " << std::endl;
        std::cout << to_do_list << std::endl;
    }

    void raw_str_literals_c_str() {
        char const* c_string {R"(        Clean the house
        Walk the dog
        Do Laundry
        Pick groceries)"};
        std::cout << "to_do_list: " << std::endl;
        std::cout << c_string << std::endl; 
    }

    void other_escaped_str() {
        std::string windows_path {R"(D:\sandbox\testProject\hello.txt)"};
        std::string linux_path {R"(/home/fredric/files/hello.txt)"};
        std::string hint {R"(\\"escapes a backslash character like \.)"};
        std::cout << "windows_path: " << windows_path << std::endl;
        std::cout << "linux_path: " << linux_path << std::endl;
        std::cout << "hint: " << hint << std::endl; 
    }

    void probmatic_raw_string_literals() {
        std::string sentence {R"--(The  message was "(Stay out of this!)")--"};
        std::cout << "sentence: " << sentence << std::endl;
    }

    void operator()(op_t type_) {
        switch (type_) {
        case THE_BAD_WAY:
            the_bad_way();
            break;
        case RAW_STR_LITERALS_INIT:
            raw_str_literals_init();
            break;
        case RAW_STR_LITERALS_ASSIGN:
            raw_str_literals_assign();
            break;
        case RAW_STR_LITERALS_C_STR:
            raw_str_literals_c_str();
            break;
        case OTHER_ESCAPED_STR:
            other_escaped_str();
            break;
        case PROBMATIC_RAW_STR_LITERALS:
            probmatic_raw_string_literals();
            break;
        default:
            break;
        }
    }
};

int main(int argc, char* argv[]) {
    string_literal_demo_t s_l_demo;
    s_l_demo(op_t::THE_BAD_WAY);
    s_l_demo(op_t::RAW_STR_LITERALS_INIT);
    s_l_demo(op_t::RAW_STR_LITERALS_ASSIGN);
    s_l_demo(op_t::RAW_STR_LITERALS_C_STR);
    s_l_demo(op_t::OTHER_ESCAPED_STR);
    s_l_demo(op_t::PROBMATIC_RAW_STR_LITERALS);

    return EXIT_SUCCESS;
}