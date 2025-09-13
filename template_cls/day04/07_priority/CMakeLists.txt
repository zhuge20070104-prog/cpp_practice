cmake_minimum_required(VERSION 2.6)

if(APPLE)
    message(STATUS "This is Apple, do nothing.")
elseif(UNIX)
    message(STATUS "This is linux, set CMAKE_PREFIX_PATH.")
    set(CMAKE_PREFIX_PATH /vcpkg/ports/cppwork/vcpkg_installed/x64-linux/share)
endif(APPLE)

project(07_priority)

add_definitions(-std=c++17)

add_definitions(-g)


include_directories(${INCLUDE_DIRS})
LINK_DIRECTORIES(${LINK_DIRS})

file( GLOB main_file_list ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp) 

foreach( main_file ${main_file_list} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${main_file})
    string(REPLACE ".cpp" "" file ${filename})
    add_executable(${file}  ${main_file})
endforeach( main_file ${main_file_list})