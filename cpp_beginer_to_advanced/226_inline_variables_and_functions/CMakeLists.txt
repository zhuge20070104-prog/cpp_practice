cmake_minimum_required(VERSION 3.5)

project(226_inline_variables_and_functions LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(226_inline_variables_and_functions main.cpp
    inline_variables_and_func1.cpp
    inline_variables_and_func2.cpp)


include(GNUInstallDirs)
install(TARGETS 226_inline_variables_and_functions
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
