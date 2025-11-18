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


void send_data() {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    // 只让 rank 0 打印标题
    if(rank == 0) {
        printf("\n========== send_data (MPI_Send - 非阻塞发送) ==========\n");
        fflush(stdout);
    }
    MPI_Barrier(MPI_COMM_WORLD);  // 等待标题打印完成

    int value;
    
    if(rank == 0) {
        value = 42;
        for(int i=1; i<size; ++i) {
            printf("Ready to send %d--->%d\n", rank, i);
            fflush(stdout);
            MPI_Send(&value, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf("Data sent %d--->%d\n", rank, i);
            fflush(stdout);
        }
    } else {
        // 非 rank 0 进程接收数据
        value = -1;
        MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    
    // ⭐ 关键：等待所有通信完成
    MPI_Barrier(MPI_COMM_WORLD);
    
    // 🎯 统一由 rank 0 收集并输出结果（避免多进程输出混乱）
    if(rank == 0) {
        // rank 0 负责输出所有接收结果
        for(int i = 1; i < size; ++i) {
            int received_value;
            MPI_Recv(&received_value, 1, MPI_INT, i, 99, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Rank %d received from 0 the value %d\n", i, received_value);
            fflush(stdout);
        }
    } else {
        // 其他进程把接收到的值发送给 rank 0
        MPI_Send(&value, 1, MPI_INT, 0, 99, MPI_COMM_WORLD);
    }
    
    // 最后再同步一次
    MPI_Barrier(MPI_COMM_WORLD);
}

void ssend_data() {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    // 只让 rank 0 打印标题
    if(rank == 0) {
        printf("\n========== ssend_data (MPI_Ssend - 同步阻塞发送) ==========\n");
        fflush(stdout);
    }
    MPI_Barrier(MPI_COMM_WORLD);  // 等待标题打印完成

    int value;
    
    if(rank == 0) {
        value = 42;
        for(int i=1; i<size; ++i) {
            printf("Ready to send %d--->%d\n", rank, i);
            fflush(stdout);
            MPI_Ssend(&value, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf("Data sent %d--->%d\n", rank, i);
            fflush(stdout);
        }
    } else {
        // 非 rank 0 进程接收数据
        value = -1;
        MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    
    // ⭐ 关键：等待所有通信完成
    MPI_Barrier(MPI_COMM_WORLD);
    
    // 🎯 统一由 rank 0 收集并输出结果（避免多进程输出混乱）
    if(rank == 0) {
        // rank 0 负责输出所有接收结果
        for(int i = 1; i < size; ++i) {
            int received_value;
            MPI_Recv(&received_value, 1, MPI_INT, i, 99, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Rank %d received from 0 the value %d\n", i, received_value);
            fflush(stdout);
        }
    } else {
        // 其他进程把接收到的值发送给 rank 0
        MPI_Send(&value, 1, MPI_INT, 0, 99, MPI_COMM_WORLD);
    }
    
    // 最后再同步一次
    MPI_Barrier(MPI_COMM_WORLD);
}

void ssend_data_without_recv() {
    int size, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if(rank == 0) {
        printf("\n========== ssend_data_without_recv (MPI_Ssend - 同步阻塞发送，不接收) ==========\n");
        fflush(stdout);
    }
    // 等待标题打印完成
    MPI_Barrier(MPI_COMM_WORLD);

    int value;
    if(rank == 0) {
        value = 42;
        for(int i=1; i<size; ++i) {
            printf("Ready to send %d--->%d\n", rank, i);
            fflush(stdout);
            MPI_Ssend(&value, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            printf("Data sent %d--->%d\n", rank, i);
            fflush(stdout);
        }
    } else {
        // 非 rank 0 进程接收数据
        MPI_Recv(&value, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        value = -1;
    } 

    // 等待所有进程 赋值 -1 完成
    MPI_Barrier(MPI_COMM_WORLD);

    if(rank == 0) {
        for(int i=1; i<size; ++i) {
            int received_value;
            MPI_Recv(&received_value, 1, MPI_INT, i, 99, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Rank %d received from %d the value %d\n", rank, i, received_value);
            fflush(stdout);
        }
    } else {
        MPI_Send(&value, 1, MPI_INT, 0, 99, MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);
}

int main(int argc, char* argv[]) {
    // ⭐ MPI_Init 只能调用一次，在程序开始时
    MPI_Init(&argc, &argv);
    
    // 🔥 关闭标准输出缓冲，强制立即输出
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    
    // 运行测试函数
    send_data();
    
    // 为了更清晰地看到分隔，rank 0 输出分隔线
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank == 0) {
        printf("\n========== 分隔线 ==========\n");
        fflush(stdout);
    }
    MPI_Barrier(MPI_COMM_WORLD);  // 等待分隔线打印完成
    
    ssend_data();

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if(rank == 0) {
        printf("\n========== 分隔线 ==========\n");
        fflush(stdout);
    }
    MPI_Barrier(MPI_COMM_WORLD);  // 等待分隔线打印完成

    ssend_data_without_recv();
    
    // ⭐ MPI_Finalize 只能调用一次，在程序结束前
    MPI_Finalize();
    return EXIT_SUCCESS;
}



