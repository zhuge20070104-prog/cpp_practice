#ifndef _FREDRIC_VARIANT_STD_VISIT_HPP_
#define _FREDRIC_VARIANT_STD_VISIT_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <variant>

struct AddressPrinter {
    void operator()(std::string const& house_name) const {
        std::cout << "A house called: " << house_name << "\n";
    }

    void operator()(int const house_number) const {
        std::cout << "House number: " << house_number << "\n";
    }
};
#endif