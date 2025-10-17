cmake_minimum_required(VERSION 3.5)

project(331_passing_by_rvalue_references LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(331_passing_by_rvalue_references main.cpp)


include(GNUInstallDirs)
install(TARGETS 331_passing_by_rvalue_references
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
