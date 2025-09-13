#include "stopwatch11.h"    // stopwatch class for performance testing
#include "block_mgr.h"
#include <exception>
#include <random> // for random allocating and freeing nodes
#include <functional> // for bind, used by random
#include <iostream> // std::cout etc


// Something for global memory manager to allocate
class TestClass {
    int contents_;
public:
    TestClass(int c): contents_(c) {}
};


// class with class-specific operator new
class MemManagerTester {
    int contents_;;
public:
    MemManagerTester(int c): contents_(c) {}
    static void* operator new(std::size_t s) {
        return mgr_.allocate(s);
    }

    static void operator delete(void* p) {
        mgr_.deallocate(p);
    }
    static fixed_block_memory_manager<fixed_arena_controller> mgr_;
};

char arena2[8008] = {0};
fixed_block_memory_manager<fixed_arena_controller> MemManagerTester::mgr_(arena2);

int test_fixed_block_memory_manager(int test_no, unsigned long multiplier) {
    bool rc = true;
    switch (test_no) {
    default: return -1;
    case 0: return 3; // total number of tests

    case 1: {
        {
            char arena[101];
            fixed_block_memory_manager<fixed_arena_controller> block_mgr(arena);
            for(int i=0; i<10; ++i) {
                block_mgr.allocate(10);
            }

            try{
                block_mgr.allocate(10);
                rc = false;
            } catch(std::bad_alloc&) {
                rc &= true;
            }
        }
       
        {
            char arena[15];
            fixed_block_memory_manager<fixed_arena_controller> block_mgr(arena);
            try {
                // should allocated a single 8 byte node, sizeof(void*) on 64-bit platform is 8 byte
                block_mgr.allocate(3);
                rc &= true;
            }catch(std::bad_alloc&) {
                rc &= false;
            }


            try {
                block_mgr.allocate(3);
                rc &= false;
            }catch(std::bad_alloc&) {
                rc &= true;
            }
        }

        {
            char arena[1];
            fixed_block_memory_manager<fixed_arena_controller> block_mgr(arena);
            try {
                // 将会挂掉，在一次分配时，因为arena_controller 剩余内存不足
                block_mgr.allocate(4);
                rc &= false;
            }catch(std::bad_alloc&) {
                rc &= true;
            }
        }
    }
        break;
    
    // 直接分配单个元素的速度
    case 2: {   
        {   
            // 全局的分配操作符 new
            StopWatch sw("allocate TestClass");
            for(auto j=10*multiplier; j>0; --j) {
                for(auto i=0; i<1000; ++i) {
                    new TestClass(i);
                }
            }
        }

        {
            // MemMgrTest对象的new
            std::cout << "sizeof(MemMgrTester) = " << sizeof(MemManagerTester) << std::endl;
            StopWatch sw("allocate MemManTester: local new");
            for(auto j=10*multiplier; j>0; --j) {
                MemManagerTester::mgr_.clear();
                for(auto i=0; i<1000; ++i) {
                    new MemManagerTester(i);
                }
            }
        }

        {
            StopWatch sw("allocate MemManTester: global new");
            for(auto j=10*multiplier; j>0; --j) {
                for(auto i=0; i<1000; ++i) {
                    // ::new 调用全局new 运算符
                    ::new MemManagerTester(i);
                }
            }
        }
    }   
        break;
    
    case 3: {
        // 随机分配单个元素的速度
        static const unsigned array_size = 1000;
        {
            std::default_random_engine e;
            std::uniform_int_distribution<unsigned> d(0, array_size - 1);
            auto randomizer = std::bind(d, e);

            MemManagerTester::mgr_.clear();

            MemManagerTester* a[array_size];
            for(int i=0; i<array_size; ++i) {
                a[i] = nullptr;
            }

            StopWatch sw("MemMgrTester: local new/delete");
            for (auto  i = 10000*multiplier; i>0; --i) {
                auto idx =randomizer();
                auto p = new MemManagerTester(i);
                if(a[idx] != nullptr) {
                    delete a[idx];
                }
                a[idx] = p;
            }


            for(auto i=0; i<array_size; ++i) {
                delete a[i];
            }
        }


         {
            std::default_random_engine e;
            std::uniform_int_distribution<unsigned> d(0, array_size - 1);
            auto randomizer = std::bind(d, e);

            MemManagerTester::mgr_.clear();

            MemManagerTester* a[array_size];
            for(int i=0; i<array_size; ++i) {
                a[i] = nullptr;
            }

            StopWatch sw("MemMgrTester: global new/delete");
            for (auto  i = 10000*multiplier; i>0; --i) {
                auto idx =randomizer();
                auto p = ::new MemManagerTester(i);
                if(a[idx] != nullptr) {
                    ::delete a[idx];
                }
                a[idx] = p;
            }


            for(auto i=0; i<array_size; ++i) {
                ::delete a[i];
            }
        }

    }
        break;
  
    }
    return (rc)? 1: 0;
}