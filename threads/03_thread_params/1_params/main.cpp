#include <iostream>
#include <thread>

// 虽然用了引用，但是这里还是做了拷贝
void my_print(int const& i, char* pmybuf) {
    std::cout << i << std::endl;
    std::cout << pmybuf << std::endl;
}


int main(int argc, char* argv[]) {
    int mvar = 1;
    int& myvary = mvar;
    char mybuf[] = "This is a test";

    std::thread myobj(my_print, myvary, mybuf);
    myobj.join();

    std::cout << "Hello world!" << std::endl;

    return EXIT_SUCCESS;
}