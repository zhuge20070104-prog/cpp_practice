#include <iostream>

int main(int argc, char* argv[]) {
    int num = 10;
    int* p_num = &num;
    int** p_2_num = &p_num;

    std::cout << "address of num: " << &num << std::endl;
    std::cout << "address stored in p_num: " << p_num << std::endl;
    std::cout << "address of p_num: " << &p_num << std::endl;
    std::cout << "address stored in p_2_num: " << p_2_num << std::endl;

    // 二维指针可能看起来有点混乱，但是在处理大型数组排序时非常高效
    int scores[5] = {100, 95, 99, 85, 83};
    int* pt_arr[5];
    for(int i=0; i<5; ++i) {
        pt_arr[i] = (scores + i);
        std::cout << *(pt_arr + i) << std::endl;
    }

    // 打印 scores的所有地址和值
    for(int i=0; i<5; ++i) {
        std::cout << *(pt_arr + i) << ": " << **(pt_arr + i) << std::endl;
    }
    return EXIT_SUCCESS;
}