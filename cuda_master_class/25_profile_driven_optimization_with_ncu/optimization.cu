#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "common.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// 参数结构体
struct KernelParams {
    int kernel_type;  // 0=1D, 1=2D
    int power_size;   // 数据大小的幂次 (例如25表示2^25)
    int power_grid_x; // 2D时grid的x维度幂次
    int power_block_x; // block的x维度幂次
    int power_block_y; // 2D时block的y维度幂次
};

// CPU参考实现
void sum_array_cpu(int* a, int* b, int* c, int size) {
    for(int i = 0; i < size; i++) {
        c[i] = a[i] + b[i];
    }
}

// 1D Kernel: Arguments: 0 25 0 7
__global__ void sum_array_1d(int* a, int* b, int* c, int size) {
	int gid = blockIdx.x * blockDim.x + threadIdx.x;
	if(gid < size) {
        c[gid] = a[gid] + b[gid];
    }
}

// 2D Kernel: Arguments: 1 25 20 7 2
__global__ void sum_array_2d(int* a, int* b, int* c, int size) {
	int gid = blockIdx.y * gridDim.x * blockDim.x * blockDim.y 
            + blockIdx.x * blockDim.x * blockDim.y
            + threadIdx.y * blockDim.x 
            + threadIdx.x;
	if(gid < size) {
        c[gid] = a[gid] + b[gid];
    }
}

void run_sum_array_test(const KernelParams& params) {
    printf("================================\n");
    if (params.kernel_type == 0) {
        printf("运行 1D Sum Array Kernel\n");
        printf("参数: %d %d %d %d\n", params.kernel_type, params.power_size, 
               params.power_grid_x, params.power_block_x);
    } else {
        printf("运行 2D Sum Array Kernel\n");
        printf("参数: %d %d %d %d %d\n", params.kernel_type, params.power_size, 
               params.power_grid_x, params.power_block_x, params.power_block_y);
    }

    // 计算数据大小: 2^power_size 个元素
    int size = 1 << params.power_size;  // 元素个数
    int byte_size = size * sizeof(int);  // 总字节数
    
    printf("数组元素个数: 2^%d = %d\n", params.power_size, size);
    printf("总字节数: %d bytes (%.2f MB)\n", byte_size, byte_size / (1024.0 * 1024.0));

    // 分配主机内存
    int* h_a = (int*)malloc(byte_size);
    int* h_b = (int*)malloc(byte_size);
    int* h_c = (int*)malloc(byte_size);
    int* gpu_results = (int*)malloc(byte_size);

    // 初始化数据
    time_t t;
    srand((unsigned)time(&t));
    for(int i = 0; i < size; i++) {
        h_a[i] = (int)(rand() & 0xff);
        h_b[i] = (int)(rand() & 0xff);
    }
    memset(gpu_results, 0, byte_size);

    // 分配设备内存
    int *d_a, *d_b, *d_c;
    gpuErrCheck(cudaMalloc((void**)&d_a, byte_size));
    gpuErrCheck(cudaMalloc((void**)&d_b, byte_size));
    gpuErrCheck(cudaMalloc((void**)&d_c, byte_size));

    // 拷贝数据到设备
    gpuErrCheck(cudaMemcpy(d_a, h_a, byte_size, cudaMemcpyHostToDevice));
    gpuErrCheck(cudaMemcpy(d_b, h_b, byte_size, cudaMemcpyHostToDevice));

    if (params.kernel_type == 0) {
        // 1D 配置
        int block_size = 1 << params.power_block_x;
        int grid_size = (size + block_size - 1) / block_size;
        
        printf("Block大小: 2^%d = %d\n", params.power_block_x, block_size);
        printf("Grid大小: %d\n", grid_size);
        
        dim3 blocks(block_size);
        dim3 grid(grid_size);
        sum_array_1d<<<grid, blocks>>>(d_a, d_b, d_c, size);
        
    } else if (params.kernel_type == 1) {
        // 2D 配置
        int block_x = 1 << params.power_block_x;
        int block_y = 1 << params.power_block_y;
        
        int grid_x = 1 << (params.power_grid_x - params.power_block_x);
        int grid_y = 1 << (params.power_size - params.power_grid_x - params.power_block_y);
        
        printf("Block大小: (2^%d, 2^%d) = (%d, %d)\n", 
               params.power_block_x, params.power_block_y, block_x, block_y);
        printf("Grid大小: (2^%d, 2^%d) = (%d, %d)\n", 
               params.power_grid_x - params.power_block_x,
               params.power_size - params.power_grid_x - params.power_block_y,
               grid_x, grid_y);
        printf("总线程数: %d * %d * %d * %d = %d\n", 
               grid_x, grid_y, block_x, block_y, grid_x * grid_y * block_x * block_y);
        
        dim3 blocks(block_x, block_y);
        dim3 grid(grid_x, grid_y);
        sum_array_2d<<<grid, blocks>>>(d_a, d_b, d_c, size);
    }

    gpuErrCheck(cudaDeviceSynchronize());
    printf("Kernel执行完成\n");
    
    // 拷贝结果回主机
    gpuErrCheck(cudaMemcpy(gpu_results, d_c, byte_size, cudaMemcpyDeviceToHost));
    
    // CPU计算用于验证
    printf("验证结果...\n");
    sum_array_cpu(h_a, h_b, h_c, size);
    
    // 验证结果
    compare_results(h_c, gpu_results, size);
    
    // 清理
    gpuErrCheck(cudaFree(d_a));
    gpuErrCheck(cudaFree(d_b));
    gpuErrCheck(cudaFree(d_c));
    free(h_a);
    free(h_b);
    free(h_c);
    free(gpu_results);
    
    printf("完成!\n");
    printf("================================\n\n");
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("用法:\n");
        printf("  1D kernel: %s 0 25 0 7\n", argv[0]);
        printf("  2D kernel: %s 1 25 20 7 2\n", argv[0]);
        printf("\n参数说明:\n");
        printf("  第1个参数: kernel类型 (0=1D, 1=2D)\n");
        printf("  第2个参数: power_size (2^n 个元素)\n");
        printf("  第3个参数: power_grid_x (2D时使用)\n");
        printf("  第4个参数: power_block_x\n");
        printf("  第5个参数: power_block_y (2D时使用)\n");
        return 1;
    }

    KernelParams params;
    params.kernel_type = atoi(argv[1]);
    params.power_size = atoi(argv[2]);
    params.power_grid_x = atoi(argv[3]);
    params.power_block_x = atoi(argv[4]);
    params.power_block_y = (argc > 5) ? atoi(argv[5]) : 0;

    run_sum_array_test(params);
    
    gpuErrCheck(cudaDeviceReset());
    return 0;
}