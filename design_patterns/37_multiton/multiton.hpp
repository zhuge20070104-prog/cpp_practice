#ifndef _FREDRIC_MULTITON_HPP_
#define _FREDRIC_MULTITON_HPP_

#include <iostream>
#include <memory>
#include <map>
#include <string>

enum class Importance {
    Primary,
    Secondary,
    Tertiary
}; 

enum class Size {
    Large,
    Medium,
    Small
};


template <typename T, typename Key = std::string>
class Multiton {

public:
    template <typename ... Args> 
    static std::shared_ptr<T> get(Key const& key, Args&& ... args) {
        auto it  = instances.find(key);
        if(it != instances.end()) {
            return it->second;
        }

        auto instance = std::make_shared<T>(std::forward<Args>(args)...);
        instances[key] = instance;
        return instance;
    }

private:
    static std::map<Key, std::shared_ptr<T>> instances;

protected:
    Multiton() = default;
    virtual ~Multiton() = default;
};

template <typename T, typename Key>
std::map<Key, std::shared_ptr<T>> Multiton<T, Key>::instances {};


class Printer {
    static int printer_count;
public:
    Printer() {
        ++ Printer::printer_count;
        std::cout << "A total of " <<
            Printer::printer_count 
            << " instances created so far\n";
    }
};

int Printer::printer_count = 0;


class Circle {
    static int circle_count;
    float radius {1.0f};

public:
    Circle() {
        ++ Circle::circle_count;
        std::cout << "A total of " <<
            Circle::circle_count <<
            "   circles created so far\n";
    }

    Circle(float radius_): radius{radius_} {
        ++ Circle::circle_count;
        std::cout << "A total of " <<
            Circle::circle_count <<
            "    circles created so far\n";
    }
};

int Circle::circle_count = 0;

using MultitonPrinter = Multiton<Printer, Importance>;
using MultitonCircle = Multiton<Circle, Size>;

#endif