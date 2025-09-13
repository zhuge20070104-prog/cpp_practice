#ifndef _FREDRIC_PRODUCTS_HPP_
#define _FREDRIC_PRODUCTS_HPP_
#include <vector>
#include <string>

enum class Color {
    red, green, blue
};

enum class Size {
    small, medium, large
};

struct Product {
    std::string name;
    Color color;
    Size size;
};

struct Specification {
    virtual bool is_satisfied(Product* p) const = 0;
};

struct BetterFilter {
    std::vector<Product*> filter(std::vector<Product*> const& items, Specification& spec) {
        std::vector<Product*> result;
        for(auto& item: items) {
            if(spec.is_satisfied(item)) {
                result.push_back(item);
            }
        }
        return result;
    }
};

struct ColorSpec: public Specification {
    Color color;
    ColorSpec(Color color_): color(color_) {}

    bool is_satisfied(Product* item) const override {
        return item->color == color;
    }
};

struct SizeSpec: public Specification {
    Size size;
    SizeSpec(Size size_): size(size_) {}
    
    bool is_satisfied(Product* item) const override {
        return item->size == size;
    }
};

struct AndSpec: public Specification {
    Specification const& first;
    Specification const& second;

    AndSpec(Specification const& first_, Specification const& second_):
        first(first_), second(second_) {
    }

    bool is_satisfied(Product* item) const override {
        return first.is_satisfied(item) && second.is_satisfied(item);
    }
};

AndSpec operator&&(Specification const& first, Specification const& second) {
    return AndSpec(first, second);
}

#endif