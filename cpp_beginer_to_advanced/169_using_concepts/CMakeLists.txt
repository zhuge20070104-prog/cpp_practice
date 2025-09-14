cmake_minimum_required(VERSION 3.5)

project(169_using_concepts LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(169_using_concepts main.cpp)

include(GNUInstallDirs)
install(TARGETS 169_using_concepts
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
