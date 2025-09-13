#ifndef _FREDRIC_VIRTUAL_PROXY_HPP_
#define _FREDRIC_VIRTUAL_PROXY_HPP_
#include <string>
#include <iostream>
#include <memory>
#include <functional>

#include "log.h"

struct Image {
    virtual void draw() = 0;
};

struct Bitmap: Image {
    Bitmap(std::string const& file_name_): file_name(file_name_) {
        std::cout << "Loading bitmap from " << file_name << std::endl;
    }

    void draw() override {
        std::cout << "Drawing Bitmap\n";
    }
    std::string file_name;
};

struct LazyBitmap: Image{
    LazyBitmap(std::string const& file_name_): file_name(file_name_) {}

    void draw() override {
        if(!bmp) {
            bmp = std::make_unique<Bitmap>(file_name);
        }
        bmp->draw();
    }

private:
    std::string file_name;
    std::unique_ptr<Image> bmp{nullptr};
};
#endif