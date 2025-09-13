#ifndef _FREDRIC_FUNCTION_DECORATOR_HPP_
#define _FREDRIC_FUNCTION_DECORATOR_HPP_

#include "log.h"
#include <memory>
#include <string>
#include <array>
#include <numeric>
#include <iostream>
#include <sstream>
#include <memory>
#include <functional>

template <typename> 
struct Logger;

template <typename R, typename ... Args>
struct Logger<R(Args...)> {
    std::function<R(Args...)> func;
    std::string name;

    Logger(std::function<R(Args...)> const& func_, std::string const& name_): func(func_), name(name_) {}

    R operator()(Args ... args) {
        B_LOG(info) << "Entering [" << name << "]\n";
        R result = func(args...);
        B_LOG(info) << "Exiting [" << name << "]\n";
        return result;
    }
};

template <typename R, typename ... Args>
Logger<R(Args...)> make_logger(R(*func)(Args...), std::string const& name) {
    return Logger<R(Args...)>(std::function<R(Args...)>(func), name);
}

#endif