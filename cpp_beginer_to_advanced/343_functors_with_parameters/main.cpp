#include <exception>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <functional>
#include <concepts>

template <typename T>
requires std::is_arithmetic_v<T>
class IsInRange {
public:
    IsInRange(T min, T max): min_inclusive{min}, max_inclusive{max} {}

    bool operator()(T value) const {
        return (value >= min_inclusive) && (value <= max_inclusive);
    }
private:
    T min_inclusive {};
    T max_inclusive {};
};


template <typename T, typename Rangepicker>
requires std::is_arithmetic_v<T>
T range_sum(const std::vector<T>& numbers, Rangepicker rangepicker) {
    T sum {};

    for(std::size_t i{}; i<numbers.size(); ++i) {
        if(rangepicker(numbers[i])) {
            sum += numbers[i];
        }
    }
    return sum;
}


int main(int argc, char* argv[]) {
    std::vector<double> double_vec {22.1, 11.2, 19.6, 9.8};
    
    std::cout << "range_sum(double_vec, IsInRange<double>(5.5, 15.0)): " << range_sum(double_vec, IsInRange<double>(5.5, 15.0)) << std::endl;
    std::cout << "range_sum(double_vec, IsInRange<double>(0.0, 30.0)): " << range_sum(double_vec, IsInRange<double>(0.0, 30.0)) << std::endl;
    return EXIT_SUCCESS;    
}
