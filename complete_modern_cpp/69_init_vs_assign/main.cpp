#include "integer.h"
#include <iostream>

void test_assign_operator() {
    Integer a;
    a = 6;
}

void test_initialization() {
    Integer a(6);
}

class ProductWithAssignment {
public:
    ProductWithAssignment(Integer const& id) {
        std::cout << "ProductWithAssignment(Integer const& id)\n";
        m_id = id;
    }

    ~ProductWithAssignment() {
        std::cout << "~ProductWithAssignment()\n";
    }
private:
    Integer m_id;
};

class ProductWithInit {
public:
    ProductWithInit(Integer const& id): m_id(id) {
        std::cout << " ProductWithInit(Integer const& id)\n";
    }

    ~ProductWithInit() {
        std::cout << "~ProductWithInit()\n";
    }
private:
    Integer m_id;
};


int main(int argc, char* argv[]) {

    std::cout << "Test assign operator\n";
    test_assign_operator();
    std::cout << "==============================\n";
    
    // Prefer intialization to assign operator
    std::cout << "Test initialization\n";
    test_initialization();
    std::cout << "==============================\n";
    
    std::cout << "Product with Assignment\n";
    {
        ProductWithAssignment pAssign(5);
    }
    std::cout << "==============================\n";

    // Prefer initialization to assign operator
    std::cout << "Product with Initialization list\n";
    {
        ProductWithInit pInit(5);
    }
    std::cout << "==============================\n";

    return EXIT_SUCCESS;
}