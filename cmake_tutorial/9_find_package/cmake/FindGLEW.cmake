
find_path(GLEW_INCLUDE_DIR GL/glew.h)
set(GLEW_INCLUDE_DIRS ${GLEW_INCLUDE_DIR})


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

# 有多个的时候，先转成list，再传回来
list(APPEND GLEW_LIBRARY  ${my_glew_lib})
list(APPEND GLEW_LIBRARY  ${my_glu_lib}) 
list(APPEND GLEW_LIBRARY  ${my_gl_lib})
set(GLEW_LIBRARIES ${GLEW_LIBRARY})

message(STATUS "GLEW_LIB: ${GLEW_LIBRARIES}")
set(GLEW_FOUND TRUE)