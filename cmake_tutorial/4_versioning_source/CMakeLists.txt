cmake_minimum_required(VERSION 3.10.2)

project(OLAS VERSION 1.2)

configure_file(olas_config.h.in olas_config.h)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})
