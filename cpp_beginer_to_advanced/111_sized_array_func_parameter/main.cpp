#include <iostream>

double sum(double scores[], std::size_t count) {
    double sum{};
    for(std::size_t i{}; i<count; ++i) {
        sum += scores[i];
    }
    return sum;
}

int main(int argc, char* argv[]) {
    double student_scores[] {10.0,20.0,30.0,4,5,6,7,8,9};
    double result = sum(student_scores, std::size(student_scores));
    std::cout << "result: " << result << std::endl;
    return EXIT_SUCCESS;
}