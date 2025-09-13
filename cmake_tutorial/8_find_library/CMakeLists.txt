cmake_minimum_required(VERSION 3.10.2)

project(OLAS)

# my_glew_lib 后面链接用的名字
# glew 实际的库名， linux会扩充其为libglew.a
# glew2 GLEW GLEW2 你也可以叫他们glew2 GLEW GLEW2 都可以
find_library(my_glew_lib GLEW NAME glew2 GLEW GLEW2 DOC "glew library")

if(${my_glew_lib} STREQUAL my_glew_lib-NOTFOUND)
    message(FATAL_ERROR "no glew, sad day")
else()
    message(STATUS "glew found! as ${my_glew_lib}")
endif ()

find_library(my_glu_lib GLU)
if(${my_glu_lib} STREQUAL my_glu_lib-NOTFOUND)
    message(FATAL_ERROR "no glu, sad day")
else()
    message(STATUS "glu found! as ${my_glu_lib}")
endif()

find_library(my_gl_lib GL DOC "gl library")
if(${my_gl_lib} STREQUAL my_gl_lib-NOTFOUND)
    message(FATAL_ERROR "no gl, sad day")
else()
    message(STATUS "gl found! as ${my_gl_lib}")
endif()

link_directories(external/glfw/src)
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(external/glfw)

target_include_directories(${PROJECT_NAME} PUBLIC external/glfw/include)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw ${my_glew_lib} ${my_glu_lib} ${my_gl_lib})