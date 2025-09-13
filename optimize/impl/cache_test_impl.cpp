#include "stopwatch11.h"
#include <iostream>
#include <memory>

template <typename T>
void cache_init_origin_val(T* p, unsigned limit) {
    for(unsigned j=0; j<limit; ++j) {
        p[j] = (T)(j%256);
    }
}

// 重复10遍，+ 1024
// step = 1024, reps = 10
template <typename T>
T cache_test(T* p, unsigned limit, unsigned step=1, unsigned reps = 1) {
    T sum = 0;
    for(unsigned k=0; k<reps; ++k) {
        for(unsigned i=0, j=0; j<limit; i=(i+step)%limit, ++j) {
            sum += p[i];
        }
    }
    return sum;
}

int test_cache(int test_no, unsigned long multiplier) {
    bool rc = true;

    switch (test_no) {
    default: return -1;
    case 0: return 5;
    case 1: {}
        break;
    
    case 2: {}
        break;
    
    case 3: {}
        break;
    
    case 4: {
        typedef unsigned long long T;
        size_t memsize = (1 << 28) / sizeof(T);
        unsigned step = 1025;
        unsigned reps = 10;
        std::cout << "T == unsigned long long" << std::endl;

        std::unique_ptr<T> p;

        try {
            p.reset(new T[memsize]);
        }catch(std::exception& ) {
            std::cout << "Could not allocate a block of 10,000,000 bytes" << std::endl;
            rc = false;
            break;
        }

        // 初始化unsigned long long 类型值
        cache_init_origin_val(p.get(), memsize);
        T sum = 0;
        for(unsigned limit=memsize, iterations = reps; limit > 65536; limit >>= 1) {
            std::cout << "cache_test("<<limit << ", " << step << "," <<iterations <<  ")";
            StopWatch sw("=");
            sum += cache_test<T>(p.get(), limit, step, iterations);
        }

        std::cout << sum << std::endl;
    }
        break;
    
    case 5: {
        typedef unsigned char T;
        size_t memsize = (1 << 28) / sizeof(T);
        unsigned step = 1025;
        unsigned reps = 10;
        std::cout << "T == unsigned long long" << std::endl;

        std::unique_ptr<T> p;

        try {
            p.reset(new T[memsize]);
        }catch(std::exception& ) {
            std::cout << "Could not allocate a block of 10,000,000 bytes" << std::endl;
            rc = false;
            break;
        }

        // 初始化unsigned long long 类型值
        cache_init_origin_val(p.get(), memsize);
        T sum = 0;
        for(unsigned limit=memsize, iterations = reps; limit > 65536; limit >>= 1) {
            std::cout << "cache_test("<<limit << ", " << step << "," <<iterations <<  ")";
            StopWatch sw("=");
            sum += cache_test<T>(p.get(), limit, step, iterations);
        }

        std::cout << sum << std::endl;
    }
        break;

    }
    
    return (rc) ? 1: 0;
}
