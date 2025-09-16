cmake_minimum_required(VERSION 3.5)

project(183_order_of_constructor_destructor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(183_order_of_constructor_destructor main.cpp)


include(GNUInstallDirs)
install(TARGETS 183_order_of_constructor_destructor
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
