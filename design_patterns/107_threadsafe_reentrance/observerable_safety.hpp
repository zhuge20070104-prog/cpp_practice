#ifndef _FREDRIC_OBSERVERABLE_SAFETY_HPP_
#define _FREDRIC_OBSERVERABLE_SAFETY_HPP_
#include <vector>
#include <string>
#include <mutex>
#include <algorithm>

template <typename T>
struct Observer;

template <typename T>
struct Observerable {
    std::vector<Observer<T>*> observers;

    std::mutex mtx;

    void notify(T& source, std::string const& field_name) {
        std::lock_guard<std::mutex> lock{mtx};
        for(auto&& observer: observers) {
            // 指针要注意判空
            if(observer) {
                observer->field_change(source, field_name);
            }
        }
    }

    void subscribe(Observer<T>& observer) {
        std::lock_guard<std::mutex> lock{mtx};
        observers.push_back(&observer);
    }

    void unsubscribe(Observer<T>& observer) {
        // 有可能unsubscribe是在notify中调用的
        // 这个时候如果这里加锁会产生死锁，同时对一个互斥元加锁两次
        auto it = std::find(observers.begin(), observers.end(), &observer);
        if(it != observers.end()) {
            *it = nullptr;
        }
    }
};
#endif 