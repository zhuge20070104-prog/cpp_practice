#ifndef _FREDRIC_ASYNC_OUT_HPP_
#define _FREDRIC_ASYNC_OUT_HPP_

#include <sstream>
#include <mutex>
#include <iostream>

struct AsyncOut: public std::stringstream {
    static inline std::mutex cout_mutex;

    ~AsyncOut() {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << rdbuf();
        std::cout.flush();
    }
};

#define aout AsyncOut{}

#endif