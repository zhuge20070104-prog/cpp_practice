cmake_minimum_required(VERSION 2.6)

if(APPLE)
    message(STATUS "This is Apple, do nothing.")
elseif(UNIX)
    message(STATUS "This is linux, set CMAKE_PREFIX_PATH.")
    set(CMAKE_PREFIX_PATH /vcpkg/ports/cppwork/vcpkg_installed/x64-linux/share)
endif(APPLE)

project(7_regex)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O0 -g")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
LINK_DIRECTORIES(${LINK_DIRS})

file( GLOB main_file_list ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp) 
file( GLOB source_file_list ${CMAKE_CURRENT_SOURCE_DIR}/impl/*.cpp)

foreach( main_file ${main_file_list} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${main_file})
    string(REPLACE ".cpp" "" file ${filename})
    add_executable(${file}  ${main_file} ${source_file_list})
    target_link_libraries(${file} pthread)
endforeach( main_file ${main_file_list})