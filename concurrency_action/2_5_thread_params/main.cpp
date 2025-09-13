#include <iostream>
#include <thread>

void some_funtion() {
    std::cout << "some_function() called\n"; 
}

void some_other_function(int param) {
    std::cout << "some_other_function(" << param << ") called\n"; 
}
 
 std::thread f() {
    void some_function();
    return std::thread(some_funtion);
 }

 std::thread g() {
    void some_other_function(int);
    std::thread t(some_other_function, 42);
    return t;
 }
int main(int argc, char* argv[]) {
    std::thread t1 = f();
    t1.join();
    std::thread t2 = g();
    t2.join();
    return EXIT_SUCCESS;
}