cmake_minimum_required(VERSION 2.6)


project(3_timed_mutex_try_lock_for)
set ( CMAKE_CXX_FLAGS "-pthread")
add_definitions(-std=c++17)

add_definitions(-g)


include_directories(${INCLUDE_DIRS})
LINK_DIRECTORIES(${LINK_DIRS})

file( GLOB main_file_list ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp) 

foreach( main_file ${main_file_list} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${main_file})
    string(REPLACE ".cpp" "" file ${filename})
    add_executable(${file}  ${main_file})
    target_link_libraries(${file} pthread)
endforeach( main_file ${main_file_list})