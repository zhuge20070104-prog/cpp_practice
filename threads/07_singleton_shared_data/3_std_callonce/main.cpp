#include <iostream>
#include <mutex>

std::once_flag g_flag;

class Singleton {
public:
    static void create_instance() {
        std::cout << "创建示例" << std::endl;
        static CGarbge gab;
        instance = new Singleton();
    }

    static Singleton* get_instance() {
        std::call_once(g_flag, create_instance);
        return instance;
    }

    class CGarbge {
    public:
        ~CGarbge() {
            if(Singleton::instance) {
                std::cout << "销毁示例" << std::endl;
                delete Singleton::instance;
                Singleton::instance = nullptr;
            }
        }
    };

    Singleton(Singleton const&) = delete;
    Singleton& operator=(Singleton const&) = delete;
private:
    Singleton() {};
    static Singleton* instance;
};

Singleton* Singleton::instance = nullptr;

int main(int argc, char* argv[]) {

    auto sing1 = Singleton::get_instance();
    auto sing2 = Singleton::get_instance();
    if(sing1 == sing2) {
        std::cout << "获得同一个单例示例" << std::endl;
    } else {
        std::cout << "获得不同的单例示例" << std::endl;
    }

    return EXIT_SUCCESS;
}


