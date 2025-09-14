cmake_minimum_required(VERSION 3.5)

project(173_concepts_and_auto LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(173_concepts_and_auto main.cpp)

include(GNUInstallDirs)
install(TARGETS 173_concepts_and_auto
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
