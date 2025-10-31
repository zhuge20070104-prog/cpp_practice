cmake_minimum_required(VERSION 3.22)

project(384_modules_funcs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 模块接口文件
set(MODULE_SOURCES
    print.ixx
    math.div.ixx
    math.multi-part.ixx
    math.ixx
)

# 实现文件和主程序
set(IMPL_SOURCES
    math.cpp
    main.cpp
)

add_executable(384_modules_funcs
    ${MODULE_SOURCES}
    ${IMPL_SOURCES}
)

# GCC 需要 -fmodules-ts 标志
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(384_modules_funcs PRIVATE -fmodules-ts)
    
    # 设置模块文件的属性
    set_source_files_properties(
        ${MODULE_SOURCES}
        PROPERTIES 
        COMPILE_FLAGS "-fmodules-ts -x c++"
    )
endif()


include(GNUInstallDirs)
install(TARGETS 384_modules_funcs
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
