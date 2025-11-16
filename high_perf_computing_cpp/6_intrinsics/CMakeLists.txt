cmake_minimum_required(VERSION 3.10)
project(6_intrinsics LANGUAGES CXX)

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

# 创建可执行文件
add_executable(6_intrinsics main.cpp)

# 编译选项：启用 SIMD 指令集支持
target_compile_options(6_intrinsics PRIVATE
    -msse4.2    # 启用 SSE4.2
    -mavx       # 启用 AVX
    -mavx2      # 启用 AVX2
    $<$<CONFIG:Release>:-O3>                # Release模式优化级别
)

# 输出编译信息
message(STATUS "编译器: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "目标架构: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "C++标准: C++${CMAKE_CXX_STANDARD}")

