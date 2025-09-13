#ifndef _FREDRIC_FACADE_HPP_
#define _FREDRIC_FACADE_HPP_

#include "window.hpp"
#include <memory>

class Console {
public:
    static Console& instance() {
        static Console console;
        return console;
    }

    std::unique_ptr<Window> single_buffer() {
        std::unique_ptr<Window> w {new Window};
        w->add_buffer(TextBuffer{});
        return w;
    }

    std::unique_ptr<Window> multi_buffers(int buffer_count) {
        std::unique_ptr<Window> w {new Window};
        for(int i=0; i<buffer_count; ++i) {
            w->add_buffer(TextBuffer{});
        }
        return w;
    }
};

#endif