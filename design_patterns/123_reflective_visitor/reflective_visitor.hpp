#ifndef _FREDRIC_REFLECTIVE_VISITOR_HPP_
#define _FREDRIC_REFLECTIVE_VISITOR_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <typeinfo>
#include <sstream>

struct Expression {
    virtual ~Expression() = default;
};

struct DoubleExpression: public Expression {
    double value;

    explicit DoubleExpression(double value_): value(value_) {}
};

struct AdditionExpression: public Expression {
    std::unique_ptr<Expression> left, right;

    AdditionExpression(std::unique_ptr<Expression> left_, std::unique_ptr<Expression> right_):
        left(std::move(left_)), right(std::move(right_)) {}
};

struct ExpressionPrinter {
    std::stringstream ss;

    void print(Expression* e) {
        // 这种做法不好，if-else 太多，而且有性能损失dynamic_cast
        // 如果忘记某个条件，还会丢失数据
        if(typeid(*e) == typeid(DoubleExpression)) {
            auto de = dynamic_cast<DoubleExpression*>(e);
            ss << de->value;
        } else if(typeid(*e) == typeid(AdditionExpression)) {
            auto ae = dynamic_cast<AdditionExpression*>(e);
            ss << "(";
            print(ae->left.get());
            ss << "+";
            print(ae->right.get());
            ss << ")";
        }
    }
    std::string str() const {
        return ss.str();
    }
};
#endif