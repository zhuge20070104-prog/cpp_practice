#include <iostream>
#include <thread>

void hello() {
    std::cout << "Hello Concurrent World\n";
}
int main(int argc, char* argv[]) {
    std::thread t(hello);
    t.join();
    return EXIT_SUCCESS;
}