#include <iostream>

// 下面两种声明方法是一样的
//double sum( double scores[], size_t count){
double sum_array(double* scores, std::size_t count) {
    double score_sum{};
    for(std::size_t i{0}; i<count; ++i) {
        score_sum += *(scores + i);
    }
    return score_sum;
}

int main(int argc, char* argv[]) {
    double my_scores[] = {10.5, 34.3, 4.8, 6.5};
    double result = sum_array(my_scores, 4);
    std::cout << "result: " << result << std::endl;

    return EXIT_SUCCESS;
}