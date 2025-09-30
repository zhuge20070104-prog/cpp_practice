cmake_minimum_required(VERSION 3.5)

project(262_logical_operators_with_implicit_conversions LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(262_logical_operators_with_implicit_conversions main.cpp
                number.cpp)


include(GNUInstallDirs)
install(TARGETS 262_logical_operators_with_implicit_conversions
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
