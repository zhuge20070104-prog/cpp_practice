#include <iostream>
#include <string>
#include <typeinfo>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <vector>
#include <memory>
#include "boost/filesystem.hpp"
#include "gtest/gtest.h"
#include "log.hpp"
#include "assert_eq.h"

class Integer {
	int* m_pint;
public:
	Integer() {
		std::cout << "Integer::Integer()" << std::endl;
		m_pint = new int(0);
	}
		
	Integer(int value) {
		std::cout << "Integer::Integer(int value)" << std::endl;
		m_pint = new int(value);
	}
		
	Integer(Integer const& obj) {
		std::cout << "Integer::Integer(Integer const& obj)" << std::endl;
		if(this == &obj) {
			return;
		}
		
		m_pint = new int(obj.get_value());
	}
		
	Integer(Integer&& obj) {
		std::cout << "Integer::Integer(Integer&& obj)" << std::endl;
		if(this == &obj) {
			return;
		}
		
		m_pint = obj.m_pint;
		obj.m_pint = nullptr;
	}
	
	int get_value() const {
		if(m_pint) {
			return *m_pint;
		}
		return 0;
	}
	void set_value(int value) {
		if(!m_pint) {
			m_pint = new int();
		}
		*m_pint = value;
	}
	~Integer() {
		std::cout << "Integer::~Integer()" << std::endl;
		if(m_pint) {
			delete m_pint;
			m_pint = nullptr;
		}
	}
};

template <typename NameT, typename IDT>
class Employee {
    NameT m_name;
    IDT m_id;

public:
    Employee(NameT && name, IDT&& id_): m_name(std::forward<NameT>(name)), m_id(std::forward<IDT>(id_)){
        std::cout << "Employee::Employee(NameT && name, IDT&& id)" << std::endl;
    }
    
    IDT& get_id() {
        return m_id;
    }
    
    NameT& get_name() {
        return m_name;
    }
};

template <typename NameT, typename IDT>
std::shared_ptr<Employee<NameT, IDT>> make_employee(NameT&& name, IDT&& id_) {
    // name和id都要当做右值引用，而不是左值传递过去
    // 这个时候就需要用到完美转发，不改变当前对象的左右值属性
    return std::shared_ptr<Employee<NameT, IDT>>(new Employee<NameT, IDT>(std::forward<NameT>(name), std::forward<IDT>(id_)));
}

GTEST_TEST(TplTests, TestPassRVal) {
    auto emp = make_employee(std::string("Umar"), Integer(100));
    std::cout << emp->get_id().get_value() << std::endl;
    ASSERT_EQ(emp->get_id().get_value(), 100);
}

