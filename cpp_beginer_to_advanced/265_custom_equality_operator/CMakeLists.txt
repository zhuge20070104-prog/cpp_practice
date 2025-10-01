cmake_minimum_required(VERSION 3.5)

project(265_custom_equality_operator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(265_custom_equality_operator main.cpp
    point.cpp)


include(GNUInstallDirs)
install(TARGETS 265_custom_equality_operator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
