cmake_minimum_required(VERSION 3.10.2)

project(OLAS)

link_directories(external/glfw/src)
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} PUBLIC external/glfw/include)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)