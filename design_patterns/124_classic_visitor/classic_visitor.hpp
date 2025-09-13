#ifndef _FREDRIC_CLASSIC_VISITOR_HPP_
#define _FREDRIC_CLASSIC_VISITOR_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <typeinfo>
#include <sstream>

struct DoubleExpression;
struct AdditionExpression;
struct SubstractionExpression; 

struct ExpressionVisitor {
    virtual void visit(DoubleExpression* de) = 0;
    virtual void visit(AdditionExpression* ae) = 0;
    virtual void visit(SubstractionExpression* se) = 0;
};

// 打印表达式内容的visitor
struct ExpressionPrinter: public ExpressionVisitor {
    std::stringstream ss;
    std::string str() const {
        return ss.str();
    }

    void visit(DoubleExpression* de) override;
    void visit(AdditionExpression* ae) override;
    void visit(SubstractionExpression* se) override;
};

// 计算表达式值的visitor
struct ExpressionEvaluator: public ExpressionVisitor {
    double result;
    void visit(DoubleExpression* de) override;
    void visit(AdditionExpression* ae) override;
    void visit(SubstractionExpression* se) override;
};


struct Expression {
    virtual ~Expression() = default;
    virtual void accept(ExpressionVisitor* visitor) = 0;
};

struct DoubleExpression: public Expression {
    double value;

    explicit DoubleExpression(double value_): value(value_) {}

    void accept(ExpressionVisitor* visitor) override {
        visitor->visit(this);
    }
};

struct AdditionExpression: public Expression {
    std::unique_ptr<Expression> left, right;

    AdditionExpression(std::unique_ptr<Expression> left_, std::unique_ptr<Expression> right_):
        left(std::move(left_)), right(std::move(right_)) {}

    void accept(ExpressionVisitor* visitor) override {
        visitor->visit(this);
    }
};

struct SubstractionExpression: public Expression {
    std::unique_ptr<Expression> left, right;
    SubstractionExpression(std::unique_ptr<Expression> left_, std::unique_ptr<Expression> right_):
        left(std::move(left_)), right(std::move(right_)) {}
    
    void accept(ExpressionVisitor* visitor) override {
        visitor->visit(this);
    }  
};

// # region Expression printer
void ExpressionPrinter::visit(DoubleExpression* de) {
    ss << de->value;
}

void ExpressionPrinter::visit(AdditionExpression* ae) {
    bool need_braces = dynamic_cast<SubstractionExpression*>(ae->right.get());
    ae->left->accept(this);
    ss << "+";
    if(need_braces) ss << "(";
    ae->right->accept(this);
    if(need_braces) ss << ")";
}

void ExpressionPrinter::visit(SubstractionExpression* se) {
    bool need_braces = dynamic_cast<SubstractionExpression*>(se->right.get());
    se->left->accept(this);
    ss << "-";
    if(need_braces) ss << "(";
    se->right->accept(this);
    if(need_braces) ss << ")";
}
// # end region 


// # region Expression Evaluator
void ExpressionEvaluator::visit(DoubleExpression* de) {
    result = de->value;
}

void ExpressionEvaluator::visit(AdditionExpression* ae) {
    ae->left->accept(this);
    auto temp = result;
    ae->right->accept(this);
    result += temp;
}

void ExpressionEvaluator::visit(SubstractionExpression* se) {
    se->left->accept(this);
    auto temp = result;
    se->right->accept(this);
    result = temp - result;
}
// # end region
#endif