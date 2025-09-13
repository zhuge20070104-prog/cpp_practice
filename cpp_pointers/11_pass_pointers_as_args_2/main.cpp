#include <iostream>

// 把count当指针传进去，修改count的值
double average_price(double* arr, int* count) {
    double sum = 0;
    for(int i=0; i<*count; ++i) {
        sum += *(arr + i);
    }
    double avg = sum / *count;
    *count += 5;
    std::cout << "in function, count: " << *count << std::endl; 
    return avg;
}

int main(int argc, char* argv[]) {
    double prices[5] = {5.00, 4.50, 3.75, 3.10, 6.75};
    int quantity = 5;
    double average = average_price(prices, &quantity);
    std::cout << "$" << average << std::endl;
    std::cout << "in main, quantity: " << quantity << std::endl;
    return EXIT_SUCCESS;
}