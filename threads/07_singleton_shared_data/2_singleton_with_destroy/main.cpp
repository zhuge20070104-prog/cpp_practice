
#include <iostream>
#include <mutex>

std::mutex g_mutex;

class Singleton {
public:
    static Singleton* get_instance() {
        if(instance== nullptr) {
            std::lock_guard<std::mutex> lock(g_mutex);
            if(instance==nullptr) {
                std::cout << "创建示例" << std::endl;
                static CGarbage gab;
                instance = new Singleton();
            }
        }
        return instance;
    }

    class CGarbage {
    public:
        ~CGarbage() {
            if(Singleton::instance!=nullptr) {
                std::cout << "销毁全局单例" << std::endl;
                delete Singleton::instance;
                Singleton::instance = nullptr;
            }
        }
    };

    Singleton(Singleton const&) = delete;
    Singleton& operator=(Singleton const&) = delete;

private:
    Singleton() {}
    static Singleton* instance;
};

Singleton* Singleton::instance = nullptr;

int main(int argc, char* argv[]) {
    auto sing1 = Singleton::get_instance();
    auto sing2 = Singleton::get_instance();

    if(sing1 == sing2) {
        std::cout << "获得同一个单例示例" << std::endl;
    } else {
        std::cout << "获取的不是单例示例" << std::endl;
    }

    return EXIT_SUCCESS;
}