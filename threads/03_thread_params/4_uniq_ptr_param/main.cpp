#include <iostream>
#include <memory>
#include <thread>


void my_print(std::unique_ptr<int> ptn) {
    std::cout << "Thread= " << std::this_thread::get_id() << std::endl;
}


int main(int argc, char* argv[]) {
    std::unique_ptr<int> up(new int(10));
    std::thread my_thread(my_print, std::move(up));
    my_thread.join();


    return EXIT_SUCCESS;
}