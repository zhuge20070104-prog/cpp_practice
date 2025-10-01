cmake_minimum_required(VERSION 3.5)

project(263_threeway_comparison_operator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(263_threeway_comparison_operator main.cpp)


include(GNUInstallDirs)
install(TARGETS 263_threeway_comparison_operator
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
