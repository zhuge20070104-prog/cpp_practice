#include <iostream>

int main(int argc, char* argv[]) {
    int* p_int(new int(55));
    std::cout << *p_int << std::endl;
    delete p_int;

    int* p_arr(new int[5]{10, 20, 30, 40, 50});
    *(p_arr + 1) += 5;
    for(int i=0; i<5; ++i) {
        std::cout << *(p_arr + i) << std::endl; 
    }
    delete [] p_arr;
    return EXIT_SUCCESS;
}