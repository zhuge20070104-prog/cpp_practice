cmake_minimum_required(VERSION 3.10.2)

project(OLAS VERSION 1.3)

configure_file(olas_config.h.in olas_config.h)

option(USE_ADDER "A simple library for adding 2 floats" ON)

if(USE_ADDER)
    add_subdirectory(lib)

    list(APPEND EXTRA_LIB_DIRS "lib")
    list(APPEND EXTRA_INCLUDE_DIRS "lib")
    list(APPEND EXTRA_LINKS my_math)
endif()

add_definitions(-g)

link_directories(${EXTRA_LINK_DIRS})

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${EXTRA_INCLUDE_DIRS}
    ${PROJECT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} ${EXTRA_LINKS})