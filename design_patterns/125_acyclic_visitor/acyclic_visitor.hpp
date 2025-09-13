#ifndef _FREDRIC_ACYCLIC_VISITOR_HPP_
#define _FREDRIC_ACYCLIC_VISITOR_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <typeinfo>
#include <sstream>

template <typename Visitable>
struct Visitor {
    virtual void visit(Visitable& obj) = 0;
};

// 标记接口
struct VisitorBase {
    virtual ~VisitorBase() = default;
};

struct Expression {
    virtual ~Expression() = default;
    virtual void accept(VisitorBase& vistor) {
        using EV = Visitor<Expression>;
        if(auto ev = dynamic_cast<EV*>(&vistor)) {
            ev->visit(*this);
        }
    }
}; 

struct DoubleExpression: public Expression {
    double value;
    explicit DoubleExpression(double value_): value(value_) {}

    void accept(VisitorBase& visitor) override {
        using DEV = Visitor<DoubleExpression>;
        if(auto dev = dynamic_cast<DEV*>(&visitor)) {
            dev->visit(*this);
        }
    }
};

struct AdditionExpression: public Expression {
    std::unique_ptr<Expression> left, right;
    AdditionExpression(std::unique_ptr<Expression> left_, std::unique_ptr<Expression> right_):
        left(std::move(left_)), right(std::move(right_)) {}
    
    void accept(VisitorBase& visitor) override {
        using AEV = Visitor<AdditionExpression>;
        if(auto aev = dynamic_cast<AEV*>(&visitor)) {
            aev->visit(*this); 
        }
    }
};

struct SubstractionExpression: public Expression {
    std::unique_ptr<Expression> left, right;
    SubstractionExpression(std::unique_ptr<Expression> left_, std::unique_ptr<Expression> right_):
        left(std::move(left_)), right(std::move(right_)) {}
    
    void accept(VisitorBase& visitor) override {
        using SEV = Visitor<SubstractionExpression>;
        if(auto sev = dynamic_cast<SEV*>(&visitor)) {
            sev->visit(*this);
        }
    }
};

struct ExpressionPrinter: public VisitorBase,
                                                    Visitor<Expression>,
                                                    Visitor<DoubleExpression>,
                                                    Visitor<AdditionExpression>,
                                                    Visitor<SubstractionExpression> 
{
    void visit(Expression& obj) override {}

    void visit(DoubleExpression& de) override {
        ss << de.value;
    }

    void visit(AdditionExpression& ae) override {
        bool need_braces = dynamic_cast<SubstractionExpression*>(ae.right.get());
        ae.left->accept(*this);
        ss << "+";
        if(need_braces) ss << "(";
        ae.right->accept(*this);
        if(need_braces) ss << ")";
    }

    void visit(SubstractionExpression& se) override {
        bool need_braces = dynamic_cast<SubstractionExpression*>(se.right.get());
        se.left->accept(*this);
        ss << "-";
        if(need_braces) ss << "(";
        se.right->accept(*this);
        if(need_braces) ss << ")";
    }

    std::string str() const {
        return ss.str();
    }

private:
    std::stringstream ss;
};

struct ExpressionEvaluator: public VisitorBase,
                                                         Visitor<Expression>,
                                                         Visitor<DoubleExpression>,
                                                         Visitor<AdditionExpression>,
                                                         Visitor<SubstractionExpression>
{
    void visit(Expression& e) override {}

    void visit(DoubleExpression& de) override {
        result = de.value;
    }

    void visit(AdditionExpression& ae) override {
        ae.left->accept(*this);
        auto temp = result;
        ae.right->accept(*this);
        result += temp;
    }

    void visit(SubstractionExpression& se) override {
        se.left->accept(*this);
        auto temp = result;
        se.right->accept(*this);
        result = temp - result;
    }

    double result;
};
#endif