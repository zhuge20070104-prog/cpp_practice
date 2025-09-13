#ifndef _FREDRIC_DRINK_HPP_
#define _FREDRIC_DRINK_HPP_

#include <iostream>
#include <memory>
#include <map>
#include <functional>

enum class DrinkType {
    Tea, 
    Coffe
};

struct HotDrink {
    virtual ~HotDrink() = default;
    virtual void prepare(int volume) = 0;
};

struct Tea: HotDrink {
    void prepare(int volume) override {
        std::cout << "Take tea bag, boil water, pour " << volume << "ml, add some lemon\n";
    }
};

struct Coffee: HotDrink {
    void prepare(int volume) override {
        std::cout << "Grind some beans, boil water, pour " << volume << "ml, add cream, enjoy!\n";
    }
};

class DrinkFactory {
    std::map<DrinkType, std::function<std::unique_ptr<HotDrink>()>> factories;
public:
    DrinkFactory() {
        factories[DrinkType::Tea] = [] {
            auto tea = std::make_unique<Tea>();
            tea->prepare(200);
            return tea;
        };

        factories[DrinkType::Coffe] = [] {
            auto coffee = std::make_unique<Coffee>();
            coffee->prepare(300);
            return coffee;
        };
    }


    std::unique_ptr<HotDrink> make_drink(DrinkType d_type) {
        return factories[d_type]();
    }
};
#endif