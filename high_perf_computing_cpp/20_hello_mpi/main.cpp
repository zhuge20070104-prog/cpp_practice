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


int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int size, rank;

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0) {
        std::cout << "Enter a number: ";
        int n;
        std::cin >> n;
        for(std::size_t i=1; i<size; ++i) {
            MPI_Send(&n, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    } else {
        int n;
        MPI_Recv(&n, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << n << "^" << rank << " = " << std::pow(n, rank) << std::endl;
    }

    MPI_Finalize();
    return EXIT_SUCCESS;
}


