#include "boost/hana.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <functional>

namespace hana = boost::hana;
using namespace hana::literals;

struct Truck {
    std::string name;
    double bed_length;
};

struct Car {
    std::string name;
};

struct MotorCycle {
    std::string name;
};

int main(int argc, char* argv[]) {
    auto vehicles = hana::make_tuple(
        Truck{"F-150", 8.5},
        Car{"Volt"},
        MotorCycle{"Ninja"});
    
    auto has_bed_length = hana::is_valid(
        [](auto&& x) -> decltype((void)x.bed_length) {}
    );

    auto trucks = hana::filter(vehicles, has_bed_length);
    auto nontrucks = hana::filter(vehicles, hana::compose(hana::not_, has_bed_length));

    hana::for_each(trucks, [](auto& vehicle) {
        std::cout << "Truck = " << vehicle.name << " bed length = " << vehicle.bed_length << std::endl;
    });

    hana::for_each(nontrucks, [](auto& vehicle) {
        std::cout << "Vehicle = " << vehicle.name << std::endl;
    });
    return EXIT_SUCCESS;
}
