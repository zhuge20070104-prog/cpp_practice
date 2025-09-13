#include <iostream>
#include <mutex>

std::mutex g_mutex;

class Singleton {
public:
    static Singleton* get_instance() {
        if(!instance) {
            std::lock_guard<std::mutex> lock(g_mutex);
            if(!instance) {
                instance = new Singleton();
            }
        }
        return instance;
    }
private:
    Singleton() {}
    static Singleton* instance;
};
Singleton* Singleton::instance = nullptr;


class Singleton2 {
public:
    static Singleton2* get_instance() {
        return instance;
    }

private:
    Singleton2() {}
    static Singleton2* instance;
};

Singleton2* Singleton2::instance = new Singleton2();

int main(int argc, char* argv[]) {
    auto sing1 = Singleton::get_instance();
    auto sing2 = Singleton::get_instance();
    if(sing1 == sing2) {
        std::cout << "获取到同一个单例类示例" << std::endl;
    } else {
        std::cout << "获取到不同的示例" << std::endl;
    }

    auto sing3 = Singleton2::get_instance();
    auto sing4 = Singleton2::get_instance();

    if(sing3 == sing4) {
        std::cout << "获取到同一个单例类示例" << std::endl;
    } else {
        std::cout << "获取到不同的示例" << std::endl;
    }

    return EXIT_SUCCESS;
}