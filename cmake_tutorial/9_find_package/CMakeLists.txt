cmake_minimum_required(VERSION 3.10.2)

project(OLAS)

include (${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindGLEW.cmake)
set(CMAKE_MODULE_PATH cmake)
find_package(GLEW REQUIRED)

if(GLEW_FOUND)
    list(APPEND EXTRA_INCLUDE_DIRS ${GLEW_INCLUDE_DIRS} )
    message(STATUS "GLEW LIBRARIES: ${GLEW_LIBRARIES}")
    list(APPEND EXTRA_LINKS ${GLEW_LIBRARIES})    
endif()


link_directories(external/glfw/src)
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} PUBLIC external/glfw/include ${EXTRA_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw ${EXTRA_LINKS} )