cmake_minimum_required(VERSION 3.5)

project(370_copy LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(370_copy main.cpp)


include(GNUInstallDirs)
install(TARGETS 370_copy
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
