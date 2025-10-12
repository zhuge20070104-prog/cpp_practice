#ifndef _FREDRIC_EXCEPTIONS_H
#define _FREDRIC_EXCEPTIONS_H

#include <iostream>
#include <string>
#include <string_view>

class SomethingWrong {
public:
    SomethingWrong() = default;
    SomethingWrong(std::string_view message): m_message{message} {}
    virtual ~SomethingWrong() = default;
    SomethingWrong(const SomethingWrong& src):
        m_message{src.m_message} {
        std::cout << "SomethingWrong copy constructor called\n";     
    }

    virtual std::string what() const {
        return m_message;
    }
protected:
    std::string m_message{};
};

class Warning: public SomethingWrong {
public:
    Warning(std::string_view message): SomethingWrong(message) {}
    virtual std::string what() const override {
        return m_message + ": YELLOW (warning)";
    }
};


class SmallError: public Warning {
public:
    SmallError(std::string_view message): Warning(message) {}
    virtual std::string what() const override {
        return m_message + ": ORANGE (small error)";
    }
};


class CriticalError: public SmallError {
public:
    CriticalError(std::string_view message): SmallError(message) {}
    virtual std::string what() const override {
        return m_message + ": RED (critical error)";
    }
};

#endif