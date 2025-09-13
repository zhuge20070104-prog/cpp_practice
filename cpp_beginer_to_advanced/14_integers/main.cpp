#include <iostream>

void braced_initialization() {
    // 不初始化就是垃圾数据
    int elephant_count;
    // Initializes to zero
    int lion_count {};
    // Initializes to 10
    int dog_count {10};
    // Initializes to 15
    int cat_count {15};

    // use expressions to initialize
    int demesticated_animals {dog_count + cat_count};
    // 使用未声明的变量, 编译错误
    // int bad_initialization {doesnt_exist1 + doesnt_exist2};
    // 初始化列表会报error或warning
    // error: narrowing conversion of ‘2.8999999999999999e+0’ from ‘double’ to ‘int’ inside { }
    // int narrowing_conversion {2.9};
}

// 函数式变量初始化
void functional_initialization() {
    int apple_count(5);
    int orange_count(10);
    int fruit_count(apple_count + orange_count);
    int narrowing_conversion_functional(2.9);

    std::cout << "apple count: " << apple_count  << std::endl; 
    std::cout << "orange count: " << orange_count << std::endl;
    std::cout << "fruit count: " << fruit_count << std::endl;
    std::cout << "narrowing conversion: " << narrowing_conversion_functional << std::endl;
}

// 赋值初始化
void assignment_initialization() {
    int bike_count = 2;
    int truck_count = 7;
    int vehicle_count = bike_count + truck_count;
    int narrowing_conversion_assignment = 2.9;

    std::cout << "sizeof int: " << sizeof(int) << std::endl;
    std::cout << "sizeof truct_count: " << sizeof(truck_count) << std::endl;
}


int main(int argc, char* argv[]) {
    braced_initialization();
    functional_initialization();
    assignment_initialization();
    return EXIT_SUCCESS;
}