#include <iostream>
#include <ctime>
#include <cstdlib>


int main(int argc, char* argv[]) {

    std::srand(std::time(0));

    auto gen_a_rand = []() {
        std::cout << "generating a random number between 0 ~ RAND_MAX" << std::endl;
        int random_num = std::rand();
        std::cout << "random_num: " << random_num << std::endl; // 0 ~ RAND_MAX
        random_num = std::rand();
        std::cout << "random_num: " << random_num << std::endl; // 0 ~ RAND_MAX
        std::cout << std::endl;
    };

    auto gen_rand_loop = []() {
        std::cout << "generating a random number 0-RAND_MAX in a loop" << std::endl;
        int random_num;
        for(std::size_t i = 0; i < 20; ++i) {
            random_num = std::rand();
            std::cout << "random_num " << i << ":" << random_num << std::endl; // 0 ~ RAND_MAX
        }
        std::cout << std::endl;
    };

    auto gen_rand_0_10 = []() {
        std::cout << "generating a random number 0-10 in a loop" << std::endl;
        int random_num = std::rand() % 11;
        for(std::size_t i = 0; i < 20; ++i) {
            random_num = std::rand() % 11;
            std::cout << "random_num " << i << ":" << random_num << std::endl; // 0 ~ 10
        }
        std::cout << std::endl;
    };

    auto gen_rand_1_10 = []() {
        std::cout << "generating a random number 1-10 in a loop" << std::endl;
        int random_num = std::rand() % 10 + 1;
        for(std::size_t i = 0; i < 20; ++i) {
            random_num = std::rand() % 10 + 1;
            std::cout << "random_num " << i << ":" << random_num << std::endl; // 0 ~ 10
        }
        std::cout << std::endl;
    };

    gen_a_rand();
    gen_rand_loop();
    gen_rand_0_10();
    gen_rand_1_10();
    
    return EXIT_SUCCESS;
}