#include <iostream>
#include <memory>
#include <cstring>

std::shared_ptr<const char> combine(const char* first, const char* second) {
    // +1 是 '\0'
    std::shared_ptr<const char> fullname{new char[strlen(first) +strlen(second) + 1],  std::default_delete<char[]>()};
    strcpy((char*)fullname.get(), first);
    strcat((char*)fullname.get(), second);
    return fullname;
}
int main(int argc, char* argv[]) {
    char first[10];
    char last[10];

    std::cout << "Please input first name: ";
    std::cin.getline(first, 10);
    std::cout << "Please input last name: ";
    std::cin.getline(last, 10);
    auto full_name = combine(first, last);
    std::cout << full_name.get() << std::endl;

    return EXIT_SUCCESS;
}