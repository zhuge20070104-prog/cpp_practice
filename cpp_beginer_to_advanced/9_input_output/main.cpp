#include <iostream>
#include <string>


void func1() {
    std::cout << "Hello world in C++" << std::endl;
    int a{4};
    int b{4};

    // Runtime error 
    // int c = 10/ (a-b);
    // std::cout << "The value of c is: " << c << std::endl;

    // Warnings
    // 20/0;
}

void cin_cout_func1() {
    int age;
    std::string name;

    std::cout << "Please type in your last name: ";
    std::cin >> name;

    std::cout << "Please type in your age: ";
    std::cin >> age;

    std::cout << "Hello " << name << "! you are " << age << " years old" << std::endl;
}

void cin_cout_func2() {
    // 读取有空格的数据
    int age;
    std::string full_name;

    std::cout << "Please type in your full name: ";
    while(full_name.empty()) {
        std::getline(std::cin, full_name);
    }

    std::cout << "Please type in your age: ";
    std::cin >> age;

    std::cout << "Hello " << full_name << "! you are " << age << " years old" << std::endl;
}

int main(int argc, char* argv[]) {
    func1();
    cin_cout_func1();
    cin_cout_func2();

    return EXIT_SUCCESS;
}