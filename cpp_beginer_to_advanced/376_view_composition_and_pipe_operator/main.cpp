#include <iostream>
#include <algorithm>
#include <ranges>
#include <vector>
#include <unordered_map>
#include <map>


void print_view(auto view) {
    for(auto element: view) {
        std::cout << element << ' ';
    }
    std::cout << '\n';
}


int main(int argc, char* argv[]) {
    std::vector<int> vector {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    print_view(vector);

    auto is_even { [](int n) { return n % 2 == 0; } };

    auto raw_func_comp {
        std::views::transform(std::views::filter(vector, is_even), 
        [](int n) { return n * n; })
    };

    print_view(raw_func_comp);

    auto pipe_out {
        vector | std::views::filter(is_even) | std::views::transform([](int n) { return n * n; })
    };

    print_view(pipe_out);

    std::unordered_map<std::string, int> students {
        {"leon", 22},
        {"john", 28},
        {"dan", 20},
        {"lucifer", 18},
        {"stella", 30}
    };

    std::map<std::string, int> students_map {
        {"leon", 22},
        {"john", 28},
        {"dan", 20},
        {"lucifer", 18},
        {"stella", 30}
    };

    auto names_only {students | std::views::keys};
    std::ranges::copy(names_only, std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;

    std::ranges::copy(students_map | std::views::keys | std::views::reverse, std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;

    auto before_m {[] (const std::string& str) {
        return (static_cast<unsigned char>(str[0])) < (static_cast<unsigned char>('m'));
    }};

    std::ranges::copy(students_map | std::views::keys | std::views::filter(before_m), std::ostream_iterator<std::string>(std::cout, " "));
    std::cout << std::endl;

    return EXIT_SUCCESS;
}