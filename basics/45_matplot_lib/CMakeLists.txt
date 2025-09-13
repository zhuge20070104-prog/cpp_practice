cmake_minimum_required(VERSION 3.3)


project(45_matplot_lib)

set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:/usr/local/lib/pkgconfig/")

set ( CMAKE_CXX_FLAGS "-pthread")
set(CMAKE_CXX_STANDARD 17)
add_definitions(-g)

add_definitions(-DSAVE_PERCEPTION_CONCAT_IMG)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include_directories(${INCLUDE_DIRS} /opt/pyenv/versions/3.7.13/include/python3.7m/)
LINK_DIRECTORIES(${LINK_DIRS} /opt/pyenv/versions/3.7.13/lib/)

file( GLOB main_file_list ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp) 
file( GLOB source_files ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

foreach( main_file ${main_file_list} )
    file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${main_file})
    string(REPLACE ".cpp" "" file ${filename})
    add_executable(${file}  ${main_file} ${source_files})
    target_link_libraries(${file} ${CONAN_LIBS} pthread python3.7m)
endforeach( main_file ${main_file_list})