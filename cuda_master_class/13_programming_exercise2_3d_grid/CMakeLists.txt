cmake_minimum_required(VERSION 3.18)

# 设置 CUDA 架构策略（在 project() 之前设置）
if(NOT DEFINED CMAKE_CUDA_ARCHITECTURES)
    set(CMAKE_CUDA_ARCHITECTURES 50)
endif()

# 解决 CUDA 和 GCC 13.x 兼容性问题
# CUDA 12.4 不完全支持 GCC 13，需要指定使用兼容的编译器
if(NOT DEFINED CMAKE_CUDA_HOST_COMPILER)
    # 尝试查找兼容的 GCC 版本 (优先级: gcc-12, gcc-11, gcc-10)
    find_program(GCC_12 NAMES gcc-12)
    find_program(GCC_11 NAMES gcc-11)
    find_program(GCC_10 NAMES gcc-10)
    
    if(GCC_12)
        set(CMAKE_CUDA_HOST_COMPILER ${GCC_12})
        message(STATUS "使用 GCC-12 作为 CUDA 主机编译器")
    elseif(GCC_11)
        set(CMAKE_CUDA_HOST_COMPILER ${GCC_11})
        message(STATUS "使用 GCC-11 作为 CUDA 主机编译器")
    elseif(GCC_10)
        set(CMAKE_CUDA_HOST_COMPILER ${GCC_10})
        message(STATUS "使用 GCC-10 作为 CUDA 主机编译器")
    else()
        message(WARNING "未找到兼容的 GCC 版本 (gcc-10/11/12)。如果编译失败，请安装: sudo apt install gcc-12 g++-12")
    endif()
endif()

# 显式设置 CUDA 编译器路径（如果 CMake 找不到的话）
if(NOT DEFINED CMAKE_CUDA_COMPILER)
    # 尝试查找 nvcc
    find_program(NVCC_EXECUTABLE nvcc
        PATHS
        /usr/local/cuda/bin
        /usr/local/cuda-12/bin
        /usr/local/cuda-11/bin
        ENV CUDA_PATH
        PATH_SUFFIXES bin
    )
    
    if(NVCC_EXECUTABLE)
        set(CMAKE_CUDA_COMPILER ${NVCC_EXECUTABLE})
        message(STATUS "找到 nvcc: ${NVCC_EXECUTABLE}")
    endif()
endif()

# 项目名称，先只声明 CXX
project(ThreeDGrid LANGUAGES CXX)

# Conan 1.x 集成
# 在运行 cmake 之前需要先执行: conan install . --build=missing
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    # 不使用 TARGETS 模式，使用默认模式自动设置包含路径和库
    conan_basic_setup()
    message(STATUS "✓ Conan 依赖已加载")
    message(STATUS "  Conan 包含目录: ${CONAN_INCLUDE_DIRS}")
    message(STATUS "  Conan 库: ${CONAN_LIBS}")
else()
    message(WARNING "⚠ 未找到 conanbuildinfo.cmake")
    message(WARNING "  请先运行: conan install . --build=missing")
    message(WARNING "  或在 build 目录中运行: conan install .. --build=missing")
endif()

# 查找 CUDA
include(CheckLanguage)
check_language(CUDA)

if(CMAKE_CUDA_COMPILER)
    enable_language(CUDA)
    message(STATUS "CUDA 编译器找到: ${CMAKE_CUDA_COMPILER}")
    message(STATUS "CUDA 版本: ${CMAKE_CUDA_COMPILER_VERSION}")
    if(CMAKE_CUDA_HOST_COMPILER)
        message(STATUS "CUDA 主机编译器: ${CMAKE_CUDA_HOST_COMPILER}")
    endif()
else()
    message(FATAL_ERROR "未找到 CUDA 编译器！请确保已安装 NVIDIA CUDA Toolkit 并设置了环境变量。")
endif()

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置 CUDA 标准
set(CMAKE_CUDA_STANDARD 11)
set(CMAKE_CUDA_STANDARD_REQUIRED ON)

# 添加可执行文件
add_executable(threeDGrid threeDGrid.cu)

# 设置 CUDA 编译选项
target_compile_options(threeDGrid PRIVATE
    $<$<COMPILE_LANGUAGE:CUDA>:
        --use_fast_math
        -Xcompiler -Wall
    >
)

# 链接 C++ 标准库和数学库（因为 .cu 文件中使用了 Catch2）
target_link_libraries(threeDGrid PRIVATE stdc++ m)

# 链接 Conan 依赖库（Catch2）
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    target_link_libraries(threeDGrid PRIVATE ${CONAN_LIBS})
endif()

# 打印一些信息
message(STATUS "CUDA Version: ${CMAKE_CUDA_COMPILER_VERSION}")
message(STATUS "CUDA Architectures: ${CMAKE_CUDA_ARCHITECTURES}")