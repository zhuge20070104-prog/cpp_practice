cmake_minimum_required(VERSION 3.15)

project(44_transform)

# 设置默认构建类型为 Debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -g")

# 使用 Conan 1.x
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file( GLOB main_file_list ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp) 

foreach( main_file ${main_file_list} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${main_file})
    string(REPLACE ".cpp" "" file ${filename})
    add_executable(${file}  ${main_file})
    target_link_libraries(${file} ${CONAN_LIBS} pthread)
endforeach( main_file ${main_file_list})