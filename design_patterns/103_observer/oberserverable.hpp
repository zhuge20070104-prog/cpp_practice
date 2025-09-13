#ifndef _FREDRIC_OBSERVERABLE_HPP_
#define _FREDRIC_OBSERVERABLE_HPP_
#include <vector>
#include <string>
#include <algorithm>


template <typename T>
struct Observer;

template <typename T>
struct Observerable {
    std::vector<Observer<T>*> observers;

public:
    void notify(T& source, std::string const& field_name) {
        for(auto&& observer: observers) {
            observer->field_change(source, field_name);
        }
    }

    void subscribe(Observer<T>& observer) {
        observers.push_back(&observer);
    }

    void unsubscribe(Observer<T>& observer) {
        // std::remove 返回的是第一个没有用的元素，把后面的都删除掉
        observers.erase(std::remove(observers.begin(), observers.end(), &observer),
        observers.end());
    }
};
#endif