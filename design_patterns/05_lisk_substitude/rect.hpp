#ifndef _FREDRIC_PRODUCTS_HPP_
#define _FREDRIC_PRODUCTS_HPP_

#include <iostream>
#include "log.hpp"

struct Rect {
    friend class RectFactory;
protected:
    Rect(int width_, int height_): width(width_), height(height_) {

    }

    int width, height;

public:
    virtual ~Rect() {}
    int get_width() const {
        return width;   
    }

    int get_height() const {
        return height;
    }

    virtual void set_height(int height) {
        this->height = height;
    }

    virtual void set_width(int width) {
        this->width = width;
    }

    int area() const {
        return width * height;
    }
};

struct Square: public Rect {
    friend class RectFactory;
protected:
    Square(int size_): Rect(size_, size_){}
public:    
    void set_height(int height) {
        this->height = this->width = height;
    }

    void set_width(int width) {
        this->width = this->height = width;
    }
};


struct RectFactory {
    static Rect create_rect(int width, int height) {
        return Rect(width, height);
    }

    static Square create_square(int size) {
        return Square(size);
    }
};


int process(Rect* rect) {
    int width = rect->get_width();
    rect->set_height(10);
    LOG(std::cout, "Rect width: ", rect->get_width());
    LOG(std::cout, "Rect height: ", rect->get_height());
    return rect->area();
}
#endif