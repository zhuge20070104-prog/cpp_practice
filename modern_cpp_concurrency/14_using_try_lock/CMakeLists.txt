cmake_minimum_required(VERSION 3.3)

project(14_using_try_lock)


set ( CMAKE_CXX_FLAGS "-pthread")
# CMake 添加sanitize检查
set ( CMAKE_CXX_FLAGS "-fsanitize=thread")
set(CMAKE_CXX_STANDARD 17)
add_definitions(-g)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(${INCLUDE_DIRS})
LINK_DIRECTORIES(${LINK_DIRS})

file( GLOB main_file_list ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp) 

foreach( main_file ${main_file_list} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${main_file})
    string(REPLACE ".cpp" "" file ${filename})
    add_executable(${file}  ${main_file})
    target_link_libraries(${file} ${CONAN_LIBS} pthread)
endforeach( main_file ${main_file_list})