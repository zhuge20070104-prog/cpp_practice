#include <iostream>
#include <algorithm>

struct print_array {

    template<typename T, std::size_t N>
    void operator()(T (&arr) [N]){
        std::for_each(std::begin(arr), std::end(arr), [](T const& ele) {
            std::cout << ele << " ";
        });

        std::cout << std::endl;
    }


    template<typename T>
    void operator()(T* arr, int n){
        std::for_each(arr, arr+n, [](T const& ele) {
            std::cout << ele << " ";
        });

        std::cout << std::endl;
    }
};


struct assign_array {
    template <typename T, std::size_t N>
    void operator()(T (&arr0) [N], T (&arr1) [N]) {
        // arr0 = arr1 
        std::transform(std::begin(arr1), std::end(arr1), std::begin(arr0), [](int const& ele){
            return ele;
        });
    }
};

int main(int argc, char* argv[]) {
    int arr0[5] {1, 2, 3, 4, 5};
    int arr1[5] {6, 7, 8, 9, 10};

    int* p_arr0{arr0};
    int* p_arr1{arr1};
    print_array pt;
    std::cout << "arr0: ";
    pt(arr0);
    std::cout << "arr1: ";
    pt(arr1); 

    // swapping data the hard way
    int temp[5];
    assign_array assgin;
    assgin(temp, arr1);
    assgin(arr1, arr0);
    assgin(arr0, temp);
    
    std::cout << "After swap: " << std::endl;
    std::cout << "arr0: ";
    pt(arr0);
    std::cout << "arr1: ";
    pt(arr1); 


    int* p_temp{nullptr};
    p_temp = p_arr1;
    p_arr1 = p_arr0;
    p_arr0 = p_temp;

    std::cout << "Swap again: " << std::endl;
    std::cout << "arr0: ";
    pt(p_arr0, std::size(arr0));
    std::cout << "arr1: ";
    pt(p_arr1, std::size(arr1));

    return EXIT_SUCCESS;
}