#include <string>
#include <iostream>
#include <cstdint>
#include <iomanip>
#include <bitset>
#include <cpuid.h>
#include <cstring>
#include <chrono>
#include <random>
#include <thread>  // for std::this_thread::sleep_for


#include <mpi.h>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/mpi.hpp>
#include <sstream>


struct Person {
    std::string name;
    int age;
    friend class boost::serialization::access;

    template <typename Ar>
    void serialize(Ar& ar, const unsigned int version) {
        ar & name;
        ar & age;
    }
};


int main(int argc, char** argv) {
    namespace mpi = boost::mpi;
    mpi::environment env;
    mpi::communicator world;

    if(world.rank() == 0) {
        Person p;
        p.name = "Fredric";
        p.age = 19;
        for(std::size_t i=1; i<world.size(); ++i) {
            world.send(i, 0, p);
        }
    } else {
        Person p;
        world.recv(0, 0, p);
        std::cout << "Hello, " << p.name << ", You are " << p.age 
            << " years old!" << std::endl;
    }

    return EXIT_SUCCESS;
}


