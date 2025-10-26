#include <iostream>
#include <algorithm>

class DivisibleBy {
public:
    explicit DivisibleBy(int d): m_d{d} {}

    bool operator()(int n) const {
        return n % m_d == 0;
    }
private:
    int m_d;
}; 


bool is_odd(int n) {
    return (n % 2 != 0);
}


int main(int argc, char* argv[]) {
    int collection[] {20, 21, 37, 25};

    auto result {
        std::all_of(std::begin(collection), std::end(collection), [](int x) {
            return (x % 2 == 0);
        })
    };

    if(result) {
        std::cout << "All the elements are even" << std::endl;
    } else {
        std::cout << "Not all the elements are even" << std::endl;
    }


    auto result1 {
        std::any_of(std::begin(collection), std::end(collection), DivisibleBy(4))
    };

    if(result1) {
        std::cout << "At least one element is divisible by 4" << std::endl;
    } else {
        std::cout << "No element is divisible by 4" << std::endl;
    }

    auto result2 {
        std::none_of(std::begin(collection), std::end(collection), is_odd)
    };

    if(result2) {
        std::cout << "No element is odd" << std::endl;
    } else {
        std::cout << "At least one element is odd" << std::endl;
    }
    return EXIT_SUCCESS;
}