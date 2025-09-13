#include <iostream>

enum new_fail_cond_t {
    NO_PROTECT,
    NO_PROTECT_1,
    EXCEPT,
    NO_THROW
};

struct new_fail_demo_t {
    

    void no_protect() {
        // terminate called after throwing an instance of 'std::bad_alloc'
        // int * data = new int[10000000000000000];
    }

    void no_protect_1() {
        // terminate called after throwing an instance of 'std::bad_alloc'
        // for(std::size_t i=0; i<10000000; ++i) {
        //     int* data = new int[100000000];
        // }
    }

    void except() {
        // Something went wrong: std::bad_alloc
        // for(std::size_t i=0; i<1000000; ++i) {  
        //     try {
        //         int* data = new int[100000000];
        //     } catch(std::exception& ex) {
        //         std::cout << "Something went wrong: " << ex.what() << std::endl;
        //     }
        // }
    }


    void no_throw() {
        for(std::size_t i=0; i<1000000; ++i) {  
            int* data = new (std::nothrow) int[100000000];
            if(data != nullptr) {
                std::cout << "Data allocated" << std::endl;
            } else {
                std::cout << "Data allocation failed" << std::endl;
            }
        }
    }

    void operator()(new_fail_cond_t cond) {
        switch(cond) {
        case NO_PROTECT:
            no_protect();
        break;

        case NO_PROTECT_1:
            no_protect_1();
        break;

        case EXCEPT:
            except();
        break;

        case NO_THROW:
            no_throw();
        break;

        default:
        break;
        }
    }
};

int main(int argc, char* argv[]) {
    new_fail_demo_t fail_demo;
    fail_demo(new_fail_cond_t::NO_PROTECT);
    fail_demo(new_fail_cond_t::NO_PROTECT_1);
    fail_demo(new_fail_cond_t::EXCEPT);
    fail_demo(new_fail_cond_t::NO_THROW);
    return EXIT_SUCCESS;
}