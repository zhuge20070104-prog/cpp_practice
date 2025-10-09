#ifndef _FREDRIC_SHAPE_H
#define _FREDRIC_SHAPE_H

#include <iostream>

class Shape {
public:
    Shape():
        m_description("No Description") {}
    
    Shape(std::string_view description);

    virtual ~Shape() {
        --m_count;
    }

    void draw() const {
        std::cout << "Shape::draw() called: " << m_description << "\n";
    }

    virtual int get_count() const {
        return m_count;
    }

    inline static int m_count {0};
protected:
    std::string m_description;
};

#endif