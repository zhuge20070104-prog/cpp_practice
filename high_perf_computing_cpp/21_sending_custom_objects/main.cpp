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
    MPI_Init(&argc, &argv);

    int size, rank;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0) {
        Person p;
        p.name = "Fredric";
        p.age = 19;
        std::ostringstream oss;
        boost::archive::text_oarchive oa(oss);
        oa << p;
        auto s = oss.str();
        int len = s.length() + 1;
        for(std::size_t i=1; i<size; ++i) {
            MPI_Send(s.c_str(), len, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    } else {
        MPI_Status status;
        MPI_Probe(0, 0, MPI_COMM_WORLD, &status);
        int count;
        MPI_Get_count(&status, MPI_CHAR, &count);

        char* buffer = new char[count];
        MPI_Recv(buffer, count, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);
        std::istringstream iss(buffer);
        boost::archive::text_iarchive ia(iss);
        Person p;
        ia >> p;

        std::cout << "Hello, " << p.name << ", You are " << p.age 
            << " year old!" << std::endl;
        delete [] buffer;

    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}


