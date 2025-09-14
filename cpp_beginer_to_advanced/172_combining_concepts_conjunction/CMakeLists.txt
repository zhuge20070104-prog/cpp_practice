cmake_minimum_required(VERSION 3.5)

project(172_combining_concepts_conjunction LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(172_combining_concepts_conjunction main.cpp)

include(GNUInstallDirs)
install(TARGETS 172_combining_concepts_conjunction
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
