cmake_minimum_required(VERSION 3.3)

project(03_single_responsibility)

set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:/usr/local/lib/pkgconfig/")

set ( CMAKE_CXX_FLAGS "-pthread")
set(CMAKE_CXX_STANDARD 17)
add_definitions(-g)


include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()



include_directories(${INCLUDE_DIRS})
LINK_DIRECTORIES(${LINK_DIRS})

file( GLOB main_file_list ${CMAKE_CURRENT_SOURCE_DIR}/*_test.cpp) 
file( GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

foreach( main_file ${main_file_list} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${main_file})
    string(REPLACE ".cpp" "" file ${filename})
    add_executable(${file}  ${main_file} ${sources})
    target_link_libraries(${file} PRIVATE gtest_main  pthread)
    target_link_libraries(${file} PRIVATE  ${CONAN_LIBS})


endforeach( main_file ${main_file_list})