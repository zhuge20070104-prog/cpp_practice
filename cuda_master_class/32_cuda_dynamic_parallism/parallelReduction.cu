// 32. CUDA Dynamic Parallelism Demo
// 一个最小可运行的动态并行示例：
//  - host 启动 parent kernel（1 个 block，16 个线程）
//  - 每一层只有 tid==0 的线程再启动一个 child kernel
//  - child kernel 的线程数是上一层的一半
//  - 一直递归到 size == 1 为止

#include <stdio.h>
#include <stdlib.h>

#include "cuda_runtime.h"
#include "device_launch_parameters.h"

// 设备端递归 kernel
__global__ void dynamic_parallelism_check(int size, int depth) {
    printf("Depth: %d - tid: %d\n", depth, threadIdx.x);

    // 递归结束条件：只剩 1 个线程时停止
    if (size == 1) {
        return;
    }

    // 只让 tid==0 的线程去启动下一层 child grid，避免重复 launch
    if (threadIdx.x == 0) {
        int child_size = size / 2;
        // 一个 block，child_size 个线程
        dynamic_parallelism_check<<<1, child_size>>>(child_size, depth + 1);
    }
}

int main(int argc, char** argv) {
    int size = 16;   // 第一层有 16 个线程
    int depth = 0;   // 从深度 0 开始

    printf("=========================================\n");
    printf("CUDA Dynamic Parallelism - Simple Demo\n");
    printf("Parent grid: 1 block, %d threads\n", size);
    printf("Each child grid uses half of the threads of its parent.\n");
    printf("=========================================\n\n");

    // 启动 parent kernel（只能由 host 启动）
    dynamic_parallelism_check<<<1, size>>>(size, depth);

    // 等待所有 parent + child grid 执行完成
    cudaDeviceSynchronize();
    cudaDeviceReset();

    return 0;
}
