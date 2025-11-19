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

void broadcast_data() {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    if(rank == 0) {
        printf("Broadcast data from rank 0 to all ranks\n");
        fflush(stdout);
    }
    MPI_Barrier(MPI_COMM_WORLD);

    int value = 42;
    MPI_Bcast(&value, 1, MPI_INT, 0, MPI_COMM_WORLD);   
    printf("Rank %d received from 0 the value %d\n", rank, value);
    fflush(stdout);
    MPI_Barrier(MPI_COMM_WORLD);
    printf("Rank %d is done working\n", rank);
    fflush(stdout);
    MPI_Barrier(MPI_COMM_WORLD);
}

void reduce_data() {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0) {
        printf("Reduce data from all ranks to rank 0\n");
        fflush(stdout);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    const int itemsPerProcess = 10;
    const int count = size * itemsPerProcess;
    int* data = new int[count];

    if(rank == 0) {
        for(std::size_t i=0; i<count; ++i) {
            data[i] = rand() % 10;
        }
    }

    int* localData = new int[itemsPerProcess];
    MPI_Scatter(data, itemsPerProcess, MPI_INT, localData, itemsPerProcess, MPI_INT, 0, MPI_COMM_WORLD);

    int localSum = 0;
    for(std::size_t i=0; i<itemsPerProcess; ++i) {
        localSum += localData[i];
    }
 
    delete[] localData;
    int globalSum;
    MPI_Reduce(&localSum, &globalSum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if(rank == 0) {
        printf("Global sum: %d\n", globalSum);
        delete[] data;
    }
}

int main(int argc, char* argv[]) {
    // ⭐ MPI_Init 只能调用一次，在程序开始时
    MPI_Init(&argc, &argv);
    
    // 🔥 关闭标准输出缓冲，强制立即输出
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    
    broadcast_data();
    reduce_data();
    
    // ⭐ MPI_Finalize 只能调用一次，在程序结束前
    MPI_Finalize();
    return EXIT_SUCCESS;
}



