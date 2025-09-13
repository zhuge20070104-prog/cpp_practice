#include <iostream>
#include <algorithm>


template <typename T>
struct array_printer_t {
    array_printer_t(T* arr_, std::size_t sz_):
        arr(arr_), sz(sz_) {}
    
    void operator()() {
        std::for_each(arr, arr + sz, [](int const& ele){
            std::cout << ele << " ";
        });
        std::cout << std::endl;
    }

private:
    T* arr;
    std::size_t sz;
};


int main(int argc, char* argv[]) {
    int arr0[] = {1, 2, 3, 4, 5};    
    int arr1[] = {6, 7, 8, 9, 10};

    int* p_arr0 {arr0};
    int* p_arr1 {arr1};

    std::cout << "Before Swap: ";
    std::cout << "arr0: ";
    array_printer_t<int> pt0(arr0, std::size(arr0));
    pt0();
    std::cout << "arr1: ";
    array_printer_t<int> pt1(arr1, std::size(arr1));
    pt1();

    // swapping data the hard way
    int temp[5];
    int i = 0;
    std::for_each(arr1, arr1 + std::size(arr0), [&i, &temp](int const& ele) {
        temp[i] = ele;
        ++i;
    });

    i = 0;
    std::for_each(arr0, arr0 + std::size(arr0), [&i, &arr1](int const& ele) {
        arr1[i] = ele;
        ++i;
    });


    i = 0;
    std::for_each(temp, temp + std::size(temp), [&i, &arr0](int const& ele) {
        arr0[i] = ele;
        ++i;
    });

    std::cout << "After Swap: ";
    std::cout << "arr0: ";
    pt0();
    std::cout << "arr1: ";
    pt1();


    // 注意这里只是交换了两个指针，p_arr0和p_arr1,
    // 并没有交换原数组，arr0和arr1
    // swapping array the easy way
    int* p_temp {nullptr};
    p_temp = p_arr1;
    p_arr1 = p_arr0;
    p_arr0 = p_temp;

    std::cout << "After Swap again: ";
    std::cout << "arr0: ";
    // 这里只能用std::size(arr0)，因为指针变量无法获取std::size,只有array能std::size
    array_printer_t<int> pt0_1(p_arr0, std::size(arr0));
    pt0_1();
    std::cout << "arr1: ";
    array_printer_t<int> pt1_1(p_arr1, std::size(arr1));
    pt1_1();


    return EXIT_SUCCESS;
}