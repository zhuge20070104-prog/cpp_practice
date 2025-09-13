cmake_minimum_required(VERSION 3.3)


project(54_boss_crawer)

set ( CMAKE_CXX_FLAGS "-pthread")
set(CMAKE_CXX_STANDARD 17)
add_definitions(-D _GLIBCXX_USE_CXX11_ABI=0)
add_definitions(-g)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${CONAN_LIB_DIRS_POCO})

file( GLOB main_file_list ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp) 
file( GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/src/utils/*.cc)

foreach( main_file ${main_file_list} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${main_file})
    string(REPLACE ".cpp" "" file ${filename})
    add_executable(${file}  ${main_file} ${sources})
    target_link_libraries(${file} ${CONAN_LIBS} pthread)
endforeach( main_file ${main_file_list})
