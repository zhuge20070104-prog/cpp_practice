#include <iostream>

class Print {
public:
    void operator()(const std::string& name) {
        std::cout << "Name: " << name << '\n';
    }

    std::string operator()(const std::string& lastname, const std::string& firstname) {
        return lastname + " " + firstname;
    }
};


void do_something(Printer& printer) {
    printer("Draper");
}


int main(int argc, char* argv[]) {
    Print p1;
    p1("leon");

    std::cout << p1("Mr.", "Robot") << '\n';

    do_something(p1);

    return EXIT_SUCCESS;
}