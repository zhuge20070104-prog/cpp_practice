#include <iostream>
#include <string>
#include <sstream>
#include "log.h"
#include <utility>
#include <variant>
#include <vector>
#include <iterator>
#include "variant_std_visit.hpp"


#define BOOST_TEST_MODULE  VariantAndStdVisit
#include "test.hpp"


BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(VariantAndStdVisitTest) {
     std::variant<std::string, int> house;
     house = 221;
     AddressPrinter ap;
     std::visit(ap, house);

     // 2. create a std::visit in-place

     std::visit([](auto& arg) {
          using T = std::decay_t<decltype(arg)>;
          if constexpr (std::is_same_v<T, std::string>) {
               std::cout << "A house called " << arg << "\n";
          } else {
               std::cout << "House number: " << arg << "\n";
          }
     }, house);
}

BOOST_AUTO_TEST_SUITE_END()
