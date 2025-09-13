#include <iostream>
#include <string>

int find_char_v0(std::string const& str, char c) {
    // if found, return index else return -1
    int not_found {-1};
    for(std::size_t i=0; i<str.size(); ++i) {
        if(str.data()[i] == c) {
            return i;
        }
    }
    return not_found;
}

void find_char_v1(std::string const& str, char c, bool& success) {
    //If found set success to true, else set to false
    for(std::size_t i=0; i<str.size(); ++i) {
        if(str.data()[i] == c) {
            success = true;
            return;
        }
    }
    success = false;
}

int main()
{
    std::string str1 {"Hello world in C++ 17"};
    char c{'r'};

    int index = find_char_v0(str1, c);
    if(index != -1) {
        std::cout << "Found character " << c << " at index: " << index << std::endl;
    } else {
        std::cout << "Didn't find our character!" << std::endl;
    }

    bool success {false};
    find_char_v1(str1, c, success);
    if(success) {
        std::cout << "Found character " << c << " in our string" << std::endl;
    } else {
        std::cout << "Didn't find our character!" << std::endl;
    }
    return 0;
}
