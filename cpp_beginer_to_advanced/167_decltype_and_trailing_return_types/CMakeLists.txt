cmake_minimum_required(VERSION 3.5)

project(167_decltype_and_trailing_return_types LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(167_decltype_and_trailing_return_types main.cpp)

include(GNUInstallDirs)
install(TARGETS 167_decltype_and_trailing_return_types
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
