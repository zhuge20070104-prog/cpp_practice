#include <iostream>

double sum(double const array[][3], std::size_t size);
double sum_3d(double const array[][3][2], std::size_t size);

int main(int argc, char* argv[]) {
    double weights[][3] = {
        {10.0,20.0,30.0,},
        {40.0,50.0,60.0},
        {70.0,80.0,90.0},
        {100.0,110.0,120.0}    
    };

    double weights_3d[][3][2] = {
        {
            {10,20},
            {30,40},
            {50,60},
        },
        {
            {70,80},
            {90,100},
            {110,120},
        }   
    };

    double result = sum(weights, std::size(weights));
    std::cout << "2d array sum: " << result << std::endl;

    result = sum_3d(weights_3d, std::size(weights_3d));
    std::cout << "3d array sum: " << result << std::endl;
    
    return EXIT_SUCCESS;
}

double sum(double const array[][3], std::size_t size) {
    double sum{};
    for(std::size_t i=0; i<size; ++i) {
        for(std::size_t j{}; j<3; ++j) {
            sum += array[i][j];
        }
    }
    return sum;
}

double sum_3d(double const array[][3][2], std::size_t size) {
    double sum {};
    for(std::size_t i{}; i<size; ++i) {
        for(std::size_t j{}; j<3; ++j) {
            for(std::size_t k{}; k<2; ++k) {
                sum += array[i][j][k];
            }
        }
    }
    return sum;
}