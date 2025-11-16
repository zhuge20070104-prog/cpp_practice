cmake_minimum_required(VERSION 3.10)
project(7_complier_vectorization LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 检查编译器是否支持内联汇编
if(NOT (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang"))
    message(WARNING "此项目使用GCC风格内联汇编，建议使用GCC或Clang编译器")
endif()

# 检查目标架构
if(NOT (CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|AMD64|i686|i386"))
    message(WARNING "此程序使用x86 CPUID指令，需要x86/x86_64架构")
endif()

# 设置默认构建类型为 Release（如果未指定）
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    message(STATUS "未指定构建类型，默认使用 Release")
endif()

# 创建可执行文件
add_executable(7_complier_vectorization main.cpp)

# 编译选项：启用 SIMD 指令集支持
target_compile_options(7_complier_vectorization PRIVATE
    -msse4.2                                # 启用 SSE4.2
    -mavx                                   # 启用 AVX
    -mavx2                                  # 启用 AVX2
    -O3                                     # 最高优化级别（可改为 -O0 对比）
    -save-temps=obj                         # 保存中间文件（包括.s汇编文件）
    -fverbose-asm                           # 生成带源代码注释的汇编代码
)

# 输出编译信息
message(STATUS "编译器: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "构建类型: ${CMAKE_BUILD_TYPE}")
message(STATUS "目标架构: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "C++标准: C++${CMAKE_CXX_STANDARD}")
message(STATUS "优化级别: -O3 (自动向量化测试)")
message(STATUS "汇编文件生成: 已启用 (-save-temps=obj -fverbose-asm)")
message(STATUS "  编译后将在 CMakeFiles/<target>.dir/ 目录下生成 .s 汇编文件")

