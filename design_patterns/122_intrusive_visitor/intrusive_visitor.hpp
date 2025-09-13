#ifndef _FREDRIC_INTRUSIVE_VISITOR_HPP_
#define _FREDRIC_INTRUSIVE_VISITOR_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <memory>


struct Expression {
    virtual ~Expression() = default;
    virtual void print(std::stringstream& oss) = 0;
};

struct DoubleExpression: Expression {
    double value;
    explicit DoubleExpression(double value_): value (value_) {}

    void print(std::stringstream& oss) override {
        oss << value;
    }
};

struct AdditionExpression: Expression {
    std::unique_ptr<Expression> left, right;

    AdditionExpression(std::unique_ptr<Expression> left_, std::unique_ptr<Expression> right_)
        : left(std::move(left_)), right(std::move(right_)) {}

    void print(std::stringstream& oss) override {
        oss << "(";
        left->print(oss);
        oss << "+";
        right->print(oss);
        oss << ")";
    }
};


#endif