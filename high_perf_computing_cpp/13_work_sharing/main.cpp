#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"

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
#include <omp.h>
#include <cmath>  // 需要包含 erff()

TEST_CASE("parallel for large scale computing") {
    const int length = 1024 * 1024 * 64;

    float* a = new float[length];
    float* b = new float[length];
    float* c = new float[length];
    float* result = new float[length];

    // 初始化输入数据（使用随机数）
    std::mt19937_64 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    
    std::cout << "初始化数据中..." << std::endl;
    for(int i = 0; i < length; ++i) {
        a[i] = dist(rng);
        b[i] = dist(rng);
        c[i] = dist(rng);
    }
    std::cout << "数据初始化完成" << std::endl;

    // 串行版本计算
    auto begin = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < length; ++i) {
        result[i] = a[i] + b[i] * erff(c[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto serial_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    std::cout << "串行计算耗时: " << serial_time << " ms" << std::endl;

    // 并行版本计算
    begin = std::chrono::high_resolution_clock::now();
    #pragma omp parallel for 
    for(int i = 0; i < length; ++i) {
        result[i] = a[i] + b[i] * erff(c[i]);
    }
    end = std::chrono::high_resolution_clock::now();
    auto parallel_time = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    std::cout << "并行计算耗时: " << parallel_time << " ms" << std::endl;
    std::cout << "加速比: " << (double)serial_time / parallel_time << "x" << std::endl;

    // 清理内存
    delete[] a;
    delete[] b;
    delete[] c;
    delete[] result;
}


/*
 * OpenMP Sections 工作机制说明
 * 
 * 重要概念：
 * - 一个 section = 一个独立的任务（不是一个线程！）
 * - section 会被动态分配给线程池中的某个线程执行
 * - 每个 section 同一时刻只被一个线程执行
 * 
 * 场景1：线程数 > section 数（最常见情况）
 * ┌──────────────────────────────────────────┐
 * │ 可用线程：8个                             │
 * │ Section 数：2个                           │
 * │                                          │
 * │ 执行情况：                                │
 * │   线程0 → 执行 section 1                 │
 * │   线程1 → 执行 section 2                 │
 * │   线程2-7 → 空闲（不执行任何工作）         │
 * └──────────────────────────────────────────┘
 * 
 * 场景2：线程数 = section 数（理想情况）
 * ┌──────────────────────────────────────────┐
 * │ 可用线程：2个                             │
 * │ Section 数：2个                           │
 * │                                          │
 * │ 执行情况：                                │
 * │   线程0 → 执行 section 1                 │
 * │   线程1 → 执行 section 2                 │
 * └──────────────────────────────────────────┘
 * 
 * 场景3：线程数 < section 数（线程复用）
 * ┌──────────────────────────────────────────┐
 * │ 可用线程：2个                             │
 * │ Section 数：4个                           │
 * │                                          │
 * │ 执行情况：                                │
 * │   线程0 → 先执行 section 1，完成后执行 section 3  │
 * │   线程1 → 先执行 section 2，完成后执行 section 4  │
 * └──────────────────────────────────────────┘
 * 
 * 注意：下面的代码存在输出混乱问题（多线程同时写 cout）
 *      这是为了演示 sections 的执行方式，生产代码应使用 critical 保护
 */
TEST_CASE("parallel for sections") {
#pragma omp parallel sections
{
#pragma omp section 
    {   
        for(int i=0; i<1000; ++i) {
            std::cout << "Thread " << omp_get_thread_num() << ": ";
            std::cout << i;
        }
    }
#pragma omp section 
    {
        for(int i=0; i<1000; ++i) {
            std::cout << "Thread " << omp_get_thread_num() << ": ";
            std::cout << static_cast<char>('a' + (i % 26));
        }
    }
}
}


/*
 * OpenMP single vs master 详解
 * 
 * #pragma omp single
 * - 作用：在并行区域中，只有一个线程执行，其他线程等待
 * - 执行线程：任意一个线程（运行时随机选择）
 * - 隐式barrier：有（所有线程会等待single区域完成）
 * - 可选参数：nowait（取消隐式barrier）
 * - 语法：可以是单行，也可以是代码块
 *   单行：#pragma omp single
 *         printf("...");           // 只作用于下一行
 *   块：  #pragma omp single
 *         {                        // 使用花括号包含多行代码
 *             printf("...");
 *             int x = 10;
 *         }
 * 
 * #pragma omp master  
 * - 作用：只有主线程（0号线程）执行
 * - 执行线程：必须是0号主线程
 * - 隐式barrier：无（其他线程不等待，直接跳过）
 * - 语法：同样支持单行或代码块
 * 
 * ┌─────────────────────────────────────────────────────────────┐
 * │ 快速记忆表格                                                │
 * ├─────────────────┬──────────┬──────────┬──────────────────┤
 * │ 代码            │ 执行次数 │ 执行线程 │ 其他线程         │
 * ├─────────────────┼──────────┼──────────┼──────────────────┤
 * │ #pragma omp     │   1次    │  任意1个 │ 等待（barrier）  │
 * │ single          │          │          │                  │
 * ├─────────────────┼──────────┼──────────┼──────────────────┤
 * │ 普通代码        │   N次    │ 所有线程 │ 都执行           │
 * │ (无指令)        │          │          │                  │
 * ├─────────────────┼──────────┼──────────┼──────────────────┤
 * │ #pragma omp     │   1次    │ 0号主线程│ 不等待（直接跳过)│
 * │ master          │          │          │                  │
 * └─────────────────┴──────────┴──────────┴──────────────────┘
 * 
 * 执行流程示例（假设8个线程）：
 * ┌────────────────────────────────────────────────────┐
 * │ #pragma omp parallel                              │
 * │ {                                                 │
 * │     #pragma omp single                            │
 * │     printf("gathering: %d\n", tid);               │
 * │     // ↑ 只有1个线程执行（如线程3）               │
 * │     //   其他7个线程等待（隐式barrier）            │
 * │                                                   │
 * │     printf("in parallel: %d\n", tid);             │
 * │     // ↑ 所有8个线程都执行                        │
 * │     //   输出8次                                  │
 * │                                                   │
 * │     #pragma omp barrier                           │
 * │     // ↑ 显式同步点                               │
 * │                                                   │
 * │     #pragma omp master                            │
 * │     printf("output: %d\n", tid);                  │
 * │     // ↑ 只有线程0执行                            │
 * │     //   其他线程不等待，直接往下                  │
 * │ }                                                 │
 * └────────────────────────────────────────────────────┘
 */
TEST_CASE("parallel for single") {
    omp_set_num_threads(8);

#pragma omp parallel 
{
    #pragma omp single
    {
        printf("Gathering input: %d\n", omp_get_thread_num());
    }

    {
        printf("In parallel on: %d\n", omp_get_thread_num());
    }
    #pragma omp barrier
    #pragma omp master 
    {
        printf("Output on: %d\n", omp_get_thread_num());
    }
}

}