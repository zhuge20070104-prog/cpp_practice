#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

enum artematc_t {
    PLUS_PLUS,
    PLUS_BY_NUMBER,
    PLUS_ON_ARRAY_NAME,
    REVERSE_PRINT_ARRAY,
    REVERSE_PRINT_BY_POINTER,
    MODIFY_ARRAY
};


struct pointer_arthematic_demo_t {
    pointer_arthematic_demo_t() {}

    void plus_plus() {
        int* p_scores{scores};
        std::for_each(p_scores, p_scores + std::size(scores), [](int const& ele) {
            std::cout << ele << " ";
        });
        std::cout << std::endl;
    }

    void plus_by_number() {
        int* p_scores{scores};
        std::cout << "scores[4]: " << *(p_scores + 4) << std::endl;
    }

    void plus_on_array_name() {
        std::for_each(scores, scores + std::size(scores), [](int const& ele) {
            std::cout << ele << " ";
        });
        std::cout << std::endl;
    }

    void reverse_print_array() {
        std::for_each(std::crbegin(scores), std::crend(scores), [](int const& ele) {
            std::cout << ele << " ";
        });
        std::cout << std::endl;
    }

    void reverse_print_by_pointer() {
        std::vector<int> idxes((int)(std::size(scores)), 0);
        std::iota(idxes.begin(), idxes.end(), 0);
        int* pscores{scores + std::size(scores) - 1};
        std::for_each(idxes.crbegin(), idxes.crend(), [&pscores](int const& _) {
            std::cout << *(pscores--) << " ";
        });
        std::cout << std::endl;
    }

    void modify_array() {
        int* pscores {scores};
        scores[0] = 31;
        *(scores + 1) = 32;
        *(pscores + 2) = 33;

        std::cout << std::endl;
        std::cout << "Printing out the array after modification of 3 first elements:" << std::endl; 
        std::for_each(scores, scores + std::size(scores), [](int const& ele) {
            std::cout << ele << " ";
        });
        std::cout << std::endl;
    }

    void operator()(artematc_t type_) {
        switch(type_) {
        case PLUS_PLUS:
            plus_plus();
            break;
        case PLUS_BY_NUMBER:
            plus_by_number();
            break;
        case PLUS_ON_ARRAY_NAME:
            plus_on_array_name();
            break;
        case REVERSE_PRINT_ARRAY:
            reverse_print_array();
            break;
        case REVERSE_PRINT_BY_POINTER:
            reverse_print_by_pointer();
            break;
        case MODIFY_ARRAY:
            modify_array();
            break;
        default:
            break;
        }
    }

private:
    int scores[10] {11,12,13,14,15,16,17,18,19,20};
};
int main(int argc, char* argv[]) {
    pointer_arthematic_demo_t pt_demo;
    pt_demo(artematc_t::PLUS_PLUS);
    pt_demo(artematc_t::PLUS_BY_NUMBER);
    pt_demo(artematc_t::PLUS_ON_ARRAY_NAME);
    pt_demo(artematc_t::REVERSE_PRINT_ARRAY);
    pt_demo(artematc_t::REVERSE_PRINT_BY_POINTER);
    pt_demo(artematc_t::MODIFY_ARRAY);

    return EXIT_SUCCESS;
}