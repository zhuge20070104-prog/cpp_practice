#include <iostream>
#include <string>
#include <sstream>
#include "log.hpp"
#include "shape.hpp"
#include <utility>

#define BOOST_TEST_MODULE VirtualObject
#include "test.hpp"

BOOST_AUTO_TEST_SUITE(Suite01, *fixture<SuiteSetUp>())


BOOST_AUTO_TEST_CASE(TestVirtualObject) {
    PolyGroup poly_g1 {
        std::make_shared<ParkingLot>(1, 1, true),
        std::make_shared<ParkingLot>(1, 2, true)
    };

    PolyGroup poly_g2 {
        std::make_shared<ParkingLot>(1, 1, true),
        std::make_shared<ParkingLot>(1, 3, true)
    };

    for(auto const& poly: poly_g1) {
        std::cout << poly->print() << std::endl;
    }

    for(auto const& poly: poly_g1) {
        for(auto const& poly1: poly_g2) {
            if(poly->equal(poly1)) {
                std::cout << "Equals poly: " << std::endl;
                std::cout << poly->print() << std::endl;
            }
        }
    }
}

BOOST_AUTO_TEST_SUITE_END()
