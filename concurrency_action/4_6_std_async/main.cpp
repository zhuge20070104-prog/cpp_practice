#include <iostream>
#include <mutex>
#include <thread>
#include <future>

int find_the_answer_to_ltuae() {
    return 42;
}

void do_other_stuff() {
    std::cout << "do_other_stuff()...\n";
}

int main(int argc, char* argv[]) {  
    std::future<int> the_answer = std::async(find_the_answer_to_ltuae);
    do_other_stuff();
    std::cout << "The answer is: " << the_answer.get() << std::endl;
    return EXIT_SUCCESS;
}