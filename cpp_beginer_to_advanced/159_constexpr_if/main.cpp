#include <iostream>
#include <type_traits>

/*
 * constexpr if - conditional compilation of the code, parts discarded by the constexpr
 * if arent' included in the template instance,
 */

 void fpoint_func(double d) {
    std::cout << "Floating point function used!\n";
 }

 void integral_func(int i) {
    std::cout << "Integral function used!\n";
 }

 template <typename T>
 void func_dispatcher(T t) {
    if constexpr(std::is_integral_v<T>) {
        integral_func(t);
    } else if constexpr(std::is_floating_point_v<T>) {
        fpoint_func(t);
    } else {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "Please pass an int or a float!");
    }
 }
 
int main(int argc, char* argv[]) {

    func_dispatcher(8);
    func_dispatcher(8.2);
    
    return EXIT_SUCCESS;
}