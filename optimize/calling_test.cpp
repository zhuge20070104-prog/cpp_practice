#include <iostream>
#include "calling.h"
#include "stopwatch11.h"

#include "test_driver.h"

using counter_t = unsigned long long;

int test_calling(int test_no, unsigned long multiplier) {
    bool rc = true;
    volatile int retval;
    counter_t const nCalls = 1000000ULL * 10ULL;
    std::cout << nCalls << " iterations" << std::endl;
    switch (test_no) {
    default:
        return -1;
    
    case 0:
        return 5;
    case 1:
        return 1;
    
    case 2: {
        C c;
        c.x_ = 0;
        C1 c1(c);
        C2 c2(c1);
        C3 c3(c2);
        C4 c4(c3);
        C5 c5(c4);

        StopWatch sw("zero arg");
        for(counter_t i=0; i<nCalls; ++i) {
            c.f0();
        }
       sw.Start("c.f0()");

        for(counter_t i=0; i<nCalls; ++i) {
            c1.f0();
        }
        sw.Start("c1.f0()");

        for(counter_t i=0; i<nCalls; ++i) {
            c2.f0();
        }

        sw.Start("c2.f0()");

        for(counter_t i=0; i<nCalls; ++i) {
            c3.f0();
        }
        sw.Start("c3.f0()");

        for(counter_t i=0; i<nCalls; ++i) {
            c4.f0();
        }
        sw.Start("c4.f0()");

        for(counter_t i=0; i<nCalls; ++i) {
            c5.f0();
        }
        sw.Stop("c5.f0()");

        rc &= (c.x_ == 0);
    }
        break;
    
    case 3: {
        C c;
        c.x_ = 0;
        C1 c1(c);
        C2 c2(c1);
        C3 c3(c2);
        C4 c4(c3);
        C5 c5(c4);

        StopWatch sw("zero arg with retval");
        for(counter_t i=0; i<nCalls; ++i) {
           retval  = c.f0();
        }
       sw.Start("c.f0()");

        for(counter_t i=0; i<nCalls; ++i) {
            retval = c1.f0();
        }
        sw.Start("c1.f0()");

        for(counter_t i=0; i<nCalls; ++i) {
            retval = c2.f0();
        }

        sw.Start("c2.f0()");

        for(counter_t i=0; i<nCalls; ++i) {
            retval = c3.f0();
        }
        sw.Start("c3.f0()");

        for(counter_t i=0; i<nCalls; ++i) {
            retval = c4.f0();
        }
        sw.Start("c4.f0()");

        for(counter_t i=0; i<nCalls; ++i) {
            retval = c5.f0();
        }
        sw.Stop("c5.f0()");

        rc &= (c.x_ == 0);
    }
        break;
    
    case 4: {   
        C c;
        c.x_ = 0;
        C1 c1(c);
        C2 c2(c1);
        C3 c3(c2);
        C4 c4(c3);
        C5 c5(c4);

        StopWatch sw("single arg");
        for(counter_t i=0; i<nCalls; ++i) {
            c.f1(i);
        }
       sw.Start("c.f1(i)");

        for(counter_t i=0; i<nCalls; ++i) {
            c1.f1(i);
        }
        sw.Start("c1.f1(i)");

        for(counter_t i=0; i<nCalls; ++i) {
            c2.f1(i);
        }

        sw.Start("c2.f1(i)");

        for(counter_t i=0; i<nCalls; ++i) {
            c3.f1(i);
        }
        sw.Start("c3.f1(i)");

        for(counter_t i=0; i<nCalls; ++i) {
            c4.f1(i);
        }
        sw.Start("c4.f1(i)");

        for(counter_t i=0; i<nCalls; ++i) {
            c5.f1(i);
        }
        sw.Stop("c5.f1(i)");
    }
        break;

    case 5: {
         C c;
        c.x_ = 0;
        C1 c1(c);
        C2 c2(c1);
        C3 c3(c2);
        C4 c4(c3);
        C5 c5(c4);

        StopWatch sw("single arg with return value");
        for(counter_t i=0; i<nCalls; ++i) {
            retval = c.f1(0);
        }
       sw.Start("c.f1(0)");

        for(counter_t i=0; i<nCalls; ++i) {
            retval = c1.f1(1);
        }
        sw.Start("c1.f1(1)");

        for(counter_t i=0; i<nCalls; ++i) {
            retval = c2.f1(2);
        }

        sw.Start("c2.f1(2)");

        for(counter_t i=0; i<nCalls; ++i) {
            retval = c3.f1(3);
        }
        sw.Start("c3.f1(3)");

        for(counter_t i=0; i<nCalls; ++i) {
            retval = c4.f1(4);
        }
        sw.Start("c4.f1(4)");

        for(counter_t i=0; i<nCalls; ++i) {
            retval = c5.f1(5);
        }

        rc &= (c.x_ == 5);
        sw.Stop("c5.f1(5)");
    }
        break;
    } 

    return rc? 1: 0;
}

// 调用栈越深，时间越长
// 带不带返回值，效果差不多
int main(int argc, char* argv[]) {
    test_driver(test_calling, argc, argv);
    return EXIT_SUCCESS;
}