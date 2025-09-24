cmake_minimum_required(VERSION 3.5)

project(227_inline_vs_static LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(227_inline_vs_static main.cpp
     inline_static_ns1.cpp
     inline_static_ns2.cpp)


include(GNUInstallDirs)
install(TARGETS 227_inline_vs_static
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
