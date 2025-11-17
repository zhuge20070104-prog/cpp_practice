cmake_minimum_required(VERSION 3.10)
project(14_synchronization LANGUAGES CXX)

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

# 查找系统安装的 Boost（可选）
find_package(Boost COMPONENTS system thread)
if(Boost_FOUND)
    message(STATUS "✓ 系统 Boost 已找到")
    message(STATUS "  Boost 版本: ${Boost_VERSION}")
    message(STATUS "  Boost 包含目录: ${Boost_INCLUDE_DIRS}")
else()
    message(STATUS "✗ 系统 Boost 未找到（如需要请安装: sudo apt install libboost-all-dev）")
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
add_executable(14_synchronization main.cpp)

# 链接 Conan 依赖库（conan_basic_setup() 已自动设置包含路径）
# CONAN_LIBS 变量包含所有 Conan 依赖
target_link_libraries(14_synchronization PRIVATE ${CONAN_LIBS})

# 链接系统 Boost（如果找到）
if(Boost_FOUND)
    target_include_directories(14_synchronization PRIVATE ${Boost_INCLUDE_DIRS})
    target_link_libraries(14_synchronization PRIVATE ${Boost_LIBRARIES})
endif()

# 链接 OpenMP 库
if(OpenMP_CXX_FOUND)
    target_link_libraries(14_synchronization PRIVATE OpenMP::OpenMP_CXX)
endif()

# 编译选项：启用 SIMD 指令集支持
target_compile_options(14_synchronization PRIVATE
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
message(STATUS "优化级别: -O3 (自动向量化+OpenMP并行)")
message(STATUS "汇编文件生成: 已启用 (-save-temps=obj -fverbose-asm)")
message(STATUS "  编译后将在 CMakeFiles/<target>.dir/ 目录下生成 .s 汇编文件")
if(OpenMP_CXX_FOUND)
    message(STATUS "OpenMP 多线程: 已启用")
else()
    message(STATUS "OpenMP 多线程: 未启用")
endif()

