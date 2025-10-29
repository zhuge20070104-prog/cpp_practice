#include <iostream>
#include <vector>
#include <ranges>

void print_view(auto view) {
    for(auto element: view) {
        std::cout << element << ' ';
    }
    std::cout << '\n';
}


int main(int argc, char* argv[]) {
    std::vector<int> vector {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto is_even {[](int n) {
        return n % 2 == 0;
    }};    

    std::ranges::filter_view v_evens {std::ranges::filter_view(vector, is_even)};
    print_view(v_evens);

    print_view(std::ranges::filter_view(vector, [](int n) {
        return n%2 != 0;
    }));

    print_view(vector);

    std::ranges::transform_view v_transformed {
        std::ranges::transform_view(vector, [](int n) {
            return n*10;
        })
    };

    print_view(v_transformed);
    print_view(vector);


    std::ranges::take_view view_taken {std::ranges::take_view(vector, 4)};
    print_view(view_taken);

    std::ranges::take_while_view view_taken_while {
        std::ranges::take_while_view(vector, [](int n) {
            return n % 2 != 0;
        }
    };

    print_view(view_taken_while);

    // drops the 4 elements from the vector and then saves the rest in the view
    std::ranges::drop_view drop_elements {
        std::ranges::drop_view(vector, 4)
    };

    print_view(drop_elements);


    std::ranges::drop_while_view drop_elements_while {
        std::ranges::drop_while_view(vector, [](int n) {
            return n % 2 != 0;
        })
    };

    print_view(drop_elements_while);


    std::vector<std::pair<int, std::string>> pair_vector{
        {1, "one"},
        {2, "two"}
    };

    std::cout << "keys_view: \n";
    auto keys_view {std::views::values(pair_vector)};
    print_view(keys_view);


    auto is_odd {[](int n) {
        return n % 2 != 0;
    }};

    auto odd_view {std::views::filter(vector, is_odd)};
    print_view(odd_view);
    return EXIT_SUCCESS;
}