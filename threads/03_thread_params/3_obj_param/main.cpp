#include <iostream>
#include <thread>

class A {
public:
    mutable int m_i;
    A(int i): m_i(i) {}
};

void my_print(A const& pmybuf) {
    pmybuf.m_i = 199;
    std::cout << "子线程的参数地址是: " << &pmybuf << " Thread id= " << std::this_thread::get_id() 
        << std::endl;
}


int main(int argc, char* argv[]) {
    A myobj(10);

    std::thread mythread(my_print, myobj);
    mythread.join();

    std::cout << "Hello world!" << std::endl;

    return EXIT_SUCCESS;
}