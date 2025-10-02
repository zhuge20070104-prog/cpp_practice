cmake_minimum_required(VERSION 3.5)

project(270_reused_symbols_in_inheritance LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(270_reused_symbols_in_inheritance main.cpp)


include(GNUInstallDirs)
install(TARGETS 270_reused_symbols_in_inheritance
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
