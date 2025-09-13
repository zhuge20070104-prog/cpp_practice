#include <iostream>

void say_my_name(std::string const& name);
void process_name(std::string_view name_sv);

int main(int argc, char* argv[]) {
    process_name("Daniel");
    return EXIT_SUCCESS;
}

// Definitions 
void say_my_name(std::string const& name) {
    std::cout << "Your name is " << name << std::endl;
}

void process_name(std::string_view name_sv) {
    // say_my_name(name_sv); // Compiler error, implict conversion from std::string_view to std::string 
                          // is not allowed
    // Fix: Be explict about the conversion
    say_my_name(std::string(name_sv));
}