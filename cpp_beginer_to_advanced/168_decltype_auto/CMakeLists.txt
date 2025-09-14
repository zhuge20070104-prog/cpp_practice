cmake_minimum_required(VERSION 3.5)

project(168_decltype_auto LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(168_decltype_auto main.cpp)

include(GNUInstallDirs)
install(TARGETS 168_decltype_auto
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
