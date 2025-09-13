#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    std::string message {"Hello world!Hello world!Hello world!Hello world!Hello world!Hello world!Hello world!Hello world!Hello world!Hello world!Hello world!Hello world!Hello world!Hello world!Hello world!vvHello world!Hello world!Hello world!Hello world!Hello world!"};
    std::string& message_copy {message};
    char const* p1 = message.data();
    char const* p2 = message_copy.data();

    std::cout << "&message[0]: " << (void*)p1 << std::endl;
    std::cout << "&message_copy[0]: " << (void*)p2 << std::endl;
     
    return EXIT_SUCCESS;
}