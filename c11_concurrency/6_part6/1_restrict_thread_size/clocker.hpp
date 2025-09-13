#ifndef _FREDRIC_CLOCKER_HPP_
#define _FREDRIC_CLOCKER_HPP_
#include <chrono>
#include "asyc_out.hpp"

struct Clocker {
    std::chrono::time_point<std::chrono::high_resolution_clock> start;

    Clocker() {
        start = std::chrono::high_resolution_clock::now();
    }

    ~Clocker() {
        auto end = std::chrono::high_resolution_clock::now();
        auto mill_dur = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
        aout << "Takes " << mill_dur << " milliseconds\n";
    }
};
#endif