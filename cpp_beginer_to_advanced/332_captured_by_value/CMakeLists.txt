cmake_minimum_required(VERSION 3.5)

project(332_captured_by_value LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(332_captured_by_value main.cpp)


include(GNUInstallDirs)
install(TARGETS 332_captured_by_value
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
