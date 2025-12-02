cmake_minimum_required(VERSION 3.18)

# 设置 CUDA 架构策略（在 project() 之前设置）
if(NOT DEFINED CMAKE_CUDA_ARCHITECTURES)
    # RTX 3500 Ada / L40G = compute capability 8.9
    # CUDA 13.0 支持 75, 80, 86, 87, 89, 90 等
    set(CMAKE_CUDA_ARCHITECTURES 89)
endif()

# 解决 CUDA 和 GCC 13.x 兼容性问题（仅限 Linux/Unix）
# CUDA 12.4 不完全支持 GCC 13，需要指定使用兼容的编译器
if(UNIX AND NOT DEFINED CMAKE_CUDA_HOST_COMPILER)
    # 尝试查找兼容的 GCC 版本 (优先级: gcc-11, gcc-10, gcc-12)
    find_program(GCC_11 NAMES gcc-11)
    find_program(GCC_10 NAMES gcc-10)
    find_program(GCC_12 NAMES gcc-12)
    
    if(GCC_11)
        set(CMAKE_CUDA_HOST_COMPILER ${GCC_11})
        message(STATUS "使用 GCC-11 作为 CUDA 主机编译器")
    elseif(GCC_10)
        set(CMAKE_CUDA_HOST_COMPILER ${GCC_10})
        message(STATUS "使用 GCC-10 作为 CUDA 主机编译器")
    elseif(GCC_12)
        set(CMAKE_CUDA_HOST_COMPILER ${GCC_12})
        message(STATUS "使用 GCC-12 作为 CUDA 主机编译器")
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
project(CudaMemoryModel LANGUAGES CXX)

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

# 强制允许不支持的编译器（绕过旧头文件版本检查）
set(CMAKE_CUDA_FLAGS "${CMAKE_CUDA_FLAGS} -allow-unsupported-compiler")

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

# ==========================================
# 定义复用函数：创建一个 CUDA 示例程序
# 用法：create_cuda_example(target_name source_file.cu)
# ==========================================
function(create_cuda_example TARGET_NAME SOURCE_FILE)
    # 添加可执行文件 (自动包含 common.cpp)
    add_executable(${TARGET_NAME} ${SOURCE_FILE} ${CMAKE_CURRENT_SOURCE_DIR}/../common/common.cpp)
    
    # 包含路径
    target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../common)

    # 启用可重定位设备代码（动态并行需要）
    set_target_properties(${TARGET_NAME} PROPERTIES CUDA_SEPARABLE_COMPILATION ON)

    # 设置编译选项
    target_compile_options(${TARGET_NAME} PRIVATE
        $<$<COMPILE_LANGUAGE:CUDA>:
            --use_fast_math
            --ptxas-options=-v
            -allow-unsupported-compiler  # 强制允许 GCC 12 编译（绕过旧头文件版本检查）
            $<$<PLATFORM_ID:Windows>:-Xcompiler /wd5045>  # 禁用 Spectre 警告
            $<$<PLATFORM_ID:Linux>:-Xcompiler -Wall>
        >
    )

    # Windows/MSVC 特定选项
    if(MSVC)
        target_compile_options(${TARGET_NAME} PRIVATE 
            $<$<COMPILE_LANGUAGE:CXX>:/wd5045>
        )
    endif()

    # 链接标准库
    if(UNIX)
        target_link_libraries(${TARGET_NAME} PRIVATE stdc++ m)
    endif()

    # 链接 Conan 依赖 (Catch2)
    if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
        target_link_libraries(${TARGET_NAME} PRIVATE ${CONAN_LIBS})
    endif()
endfunction()

# ==========================================
# 添加示例程序
# ==========================================

# 示例 1: 原始的内存模型示例
create_cuda_example(cudaMemoryModel cudaMemoryModel.cu)

# 你可以像这样轻松添加更多示例：
# create_cuda_example(test_registers test_registers.cu)
# create_cuda_example(test_shared test_shared_mem.cu)

# 打印一些信息
message(STATUS "CUDA Version: ${CMAKE_CUDA_COMPILER_VERSION}")
message(STATUS "CUDA Architectures: ${CMAKE_CUDA_ARCHITECTURES}")
