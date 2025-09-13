#include <iostream>

double sum(double const (&scores) [10]);

int main(int argc, char* argv[]) {
    double student_scores[] = {10.0,20.0,30.0,40.0,50.0,60.0,70.0,80.0,90.0,1}; 
    double sum_result = sum(student_scores);
    std::cout << "result is: " << sum_result << std::endl;
    return EXIT_SUCCESS;
}

double sum(double const (&scores) [10]) {
    double sum{};
    for(std::size_t i{}; i<std::size(scores); ++i) {
        sum += scores[i];
    }
    return sum;
}