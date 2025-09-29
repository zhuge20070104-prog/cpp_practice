cmake_minimum_required(VERSION 3.5)

project(256_logic_operators_simplified LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(256_logic_operators_simplified main.cpp number.cpp)


include(GNUInstallDirs)
install(TARGETS 256_logic_operators_simplified
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
