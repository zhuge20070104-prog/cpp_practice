#include <iostream>

enum auto_deduct_type_t {
    deduct_with_copy,
    deduct_ref_variable_with_copy,
    true_ref_deduct,
    ref_preserve_constness,
    constness_dosent_matter_with_copy
};

struct auto_deduct_t {
    void deduct_with_copy() {
        //Type deduction with auto : Just a copy
        double some_var {55.5};
        auto x = some_var; 

        std::cout << "sizeof(some_var): " << sizeof(some_var) << std::endl;
        std::cout << "sizeof(x): " << sizeof(x) << std::endl;
        std::cout << "&some_var: " << &some_var << std::endl;
        std::cout << "&x: " << &x << std::endl;
        std::cout << "some_var: " << some_var << std::endl;
        std::cout << "x: " << x << std::endl;
    }

    void deduct_ref_variable_with_copy() {
        double some_var = 55.5;
        double& some_var_ref {some_var};
        // y is not deduced as a reference to double
        // it's just a double that contains the value 
        // in some_var_ref
        auto y = some_var_ref;

        ++y;

        std::cout << "sizeof(some_var): " << sizeof(some_var) << std::endl;
        std::cout << "sizeof(some_var_ref): " << sizeof(some_var_ref) << std::endl;
        std::cout << "sizeof(y): " << sizeof(y) << std::endl;
        std::cout << "&some_var : " << &some_var << std::endl; // 0xabc123
        std::cout << "&some_var_ref : " << &some_var_ref << std::endl ;// 0xabc123
        std::cout << "&y : " << &y << std::endl;  // 0xaab543
        std::cout << "some_var : " << some_var << std::endl; //55.5
        std::cout << "some_var_ref : " << some_var_ref << std::endl; // 55.5
        std::cout << "y : " << y << std::endl; // 56.5 
    }

    void true_ref_deduct() {
        double some_var = 55.5;
        double& some_var_ref {some_var};
        // z is deduced as a double reference
        auto& z = some_var_ref;

        ++z;

        std::cout << "sizeof(some_var) : " << sizeof(some_var) << std::endl; // 8
        std::cout << "sizeof(some_var_ref) : " << sizeof(some_var_ref) << std::endl; // 8
        std::cout << "sizeof(z) : " << sizeof(z) << std::endl; // 8
        std::cout << "&some_var : " << &some_var << std::endl;// 0xabc123
        std::cout << "&some_var_ref : " << &some_var_ref << std::endl;// 0xabc123
        std::cout << "&z : " << &z << std::endl;// 0xabc123
        std::cout << "some_var : " << some_var << std::endl; // 56.5
        std::cout << "some_var_ref : " << some_var_ref << std::endl; //56.5
        std::cout << "z : " << z << std::endl; // 56.5
    }

    void ref_preserve_constness() {
        //Constness is preserved with properly deduced references.
        double const some_other_var {44.3};
        double const& const_ref {some_other_var};
        auto& p = const_ref; 

        std::cout << "some_other_var : " << some_other_var << std::endl;
        std::cout << "const_ref : " << const_ref << std::endl;
        std::cout <<  "p : " << p << std::endl;
        // ++p; // Complier error
    }

    void constness_dosent_matter_with_copy() {
        //Constness doesn't matter with non reference deduction
        double const i_am_const {71.2};
        double const& my_ref {i_am_const};
        // q is a separate variable, initialized with the
        // value in i_am_const.
        auto q = my_ref; 
        // Can modify q without a problem. It's a copy.
        ++q;
    }
    
    void operator()(auto_deduct_type_t deduct_type) {
        switch (deduct_type) {
        case auto_deduct_type_t::deduct_with_copy:
            deduct_with_copy();
            break;
        case auto_deduct_type_t::deduct_ref_variable_with_copy:
            deduct_ref_variable_with_copy();
            break;
        case auto_deduct_type_t::true_ref_deduct:
            true_ref_deduct();
            break;
        case auto_deduct_type_t::ref_preserve_constness:
            ref_preserve_constness();
            break;
        case auto_deduct_type_t::constness_dosent_matter_with_copy:
            constness_dosent_matter_with_copy();
            break;
        default:
            break;
        }
    }
};

int main(int argc, char* argv[]) {
    auto_deduct_t deduce;
    deduce(auto_deduct_type_t::deduct_with_copy);
    deduce(auto_deduct_type_t::deduct_ref_variable_with_copy);
    deduce(auto_deduct_type_t::true_ref_deduct);
    deduce(auto_deduct_type_t::ref_preserve_constness);
    deduce(auto_deduct_type_t::constness_dosent_matter_with_copy);
    return EXIT_SUCCESS;
}