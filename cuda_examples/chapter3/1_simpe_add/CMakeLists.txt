cmake_minimum_required(VERSION 3.3)

project(1_simpe_add)

set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:/usr/local/lib/pkgconfig/")

set ( CMAKE_CXX_FLAGS "-pthread")
set(CMAKE_CXX_STANDARD 17)
add_definitions(-g)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(CUDA)

include_directories(${INCLUDE_DIRS})
LINK_DIRECTORIES(${LINK_DIRS})

if (CUDA_FOUND)

    file( GLOB main_file_list ${CMAKE_CURRENT_SOURCE_DIR}/*.cu)

    foreach( main_file ${main_file_list} )
        file(RELATIVE_PATH filename ${CMAKE_CURRENT_SOURCE_DIR} ${main_file})
        string(REPLACE ".cu" "" file ${filename})
        CUDA_ADD_EXECUTABLE(${file}  ${main_file})
        target_link_libraries(${file} ${CUDA_LINK_LIBRARIES_KEYWORD}  pthread)
        target_link_libraries(${file} ${CUDA_LINK_LIBRARIES_KEYWORD}  ${CONAN_LIBS})
    endforeach( main_file ${main_file_list})
else()
	message("CUDA not found!")
endif()