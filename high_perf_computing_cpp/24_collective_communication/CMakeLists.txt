cmake_minimum_required(VERSION 3.10)
project(24_collective_communication LANGUAGES CXX)

# Conan 1.x 集成
# 在运行 cmake 之前需要先执行: conan install . --build=missing
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    # 不使用 TARGETS 模式，使用默认模式自动设置包含路径和库
    conan_basic_setup()
    message(STATUS "✓ Conan 依赖已加载")
    message(STATUS "  Conan 包含目录: ${CONAN_INCLUDE_DIRS}")
else()
    message(WARNING "⚠ 未找到 conanbuildinfo.cmake")
    message(WARNING "  请先运行: conan install . --build=missing")
    message(WARNING "  或在 build 目录中运行: conan install .. --build=missing")
endif()

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 MPI（Intel MPI 或 OpenMPI）
find_package(MPI REQUIRED)
if(MPI_CXX_FOUND)
    message(STATUS "✓ MPI 已找到")
    message(STATUS "  MPI 编译器: ${MPI_CXX_COMPILER}")
    message(STATUS "  MPI 包含目录: ${MPI_CXX_INCLUDE_DIRS}")
    message(STATUS "  MPI 库: ${MPI_CXX_LIBRARIES}")
    
    # 检测是否为 Intel MPI
    execute_process(
        COMMAND ${MPI_CXX_COMPILER} --version
        OUTPUT_VARIABLE MPI_VERSION_OUTPUT
        ERROR_QUIET
    )
    if(MPI_VERSION_OUTPUT MATCHES "Intel")
        message(STATUS "  MPI 实现: Intel MPI ⭐")
    elseif(MPI_VERSION_OUTPUT MATCHES "Open MPI")
        message(STATUS "  MPI 实现: OpenMPI")
    else()
        message(STATUS "  MPI 实现: 未知")
    endif()
else()
    message(FATAL_ERROR "✗ MPI 未找到！请安装 Intel MPI 或 OpenMPI")
endif()

# 查找 Boost.MPI（需要 mpi 和 serialization 组件）
find_package(Boost COMPONENTS mpi serialization)
if(Boost_FOUND)
    message(STATUS "✓ Boost.MPI 已找到")
    message(STATUS "  Boost 版本: ${Boost_VERSION}")
    message(STATUS "  Boost 包含目录: ${Boost_INCLUDE_DIRS}")
    message(STATUS "  Boost 库: ${Boost_LIBRARIES}")
else()
    message(WARNING "⚠ Boost.MPI 未找到")
    message(WARNING "  请安装: sudo apt install libboost-mpi-dev libboost-serialization-dev")
endif()

# 查找 OpenMP 库
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    message(STATUS "✓ OpenMP已找到")
    message(STATUS "  OpenMP版本: ${OpenMP_CXX_VERSION}")
    message(STATUS "  OpenMP标志: ${OpenMP_CXX_FLAGS}")
else()
    message(WARNING "✗ OpenMP未找到，程序将无法使用多线程并行")
endif()

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
add_executable(24_collective_communication main.cpp)

# 链接 MPI 库（必需）
target_link_libraries(24_collective_communication PRIVATE MPI::MPI_CXX)

# 链接 Boost.MPI 库（如果找到）
if(Boost_FOUND)
    target_include_directories(24_collective_communication PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(24_collective_communication PRIVATE 
        Boost::mpi 
        Boost::serialization
    )
endif()

# 链接 Conan 依赖库（如 Catch2）
if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    target_link_libraries(24_collective_communication PRIVATE ${CONAN_LIBS})
endif()

# 链接 OpenMP 库（可选）
if(OpenMP_CXX_FOUND)
    target_link_libraries(24_collective_communication PRIVATE OpenMP::OpenMP_CXX)
endif()

# 编译选项：启用 SIMD 指令集支持
target_compile_options(24_collective_communication PRIVATE
    -msse4.2                                # 启用 SSE4.2
    -mavx                                   # 启用 AVX
    -mavx2                                  # 启用 AVX2
    -O3                                     # 最高优化级别（可改为 -O0 对比）
    -save-temps=obj                         # 保存中间文件（包括.s汇编文件）
    -fverbose-asm                           # 生成带源代码注释的汇编代码
)

# 输出编译信息
message(STATUS "")
message(STATUS "========== 编译配置摘要 ==========")
message(STATUS "编译器: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "构建类型: ${CMAKE_BUILD_TYPE}")
message(STATUS "目标架构: ${CMAKE_SYSTEM_PROCESSOR}")
message(STATUS "C++标准: C++${CMAKE_CXX_STANDARD}")
message(STATUS "优化级别: -O3 (自动向量化)")
message(STATUS "")
message(STATUS "并行支持:")
if(MPI_CXX_FOUND)
    message(STATUS "  MPI: ✅ 已启用")
else()
    message(STATUS "  MPI: ❌ 未启用")
endif()
if(Boost_FOUND)
    message(STATUS "  Boost.MPI: ✅ 已启用")
else()
    message(STATUS "  Boost.MPI: ❌ 未启用")
endif()
if(OpenMP_CXX_FOUND)
    message(STATUS "  OpenMP: ✅ 已启用")
else()
    message(STATUS "  OpenMP: ❌ 未启用")
endif()
message(STATUS "")
message(STATUS "运行命令: mpirun -np 4 ./24_collective_communication")
message(STATUS "===================================")
message(STATUS "")

