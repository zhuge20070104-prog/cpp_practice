cmake_minimum_required(VERSION 3.5)

project(309_nested_try_blocks LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(309_nested_try_blocks main.cpp
)


include(GNUInstallDirs)
install(TARGETS 309_nested_try_blocks
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
