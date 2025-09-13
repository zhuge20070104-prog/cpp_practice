#ifndef _FREDRIC_SHAPE_HPP_
#define _FREDRIC_SHAPE_HPP_

#include "log.h"
#include <memory>

struct IRender {
    virtual void render_circle(float x, float y, float radius) = 0;
};

struct VectorRender: IRender {
    void render_circle(float x, float y, float radius) override {
        B_LOG(info) << "Drawing a vector circle of radius: " << radius << "\n";
    }
};

struct RasterRender: IRender {
    void render_circle(float x, float y, float radius) override {
        B_LOG(info) << "Rastering a circle of radius: " << radius << "\n";
    }
};

struct Circle {
    std::unique_ptr<IRender> render;
    Circle(std::unique_ptr<IRender> render_, float x_, float y_, float radius_): render(std::move(render_)), x(x_), y(y_), radius(radius_) {}

    void draw() {
        render->render_circle(x, y, radius);
    }

    void resize(float factor) {
        radius *= factor;
    }
private:
    float x, y, radius;
};


#endif