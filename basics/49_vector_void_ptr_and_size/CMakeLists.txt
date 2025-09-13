cmake_minimum_required(VERSION 3.3)

project(49_vector_void_ptr_and_size)

set(CMAKE_CXX_STANDARD 11)
add_definitions(-g)


include_directories(${INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/libs/include)



file( GLOB main_file_list ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp) 
file( GLOB source_files ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/*.cc)

foreach( main_file ${main_file_list} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${main_file})
    string(REPLACE ".cpp" "" file ${filename})
    add_executable(${file}  ${main_file} ${source_files})
endforeach( main_file ${main_file_list})