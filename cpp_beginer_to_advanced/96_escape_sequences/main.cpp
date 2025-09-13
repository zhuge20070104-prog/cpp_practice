#include <iostream>
#include<string>

enum op_t {
    NEW_LINE,
    COMMA,
    TODO_LIST,
    WINDOWS_PATH,
    LINUX_PATH,
    HINT,
    CHAR
};

struct escape_sequences_t {
    void new_line() {
        for(std::size_t i=0; i<10; ++i) {
            std::cout << "Hello\n";
        }
    }

    void comma() {
        std::cout << "He said \"Got out of here immediately!\"" << std::endl;
    }

    void todo_list_() {
        std::string todo_list = "\tClean the house\n\tWalk the dog\n\tDo laundry\n\tPick groceries";
        std::cout << "todo_list: " << std::endl;
        std::cout << todo_list << std::endl;
    }

    void windows_path_() {
        std::string windows_path = "D:\\sandbox\\testProject\\hello.txt";
        std::cout << "windows_path: " << windows_path << std::endl; 
    }

    void linux_path_() {
        std::string linux_path = "/home/fredric/files/hello.txt";
        std::cout << "linux_path: " << linux_path << std::endl;
    }

    void hint_() {
        std::string hint = "\"\\\\\" escapes a backslash character like \\.";
        std::cout << "hint: " << hint << std::endl;
    }

    void char_() {
        std::cout << "\a" << std::endl;
    }

    void operator()(op_t type_) {
        switch (type_) {
        case NEW_LINE:
            new_line();        
            break;
        case COMMA:
            comma();
            break;
        case TODO_LIST:
            todo_list_();
            break;
        case WINDOWS_PATH:
            windows_path_();
            break;
        case LINUX_PATH:
            linux_path_();
            break;
        case HINT:
            hint_();
            break;
        case CHAR:
            char_();
            break;
        default:
            break;
        }
    }
};

int main(int argc, char* argv[]) {
    escape_sequences_t e_s_demo;
    e_s_demo(op_t::NEW_LINE);
    e_s_demo(op_t::COMMA);
    e_s_demo(op_t::TODO_LIST);
    e_s_demo(op_t::WINDOWS_PATH);
    e_s_demo(op_t::LINUX_PATH);
    e_s_demo(op_t::HINT);
    e_s_demo(op_t::CHAR);
    
    return EXIT_SUCCESS;
}