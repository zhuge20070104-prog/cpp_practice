#include <iostream>
#include <thread>


void my_print(int const i, std::string const& pmybuf) {
    std::cout << i << std::endl;
    std::cout << pmybuf << std::endl;
}


int main(int argc, char* argv[]) {
    int mvar = 1;
    int& myvary = mvar;

    char mybuf[] = "This is a test";

    std::thread myobj(my_print, myvary, std::string(mybuf));
    myobj.join();

    std::cout << "Hello world!" << std::endl;
    
    return EXIT_SUCCESS;
}