cmake_minimum_required(VERSION 2.6)

project(optimize)
set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:/usr/local/lib/pkgconfig/")

set ( CMAKE_CXX_FLAGS "-pthread")
set(CMAKE_CXX_STANDARD 17)
add_definitions(-g)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
LINK_DIRECTORIES(${LINK_DIRS})

file( GLOB main_file_list ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp) 
file( GLOB source_file_list ${CMAKE_CURRENT_SOURCE_DIR}/impl/*.cpp)

foreach( main_file ${main_file_list} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${main_file})
    string(REPLACE ".cpp" "" file ${filename})
    add_executable(${file}  ${main_file} ${source_file_list})
    target_link_libraries(${file}  ${CONAN_LIBS} pthread atomic)
endforeach( main_file ${main_file_list})