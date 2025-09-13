#include <iostream>

double average_price(double* arr, int count) {
    double sum = 0;
    for(int i=0; i<count; ++i) {
        sum += *(arr + i);
    }
    return sum/ count;
}

int main(int argc, char* argv[]) {
    double prices[5] = {5.00, 4.50, 3.75, 3.10, 6.75};
    double average = average_price(prices, 5);
    std::cout << "$" << average << std::endl;
    return EXIT_SUCCESS;
}