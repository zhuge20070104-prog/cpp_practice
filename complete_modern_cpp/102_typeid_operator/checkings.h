#ifndef _FREDRIC_CHECKINGS_H_
#define _FREDRIC_CHECKINGS_H_
#include "account.h"

// C++ 有三大类函数不能从父类继承，
// 构造函数
// 析构函数
// 赋值操作符
class Checkings: public Account {
    float m_min_balance{50};
public:
    // C++ 11继承父类的构造函数，不建议使用
    using Account::Account;

    Checkings(std::string const& name, float balance, float min_balance);
    ~Checkings();
    void withdraw(float amount);
    float get_min_balance() const;
};

#endif