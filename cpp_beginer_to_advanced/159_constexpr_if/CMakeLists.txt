cmake_minimum_required(VERSION 3.5)

project(159_constexpr_if LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(159_constexpr_if main.cpp)

include(GNUInstallDirs)
install(TARGETS 159_constexpr_if
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
