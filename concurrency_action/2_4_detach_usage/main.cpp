#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>
#include <memory>
#include <condition_variable>

std::mutex mutex_;
int input_index = 0;


void open_docment_and_display_gui(std::string const& filename) {
    std::cout << "open_docment_and_display_gui: " << filename << std::endl;
}

enum command_type {
    open_new_document,
    insert_char,
    exit_document
};

struct user_command {
    command_type type;
    user_command(command_type const& type_=insert_char): type(type_) {

    }
};

std::unique_ptr<user_command> get_user_input() {
    std::lock_guard<std::mutex> lock_(mutex_);
    // 每 100次发一个 open_new_document
    input_index++;
    std::cout << "input index: " << input_index << std::endl;
    
    // 大于10000次用户输入就退出，这里其实可以是用户输入 exit就退出
    // 这是模拟
    if(input_index > 10000) {
        return std::make_unique<user_command>(exit_document);
    }

    // 每100次用户输入模拟一次 打开新文档
    if(input_index % 100 == 0) {
        std::cout <<"new document command: " << std::endl;
        return std::make_unique<user_command>(open_new_document);
    }

    // 平时默认是插入字符
    return std::make_unique<user_command>();
}

std::string get_filename_from_user() {
    return "foo.doc";
}

void process_user_input(user_command const& cmd) {
    std::cout << "Process insert char command" << std::endl;
}

std::unique_ptr<user_command> user_cmd;

void edit_document(std::string  filename) {
    std::cout << "==Start new edit_document thread==" << std::endl;
    open_docment_and_display_gui(filename);
    while(true) {
        auto user_cmd = get_user_input();
        if(user_cmd->type == open_new_document) {
            std::string const new_name = get_filename_from_user();
            std::thread t(edit_document, new_name);
            t.detach(); // detach的用法，不阻塞当前线程，后台运行时托管
        } else if(user_cmd->type == exit_document) {
            std::cout << "exit edit" << std::endl;
            break;
        } else {
            process_user_input(*user_cmd);
        }
    }
}


int main(int argc, char* argv[]) {
    edit_document("bar.doc");
    return EXIT_SUCCESS;
}