cmake_minimum_required(VERSION 3.5)

project(299_ellipse_catch_all_block LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(299_ellipse_catch_all_block main.cpp
)


include(GNUInstallDirs)
install(TARGETS 299_ellipse_catch_all_block
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
